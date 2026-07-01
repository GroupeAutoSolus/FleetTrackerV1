#!/usr/bin/env bash
set -euo pipefail

# Board FQBN can be changed by setting FLEETTRACKER_FQBN before running.
# ESP32 DevKit V1 default:
#   esp32:esp32:esp32doit-devkit-v1
FQBN="${FLEETTRACKER_FQBN:-esp32:esp32:esp32doit-devkit-v1}"

# Serial port can be changed by setting FLEETTRACKER_PORT before running.
# Find it with:
#   arduino-cli board list
# Current ESP32 DevKit V1 CP2102 default:
#   /dev/cu.usbserial-0001
PORT="${FLEETTRACKER_PORT:-/dev/cu.usbserial-0001}"

# Sketch path can be changed by setting FLEETTRACKER_SKETCH before running.
SKETCH="${FLEETTRACKER_SKETCH:-firmware/FleetTrackerFirmware}"

arduino-cli upload --fqbn "${FQBN}" --port "${PORT}" "${SKETCH}"
