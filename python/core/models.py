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
    account_no: str
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


@dataclass
class BalanceSelectedAccount:
    account_index: int
    account_no: str
    account_name: str = ""
    act_pdt_cd: str = ""
    amn_tab_cd: str = ""
    expr_date: str = ""
    granted: str = ""
    is_granted_batch: bool = False
    diagnostic_labels: List[str] = field(default_factory=list)


@dataclass
class BalanceSummary:
    account_no: str = ""
    deposit_amount: int = 0
    withdrawable_amount: int = 0
    orderable_amount: int = 0
    cash_margin: int = 0
    substitute_margin: int = 0
    d1_deposit: int = 0
    d2_deposit: int = 0
    purchase_amount_total: int = 0
    valuation_amount_total: int = 0
    net_asset_amount: int = 0
    total_profit_loss: int = 0
    profit_rate: float = 0.0
    net_total_asset_amount: int = 0
    activity_type: str = ""


@dataclass
class BalancePosition:
    account_no: str = ""
    stock_code: str = ""
    stock_name: str = ""
    balance_type: str = ""
    loan_date: str = ""
    quantity: int = 0
    unsettled_quantity: int = 0
    avg_buy_price: int = 0
    current_price: int = 0
    profit_loss: int = 0
    profit_rate: float = 0.0
    credit_type: str = ""
    remaining_quantity: int = 0
    expiry_date: str = ""
    valuation_amount: int = 0
    issue_margin_rate: str = ""
    avg_sell_price: int = 0
    sell_profit_loss: int = 0


@dataclass
class BalanceAccountResult:
    selected_account: BalanceSelectedAccount
    summary: BalanceSummary = field(default_factory=BalanceSummary)
    positions: List[BalancePosition] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)
