from __future__ import annotations

from pathlib import Path

from core.data_loader import trade_reason_key
from core.models import TradeRecord
from core.reason_store import ReasonStore


def test_upsert_and_get_reason(tmp_path: Path) -> None:
    db_path = tmp_path / "reasons.db"
    store = ReasonStore(db_path)

    store.save_reason(
        trade_date="2026-03-05",
        account_masked="04501****",
        order_no="0000000001",
        stock_code="005930",
        stock_name="삼성전자",
        side="buy",
        reason="실적호조",
    )

    store.save_reason(
        trade_date="2026-03-05",
        account_masked="04501****",
        order_no="0000000001",
        stock_code="005930",
        stock_name="삼성전자",
        side="buy",
        reason="상향 추세",
    )

    reasons = store.get_reasons("2026-03-05")
    assert reasons[trade_reason_key("04501****", "0000000001")] == "상향 추세"


def test_count_missing_reasons(tmp_path: Path) -> None:
    db_path = tmp_path / "reasons.db"
    store = ReasonStore(db_path)

    trades = [
        TradeRecord(
            account_masked="04501****",
            order_no="0000000001",
            orig_order_no="0000000000",
            order_type="현금매수",
            stock_code="005930",
            stock_name="삼성전자",
            side="buy",
            total_qty=10,
            avg_price=1000,
            total_amount=10000,
            executions=[],
        ),
        TradeRecord(
            account_masked="200*****21",
            order_no="0000000002",
            orig_order_no="0000000000",
            order_type="현금매도",
            stock_code="000660",
            stock_name="SK하이닉스",
            side="sell",
            total_qty=5,
            avg_price=2000,
            total_amount=10000,
            executions=[],
        ),
    ]

    store.save_reason(
        trade_date="2026-03-05",
        account_masked="04501****",
        order_no="0000000001",
        stock_code="005930",
        stock_name="삼성전자",
        side="buy",
        reason="근거 있음",
    )

    missing = store.count_missing_reasons("2026-03-05", trades)
    assert missing == 1
