from __future__ import annotations

from pathlib import Path

from openpyxl import load_workbook

from core.excel_generator import generate_excel
from core.models import ExecutionDetail, TradeRecord


def test_generate_excel(tmp_path: Path) -> None:
    trades = [
        TradeRecord(
            order_no="0000000001",
            orig_order_no="0000000000",
            order_type="현금매수",
            stock_code="005930",
            stock_name="삼성전자",
            side="buy",
            total_qty=100,
            avg_price=71546,
            total_amount=7154600,
            reason="실적호조",
            executions=[
                ExecutionDetail(exec_time="09:31:02", market="KRX", qty=37, price=71500, amount=2645500),
                ExecutionDetail(exec_time="09:31:05", market="KRX", qty=63, price=71573, amount=4509100),
            ],
        )
    ]

    output = generate_excel(trades, "2026-03-05", tmp_path)
    assert output.exists()

    wb = load_workbook(output)
    assert wb.sheetnames == ["매매 요약", "체결 상세"]

    ws_summary = wb["매매 요약"]
    assert ws_summary["A2"].value == "삼성전자"
    assert ws_summary["B2"].value == "매수"
    assert ws_summary["C2"].value == 100

    ws_detail = wb["체결 상세"]
    assert ws_detail["A2"].value == "0000000001"
    assert ws_detail["D2"].value == "09:31:02"
