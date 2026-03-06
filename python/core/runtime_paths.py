from __future__ import annotations

import os
import sys
from dataclasses import dataclass
from pathlib import Path

APP_STORAGE_DIR_NAME = "NHTradeLogger"


@dataclass(frozen=True)
class AppPaths:
    app_root: Path
    user_root: Path
    data_dir: Path
    json_dir: Path
    output_dir: Path
    logs_dir: Path
    db_path: Path


def get_app_root() -> Path:
    if getattr(sys, "frozen", False):
        return Path(sys.executable).resolve().parent
    return Path(__file__).resolve().parents[2]


def get_user_root(app_root: Path | None = None) -> Path:
    resolved_app_root = app_root or get_app_root()
    if getattr(sys, "frozen", False) and os.name == "nt":
        base = os.environ.get("LOCALAPPDATA") or os.environ.get("APPDATA")
        if base:
            return Path(base) / APP_STORAGE_DIR_NAME
    return resolved_app_root


def get_app_paths() -> AppPaths:
    app_root = get_app_root()
    user_root = get_user_root(app_root)
    data_dir = user_root / "data"
    return AppPaths(
        app_root=app_root,
        user_root=user_root,
        data_dir=data_dir,
        json_dir=data_dir / "json",
        output_dir=data_dir / "output",
        logs_dir=user_root / "logs",
        db_path=data_dir / "reasons.db",
    )


def ensure_runtime_dirs(paths: AppPaths) -> None:
    paths.user_root.mkdir(parents=True, exist_ok=True)
    paths.data_dir.mkdir(parents=True, exist_ok=True)
    paths.json_dir.mkdir(parents=True, exist_ok=True)
    paths.output_dir.mkdir(parents=True, exist_ok=True)
    paths.logs_dir.mkdir(parents=True, exist_ok=True)
