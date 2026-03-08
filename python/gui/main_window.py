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

from core.balance_loader import load_balance_json, parse_balance_accounts
from core.data_loader import load_fetch_json, merge_reasons, parse_trade_date, parse_trades
from core.excel_generator import generate_excel
from core.fetch_service import FetchError, FetchService, LoginCredentials
from core.models import TradeRecord
from core.reason_store import ReasonStore
from core.runtime_paths import AppPaths
from gui.account_selection_dialog import AccountSelectionDialog
from gui.balance_dialog import BalanceDialog
from gui.login_dialog import LoginCredentialsDialog
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
        self.session_credentials: LoginCredentials | None = None
        self.session_account_passwords: dict[str, str] = {}
        self.session_trade_password = ""
        self.remember_login_session = True
        self.remember_account_session = True
        self.active_credentials: LoginCredentials | None = None
        self.active_selections = []
        self.active_trade_password = ""
        self._initial_json_supplied = initial_json is not None

        self.setWindowTitle("NH 매매일지 자동화")
        self.resize(1100, 720)

        self.model = TradeTreeModel(self._save_reason)
        self.tree = QTreeView()
        self.tree.setModel(self.model)
        self.tree.setItemDelegateForColumn(5, ReasonDelegate(self.tree))
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

        self.btn_login = QPushButton("로그인 변경")
        self.btn_fetch = QPushButton("조회")
        self.btn_balance = QPushButton("잔고조회")
        self.btn_excel = QPushButton("엑셀 생성")
        self.btn_open = QPushButton("열기")

        top = QHBoxLayout()
        top.addWidget(QLabel("날짜:"))
        top.addWidget(self.date_edit)
        top.addWidget(self.btn_login)
        top.addWidget(self.btn_fetch)
        top.addWidget(self.btn_balance)
        top.addWidget(self.btn_excel)
        top.addWidget(self.btn_open)
        top.addStretch(1)

        root = QVBoxLayout()
        root.addLayout(top)
        root.addWidget(self.tree)

        container = QWidget()
        container.setLayout(root)
        self.setCentralWidget(container)

        self.btn_login.clicked.connect(self.on_login_clicked)
        self.btn_fetch.clicked.connect(self.on_fetch_clicked)
        self.btn_balance.clicked.connect(self.on_balance_clicked)
        self.btn_excel.clicked.connect(self.on_excel_clicked)
        self.btn_open.clicked.connect(self.on_open_clicked)

        self.statusBar().showMessage("로그인 필요")

        if initial_json:
            self.load_from_json(initial_json)
        QTimer.singleShot(0, self._startup_sequence)

    def current_trade_date(self) -> str:
        return self.date_edit.date().toString("yyyy-MM-dd")

    def current_trade_date_compact(self) -> str:
        return self.current_trade_date().replace("-", "")

    def current_json_path(self) -> Path:
        return self.paths.json_dir / f"{self.current_trade_date_compact()}.json"

    def current_balance_json_path(self) -> Path:
        return self.fetch_service.default_balance_json_path()

    def on_fetch_clicked(self) -> None:
        try:
            if not self._ensure_session():
                return
            if not self.active_trade_password:
                QMessageBox.warning(self, "거래 비밀번호", "조회 실행 전 거래 비밀번호를 입력하세요.")
                return

            json_path = self.fetch_service.run_multi_session(
                self.current_trade_date_compact(),
                self.current_json_path(),
                self.active_selections,
                self.active_trade_password,
            )
            self.load_from_json(json_path)
        except FetchError as exc:
            QMessageBox.critical(self, "조회 실패", str(exc))

    def on_balance_clicked(self) -> None:
        try:
            if not self._ensure_session():
                return

            json_path = self.fetch_service.run_balance_session(
                self.current_balance_json_path(),
                self.active_selections,
            )
            payload = load_balance_json(json_path)
            results = parse_balance_accounts(payload)
            errors = [str(item).strip() for item in payload.get("errors", []) if str(item).strip()]
            if errors:
                QMessageBox.warning(self, "잔고조회 경고", "\n".join(errors))
            if not results:
                QMessageBox.information(self, "잔고조회", "잔고조회 결과가 없습니다.")
                return
            dialog = BalanceDialog(results, self)
            dialog.exec_()
        except FetchError as exc:
            QMessageBox.critical(self, "잔고조회 실패", str(exc))
        except Exception as exc:  # noqa: BLE001
            QMessageBox.critical(self, "잔고조회 실패", f"잔고조회 결과 처리 중 오류가 발생했습니다.\n{exc}")

    def on_login_clicked(self) -> None:
        if self._ensure_session(force=True):
            if self.model.trades():
                self.model.set_trades([])
            self.update_status()

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

            errors = payload.get("errors", [])
            if isinstance(errors, list):
                messages = [str(item).strip() for item in errors if str(item).strip()]
                if messages:
                    QMessageBox.warning(self, "부분 조회 실패", "\n".join(messages))

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
                account_no=trade.account_no,
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
        if not trades:
            if self.active_selections:
                self.statusBar().showMessage(f"로그인됨 / 선택 계좌 {len(self.active_selections)}개 / 조회 대기")
            else:
                self.statusBar().showMessage("로그인 필요")
            return
        buy_count = sum(1 for trade in trades if trade.side == "buy")
        sell_count = sum(1 for trade in trades if trade.side == "sell")
        total_amount = sum(trade.total_amount for trade in trades)
        missing = sum(1 for trade in trades if not trade.reason.strip())
        account_count = len({trade.account_no for trade in trades if trade.account_no})
        self.statusBar().showMessage(
            f"계좌 {account_count}개 / 매수 {buy_count}건 / 매도 {sell_count}건 / 총 체결금액: ₩{total_amount:,} / 근거 미입력 {missing}건"
        )

    def show_startup_warnings(self) -> None:
        message = "\n\n".join(self.startup_warnings)
        QMessageBox.warning(self, "실행 전 확인", message)

    def _startup_sequence(self) -> None:
        if self.startup_warnings:
            self.show_startup_warnings()
        if self._initial_json_supplied:
            return
        if not self._ensure_session():
            self.close()
            return
        self.update_status()

    def _prompt_login_credentials(self) -> LoginCredentials | None:
        dialog = LoginCredentialsDialog(
            self,
            initial=self.session_credentials or self.active_credentials,
            remember_checked=self.remember_login_session,
        )
        if dialog.exec_() != dialog.Accepted:
            return None
        credentials = dialog.credentials()
        if not credentials.user_id or not credentials.password or not credentials.cert_password:
            QMessageBox.warning(self, "로그인 정보", "QV ID, 로그인 비밀번호, 인증서 비밀번호를 모두 입력하세요.")
            return None
        self.remember_login_session = dialog.remember_session()
        if self.remember_login_session:
            self.session_credentials = credentials
        else:
            self.session_credentials = None
        return credentials

    def _ensure_session(self, force: bool = False) -> bool:
        if not force and self.active_credentials is not None and self.active_selections:
            return True

        if force:
            self.fetch_service.close_session()
            self.active_credentials = None
            self.active_selections = []
            self.active_trade_password = ""

        credentials = self._prompt_login_credentials()
        if credentials is None:
            return False

        try:
            accounts = self.fetch_service.open_session(credentials)
        except FetchError as exc:
            QMessageBox.critical(self, "로그인 실패", str(exc))
            return False
        except Exception as exc:  # noqa: BLE001
            self.fetch_service.close_session(force=True)
            QMessageBox.critical(self, "로그인 실패", f"세션 응답 처리 중 오류가 발생했습니다.\n{exc}")
            return False

        selection_dialog = AccountSelectionDialog(
            accounts=accounts,
            remembered_passwords=self.session_account_passwords,
            remembered_trade_password=self.session_trade_password,
            remember_checked=self.remember_account_session,
            parent=self,
        )
        if selection_dialog.exec_() != selection_dialog.Accepted:
            self.fetch_service.close_session()
            self.active_trade_password = ""
            return False

        selections = selection_dialog.selected_accounts()
        trade_password = selection_dialog.trade_password()
        self.active_credentials = credentials
        self.active_selections = selections
        self.active_trade_password = trade_password
        self.remember_account_session = selection_dialog.remember_session()
        if self.remember_account_session:
            self.session_account_passwords = {
                item.account_no: item.account_password for item in selections if item.account_password
            }
            self.session_trade_password = trade_password
        else:
            self.session_account_passwords = {}
            self.session_trade_password = ""
        return True

    def closeEvent(self, event) -> None:  # type: ignore[override]
        self.fetch_service.close_session()
        self.active_credentials = None
        self.active_selections = []
        self.active_trade_password = ""
        self.session_credentials = None
        self.session_account_passwords = {}
        self.session_trade_password = ""
        super().closeEvent(event)

    @staticmethod
    def _open_file(path: Path) -> None:
        if os.name == "nt":
            os.startfile(str(path))  # type: ignore[attr-defined]
            return

        opener = "open" if platform.system() == "Darwin" else "xdg-open"
        subprocess.run([opener, str(path)], check=False)
