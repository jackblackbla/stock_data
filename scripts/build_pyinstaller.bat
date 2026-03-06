@echo off
setlocal
cd /d "%~dp0.."

set DIST_ROOT=dist\x86
set BUNDLE_DIR=%DIST_ROOT%\nh-trade-logger
set FETCH_EXE=cpp\build\fetch.exe

if not exist "%FETCH_EXE%" set FETCH_EXE=cpp\build\Release\fetch.exe
if not exist "%FETCH_EXE%" set FETCH_EXE=cpp\build\RelWithDebInfo\fetch.exe

if not exist "%FETCH_EXE%" (
  echo fetch.exe not found. Build the C++ project first.
  exit /b 1
)

pyinstaller ^
  --noconfirm ^
  --clean ^
  --onedir ^
  --windowed ^
  --name nh-trade-logger ^
  --distpath %DIST_ROOT% ^
  --workpath build\pyinstaller ^
  python\main.py

if errorlevel 1 (
  echo PyInstaller build failed.
  exit /b 1
)

if not exist "%BUNDLE_DIR%" (
  echo Bundle directory not found: %BUNDLE_DIR%
  exit /b 1
)

copy /Y "%FETCH_EXE%" "%BUNDLE_DIR%\fetch.exe" >nul
copy /Y "scripts\launch_trade_logger.bat" "%BUNDLE_DIR%\launch_trade_logger.bat" >nul
copy /Y "USER_GUIDE.txt" "%BUNDLE_DIR%\USER_GUIDE.txt" >nul

echo Build complete: %BUNDLE_DIR%
echo Runtime data will be stored under %%LOCALAPPDATA%%\NHTradeLogger

endlocal
