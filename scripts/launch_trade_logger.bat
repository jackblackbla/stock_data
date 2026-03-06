@echo off
setlocal
cd /d "%~dp0"

if not exist "nh-trade-logger.exe" (
  echo nh-trade-logger.exe not found in %~dp0
  echo This launcher must be used from the packaged install folder.
  pause
  exit /b 1
)

"%~dp0nh-trade-logger.exe"
set EXIT_CODE=%ERRORLEVEL%

if not "%EXIT_CODE%"=="0" (
  echo nh-trade-logger.exe exited with code %EXIT_CODE%.
  pause
)

endlocal
