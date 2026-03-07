from __future__ import annotations

from pathlib import Path

from core.data_loader import load_fetch_json, merge_reasons, parse_trade_date, parse_trades, trade_reason_key


def test_parse_sample_grouping() -> None:
    fixture = Path(__file__).parent / "fixtures" / "fetch_sample.json"
    payload = load_fetch_json(fixture)
    trades = parse_trades(payload)

    assert len(trades) == 2

    samsung = next(t for t in trades if t.stock_code == "005930")
    assert samsung.order_no == "0000000001"
    assert samsung.side == "buy"
    assert samsung.total_qty == 100
    assert samsung.avg_price == 71535
    assert samsung.total_amount == 7153500
    assert len(samsung.executions) == 3


def test_fallback_to_aggregate_when_split_missing() -> None:
    payload = {
        "schema_version": "1.0",
        "trade_date": "20260305",
        "generated_at": "2026-03-05T15:41:00",
        "account_no": "04501012345",
        "status": "ok",
        "errors": [],
        "executions": [
            {
                "order_no": "33",
                "orig_order_no": "0",
                "order_type": "현금매수",
                "stock_code": "005930",
                "stock_name": "삼성전자",
                "order_qty": 10,
                "exec_qty": 10,
                "order_price": 70000,
                "exec_avg_price": 70100,
                "exec_time": "09:00:00",
                "market_code": "KRX",
                "sor_split": "Y",
                "split_details": [],
            }
        ],
    }
    trades = parse_trades(payload)
    assert len(trades) == 1
    assert trades[0].avg_price == 70100
    assert trades[0].total_amount == 701000


def test_parse_trade_date() -> None:
    fixture = Path(__file__).parent / "fixtures" / "fetch_sample.json"
    payload = load_fetch_json(fixture)
    assert parse_trade_date(payload) == "2026-03-05"


def test_merge_reasons() -> None:
    fixture = Path(__file__).parent / "fixtures" / "fetch_sample.json"
    payload = load_fetch_json(fixture)
    trades = parse_trades(payload)

    merge_reasons(trades, {trade_reason_key("04501012345", "0000000001"): "실적호조"})
    target = next(t for t in trades if t.order_no == "0000000001")
    assert target.reason == "실적호조"
