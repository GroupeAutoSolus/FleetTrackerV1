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

## 2026-07-01 - Milestone v0.8.0: SPI Platform Service Foundation

Added a clean SPI platform service foundation before MCP2515-specific CAN work. The SPI service initializes the ESP32 SPI bus and reports the default pin configuration: SCK GPIO18, MISO/SO GPIO19, MOSI/SI GPIO23, CS GPIO5, and future MCP2515 INT GPIO4.

Documented the planned MCP2515 header mapping and added a hardware warning that VCC and logic-level compatibility must be validated before wiring. No MCP2515 driver logic, CAN frame handling, OBD-II, SIM7600, GPS, LTE, backend, or dashboard behavior was added.

## 2026-07-01 - Milestone v0.9.0: First External Hardware Detection

Phase 2 begins with BuildInfo and MCP2515 SPI detection. BuildInfo now owns firmware build metadata including firmware version, git commit placeholder, build date, build time, board, hardware, and build type.

MCP2515 is registered as the first hardware module under Module Manager. The module performs SPI-only controller detection and reports success or failure without reading CAN frames, connecting to a vehicle, or implementing OBD-II.

## 2026-07-01 - Milestone v0.10.0: MCP2515 Electrical Validation

Prepared the MCP2515 detection path for bench validation once VCC is connected. Detection now attempts communication three times, logs each attempt, logs CANSTAT debug values, and reports SPI initialization failure, timeout, not responding, or unknown device conditions.

The firmware continues booting if MCP2515 detection fails, so the module is not required to be present or powered. No CAN frame reading, OBD-II, SIM7600, GPS, LTE, backend, or dashboard behavior was added.

## 2026-07-01 - Milestone v0.10.1: FleetLink Naming and Hardware Revision Update

Introduced FleetLink as the physical in-vehicle telematics device name. FleetTracker now refers to the broader platform, including firmware, backend, dashboard, mobile tools, and fleet management system. GAS Smart Tracker remains the product initiative for Groupe Auto Solus.

Documented FleetLink hardware revisions. Revision A uses ESP32 + MCP2515 + SIM7600 + buck converter. Revision B uses ESP32 + SN65HVD230 + SIM7600 + buck converter. Revision C is a future custom PCB.

Documented the engineering decision to use ESP32 built-in TWAI plus SN65HVD230 instead of MCP2515 for the main vehicle CAN path. MCP2515 is deprecated for the ESP32 prototype main CAN path due to 5V logic compatibility risk.

## 2026-07-02 - Milestone v0.11.0: FleetLink TWAI CAN Architecture Pivot

Pivoted the active FleetLink vehicle CAN firmware architecture from MCP2515/SPI to ESP32 built-in TWAI plus SN65HVD230. Added a controller-neutral `CanInterface` and an ESP32-specific `TwaiCanInterface`.

`TwaiCanInterface` is registered with Module Manager as the active vehicle CAN module. It logs the planned TX/RX pins, initializes the TWAI driver, reports success or failure, and allows firmware boot to continue if initialization fails.

MCP2515 files and the SPI service remain in the repository for historical Revision A bench reference, but MCP2515 is no longer registered as the active CAN path. No vehicle connection, CAN frame reading, OBD-II decoding, SIM7600 code, GPS code, LTE code, backend code, or dashboard code was added.

## 2026-07-02 - Milestone v0.12.0: TWAI Raw CAN Receive Scaffold

Added safe TWAI receive polling to `TwaiCanInterface::Update()` without connecting FleetLink CANH/CANL to a vehicle and without decoding OBD-II.

Raw CAN frame logging is configurable through `rawCanLoggingEnabled` and defaults to disabled. When enabled, received frames are logged with CAN ID, DLC, and data bytes in hex. When no frame is available, no log line is emitted.

Startup now warns that the TWAI receive scaffold is enabled and that CANH/CANL must remain disconnected until the vehicle test milestone. No OBD-II PID decoding, VIN detection, SIM7600, GPS, LTE, backend, or dashboard behavior was added.
