from __future__ import annotations

from PyQt5.QtWidgets import (
    QCheckBox,
    QDialog,
    QDialogButtonBox,
    QFormLayout,
    QLineEdit,
    QVBoxLayout,
)

from core.fetch_service import LoginCredentials


class LoginCredentialsDialog(QDialog):
    def __init__(self, parent=None, initial: LoginCredentials | None = None, remember_checked: bool = True) -> None:
        super().__init__(parent)
        self.setWindowTitle("QV 로그인")
        self.setModal(True)
        self.resize(360, 180)

        self.edit_user = QLineEdit(initial.user_id if initial else "")
        self.edit_password = QLineEdit(initial.password if initial else "")
        self.edit_password.setEchoMode(QLineEdit.Password)
        self.edit_cert = QLineEdit(initial.cert_password if initial else "")
        self.edit_cert.setEchoMode(QLineEdit.Password)

        form = QFormLayout()
        form.addRow("QV ID", self.edit_user)
        form.addRow("QV 로그인 비밀번호", self.edit_password)
        form.addRow("인증서 비밀번호", self.edit_cert)

        self.chk_remember = QCheckBox("이번 실행 동안 로그인 정보 기억")
        self.chk_remember.setChecked(remember_checked)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)

        root = QVBoxLayout()
        root.addLayout(form)
        root.addWidget(self.chk_remember)
        root.addWidget(buttons)
        self.setLayout(root)

    def credentials(self) -> LoginCredentials:
        return LoginCredentials(
            user_id=self.edit_user.text().strip(),
            password=self.edit_password.text().strip(),
            cert_password=self.edit_cert.text().strip(),
        )

    def remember_session(self) -> bool:
        return self.chk_remember.isChecked()
