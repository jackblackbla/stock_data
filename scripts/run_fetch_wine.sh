#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
REPO_ROOT=$(cd -- "${SCRIPT_DIR}/.." && pwd)
IMAGE_NAME="${FETCH_WINE_IMAGE:-nh-fetch-wine}"
PLATFORM="${FETCH_WINE_PLATFORM:-linux/amd64}"
RESULTS_DIR="${FETCH_WINE_RESULTS_DIR:-${REPO_ROOT}/.wine-fetch-results}"

usage() {
    cat >&2 <<'EOF'
Usage:
  scripts/run_fetch_wine.sh [fetch.exe args...]

Examples:
  scripts/run_fetch_wine.sh --list-accounts --output /results/accounts.json --log /results/fetch.log
  scripts/run_fetch_wine.sh --date 20260306 --output /results/out.json --log /results/fetch.log

Environment:
  QV_ID, QV_PASSWORD, QV_CERT_PASSWORD
  QV_ACCOUNT_INDEX, QV_ACCOUNT_PASSWORD
  QV_S8180_PASSWORD_MODE=encrypted|plain|blank
  QV_TRADE_PASSWORD1, QV_TRADE_PASSWORD2
  NPKI_DIR=/absolute/path/to/NPKI
EOF
    exit 2
}

if [[ $# -eq 0 ]]; then
    usage
fi

if ! command -v docker >/dev/null 2>&1; then
    echo "docker not found in PATH" >&2
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "Docker daemon is not running. Start Docker Desktop first." >&2
    exit 1
fi

mkdir -p "${RESULTS_DIR}"

echo "Building ${IMAGE_NAME} (${PLATFORM})..."
docker build --platform "${PLATFORM}" -f "${REPO_ROOT}/docker/fetch-wine/Dockerfile" -t "${IMAGE_NAME}" "${REPO_ROOT}"

env_args=()
while IFS='=' read -r name _; do
    case "${name}" in
        QV_*|FETCH_WINE_*)
            env_args+=(-e "${name}")
            ;;
    esac
done < <(env)

volume_args=(
    -v "${RESULTS_DIR}:/results"
)

if [[ -n "${NPKI_DIR:-}" ]]; then
    if [[ ! -d "${NPKI_DIR}" ]]; then
        echo "NPKI_DIR does not exist: ${NPKI_DIR}" >&2
        exit 1
    fi
    volume_args+=(-v "${NPKI_DIR}:/app/NPKI:ro")
fi

tty_args=()
if [[ -t 0 && -t 1 ]]; then
    tty_args=(-it)
fi

echo "Running fetch.exe in Wine container..."
exec docker run --rm --platform "${PLATFORM}" \
    "${tty_args[@]}" \
    "${env_args[@]}" \
    "${volume_args[@]}" \
    "${IMAGE_NAME}" \
    "$@"
