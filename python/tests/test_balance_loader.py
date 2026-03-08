from __future__ import annotations

import json
from pathlib import Path

import pytest

from core.balance_loader import load_balance_json, parse_balance_accounts


def test_load_balance_json_requires_root_keys(tmp_path: Path) -> None:
    path = tmp_path / "balance.json"
    path.write_text(json.dumps({"schema_version": "1.0"}), encoding="utf-8")

    with pytest.raises(ValueError, match="missing root keys"):
        load_balance_json(path)


def test_parse_balance_accounts_reads_summary_and_positions(tmp_path: Path) -> None:
    path = tmp_path / "balance.json"
    payload = {
        "schema_version": "1.0",
        "generated_at": "2026-03-08T12:00:00Z",
        "status": "partial",
        "errors": ["20001505931: 부분 실패"],
        "balance_accounts": [
            {
                "selected_account": {
                    "account_index": 3,
                    "account_no": "20001505931",
                    "account_name": "종합매매",
                    "act_pdt_cd": "004",
                    "granted": "-",
                    "is_granted_batch": False,
                    "diagnostic_labels": ["unknown_product"],
                },
                "summary": {
                    "account_no": "20001505931",
                    "deposit_amount": 1000000,
                    "withdrawable_amount": 800000,
                    "orderable_amount": 750000,
                    "profit_rate": 1.25,
                    "net_total_asset_amount": 1234567,
                },
                "positions": [
                    {
                        "account_no": "20001505931",
                        "stock_code": "005930",
                        "stock_name": "삼성전자",
                        "quantity": 10,
                        "avg_buy_price": 70000,
                        "current_price": 71000,
                        "profit_loss": 10000,
                        "profit_rate": 1.43,
                        "valuation_amount": 710000,
                    }
                ],
                "warnings": ["모의 데이터"],
            }
        ],
    }
    path.write_text(json.dumps(payload, ensure_ascii=False), encoding="utf-8")

    loaded = load_balance_json(path)
    accounts = parse_balance_accounts(loaded)

    assert loaded["status"] == "partial"
    assert loaded["errors"] == ["20001505931: 부분 실패"]
    assert len(accounts) == 1
    account = accounts[0]
    assert account.selected_account.account_no == "20001505931"
    assert account.selected_account.diagnostic_labels == ["unknown_product"]
    assert account.summary.deposit_amount == 1000000
    assert account.summary.profit_rate == 1.25
    assert len(account.positions) == 1
    assert account.positions[0].stock_code == "005930"
    assert account.positions[0].valuation_amount == 710000
    assert account.warnings == ["모의 데이터"]
