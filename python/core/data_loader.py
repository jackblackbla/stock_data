from __future__ import annotations

import json
from collections import OrderedDict
from dataclasses import replace
from decimal import Decimal, ROUND_HALF_UP
from pathlib import Path
from typing import Dict, Iterable, List, Mapping

from core.models import ExecutionDetail, TradeRecord

REQUIRED_ROOT_KEYS = {
    "schema_version",
    "trade_date",
    "generated_at",
    "account_masked",
    "status",
    "errors",
    "executions",
}


def _to_int(value: object, default: int = 0) -> int:
    try:
        return int(value)
    except (TypeError, ValueError):
        return default


def normalize_order_no(order_no: object) -> str:
    digits = "".join(ch for ch in str(order_no or "") if ch.isdigit())
    if not digits:
        return "0000000000"
    return digits.zfill(10)[-10:]


def infer_side(order_type: str) -> str | None:
    if "매수" in order_type:
        return "buy"
    if "매도" in order_type:
        return "sell"
    return None


def round_half_up_won(value: Decimal) -> int:
    return int(value.quantize(Decimal("1"), rounding=ROUND_HALF_UP))


def _detail_from_split(item: Mapping[str, object], fallback_time: str, fallback_market: str) -> ExecutionDetail | None:
    qty = _to_int(item.get("exec_qty"))
    if qty <= 0:
        return None

    amount = _to_int(item.get("exec_amount"))
    price = _to_int(item.get("exec_price"))
    if price <= 0:
        if amount > 0:
            price = round_half_up_won(Decimal(amount) / Decimal(qty))
        else:
            price = 0
    if amount <= 0:
        amount = qty * price

    return ExecutionDetail(
        exec_time=str(item.get("exec_time") or fallback_time or ""),
        market=str(item.get("market") or fallback_market or ""),
        qty=qty,
        price=price,
        amount=amount,
    )


def _build_details(execution: Mapping[str, object]) -> List[ExecutionDetail]:
    fallback_time = str(execution.get("exec_time") or "")
    fallback_market = str(execution.get("market_code") or "")

    details: List[ExecutionDetail] = []
    split_items = execution.get("split_details")
    if isinstance(split_items, list):
        for item in split_items:
            if not isinstance(item, Mapping):
                continue
            detail = _detail_from_split(item, fallback_time, fallback_market)
            if detail is not None:
                details.append(detail)

    if details:
        return details

    qty = _to_int(execution.get("exec_qty"))
    if qty <= 0:
        return []
    price = _to_int(execution.get("exec_avg_price"))
    amount = qty * price
    return [
        ExecutionDetail(
            exec_time=fallback_time,
            market=fallback_market,
            qty=qty,
            price=price,
            amount=amount,
        )
    ]


def _recompute_metrics(details: Iterable[ExecutionDetail]) -> tuple[int, int, int]:
    detail_list = list(details)
    total_qty = sum(item.qty for item in detail_list)
    if total_qty <= 0:
        return 0, 0, 0
    weighted = sum(item.qty * item.price for item in detail_list)
    avg_price = round_half_up_won(Decimal(weighted) / Decimal(total_qty))
    total_amount = sum(item.amount for item in detail_list)
    return total_qty, avg_price, total_amount


def load_fetch_json(path: Path) -> dict:
    payload = json.loads(path.read_text(encoding="utf-8"))
    missing = REQUIRED_ROOT_KEYS - payload.keys()
    if missing:
        raise ValueError(f"missing root keys: {sorted(missing)}")
    if not isinstance(payload["executions"], list):
        raise ValueError("executions must be list")
    if not isinstance(payload["errors"], list):
        raise ValueError("errors must be list")
    return payload


def parse_trades(payload: Mapping[str, object]) -> List[TradeRecord]:
    grouped: "OrderedDict[str, TradeRecord]" = OrderedDict()

    executions = payload.get("executions", [])
    if not isinstance(executions, list):
        return []

    for item in executions:
        if not isinstance(item, Mapping):
            continue

        order_no = normalize_order_no(item.get("order_no"))
        details = _build_details(item)
        if not details:
            continue

        order_type = str(item.get("order_type") or "")
        side = infer_side(order_type)
        if side is None:
            continue

        if order_no not in grouped:
            qty, avg_price, amount = _recompute_metrics(details)
            grouped[order_no] = TradeRecord(
                order_no=order_no,
                orig_order_no=normalize_order_no(item.get("orig_order_no")),
                order_type=order_type,
                stock_code=str(item.get("stock_code") or ""),
                stock_name=str(item.get("stock_name") or ""),
                side=side,
                total_qty=qty,
                avg_price=avg_price,
                total_amount=amount,
                executions=list(details),
            )
            continue

        existing = grouped[order_no]
        merged = existing.executions + details
        merged.sort(key=lambda d: (d.exec_time, d.market, d.qty))
        qty, avg_price, amount = _recompute_metrics(merged)
        grouped[order_no] = replace(
            existing,
            total_qty=qty,
            avg_price=avg_price,
            total_amount=amount,
            executions=merged,
        )

    trades = list(grouped.values())
    trades.sort(key=lambda t: (t.stock_name, t.order_no))
    return trades


def merge_reasons(trades: List[TradeRecord], reasons: Dict[str, str]) -> None:
    for idx, trade in enumerate(trades):
        reason = reasons.get(trade.order_no, "")
        trades[idx] = replace(trade, reason=reason)


def parse_trade_date(payload: Mapping[str, object]) -> str:
    compact = str(payload.get("trade_date") or "")
    if len(compact) == 8 and compact.isdigit():
        return f"{compact[:4]}-{compact[4:6]}-{compact[6:8]}"
    return compact
