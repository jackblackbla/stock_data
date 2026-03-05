from __future__ import annotations

from datetime import datetime, timedelta
from pathlib import Path

from core.log_cleanup import cleanup_old_logs


def test_cleanup_old_logs(tmp_path: Path) -> None:
    old = tmp_path / "old.log"
    new = tmp_path / "new.log"
    old.write_text("old", encoding="utf-8")
    new.write_text("new", encoding="utf-8")

    old_time = datetime.now() - timedelta(days=40)
    new_time = datetime.now() - timedelta(days=1)
    old_ts = old_time.timestamp()
    new_ts = new_time.timestamp()

    old.touch()
    new.touch()

    import os

    os.utime(old, (old_ts, old_ts))
    os.utime(new, (new_ts, new_ts))

    removed = cleanup_old_logs(tmp_path, retention_days=30)
    assert removed == 1
    assert not old.exists()
    assert new.exists()
