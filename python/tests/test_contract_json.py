from __future__ import annotations

import json
from pathlib import Path

import pytest

from core.data_loader import load_fetch_json


def test_contract_json_ok() -> None:
    fixture = Path(__file__).parent / "fixtures" / "fetch_sample.json"
    payload = load_fetch_json(fixture)
    assert payload["schema_version"] == "1.0"
    assert isinstance(payload["executions"], list)


def test_contract_json_missing_key(tmp_path: Path) -> None:
    bad = {
        "schema_version": "1.0",
        "trade_date": "20260305",
    }
    path = tmp_path / "bad.json"
    path.write_text(json.dumps(bad, ensure_ascii=False), encoding="utf-8")

    with pytest.raises(ValueError):
        load_fetch_json(path)
