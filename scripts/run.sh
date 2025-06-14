#!/usr/bin/env bash
set -e

# Kill any existing server on port 3000
lsof -ti tcp:3000 | xargs kill -9 2>/dev/null || true

# Activate emsdk
source scripts/emsdk_activate.sh

# Build
emcmake cmake -B build . && \
cmake --build build

# Start server in background
python3 -m http.server 3000 --directory build &
SERVER_PID=$!

# Open in browser
open http://localhost:3000

# Cleanup handler
cleanup() {
  echo "Stopping server (PID $SERVER_PID)..."
  kill $SERVER_PID 2>/dev/null || true
  exit
}
trap cleanup INT TERM EXIT

# Wait for server to stop (until Ctrl+C)
wait $SERVER_PID
