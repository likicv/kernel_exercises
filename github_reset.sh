#!/usr/bin/env bash
set -euo pipefail

# ------------------------------------------------------------
# Configuration
# ------------------------------------------------------------
BRANCH="main"
COMMIT_MSG="Public release"

# ------------------------------------------------------------
# Sanity checks
# ------------------------------------------------------------
if [[ ! -d .git ]]; then
  echo "ERROR: This directory is not a git repository." >&2
  exit 1
fi

if [[ -n "$(git status --porcelain)" ]]; then
  echo "ERROR: Working tree is not clean. Commit or stash changes first." >&2
  exit 1
fi

REMOTE_URL="$(git remote get-url origin 2>/dev/null || true)"
if [[ -z "$REMOTE_URL" ]]; then
  echo "ERROR: No 'origin' remote configured." >&2
  exit 1
fi

# ------------------------------------------------------------
# Purge history
# ------------------------------------------------------------
echo "Purging git history..."

rm -rf .git
git init

git add .
git commit -m "$COMMIT_MSG"

git branch -M "$BRANCH"
git remote add origin "$REMOTE_URL"

git push --force origin "$BRANCH"

echo
echo "History purge complete."
echo "Repository now contains a single root commit."

