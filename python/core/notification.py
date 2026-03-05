from __future__ import annotations

import time

from PyQt5.QtWidgets import QApplication, QStyle, QSystemTrayIcon


def show_notification(title: str, message: str, timeout_ms: int = 8000) -> None:
    app = QApplication.instance()
    owns_app = app is None
    if owns_app:
        app = QApplication([])

    assert app is not None
    icon = app.style().standardIcon(QStyle.SP_MessageBoxInformation)
    tray = QSystemTrayIcon(icon)
    tray.show()
    tray.showMessage(title, message, QSystemTrayIcon.Information, timeout_ms)

    end_time = time.time() + (timeout_ms / 1000.0) + 1.0
    while time.time() < end_time:
        app.processEvents()
        time.sleep(0.05)

    tray.hide()
    if owns_app:
        app.quit()
