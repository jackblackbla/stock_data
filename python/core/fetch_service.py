from __future__ import annotations

import json
import logging
import os
import subprocess
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable

from core.runtime_paths import AppPaths

logger = logging.getLogger(__name__)


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
    account_no: str
    account_name: str = ""
    act_pdt_cd: str = ""
    amn_tab_cd: str = ""
    expr_date: str = ""
    granted: str = ""
    is_granted_batch: bool = False
    diagnostic_labels: list[str] = field(default_factory=list)


@dataclass
class AccountSelection:
    account_index: int
    account_no: str
    account_password: str
    account_name: str = ""
    act_pdt_cd: str = ""
    amn_tab_cd: str = ""
    expr_date: str = ""
    granted: str = ""
    is_granted_batch: bool = False
    diagnostic_labels: list[str] = field(default_factory=list)


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
    _session_proc: subprocess.Popen[str] | None = field(default=None, init=False, repr=False)

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

    def default_balance_json_path(self) -> Path:
        return self.paths.json_dir / "balance_latest.json"

    def session_log_path(self) -> Path:
        return self.paths.logs_dir / "fetch_session.log"

    @staticmethod
    def _base_env(
        credentials: LoginCredentials | None = None,
        account_index: int | None = None,
        account_password: str | None = None,
        batch_accounts: Iterable[AccountSelection] | None = None,
        trade_password: str | None = None,
        require_account_password: bool = True,
    ) -> dict[str, str]:
        env = os.environ.copy()
        env.pop("QV_ACCOUNT_INDEX", None)
        env.pop("QV_ACCOUNT_PASSWORD", None)
        env.pop("QV_BATCH_ACCOUNTS", None)
        env.pop("QV_TRADE_PASSWORD", None)
        env.pop("QV_REQUIRE_ACCOUNT_PASSWORD", None)
        if credentials is not None:
            env["QV_ID"] = credentials.user_id
            env["QV_PASSWORD"] = credentials.password
            env["QV_CERT_PASSWORD"] = credentials.cert_password
        if account_index is not None:
            env["QV_ACCOUNT_INDEX"] = str(account_index)
        if account_password is not None:
            env["QV_ACCOUNT_PASSWORD"] = account_password
        if batch_accounts is not None:
            encoded_accounts = []
            for item in batch_accounts:
                encoded_accounts.append(f"{item.account_index}|{item.account_no}|{item.account_password}")
            env["QV_BATCH_ACCOUNTS"] = ";".join(encoded_accounts)
        if trade_password is not None:
            env["QV_TRADE_PASSWORD"] = trade_password
        if not require_account_password:
            env["QV_REQUIRE_ACCOUNT_PASSWORD"] = "0"
        return env

    @staticmethod
    def _creationflags() -> int:
        return getattr(subprocess, "CREATE_NO_WINDOW", 0)

    @staticmethod
    def _validate_selection(item: AccountSelection) -> None:
        password = item.account_password.strip()
        if len(password) != 4 or not password.isdigit():
            raise FetchError(f"{item.account_no}: 계좌 비밀번호는 4자리 숫자여야 합니다.")
        if any(ch in item.account_no for ch in ("\t", "\r", "\n")):
            raise FetchError(f"{item.account_no}: 계좌번호 형식이 올바르지 않습니다.")
        if any(ch in password for ch in ("\t", "\r", "\n")):
            raise FetchError(f"{item.account_no}: 계좌 비밀번호 형식이 올바르지 않습니다.")

    @staticmethod
    def _validate_trade_password(trade_password: str) -> None:
        if any(ch in trade_password for ch in ("\t", "\r", "\n")):
            raise FetchError("거래 비밀번호 형식이 올바르지 않습니다.")

    @staticmethod
    def _parse_accounts_payload(payload: dict) -> list[AccountInfo]:
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
            account_no = str(item.get("account_no") or "").strip()
            if not account_no:
                continue
            raw_labels = item.get("diagnostic_labels")
            diagnostic_labels = []
            if isinstance(raw_labels, list):
                diagnostic_labels = [str(label).strip() for label in raw_labels if str(label).strip()]
            parsed.append(
                AccountInfo(
                    account_index=account_index,
                    account_no=account_no,
                    account_name=str(item.get("account_name") or "").strip(),
                    act_pdt_cd=str(item.get("act_pdt_cd") or "").strip(),
                    amn_tab_cd=str(item.get("amn_tab_cd") or "").strip(),
                    expr_date=str(item.get("expr_date") or "").strip(),
                    granted=str(item.get("granted") or "").strip(),
                    is_granted_batch=bool(item.get("is_granted_batch")),
                    diagnostic_labels=diagnostic_labels,
                )
            )
        if not parsed:
            raise FetchError("로그인 계좌 목록이 비어 있습니다.")
        return parsed

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
            encoding="utf-8",
            errors="replace",
            creationflags=self._creationflags(),
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
        return self._parse_accounts_payload(payload)

    def run(
        self,
        date_compact: str,
        output_path: Path | None = None,
        credentials: LoginCredentials | None = None,
        account_index: int | None = None,
        account_password: str | None = None,
        trade_password: str | None = None,
    ) -> Path:
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

        if credentials is not None or account_index is not None or account_password is not None or trade_password is not None:
            proc = subprocess.run(
                cmd,
                cwd=self.app_root,
                capture_output=True,
                text=True,
                encoding="utf-8",
                errors="replace",
                creationflags=self._creationflags(),
                env=self._base_env(credentials, account_index, account_password, trade_password=trade_password),
            )
        else:
            proc = subprocess.run(
                cmd,
                cwd=self.app_root,
                capture_output=True,
                text=True,
                encoding="utf-8",
                errors="replace",
                creationflags=self._creationflags(),
            )
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
        trade_password: str | None = None,
    ) -> Path:
        selected = list(selections)
        if not selected:
            raise FetchError("조회할 계좌가 선택되지 않았습니다.")
        for item in selected:
            self._validate_selection(item)
        if trade_password is not None:
            self._validate_trade_password(trade_password)

        output_path.parent.mkdir(parents=True, exist_ok=True)
        log_path = self.default_log_path(date_compact)
        log_path.parent.mkdir(parents=True, exist_ok=True)

        if not self.fetch_exe.exists():
            raise FetchError(f"fetch.exe not found: {self.fetch_exe}")

        cmd = [
            str(self.fetch_exe),
            "--date",
            date_compact,
            "--output",
            str(output_path),
            "--log",
            str(log_path),
        ]
        proc = subprocess.run(
            cmd,
            cwd=self.app_root,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            creationflags=self._creationflags(),
            env=self._base_env(
                credentials=credentials,
                batch_accounts=selected,
                trade_password=trade_password,
                require_account_password=False,
            ),
        )
        if proc.returncode != 0:
            reason = ERROR_MAP.get(proc.returncode, f"알 수 없는 오류({proc.returncode})")
            detail = (proc.stderr or proc.stdout).strip()
            message = f"fetch 실패: {reason}"
            if detail:
                message += f"\n{detail}"
            raise FetchError(message)

        if not output_path.exists():
            raise FetchError(f"fetch 성공 코드이지만 JSON 파일이 없습니다: {output_path}")
        return output_path

    def open_session(self, credentials: LoginCredentials) -> list[AccountInfo]:
        self.close_session()
        self.paths.logs_dir.mkdir(parents=True, exist_ok=True)

        if not self.fetch_exe.exists():
            raise FetchError(f"fetch.exe not found: {self.fetch_exe}")

        cmd = [
            str(self.fetch_exe),
            "--session",
            "--log",
            str(self.session_log_path()),
        ]
        self._session_proc = subprocess.Popen(
            cmd,
            cwd=self.app_root,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8",
            errors="replace",
            bufsize=1,
            creationflags=self._creationflags(),
        )

        try:
            payload = self._send_session_lines([
                "LOGIN",
                credentials.user_id,
                credentials.password,
                credentials.cert_password,
            ])
        except Exception:
            self.close_session(force=True)
            raise
        return self._parse_accounts_payload(payload)

    def run_multi_session(
        self,
        date_compact: str,
        output_path: Path,
        selections: Iterable[AccountSelection],
        trade_password: str,
    ) -> Path:
        selected = list(selections)
        if not selected:
            raise FetchError("조회할 계좌가 선택되지 않았습니다.")
        if self._session_proc is None:
            raise FetchError("로그인 세션이 없습니다. 다시 로그인하세요.")
        self._validate_trade_password(trade_password)
        for item in selected:
            self._validate_selection(item)
            logger.info(
                "Session QUERY send account_index=%s account_no=%s password_length=%s is_digit_4=%s",
                item.account_index,
                item.account_no,
                len(item.account_password.strip()),
                "Y" if item.account_password.strip().isdigit() and len(item.account_password.strip()) == 4 else "N",
            )

        output_path.parent.mkdir(parents=True, exist_ok=True)
        lines = [
            "QUERY",
            date_compact,
            str(output_path),
            trade_password,
            str(len(selected)),
        ]
        for item in selected:
            lines.append(f"{item.account_index}\t{item.account_no}\t{item.account_password}")

        payload = self._send_session_lines(lines)
        response_output = Path(str(payload.get("output") or output_path))
        if not response_output.exists():
            raise FetchError(f"fetch 성공 응답이지만 JSON 파일이 없습니다: {response_output}")
        return response_output

    def run_balance_session(
        self,
        output_path: Path | None,
        selections: Iterable[AccountSelection],
    ) -> Path:
        selected = list(selections)
        if not selected:
            raise FetchError("잔고조회할 계좌가 선택되지 않았습니다.")
        if self._session_proc is None:
            raise FetchError("로그인 세션이 없습니다. 다시 로그인하세요.")
        for item in selected:
            self._validate_selection(item)
            logger.info(
                "Session BALANCE send account_index=%s account_no=%s password_length=%s is_digit_4=%s",
                item.account_index,
                item.account_no,
                len(item.account_password.strip()),
                "Y" if item.account_password.strip().isdigit() and len(item.account_password.strip()) == 4 else "N",
            )

        resolved_output = output_path or self.default_balance_json_path()
        resolved_output.parent.mkdir(parents=True, exist_ok=True)
        lines = [
            "BALANCE",
            str(resolved_output),
            str(len(selected)),
        ]
        for item in selected:
            lines.append(f"{item.account_index}\t{item.account_no}\t{item.account_password}")

        payload = self._send_session_lines(lines)
        response_output = Path(str(payload.get("output") or resolved_output))
        if not response_output.exists():
            raise FetchError(f"잔고조회 성공 응답이지만 JSON 파일이 없습니다: {response_output}")
        return response_output

    def close_session(self, force: bool = False) -> None:
        proc = self._session_proc
        self._session_proc = None
        if proc is None:
            return

        try:
            if not force and proc.poll() is None and proc.stdin is not None and proc.stdout is not None:
                proc.stdin.write("SHUTDOWN\n")
                proc.stdin.flush()
                proc.stdout.readline()
        except Exception:
            pass

        if proc.poll() is None:
            try:
                proc.terminate()
                proc.wait(timeout=2)
            except Exception:
                try:
                    proc.kill()
                except Exception:
                    pass
                try:
                    proc.wait(timeout=1)
                except Exception:
                    pass

    def _send_session_lines(self, lines: list[str]) -> dict:
        proc = self._session_proc
        if proc is None or proc.stdin is None or proc.stdout is None:
            raise FetchError("세션 프로세스가 준비되지 않았습니다.")

        if proc.poll() is not None:
            detail = ""
            if proc.stderr is not None:
                detail = proc.stderr.read().strip()
            raise FetchError(
                f"세션 프로세스가 종료되었습니다({proc.returncode})." + (f"\n{detail}" if detail else "")
            )

        for line in lines:
            proc.stdin.write(line.replace("\r", " ").replace("\n", " ") + "\n")
        proc.stdin.flush()

        response_line = proc.stdout.readline()
        if not response_line:
            detail = ""
            if proc.stderr is not None:
                detail = proc.stderr.read().strip()
            raise FetchError("세션 프로세스 응답이 없습니다." + (f"\n{detail}" if detail else ""))

        try:
            payload = json.loads(response_line)
        except json.JSONDecodeError as exc:
            raise FetchError(f"세션 응답 파싱 실패: {exc}\nraw={response_line!r}") from exc

        if not isinstance(payload, dict):
            raise FetchError("세션 응답 형식이 올바르지 않습니다.")
        if not payload.get("ok"):
            message = str(payload.get("error") or "알 수 없는 세션 오류")
            raise FetchError(message)
        return payload
