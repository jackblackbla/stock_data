from __future__ import annotations

from dataclasses import dataclass, field
from typing import List


@dataclass
class ExecutionDetail:
    exec_time: str
    market: str
    qty: int
    price: int
    amount: int


@dataclass
class TradeRecord:
    order_no: str
    orig_order_no: str
    order_type: str
    stock_code: str
    stock_name: str
    side: str
    total_qty: int
    avg_price: int
    total_amount: int
    executions: List[ExecutionDetail] = field(default_factory=list)
    reason: str = ""
