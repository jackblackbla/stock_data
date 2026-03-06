from __future__ import annotations

from pathlib import Path

import core.runtime_paths as runtime_paths


def test_get_app_paths_dev_mode_uses_repo_root(monkeypatch, tmp_path: Path) -> None:
    monkeypatch.setattr(runtime_paths.sys, "frozen", False, raising=False)
    monkeypatch.setattr(runtime_paths, "get_app_root", lambda: tmp_path)

    paths = runtime_paths.get_app_paths()
    assert paths.app_root == tmp_path
    assert paths.user_root == tmp_path
    assert paths.db_path == tmp_path / "data" / "reasons.db"


def test_get_app_paths_frozen_windows_uses_localappdata(monkeypatch, tmp_path: Path) -> None:
    app_root = tmp_path / "bundle"
    app_root.mkdir()
    local_root = tmp_path / "localapp"

    monkeypatch.setattr(runtime_paths.sys, "frozen", True, raising=False)
    monkeypatch.setattr(runtime_paths.os, "name", "nt")
    monkeypatch.setattr(runtime_paths, "get_app_root", lambda: app_root)
    monkeypatch.setenv("LOCALAPPDATA", str(local_root))

    paths = runtime_paths.get_app_paths()
    assert paths.app_root == app_root
    assert paths.user_root == local_root / "NHTradeLogger"
    assert paths.output_dir == local_root / "NHTradeLogger" / "data" / "output"
