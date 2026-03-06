@echo off
setlocal
cd /d "%~dp0.."

call scripts\build_pyinstaller.bat
if errorlevel 1 exit /b 1

call scripts\build_installer.bat
if errorlevel 1 exit /b 1

echo Release build complete.

endlocal
