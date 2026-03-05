@echo off
setlocal
cd /d "%~dp0.."

for /f %%i in ('powershell -NoProfile -Command "Get-Date -Format yyyyMMdd"') do set TRADE_DATE=%%i
set JSON_PATH=data\json\%TRADE_DATE%.json
set FETCH_EXE=cpp\build\fetch.exe
if not exist "%FETCH_EXE%" set FETCH_EXE=cpp\build\Release\fetch.exe
if not exist "%FETCH_EXE%" set FETCH_EXE=cpp\build\RelWithDebInfo\fetch.exe
if not exist "%FETCH_EXE%" (
  echo fetch.exe not found. Build cpp project first.
  exit /b 1
)

"%FETCH_EXE%" --date %TRADE_DATE% --output %JSON_PATH%
if errorlevel 1 (
  echo fetch.exe failed with code %errorlevel%
  exit /b %errorlevel%
)

set ISO_DATE=%TRADE_DATE:~0,4%-%TRADE_DATE:~4,2%-%TRADE_DATE:~6,2%
python python\main.py --date %ISO_DATE% --json %JSON_PATH%

endlocal
