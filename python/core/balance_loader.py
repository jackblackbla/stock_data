from __future__ import annotations

import json
from pathlib import Path
from typing import Mapping

from core.models import (
    BalanceAccountResult,
    BalancePosition,
    BalanceSelectedAccount,
    BalanceSummary,
)

REQUIRED_BALANCE_ROOT_KEYS = {
    "schema_version",
    "generated_at",
    "status",
    "errors",
    "balance_accounts",
}


def _to_int(value: object, default: int = 0) -> int:
    try:
        return int(value)
    except (TypeError, ValueError):
        return default


def _to_float(value: object, default: float = 0.0) -> float:
    try:
        return float(value)
    except (TypeError, ValueError):
        return default


def _to_string_list(value: object) -> list[str]:
    if not isinstance(value, list):
        return []
    return [str(item).strip() for item in value if str(item).strip()]


def load_balance_json(path: Path) -> dict:
    payload = json.loads(path.read_text(encoding="utf-8"))
    missing = REQUIRED_BALANCE_ROOT_KEYS - payload.keys()
    if missing:
        raise ValueError(f"missing root keys: {sorted(missing)}")
    if not isinstance(payload["errors"], list):
        raise ValueError("errors must be list")
    if not isinstance(payload["balance_accounts"], list):
        raise ValueError("balance_accounts must be list")
    return payload


def parse_balance_accounts(payload: Mapping[str, object]) -> list[BalanceAccountResult]:
    raw_accounts = payload.get("balance_accounts")
    if not isinstance(raw_accounts, list):
        return []

    parsed: list[BalanceAccountResult] = []
    for raw_account in raw_accounts:
        if not isinstance(raw_account, Mapping):
            continue

        selected_raw = raw_account.get("selected_account")
        if not isinstance(selected_raw, Mapping):
            selected_raw = {}
        selected = BalanceSelectedAccount(
            account_index=_to_int(selected_raw.get("account_index")),
            account_no=str(selected_raw.get("account_no") or "").strip(),
            account_name=str(selected_raw.get("account_name") or "").strip(),
            act_pdt_cd=str(selected_raw.get("act_pdt_cd") or "").strip(),
            amn_tab_cd=str(selected_raw.get("amn_tab_cd") or "").strip(),
            expr_date=str(selected_raw.get("expr_date") or "").strip(),
            granted=str(selected_raw.get("granted") or "").strip(),
            is_granted_batch=bool(selected_raw.get("is_granted_batch")),
            diagnostic_labels=_to_string_list(selected_raw.get("diagnostic_labels")),
        )

        summary_raw = raw_account.get("summary")
        if not isinstance(summary_raw, Mapping):
            summary_raw = {}
        summary = BalanceSummary(
            account_no=str(summary_raw.get("account_no") or "").strip(),
            deposit_amount=_to_int(summary_raw.get("deposit_amount")),
            withdrawable_amount=_to_int(summary_raw.get("withdrawable_amount")),
            orderable_amount=_to_int(summary_raw.get("orderable_amount")),
            cash_margin=_to_int(summary_raw.get("cash_margin")),
            substitute_margin=_to_int(summary_raw.get("substitute_margin")),
            d1_deposit=_to_int(summary_raw.get("d1_deposit")),
            d2_deposit=_to_int(summary_raw.get("d2_deposit")),
            purchase_amount_total=_to_int(summary_raw.get("purchase_amount_total")),
            valuation_amount_total=_to_int(summary_raw.get("valuation_amount_total")),
            net_asset_amount=_to_int(summary_raw.get("net_asset_amount")),
            total_profit_loss=_to_int(summary_raw.get("total_profit_loss")),
            profit_rate=_to_float(summary_raw.get("profit_rate")),
            net_total_asset_amount=_to_int(summary_raw.get("net_total_asset_amount")),
            activity_type=str(summary_raw.get("activity_type") or "").strip(),
        )

        positions_raw = raw_account.get("positions")
        positions: list[BalancePosition] = []
        if isinstance(positions_raw, list):
            for item in positions_raw:
                if not isinstance(item, Mapping):
                    continue
                positions.append(
                    BalancePosition(
                        account_no=str(item.get("account_no") or "").strip(),
                        stock_code=str(item.get("stock_code") or "").strip(),
                        stock_name=str(item.get("stock_name") or "").strip(),
                        balance_type=str(item.get("balance_type") or "").strip(),
                        loan_date=str(item.get("loan_date") or "").strip(),
                        quantity=_to_int(item.get("quantity")),
                        unsettled_quantity=_to_int(item.get("unsettled_quantity")),
                        avg_buy_price=_to_int(item.get("avg_buy_price")),
                        current_price=_to_int(item.get("current_price")),
                        profit_loss=_to_int(item.get("profit_loss")),
                        profit_rate=_to_float(item.get("profit_rate")),
                        credit_type=str(item.get("credit_type") or "").strip(),
                        remaining_quantity=_to_int(item.get("remaining_quantity")),
                        expiry_date=str(item.get("expiry_date") or "").strip(),
                        valuation_amount=_to_int(item.get("valuation_amount")),
                        issue_margin_rate=str(item.get("issue_margin_rate") or "").strip(),
                        avg_sell_price=_to_int(item.get("avg_sell_price")),
                        sell_profit_loss=_to_int(item.get("sell_profit_loss")),
                    )
                )

        parsed.append(
            BalanceAccountResult(
                selected_account=selected,
                summary=summary,
                positions=positions,
                warnings=_to_string_list(raw_account.get("warnings")),
            )
        )

    return parsed
