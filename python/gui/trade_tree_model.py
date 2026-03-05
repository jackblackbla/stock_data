from __future__ import annotations

from typing import Callable, List, Optional, Tuple

from PyQt5.QtCore import QAbstractItemModel, QModelIndex, Qt
from PyQt5.QtGui import QColor, QFont

from core.models import TradeRecord


COL_STOCK = 0
COL_SIDE = 1
COL_QTY = 2
COL_PRICE = 3
COL_REASON = 4
COLUMNS = ["종목명", "구분", "수량", "가중평균가", "근거"]

NodePtr = Tuple[str, int, int]


class TradeTreeModel(QAbstractItemModel):
    def __init__(self, on_reason_changed: Optional[Callable[[TradeRecord], None]] = None) -> None:
        super().__init__()
        self._trades: List[TradeRecord] = []
        self._on_reason_changed = on_reason_changed

    def set_trades(self, trades: List[TradeRecord]) -> None:
        self.beginResetModel()
        self._trades = list(trades)
        self.endResetModel()

    def trades(self) -> List[TradeRecord]:
        return list(self._trades)

    def columnCount(self, parent: QModelIndex = QModelIndex()) -> int:  # type: ignore[override]
        return len(COLUMNS)

    def rowCount(self, parent: QModelIndex = QModelIndex()) -> int:  # type: ignore[override]
        if not parent.isValid():
            return len(self._trades)
        if parent.column() != 0:
            return 0

        kind, trade_idx, _ = parent.internalPointer()
        if kind == "trade":
            return len(self._trades[trade_idx].executions)
        return 0

    def index(self, row: int, column: int, parent: QModelIndex = QModelIndex()) -> QModelIndex:  # type: ignore[override]
        if row < 0 or column < 0 or column >= len(COLUMNS):
            return QModelIndex()

        if not parent.isValid():
            if row >= len(self._trades):
                return QModelIndex()
            ptr: NodePtr = ("trade", row, -1)
            return self.createIndex(row, column, ptr)

        if parent.column() != 0:
            return QModelIndex()

        kind, trade_idx, _ = parent.internalPointer()
        if kind != "trade":
            return QModelIndex()

        details = self._trades[trade_idx].executions
        if row >= len(details):
            return QModelIndex()

        ptr = ("detail", trade_idx, row)
        return self.createIndex(row, column, ptr)

    def parent(self, index: QModelIndex) -> QModelIndex:  # type: ignore[override]
        if not index.isValid():
            return QModelIndex()

        kind, trade_idx, _ = index.internalPointer()
        if kind == "trade":
            return QModelIndex()

        parent_ptr: NodePtr = ("trade", trade_idx, -1)
        return self.createIndex(trade_idx, 0, parent_ptr)

    def headerData(self, section: int, orientation: Qt.Orientation, role: int = Qt.DisplayRole):  # type: ignore[override]
        if orientation == Qt.Horizontal and role == Qt.DisplayRole and 0 <= section < len(COLUMNS):
            return COLUMNS[section]
        return None

    def data(self, index: QModelIndex, role: int = Qt.DisplayRole):  # type: ignore[override]
        if not index.isValid():
            return None

        kind, trade_idx, detail_idx = index.internalPointer()
        trade = self._trades[trade_idx]

        if role == Qt.DisplayRole:
            if kind == "trade":
                return self._trade_display(trade, index.column())
            detail = trade.executions[detail_idx]
            return self._detail_display(detail, index.column())

        if role == Qt.TextAlignmentRole and index.column() in (COL_QTY, COL_PRICE):
            return int(Qt.AlignRight | Qt.AlignVCenter)

        if role == Qt.BackgroundRole and kind == "trade":
            return QColor("#FFECEC") if trade.side == "buy" else QColor("#ECF4FF")

        if role == Qt.FontRole and kind == "trade":
            font = QFont()
            font.setBold(True)
            return font

        return None

    def flags(self, index: QModelIndex):  # type: ignore[override]
        if not index.isValid():
            return Qt.NoItemFlags

        base = Qt.ItemIsSelectable | Qt.ItemIsEnabled
        kind, _, _ = index.internalPointer()
        if kind == "trade" and index.column() == COL_REASON:
            return base | Qt.ItemIsEditable
        return base

    def setData(self, index: QModelIndex, value, role: int = Qt.EditRole):  # type: ignore[override]
        if role != Qt.EditRole or not index.isValid() or index.column() != COL_REASON:
            return False

        kind, trade_idx, _ = index.internalPointer()
        if kind != "trade":
            return False

        trade = self._trades[trade_idx]
        new_reason = str(value or "")
        if trade.reason == new_reason:
            return True

        self._trades[trade_idx] = TradeRecord(
            order_no=trade.order_no,
            orig_order_no=trade.orig_order_no,
            order_type=trade.order_type,
            stock_code=trade.stock_code,
            stock_name=trade.stock_name,
            side=trade.side,
            total_qty=trade.total_qty,
            avg_price=trade.avg_price,
            total_amount=trade.total_amount,
            executions=trade.executions,
            reason=new_reason,
        )

        self.dataChanged.emit(index, index, [Qt.DisplayRole, Qt.EditRole])
        if self._on_reason_changed is not None:
            self._on_reason_changed(self._trades[trade_idx])
        return True

    @staticmethod
    def _trade_display(trade: TradeRecord, col: int):
        if col == COL_STOCK:
            return trade.stock_name
        if col == COL_SIDE:
            return "매수" if trade.side == "buy" else "매도"
        if col == COL_QTY:
            return f"{trade.total_qty:,}"
        if col == COL_PRICE:
            return f"{trade.avg_price:,}"
        if col == COL_REASON:
            return trade.reason
        return ""

    @staticmethod
    def _detail_display(detail, col: int):
        if col == COL_STOCK:
            return detail.exec_time
        if col == COL_SIDE:
            return detail.market
        if col == COL_QTY:
            return f"{detail.qty:,}"
        if col == COL_PRICE:
            return f"{detail.price:,}"
        if col == COL_REASON:
            return ""
        return ""
