from __future__ import annotations

import sqlite3
from pathlib import Path
from typing import Dict, Iterable

from core.data_loader import ReasonKey, trade_reason_key
from core.models import TradeRecord


class ReasonStore:
    def __init__(self, db_path: Path) -> None:
        self.db_path = db_path
        if db_path.parent:
            db_path.parent.mkdir(parents=True, exist_ok=True)
        self._init_schema()

    def _connect(self) -> sqlite3.Connection:
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row
        return conn

    def _init_schema(self) -> None:
        ddl = """
        CREATE TABLE IF NOT EXISTS reasons (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            account_masked TEXT NOT NULL,
            order_no TEXT NOT NULL,
            stock_code TEXT NOT NULL,
            stock_name TEXT,
            side TEXT CHECK(side IN ('buy','sell')),
            reason TEXT,
            created_at TEXT DEFAULT (datetime('now', 'localtime')),
            updated_at TEXT DEFAULT (datetime('now', 'localtime')),
            UNIQUE(date, account_masked, order_no)
        );

        CREATE INDEX IF NOT EXISTS idx_reasons_date ON reasons(date);
        CREATE INDEX IF NOT EXISTS idx_reasons_account ON reasons(account_masked);
        CREATE INDEX IF NOT EXISTS idx_reasons_stock ON reasons(stock_code);
        """
        with self._connect() as conn:
            row = conn.execute(
                "SELECT sql FROM sqlite_master WHERE type='table' AND name='reasons'"
            ).fetchone()
            if row and "account_masked" not in str(row["sql"] or ""):
                conn.executescript(
                    """
                    ALTER TABLE reasons RENAME TO reasons_legacy;
                    CREATE TABLE reasons (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        date TEXT NOT NULL,
                        account_masked TEXT NOT NULL,
                        order_no TEXT NOT NULL,
                        stock_code TEXT NOT NULL,
                        stock_name TEXT,
                        side TEXT CHECK(side IN ('buy','sell')),
                        reason TEXT,
                        created_at TEXT DEFAULT (datetime('now', 'localtime')),
                        updated_at TEXT DEFAULT (datetime('now', 'localtime')),
                        UNIQUE(date, account_masked, order_no)
                    );
                    INSERT INTO reasons (
                        date, account_masked, order_no, stock_code, stock_name, side, reason, created_at, updated_at
                    )
                    SELECT
                        date, '', order_no, stock_code, stock_name, side, reason, created_at, updated_at
                    FROM reasons_legacy;
                    DROP TABLE reasons_legacy;
                    """
                )
            conn.executescript(ddl)

    def save_reason(
        self,
        trade_date: str,
        account_masked: str,
        order_no: str,
        stock_code: str,
        stock_name: str,
        side: str,
        reason: str,
    ) -> None:
        sql = """
        INSERT INTO reasons (date, account_masked, order_no, stock_code, stock_name, side, reason)
        VALUES (?, ?, ?, ?, ?, ?, ?)
        ON CONFLICT(date, account_masked, order_no) DO UPDATE SET
            stock_code = excluded.stock_code,
            stock_name = excluded.stock_name,
            side = excluded.side,
            reason = excluded.reason,
            updated_at = datetime('now', 'localtime');
        """
        with self._connect() as conn:
            conn.execute(
                sql,
                (trade_date, account_masked, order_no, stock_code, stock_name, side, reason),
            )

    def get_reasons(self, trade_date: str) -> Dict[ReasonKey, str]:
        sql = "SELECT account_masked, order_no, reason FROM reasons WHERE date = ?"
        with self._connect() as conn:
            rows = conn.execute(sql, (trade_date,)).fetchall()
        return {
            trade_reason_key(str(row["account_masked"] or ""), str(row["order_no"] or "")): str(row["reason"] or "")
            for row in rows
        }

    def count_missing_reasons(self, trade_date: str, trades: Iterable[TradeRecord]) -> int:
        reasons = self.get_reasons(trade_date)
        missing = 0
        for trade in trades:
            if not reasons.get(trade_reason_key(trade.account_masked, trade.order_no), "").strip():
                missing += 1
        return missing
