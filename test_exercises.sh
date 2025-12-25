#!/usr/bin/env bash
set -euo pipefail

TOP_DIR="$(pwd)"

# ------------------------------------------------------------
# Exercises to skip (no Makefile, script-only, etc.)
# ------------------------------------------------------------
SKIP_EXERCISES=(
  kernel_exercise_6.1
)

# ------------------------------------------------------------
# Discover exercise directories
# ------------------------------------------------------------
mapfile -t EX_DIRS < <(
  find . -maxdepth 1 -type d -name 'kernel_exercise_*' -printf '%f\n' | sort -V
)

# Helper: check if element is in array
is_skipped() {
  local x
  for x in "${SKIP_EXERCISES[@]}"; do
    [[ "$x" == "$1" ]] && return 0
  done
  return 1
}

# ------------------------------------------------------------
# Main loop
# ------------------------------------------------------------
for d in "${EX_DIRS[@]}"; do

  if is_skipped "$d"; then
    echo "==> Skipping $d"
    continue
  fi

  echo "==> Testing $d"

  if [[ ! -f "$d/Makefile" ]]; then
    echo "ERROR: $d has no Makefile (and is not in skip list)" >&2
    exit 1
  fi

  pushd "$d" >/dev/null

  if make; then
    echo "-> $d working"
    make clean
  else
    echo "FAIL: 'make' failed in $d" >&2
    popd >/dev/null
    exit 1
  fi

  popd >/dev/null
done

echo "All non-skipped exercises built successfully."

