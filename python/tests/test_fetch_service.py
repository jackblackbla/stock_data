from __future__ import annotations

from pathlib import Path

import pytest

from core.fetch_service import AccountInfo, AccountSelection, FetchError, FetchService
from core.runtime_paths import AppPaths


def make_paths(root: Path) -> AppPaths:
    data_dir = root / "runtime-data"
    return AppPaths(
        app_root=root,
        user_root=root,
        data_dir=data_dir,
        json_dir=data_dir / "json",
        output_dir=data_dir / "output",
        logs_dir=root / "logs",
        db_path=data_dir / "reasons.db",
    )


def test_fetch_exe_resolution_prefers_existing_release(tmp_path: Path) -> None:
    repo = tmp_path
    (repo / "cpp" / "build" / "Release").mkdir(parents=True)
    release = repo / "cpp" / "build" / "Release" / "fetch.exe"
    release.write_text("dummy", encoding="utf-8")

    service = FetchService(repo, make_paths(repo))
    assert service.fetch_exe == release


def test_fetch_exe_resolution_prefers_bundle_root(tmp_path: Path) -> None:
    repo = tmp_path
    bundle_fetch = repo / "fetch.exe"
    bundle_fetch.write_text("dummy", encoding="utf-8")
    (repo / "cpp" / "build" / "Release").mkdir(parents=True)
    (repo / "cpp" / "build" / "Release" / "fetch.exe").write_text("fallback", encoding="utf-8")

    service = FetchService(repo, make_paths(repo))
    assert service.fetch_exe == bundle_fetch


def test_runtime_paths_are_used_for_json_and_logs(tmp_path: Path) -> None:
    repo = tmp_path / "bundle"
    repo.mkdir()
    paths = make_paths(tmp_path / "user-root")

    service = FetchService(repo, paths)
    assert service.default_json_path("20260306") == paths.json_dir / "20260306.json"
    assert service.default_balance_json_path() == paths.json_dir / "balance_latest.json"
    assert service.default_log_path("20260306") == paths.logs_dir / "fetch_20260306.log"


def test_invalid_account_password_is_rejected_before_query(tmp_path: Path) -> None:
    repo = tmp_path / "bundle"
    repo.mkdir()
    paths = make_paths(tmp_path / "user-root")
    service = FetchService(repo, paths)

    with pytest.raises(FetchError):
        service.run_multi_session(
            "20260306",
            paths.json_dir / "20260306.json",
            [AccountSelection(account_index=1, account_no="04501201721", account_password="12a4")],
            "7689",
        )


def test_parse_accounts_payload_supports_extended_metadata() -> None:
    payload = {
        "accounts": [
            {
                "account_index": 3,
                "account_no": "20001505931",
                "account_name": "종합매매",
                "act_pdt_cd": "001",
                "amn_tab_cd": "1001",
                "expr_date": "20271231",
                "granted": "G",
                "is_granted_batch": True,
                "diagnostic_labels": ["unknown_product"],
            }
        ]
    }

    accounts = FetchService._parse_accounts_payload(payload)

    assert accounts == [
        AccountInfo(
            account_index=3,
            account_no="20001505931",
            account_name="종합매매",
            act_pdt_cd="001",
            amn_tab_cd="1001",
            expr_date="20271231",
            granted="G",
            is_granted_batch=True,
            diagnostic_labels=["unknown_product"],
        )
    ]


def test_parse_accounts_payload_is_backward_compatible() -> None:
    payload = {
        "accounts": [
            {
                "account_index": 1,
                "account_no": "04501201721",
            }
        ]
    }

    accounts = FetchService._parse_accounts_payload(payload)

    assert accounts == [AccountInfo(account_index=1, account_no="04501201721")]


def test_run_multi_session_uses_trade_password_payload(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    repo = tmp_path / "bundle"
    repo.mkdir()
    paths = make_paths(tmp_path / "user-root")
    service = FetchService(repo, paths)
    service._session_proc = object()  # type: ignore[assignment]
    captured: list[str] = []

    def fake_send(lines: list[str]) -> dict:
        captured.extend(lines)
        output = Path(lines[2])
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text("{}", encoding="utf-8")
        return {"ok": True, "output": str(output)}

    monkeypatch.setattr(service, "_send_session_lines", fake_send)

    output = service.run_multi_session(
        "20260306",
        paths.json_dir / "20260306.json",
        [AccountSelection(account_index=3, account_no="20001505931", account_password="1234")],
        "7689",
    )

    assert output == paths.json_dir / "20260306.json"
    assert captured == [
        "QUERY",
        "20260306",
        str(paths.json_dir / "20260306.json"),
        "7689",
        "1",
        "3\t20001505931\t1234",
    ]


def test_run_balance_session_uses_balance_payload(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    repo = tmp_path / "bundle"
    repo.mkdir()
    paths = make_paths(tmp_path / "user-root")
    service = FetchService(repo, paths)
    service._session_proc = object()  # type: ignore[assignment]
    captured: list[str] = []

    def fake_send(lines: list[str]) -> dict:
        captured.extend(lines)
        output = Path(lines[1])
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text("{}", encoding="utf-8")
        return {"ok": True, "output": str(output)}

    monkeypatch.setattr(service, "_send_session_lines", fake_send)

    output = service.run_balance_session(
        None,
        [AccountSelection(account_index=1, account_no="04501201721", account_password="1234")],
    )

    assert output == paths.json_dir / "balance_latest.json"
    assert captured == [
        "BALANCE",
        str(paths.json_dir / "balance_latest.json"),
        "1",
        "1\t04501201721\t1234",
    ]
