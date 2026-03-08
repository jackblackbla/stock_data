#!/usr/bin/env bash
set -euo pipefail

export DISPLAY="${DISPLAY:-:99}"
export LANG="${LANG:-ko_KR.UTF-8}"
export LC_ALL="${LC_ALL:-ko_KR.UTF-8}"

WINE_LOCALLOW="/home/wineuser/.wine/drive_c/users/wineuser/AppData/LocalLow"
NPKI_LINK="${WINE_LOCALLOW}/NPKI"

mkdir -p "${WINE_LOCALLOW}"
if [[ -d /app/NPKI ]]; then
    rm -rf "${NPKI_LINK}"
    ln -s /app/NPKI "${NPKI_LINK}"
fi

Xvfb "${DISPLAY}" -screen 0 1280x800x24 >/tmp/xvfb.log 2>&1 &
XVFB_PID=$!
fluxbox >/tmp/fluxbox.log 2>&1 &
WM_PID=$!

cleanup() {
    kill "${WM_PID}" "${XVFB_PID}" >/dev/null 2>&1 || true
}
trap cleanup EXIT

cd /app
exec wine ./fetch.exe "$@"
