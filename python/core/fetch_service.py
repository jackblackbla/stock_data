from __future__ import annotations

import subprocess
from dataclasses import dataclass
from pathlib import Path


class FetchError(RuntimeError):
    pass


ERROR_MAP = {
    10: "QV API DLL 로드 실패",
    20: "인증서 로그인 실패",
    30: "TR 조회 실패",
    40: "JSON 저장 실패",
}


@dataclass
class FetchService:
    repo_root: Path

    @property
    def fetch_exe(self) -> Path:
        candidates = [
            self.repo_root / "cpp" / "build" / "fetch.exe",
            self.repo_root / "cpp" / "build" / "Release" / "fetch.exe",
            self.repo_root / "cpp" / "build" / "RelWithDebInfo" / "fetch.exe",
        ]
        for path in candidates:
            if path.exists():
                return path
        return candidates[0]

    def default_json_path(self, date_compact: str) -> Path:
        return self.repo_root / "data" / "json" / f"{date_compact}.json"

    def default_log_path(self, date_compact: str) -> Path:
        return self.repo_root / "logs" / f"fetch_{date_compact}.log"

    def run(self, date_compact: str, output_path: Path | None = None) -> Path:
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

        proc = subprocess.run(cmd, cwd=self.repo_root, capture_output=True, text=True)
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
