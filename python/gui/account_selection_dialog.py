from __future__ import annotations

from dataclasses import dataclass

from PyQt5.QtCore import QRegularExpression, Qt
from PyQt5.QtGui import QRegularExpressionValidator
from PyQt5.QtWidgets import (
    QCheckBox,
    QDialog,
    QDialogButtonBox,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMessageBox,
    QScrollArea,
    QVBoxLayout,
    QWidget,
)

from core.fetch_service import AccountInfo, AccountSelection


@dataclass
class _AccountRow:
    selected: QCheckBox
    account_label: QLabel
    password: QLineEdit
    account: AccountInfo


class AccountSelectionDialog(QDialog):
    def __init__(
        self,
        accounts: list[AccountInfo],
        remembered_passwords: dict[str, str] | None = None,
        remembered_trade_password: str = "",
        remember_checked: bool = True,
        parent=None,
    ) -> None:
        super().__init__(parent)
        self.setWindowTitle("계좌 선택")
        self.setModal(True)
        self.resize(520, 460)

        remembered_passwords = remembered_passwords or {}
        self.rows: list[_AccountRow] = []

        self.chk_select_all = QCheckBox("전체 선택")
        self.chk_select_all.setChecked(True)
        self.chk_select_all.toggled.connect(self._toggle_all)

        self.trade_password_input = QLineEdit(remembered_trade_password)
        self.trade_password_input.setEchoMode(QLineEdit.Password)
        self.trade_password_input.setPlaceholderText("4~16자리 숫자, 조회 시 필요")
        self.trade_password_input.setMaxLength(16)
        self.trade_password_input.setValidator(
            QRegularExpressionValidator(QRegularExpression(r"\d{0,16}"), self.trade_password_input)
        )

        trade_row = QHBoxLayout()
        trade_row.addWidget(QLabel("거래 비밀번호"))
        trade_row.addWidget(self.trade_password_input, 1)

        grid = QGridLayout()
        grid.addWidget(QLabel("선택"), 0, 0)
        grid.addWidget(QLabel("계좌"), 0, 1)
        grid.addWidget(QLabel("계좌 비밀번호"), 0, 2)

        for row_idx, account in enumerate(accounts, start=1):
            chk = QCheckBox()
            chk.setChecked(True)
            account_label = QLabel(self._format_account_label(account))
            account_label.setWordWrap(True)
            password = QLineEdit(remembered_passwords.get(account.account_no, ""))
            password.setEchoMode(QLineEdit.Password)
            password.setPlaceholderText("4자리")
            password.setMaxLength(4)
            password.setValidator(QRegularExpressionValidator(QRegularExpression(r"\d{0,4}"), password))
            grid.addWidget(chk, row_idx, 0, alignment=Qt.AlignCenter)
            grid.addWidget(account_label, row_idx, 1)
            grid.addWidget(password, row_idx, 2)
            self.rows.append(_AccountRow(chk, account_label, password, account))

        inner = QWidget()
        inner.setLayout(grid)

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(inner)

        self.chk_remember = QCheckBox("이번 실행 동안 비밀번호 기억")
        self.chk_remember.setChecked(remember_checked)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self._on_accept)
        buttons.rejected.connect(self.reject)

        root = QVBoxLayout()
        root.addWidget(self.chk_select_all)
        root.addLayout(trade_row)
        root.addWidget(scroll)
        root.addWidget(self.chk_remember)
        root.addWidget(buttons)
        self.setLayout(root)

    def _toggle_all(self, checked: bool) -> None:
        for row in self.rows:
            row.selected.setChecked(checked)

    def remember_session(self) -> bool:
        return self.chk_remember.isChecked()

    def trade_password(self) -> str:
        return self.trade_password_input.text().strip()

    def selected_accounts(self) -> list[AccountSelection]:
        selected: list[AccountSelection] = []
        for row in self.rows:
            if not row.selected.isChecked():
                continue
            selected.append(
                AccountSelection(
                    account_index=row.account.account_index,
                    account_no=row.account.account_no,
                    account_password=row.password.text().strip(),
                    account_name=row.account.account_name,
                    act_pdt_cd=row.account.act_pdt_cd,
                    amn_tab_cd=row.account.amn_tab_cd,
                    expr_date=row.account.expr_date,
                    granted=row.account.granted,
                    is_granted_batch=row.account.is_granted_batch,
                    diagnostic_labels=list(row.account.diagnostic_labels),
                )
            )
        return selected

    @staticmethod
    def _format_account_label(account: AccountInfo) -> str:
        parts = [account.account_no]
        if account.account_name:
            parts.append(account.account_name)
        if account.act_pdt_cd:
            parts.append(f"[{account.act_pdt_cd}]")
        if account.granted:
            parts.append(f"batch={account.granted}")
        return " ".join(parts)

    def _on_accept(self) -> None:
        selected = self.selected_accounts()
        if not selected:
            QMessageBox.warning(self, "계좌 선택", "최소 1개 계좌를 선택하세요.")
            return
        trade_password = self.trade_password()
        if trade_password and not trade_password.isdigit():
            QMessageBox.warning(self, "거래 비밀번호", "거래 비밀번호는 숫자만 입력하세요.")
            return
        missing = [item.account_no for item in selected if not item.account_password]
        if missing:
            QMessageBox.warning(
                self,
                "계좌 비밀번호",
                "선택한 계좌의 비밀번호를 모두 입력하세요.\n" + "\n".join(missing),
            )
            return
        invalid = [item.account_no for item in selected if not (len(item.account_password) == 4 and item.account_password.isdigit())]
        if invalid:
            QMessageBox.warning(
                self,
                "계좌 비밀번호",
                "계좌 비밀번호는 4자리 숫자여야 합니다.\n" + "\n".join(invalid),
            )
            return
        self.accept()
