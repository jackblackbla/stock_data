from __future__ import annotations

import os
import platform
import subprocess
from pathlib import Path

from PyQt5.QtCore import QDate, QTimer
from PyQt5.QtWidgets import (
    QAbstractItemView,
    QDateEdit,
    QHBoxLayout,
    QLabel,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QTreeView,
    QVBoxLayout,
    QWidget,
)

from core.data_loader import load_fetch_json, merge_reasons, parse_trade_date, parse_trades
from core.excel_generator import generate_excel
from core.fetch_service import FetchError, FetchService
from core.models import TradeRecord
from core.reason_store import ReasonStore
from core.runtime_paths import AppPaths
from gui.reason_delegate import ReasonDelegate
from gui.trade_tree_model import TradeTreeModel


class MainWindow(QMainWindow):
    def __init__(
        self,
        paths: AppPaths,
        initial_date: str | None = None,
        initial_json: Path | None = None,
        startup_warnings: list[str] | None = None,
    ) -> None:
        super().__init__()
        self.paths = paths
        self.fetch_service = FetchService(paths.app_root, paths)
        self.reason_store = ReasonStore(paths.db_path)
        self.last_excel_path: Path | None = None
        self.startup_warnings = startup_warnings or []

        self.setWindowTitle("NH 매매일지 자동화")
        self.resize(1100, 720)

        self.model = TradeTreeModel(self._save_reason)
        self.tree = QTreeView()
        self.tree.setModel(self.model)
        self.tree.setItemDelegateForColumn(4, ReasonDelegate(self.tree))
        self.tree.setRootIsDecorated(True)
        self.tree.setAlternatingRowColors(True)
        self.tree.setEditTriggers(
            QAbstractItemView.DoubleClicked
            | QAbstractItemView.EditKeyPressed
            | QAbstractItemView.SelectedClicked
        )

        self.date_edit = QDateEdit(calendarPopup=True)
        self.date_edit.setDisplayFormat("yyyy-MM-dd")
        default_date = QDate.currentDate()
        if initial_date:
            parsed = QDate.fromString(initial_date, "yyyy-MM-dd")
            if parsed.isValid():
                default_date = parsed
        self.date_edit.setDate(default_date)

        self.btn_fetch = QPushButton("조회")
        self.btn_excel = QPushButton("엑셀 생성")
        self.btn_open = QPushButton("열기")

        top = QHBoxLayout()
        top.addWidget(QLabel("날짜:"))
        top.addWidget(self.date_edit)
        top.addWidget(self.btn_fetch)
        top.addWidget(self.btn_excel)
        top.addWidget(self.btn_open)
        top.addStretch(1)

        root = QVBoxLayout()
        root.addLayout(top)
        root.addWidget(self.tree)

        container = QWidget()
        container.setLayout(root)
        self.setCentralWidget(container)

        self.btn_fetch.clicked.connect(self.on_fetch_clicked)
        self.btn_excel.clicked.connect(self.on_excel_clicked)
        self.btn_open.clicked.connect(self.on_open_clicked)

        self.statusBar().showMessage("준비")

        if initial_json:
            self.load_from_json(initial_json)
        if self.startup_warnings:
            QTimer.singleShot(0, self.show_startup_warnings)

    def current_trade_date(self) -> str:
        return self.date_edit.date().toString("yyyy-MM-dd")

    def current_trade_date_compact(self) -> str:
        return self.current_trade_date().replace("-", "")

    def current_json_path(self) -> Path:
        return self.paths.json_dir / f"{self.current_trade_date_compact()}.json"

    def on_fetch_clicked(self) -> None:
        try:
            json_path = self.fetch_service.run(self.current_trade_date_compact(), self.current_json_path())
            self.load_from_json(json_path)
        except FetchError as exc:
            QMessageBox.critical(self, "조회 실패", str(exc))

    def load_from_json(self, json_path: Path) -> None:
        try:
            payload = load_fetch_json(json_path)
            trades = parse_trades(payload)
            payload_date = parse_trade_date(payload)
            if payload_date:
                parsed = QDate.fromString(payload_date, "yyyy-MM-dd")
                if parsed.isValid():
                    self.date_edit.setDate(parsed)

            reasons = self.reason_store.get_reasons(self.current_trade_date())
            merge_reasons(trades, reasons)
            self.model.set_trades(trades)
            self.tree.expandAll()
            self.update_status()

            if not trades:
                QMessageBox.information(self, "조회 결과", "오늘 체결 내역이 없습니다.")
        except Exception as exc:  # noqa: BLE001
            QMessageBox.critical(self, "JSON 오류", f"파싱 실패: {exc}")

    def on_excel_clicked(self) -> None:
        trades = self.model.trades()
        if not trades:
            QMessageBox.information(self, "안내", "내보낼 데이터가 없습니다.")
            return

        output = generate_excel(trades, self.current_trade_date(), self.paths.output_dir)
        self.last_excel_path = output
        QMessageBox.information(self, "완료", f"엑셀 생성 완료\n{output}")

    def on_open_clicked(self) -> None:
        target = self.last_excel_path
        if target is None:
            candidate = self.paths.output_dir / f"매매일지_{self.current_trade_date()}.xlsx"
            target = candidate if candidate.exists() else None

        if target is None or not target.exists():
            QMessageBox.information(self, "안내", "열 수 있는 엑셀 파일이 없습니다.")
            return

        self._open_file(target)

    def _save_reason(self, trade: TradeRecord) -> None:
        try:
            self.reason_store.save_reason(
                trade_date=self.current_trade_date(),
                order_no=trade.order_no,
                stock_code=trade.stock_code,
                stock_name=trade.stock_name,
                side=trade.side,
                reason=trade.reason,
            )
            self.update_status()
        except Exception as exc:  # noqa: BLE001
            QMessageBox.critical(self, "저장 실패", f"근거 저장 중 오류가 발생했습니다.\n{exc}")

    def update_status(self) -> None:
        trades = self.model.trades()
        buy_count = sum(1 for trade in trades if trade.side == "buy")
        sell_count = sum(1 for trade in trades if trade.side == "sell")
        total_amount = sum(trade.total_amount for trade in trades)
        missing = sum(1 for trade in trades if not trade.reason.strip())
        self.statusBar().showMessage(
            f"매수 {buy_count}건 / 매도 {sell_count}건 / 총 체결금액: ₩{total_amount:,} / 근거 미입력 {missing}건"
        )

    def show_startup_warnings(self) -> None:
        message = "\n\n".join(self.startup_warnings)
        QMessageBox.warning(self, "실행 전 확인", message)

    @staticmethod
    def _open_file(path: Path) -> None:
        if os.name == "nt":
            os.startfile(str(path))  # type: ignore[attr-defined]
            return

        opener = "open" if platform.system() == "Darwin" else "xdg-open"
        subprocess.run([opener, str(path)], check=False)
