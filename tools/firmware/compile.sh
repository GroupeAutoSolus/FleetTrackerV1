#!/usr/bin/env bash
set -euo pipefail

# Board FQBN can be changed by setting FLEETTRACKER_FQBN before running.
# ESP32 DevKit V1 default:
#   esp32:esp32:esp32doit-devkit-v1
FQBN="${FLEETTRACKER_FQBN:-esp32:esp32:esp32doit-devkit-v1}"

# Sketch path can be changed by setting FLEETTRACKER_SKETCH before running.
SKETCH="${FLEETTRACKER_SKETCH:-firmware/FleetTrackerFirmware}"

arduino-cli compile --fqbn "${FQBN}" "${SKETCH}"
