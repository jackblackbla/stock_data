from __future__ import annotations

from pathlib import Path

from core.fetch_service import FetchService


def test_fetch_exe_resolution_prefers_existing_release(tmp_path: Path) -> None:
    repo = tmp_path
    (repo / "cpp" / "build" / "Release").mkdir(parents=True)
    release = repo / "cpp" / "build" / "Release" / "fetch.exe"
    release.write_text("dummy", encoding="utf-8")

    service = FetchService(repo)
    assert service.fetch_exe == release
