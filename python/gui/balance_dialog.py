from __future__ import annotations

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
    QComboBox,
    QDialog,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
)

from core.models import BalanceAccountResult


def _format_int(value: int) -> str:
    return f"{value:,}"


def _format_float(value: float) -> str:
    return f"{value:.2f}"


class BalanceDialog(QDialog):
    def __init__(self, results: list[BalanceAccountResult], parent=None) -> None:
        super().__init__(parent)
        self.setWindowTitle("잔고조회")
        self.resize(1080, 720)
        self.results = results

        self.account_combo = QComboBox()
        for result in self.results:
            label = result.selected_account.account_no
            if result.selected_account.account_name:
                label += f" {result.selected_account.account_name}"
            if result.selected_account.act_pdt_cd:
                label += f" [{result.selected_account.act_pdt_cd}]"
            self.account_combo.addItem(label)
        self.account_combo.currentIndexChanged.connect(self._render_current_account)

        combo_row = QHBoxLayout()
        combo_row.addWidget(QLabel("계좌"))
        combo_row.addWidget(self.account_combo, 1)

        self.warning_label = QLabel("")
        self.warning_label.setWordWrap(True)
        self.warning_label.setStyleSheet("color: #8a5a00;")

        self.summary_grid = QGridLayout()
        self.summary_values: dict[str, QLabel] = {}
        summary_fields = [
            ("deposit_amount", "예수금"),
            ("withdrawable_amount", "출금가능"),
            ("orderable_amount", "주문가능"),
            ("d1_deposit", "D+1 예수금"),
            ("d2_deposit", "D+2 예수금"),
            ("purchase_amount_total", "매입원가"),
            ("valuation_amount_total", "평가금액"),
            ("total_profit_loss", "평가손익"),
            ("profit_rate", "수익률"),
            ("net_total_asset_amount", "순총자산"),
        ]
        for idx, (key, title) in enumerate(summary_fields):
            row = idx // 2
            col = (idx % 2) * 2
            title_label = QLabel(title)
            value_label = QLabel("-")
            value_label.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
            self.summary_grid.addWidget(title_label, row, col)
            self.summary_grid.addWidget(value_label, row, col + 1)
            self.summary_values[key] = value_label

        self.positions_table = QTableWidget(0, 11)
        self.positions_table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.positions_table.setSelectionBehavior(QTableWidget.SelectRows)
        self.positions_table.setSelectionMode(QTableWidget.SingleSelection)
        self.positions_table.setAlternatingRowColors(True)
        self.positions_table.setHorizontalHeaderLabels(
            [
                "종목코드",
                "종목명",
                "잔고수량",
                "미결제",
                "평균매입가",
                "현재가",
                "손익",
                "수익률",
                "평가금액",
                "신용유형",
                "만기일",
            ]
        )
        self.positions_table.horizontalHeader().setStretchLastSection(True)

        root = QVBoxLayout()
        root.addLayout(combo_row)
        root.addWidget(self.warning_label)
        root.addLayout(self.summary_grid)
        root.addWidget(self.positions_table, 1)
        self.setLayout(root)

        self._render_current_account()

    def _render_current_account(self) -> None:
        if not self.results:
            return
        index = self.account_combo.currentIndex()
        if index < 0 or index >= len(self.results):
            index = 0
        result = self.results[index]
        summary = result.summary

        self.summary_values["deposit_amount"].setText(_format_int(summary.deposit_amount))
        self.summary_values["withdrawable_amount"].setText(_format_int(summary.withdrawable_amount))
        self.summary_values["orderable_amount"].setText(_format_int(summary.orderable_amount))
        self.summary_values["d1_deposit"].setText(_format_int(summary.d1_deposit))
        self.summary_values["d2_deposit"].setText(_format_int(summary.d2_deposit))
        self.summary_values["purchase_amount_total"].setText(_format_int(summary.purchase_amount_total))
        self.summary_values["valuation_amount_total"].setText(_format_int(summary.valuation_amount_total))
        self.summary_values["total_profit_loss"].setText(_format_int(summary.total_profit_loss))
        self.summary_values["profit_rate"].setText(_format_float(summary.profit_rate))
        self.summary_values["net_total_asset_amount"].setText(_format_int(summary.net_total_asset_amount))

        warning_lines = list(result.warnings)
        if result.selected_account.diagnostic_labels:
            warning_lines.append("라벨: " + ", ".join(result.selected_account.diagnostic_labels))
        self.warning_label.setText("\n".join(warning_lines))
        self.warning_label.setVisible(bool(warning_lines))

        self.positions_table.setRowCount(len(result.positions))
        for row, position in enumerate(result.positions):
            values = [
                position.stock_code,
                position.stock_name,
                _format_int(position.quantity),
                _format_int(position.unsettled_quantity),
                _format_int(position.avg_buy_price),
                _format_int(position.current_price),
                _format_int(position.profit_loss),
                _format_float(position.profit_rate),
                _format_int(position.valuation_amount),
                position.credit_type,
                position.expiry_date,
            ]
            for col, value in enumerate(values):
                item = QTableWidgetItem(value)
                if col >= 2 and col not in {9, 10}:
                    item.setTextAlignment(Qt.AlignRight | Qt.AlignVCenter)
                self.positions_table.setItem(row, col, item)

        self.positions_table.resizeColumnsToContents()
