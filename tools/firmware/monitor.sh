#!/usr/bin/env bash
set -euo pipefail

# Serial port can be changed by setting FLEETTRACKER_PORT before running.
# Find it with:
#   arduino-cli board list
# Current ESP32 DevKit V1 CP2102 default:
#   /dev/cu.usbserial-0001
PORT="${FLEETTRACKER_PORT:-/dev/cu.usbserial-0001}"

# Monitor baud rate can be changed by setting FLEETTRACKER_BAUD before running.
BAUD="${FLEETTRACKER_BAUD:-115200}"

arduino-cli monitor --port "${PORT}" --config "baudrate=${BAUD}"
