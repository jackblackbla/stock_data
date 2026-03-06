from __future__ import annotations

import os
import sys
from pathlib import Path

from core.runtime_paths import AppPaths


def _path_has_wmca() -> bool:
    for raw_dir in os.environ.get("PATH", "").split(os.pathsep):
        if not raw_dir:
            continue
        if (Path(raw_dir) / "wmca.dll").exists():
            return True
    return False


def _candidate_wmca_paths(paths: AppPaths) -> list[Path]:
    candidates = [
        paths.app_root / "wmca.dll",
        paths.app_root / "cpp" / "lib" / "wmca.dll",
        paths.app_root.parent / "lib" / "wmca.dll",
    ]
    env_path = os.environ.get("QV_DLL_PATH", "").strip()
    if env_path:
        candidates.insert(0, Path(env_path))
    return candidates


def collect_startup_warnings(paths: AppPaths) -> list[str]:
    warnings: list[str] = []
    if not getattr(sys, "frozen", False):
        return warnings

    if not (paths.app_root / "fetch.exe").exists():
        warnings.append(
            "fetch.exe가 없습니다. 설치가 불완전합니다.\n"
            "설치 프로그램으로 다시 설치하거나 dist 폴더 전체를 다시 복사하세요."
        )

    if os.name == "nt":
        has_wmca = any(candidate.exists() for candidate in _candidate_wmca_paths(paths)) or _path_has_wmca()
        if not has_wmca:
            warnings.append(
                "wmca.dll을 찾지 못했습니다.\n"
                "NH QV Open API를 먼저 설치한 뒤 다시 실행하세요."
            )

    return warnings
