@echo off
setlocal
cd /d "%~dp0.."

set BUNDLE_DIR=dist\x86\nh-trade-logger
set ISS=installer\nh-trade-logger.iss
set APP_VERSION=1.0.0
set ISCC=

if defined NH_APP_VERSION set APP_VERSION=%NH_APP_VERSION%

if not exist "%BUNDLE_DIR%\nh-trade-logger.exe" (
  echo Packaged bundle not found: %BUNDLE_DIR%
  echo Run scripts\build_pyinstaller.bat first.
  exit /b 1
)

if exist "%ProgramFiles(x86)%\Inno Setup 6\ISCC.exe" set ISCC=%ProgramFiles(x86)%\Inno Setup 6\ISCC.exe
if not defined ISCC if exist "%ProgramFiles%\Inno Setup 6\ISCC.exe" set ISCC=%ProgramFiles%\Inno Setup 6\ISCC.exe

if not defined ISCC (
  echo Inno Setup 6 not found.
  echo Install it from https://jrsoftware.org/isinfo.php and retry.
  exit /b 1
)

"%ISCC%" /DMyAppVersion=%APP_VERSION% "%ISS%"
if errorlevel 1 (
  echo Inno Setup build failed.
  exit /b 1
)

echo Installer build complete: dist\installer

endlocal
