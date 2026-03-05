from __future__ import annotations

from PyQt5.QtWidgets import QLineEdit, QStyledItemDelegate


class ReasonDelegate(QStyledItemDelegate):
    def createEditor(self, parent, option, index):  # type: ignore[override]
        editor = QLineEdit(parent)
        editor.setPlaceholderText("매매 근거 입력")
        return editor
