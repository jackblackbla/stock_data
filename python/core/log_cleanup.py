from __future__ import annotations

from datetime import datetime, timedelta
from pathlib import Path


def cleanup_old_logs(log_dir: Path, retention_days: int = 30) -> int:
    if retention_days <= 0 or not log_dir.exists():
        return 0

    cutoff = datetime.now() - timedelta(days=retention_days)
    removed = 0

    for path in log_dir.glob("*.log"):
        try:
            modified = datetime.fromtimestamp(path.stat().st_mtime)
            if modified < cutoff:
                path.unlink(missing_ok=True)
                removed += 1
        except OSError:
            continue

    return removed
