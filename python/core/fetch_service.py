from __future__ import annotations

import json
import os
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from core.runtime_paths import AppPaths


class FetchError(RuntimeError):
    pass


@dataclass
class LoginCredentials:
    user_id: str
    password: str
    cert_password: str


@dataclass
class AccountInfo:
    account_index: int
    account_masked: str


@dataclass
class AccountSelection:
    account_index: int
    account_masked: str
    account_password: str


ERROR_MAP = {
    10: "QV API DLL 로드 실패",
    20: "인증서 로그인 실패",
    30: "TR 조회 실패",
    40: "JSON 저장 실패",
}


@dataclass
class FetchService:
    app_root: Path
    paths: AppPaths

    @property
    def fetch_exe(self) -> Path:
        candidates = [
            self.app_root / "fetch.exe",
            self.app_root / "bin" / "fetch.exe",
            self.app_root / "cpp" / "build" / "fetch.exe",
            self.app_root / "cpp" / "build" / "Release" / "fetch.exe",
            self.app_root / "cpp" / "build" / "RelWithDebInfo" / "fetch.exe",
        ]
        for path in candidates:
            if path.exists():
                return path
        return candidates[0]

    def default_json_path(self, date_compact: str) -> Path:
        return self.paths.json_dir / f"{date_compact}.json"

    def default_log_path(self, date_compact: str) -> Path:
        return self.paths.logs_dir / f"fetch_{date_compact}.log"

    def default_accounts_path(self) -> Path:
        return self.paths.json_dir / "accounts.json"

    @staticmethod
    def _base_env(
        credentials: LoginCredentials | None = None,
        account_index: int | None = None,
        account_password: str | None = None,
        require_account_password: bool = True,
    ) -> dict[str, str]:
        env = os.environ.copy()
        if credentials is not None:
            env["QV_ID"] = credentials.user_id
            env["QV_PASSWORD"] = credentials.password
            env["QV_CERT_PASSWORD"] = credentials.cert_password
        if account_index is not None:
            env["QV_ACCOUNT_INDEX"] = str(account_index)
        if account_password is not None:
            env["QV_ACCOUNT_PASSWORD"] = account_password
        if not require_account_password:
            env["QV_REQUIRE_ACCOUNT_PASSWORD"] = "0"
        return env

    def list_accounts(self, credentials: LoginCredentials, output_path: Path | None = None) -> list[AccountInfo]:
        output = output_path or self.default_accounts_path()
        log_path = self.paths.logs_dir / "fetch_accounts.log"
        output.parent.mkdir(parents=True, exist_ok=True)
        log_path.parent.mkdir(parents=True, exist_ok=True)

        if not self.fetch_exe.exists():
            raise FetchError(f"fetch.exe not found: {self.fetch_exe}")

        cmd = [
            str(self.fetch_exe),
            "--list-accounts",
            "--output",
            str(output),
            "--log",
            str(log_path),
        ]
        proc = subprocess.run(
            cmd,
            cwd=self.app_root,
            capture_output=True,
            text=True,
            env=self._base_env(credentials, require_account_password=False),
        )
        if proc.returncode != 0:
            reason = ERROR_MAP.get(proc.returncode, f"알 수 없는 오류({proc.returncode})")
            detail = (proc.stderr or proc.stdout).strip()
            message = f"계좌 목록 조회 실패: {reason}"
            if detail:
                message += f"\n{detail}"
            raise FetchError(message)

        payload = json.loads(output.read_text(encoding="utf-8"))
        accounts = payload.get("accounts")
        if not isinstance(accounts, list):
            raise FetchError("계좌 목록 JSON 형식이 올바르지 않습니다.")

        parsed: list[AccountInfo] = []
        for item in accounts:
            if not isinstance(item, dict):
                continue
            try:
                account_index = int(item.get("account_index"))
            except (TypeError, ValueError):
                continue
            account_masked = str(item.get("account_masked") or "").strip()
            if not account_masked:
                continue
            parsed.append(AccountInfo(account_index=account_index, account_masked=account_masked))
        if not parsed:
            raise FetchError("로그인 계좌 목록이 비어 있습니다.")
        return parsed

    def run(self,
            date_compact: str,
            output_path: Path | None = None,
            credentials: LoginCredentials | None = None,
            account_index: int | None = None,
            account_password: str | None = None) -> Path:
        output = output_path or self.default_json_path(date_compact)
        log_path = self.default_log_path(date_compact)
        output.parent.mkdir(parents=True, exist_ok=True)
        log_path.parent.mkdir(parents=True, exist_ok=True)

        if not self.fetch_exe.exists():
            raise FetchError(f"fetch.exe not found: {self.fetch_exe}")

        cmd = [
            str(self.fetch_exe),
            "--date",
            date_compact,
            "--output",
            str(output),
            "--log",
            str(log_path),
        ]

        if credentials is not None or account_index is not None or account_password is not None:
            proc = subprocess.run(
                cmd,
                cwd=self.app_root,
                capture_output=True,
                text=True,
                env=self._base_env(credentials, account_index, account_password),
            )
        else:
            proc = subprocess.run(cmd, cwd=self.app_root, capture_output=True, text=True)
        if proc.returncode != 0:
            reason = ERROR_MAP.get(proc.returncode, f"알 수 없는 오류({proc.returncode})")
            detail = (proc.stderr or proc.stdout).strip()
            message = f"fetch 실패: {reason}"
            if detail:
                message += f"\n{detail}"
            raise FetchError(message)

        if not output.exists():
            raise FetchError(f"fetch 성공 코드이지만 JSON 파일이 없습니다: {output}")

        return output

    def run_multi(
        self,
        date_compact: str,
        output_path: Path,
        credentials: LoginCredentials,
        selections: Iterable[AccountSelection],
    ) -> Path:
        payloads: list[dict] = []
        combined_errors: list[str] = []
        selected = list(selections)
        if not selected:
            raise FetchError("조회할 계좌가 선택되지 않았습니다.")

        for selection in selected:
            per_account_path = self.paths.json_dir / f"{date_compact}_{selection.account_index}.json"
            try:
                path = self.run(
                    date_compact,
                    output_path=per_account_path,
                    credentials=credentials,
                    account_index=selection.account_index,
                    account_password=selection.account_password,
                )
                payload = json.loads(path.read_text(encoding="utf-8"))
                payloads.append(payload)
            except FetchError as exc:
                combined_errors.append(f"{selection.account_masked}: {exc}")

        if not payloads:
            raise FetchError("\n".join(combined_errors) if combined_errors else "조회 결과가 없습니다.")

        merged_executions: list[dict] = []
        merged_accounts: list[dict] = []
        for payload in payloads:
            root_account = str(payload.get("account_masked") or "")
            if root_account:
                merged_accounts.append({"account_masked": root_account})
            executions = payload.get("executions", [])
            if not isinstance(executions, list):
                continue
            for execution in executions:
                if not isinstance(execution, dict):
                    continue
                merged = dict(execution)
                merged.setdefault("account_masked", root_account)
                merged_executions.append(merged)
            errors = payload.get("errors", [])
            if isinstance(errors, list):
                combined_errors.extend(str(item) for item in errors if str(item).strip())

        merged_payload = {
            "schema_version": "1.0",
            "trade_date": date_compact,
            "generated_at": payloads[-1].get("generated_at", ""),
            "account_masked": "MULTI" if len(payloads) > 1 else str(payloads[0].get("account_masked") or ""),
            "status": "partial" if combined_errors else "ok",
            "errors": combined_errors,
            "accounts": merged_accounts,
            "executions": merged_executions,
        }

        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(json.dumps(merged_payload, ensure_ascii=False, indent=2), encoding="utf-8")
        return output_path
