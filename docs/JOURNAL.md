# Project Journal

## 2026-06-30 - Milestone 0.1: Repository Foundation

Created the initial FleetTracker project scaffold with separate folders for firmware, backend, dashboard, hardware, documentation, and tests. Firmware was organized as a modular C++ source tree with placeholders only.

## 2026-06-30 - Milestone 0.2: GAS Product Architecture Update

Confirmed the product direction as GAS Smart Tracker by Groupe Auto Solus. Updated documentation to position the project around a Québec mobile mechanic and fleet service business building a custom telematics platform for commercial fleet customers.

Added initial product documentation, early data model draft, project journal, tools folder, and GitHub configuration placeholder folder.

## 2026-06-30 - Milestone 0.3: Firmware Build Baseline

Selected Arduino CLI with the ESP32 Arduino core as the initial firmware build system for ESP32 DevKit V1 / ESP32-WROOM-32 prototype development.

Added manual Arduino CLI setup documentation, firmware build documentation, a minimal serial heartbeat sketch, and helper scripts for compile, upload, and serial monitoring.

## 2026-06-30 - Milestone 0.4: ESP32 Firmware Boot Test

macOS detects the ESP32 DevKit V1 on `/dev/cu.usbserial-0001`. The boot-test milestone verifies that the Arduino CLI configuration can compile and upload the baseline firmware, then confirms serial boot and heartbeat output at `115200` baud.

Validation completed successfully with Arduino CLI. The firmware compiled, uploaded to the ESP32, and serial output showed `GAS Smart Tracker booting...` followed by repeated `GAS Smart Tracker heartbeat` messages.

## 2026-07-01 - Milestone 0.5: Firmware Platform Layer and Logging Foundation

Refactored the Arduino firmware entry point into a small delegating sketch. Added Application, Platform, Logger, and Configuration foundation files under the Arduino CLI sketch source tree.

The firmware now logs boot, firmware version, platform initialization, configuration loading, application initialization, and heartbeat messages through Logger. Platform owns Arduino timing calls. No SIM7600, CAN, OBD-II, GPS, LTE, backend, or dashboard behavior was added.

## 2026-07-01 - Milestone v0.6.0: Diagnostics and Module Manager

Added Project Phases to documentation: Foundation, Communications, Vehicle, Backend, Dashboard, and Production. The project remains in Phase 1 - Foundation.

Added Diagnostics and Module Manager foundations. Diagnostics reports firmware version, device ID, uptime, free heap memory, reset reason, boot status, and module health placeholder. Module Manager defines the future module lifecycle shape without registering hardware modules.

## 2026-07-01 - Milestone v0.7.0: Phase 1 Hardening

Added lightweight firmware status/error code conventions and improved Module Manager status formatting. Added a volatile boot counter placeholder and documented that persistent boot count should later use ESP32 NVS/flash.

Documented future watchdog strategy without enabling hardware watchdog behavior. Improved heartbeat diagnostics formatting while keeping Serial access isolated to Logger and Arduino timing isolated to Platform.
