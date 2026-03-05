@echo off
setlocal
cd /d "%~dp0.."

pyinstaller --noconfirm --clean --onedir --name nh-trade-logger --windowed --distpath dist/x86 --workpath build/pyinstaller python/main.py

endlocal
