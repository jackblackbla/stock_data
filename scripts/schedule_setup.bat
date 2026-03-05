@echo off
setlocal
cd /d "%~dp0.."

set TASK_NAME=NH_Trade_Logger_Auto
set CMD=cmd /c "cd /d \"%CD%\" && python python\main.py --auto"

schtasks /Create /TN "%TASK_NAME%" /TR "%CMD%" /SC DAILY /ST 15:40 /F
if errorlevel 1 (
  echo Failed to register scheduled task.
  exit /b 1
)

echo Scheduled task created: %TASK_NAME%
endlocal
