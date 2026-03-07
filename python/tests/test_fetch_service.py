from __future__ import annotations

from pathlib import Path

import pytest

from core.fetch_service import AccountSelection, FetchError, FetchService
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
        )
