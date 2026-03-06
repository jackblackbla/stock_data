from __future__ import annotations

import argparse
import sys
from datetime import datetime
from pathlib import Path
from zoneinfo import ZoneInfo

from PyQt5.QtWidgets import QApplication

from core.data_loader import load_fetch_json, merge_reasons, parse_trade_date, parse_trades
from core.excel_generator import generate_excel
from core.fetch_service import FetchError, FetchService
from core.log_cleanup import cleanup_old_logs
from core.notification import show_notification
from core.reason_store import ReasonStore
from core.startup_checks import collect_startup_warnings
from core.runtime_paths import ensure_runtime_dirs, get_app_paths
from gui.main_window import MainWindow

KST = ZoneInfo("Asia/Seoul")


def normalize_iso_date(value: str | None) -> str:
    if not value:
        return datetime.now(tz=KST).strftime("%Y-%m-%d")

    raw = value.strip()
    if len(raw) == 8 and raw.isdigit():
        return f"{raw[:4]}-{raw[4:6]}-{raw[6:8]}"

    parsed = datetime.strptime(raw, "%Y-%m-%d")
    return parsed.strftime("%Y-%m-%d")


def iso_to_compact(iso_date: str) -> str:
    return iso_date.replace("-", "")


def run_auto(app_root: Path, iso_date: str, json_path_arg: str | None) -> int:
    paths = get_app_paths()
    ensure_runtime_dirs(paths)
    fetch_service = FetchService(app_root, paths)
    reason_store = ReasonStore(paths.db_path)

    try:
        if json_path_arg:
            json_path = Path(json_path_arg)
        else:
            json_path = fetch_service.run(iso_to_compact(iso_date))

        payload = load_fetch_json(json_path)
        payload_date = parse_trade_date(payload)
        if payload_date:
            iso_date = payload_date

        trades = parse_trades(payload)
        reasons = reason_store.get_reasons(iso_date)
        merge_reasons(trades, reasons)

        missing = [trade for trade in trades if not trade.reason.strip()]
        if missing:
            show_notification("NH 매매일지", f"오늘 {len(missing)}건의 매매 근거를 입력해주세요")
            print(f"missing reasons: {len(missing)}")
            return 0

        output = generate_excel(trades, iso_date, paths.output_dir)
        print(f"excel generated: {output}")
        return 0
    except FetchError as exc:
        print(f"auto mode fetch error: {exc}", file=sys.stderr)
        return 1
    except Exception as exc:  # noqa: BLE001
        print(f"auto mode error: {exc}", file=sys.stderr)
        return 1


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="NH trade logger")
    parser.add_argument("--date", help="YYYY-MM-DD or YYYYMMDD")
    parser.add_argument("--json", help="existing fetch json path")
    parser.add_argument("--auto", action="store_true", help="auto mode")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    paths = get_app_paths()
    ensure_runtime_dirs(paths)
    cleanup_old_logs(paths.logs_dir, retention_days=30)
    iso_date = normalize_iso_date(args.date)

    if args.auto:
        return run_auto(paths.app_root, iso_date, args.json)

    app = QApplication(sys.argv)
    initial_json = Path(args.json) if args.json else None
    startup_warnings = collect_startup_warnings(paths)
    window = MainWindow(
        paths=paths,
        initial_date=iso_date,
        initial_json=initial_json,
        startup_warnings=startup_warnings,
    )
    window.show()
    return app.exec_()


if __name__ == "__main__":
    raise SystemExit(main())
