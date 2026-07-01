# Firmware

The firmware folder contains the embedded software for the GAS Smart Tracker device. It is structured as a modular C++ codebase rather than a single Arduino sketch.

## Source Layout

```text
firmware/
  FleetTrackerFirmware/      Arduino CLI-compatible ESP32 firmware sketch.
  FleetTrackerFirmware/src/application/
                             Application lifecycle and update loop.
  FleetTrackerFirmware/src/configuration/
                             Firmware configuration placeholders.
  FleetTrackerFirmware/src/diagnostics/
                             Boot and runtime diagnostics reporting.
  FleetTrackerFirmware/src/logging/
                             Logger implementation and serial log ownership.
  FleetTrackerFirmware/src/modules/
                             Module interface and module manager foundation.
  FleetTrackerFirmware/src/platform/
                             Arduino/ESP32 timing abstraction.
  FleetTrackerFirmware/src/status/
                             Shared firmware status/error code conventions.
  include/FleetTracker/      Public firmware interfaces shared across modules.
  src/app/                   Application orchestration and lifecycle ownership.
  src/modules/gps/           GNSS position, time, and fix-state module.
  src/modules/lte_modem/     Cellular modem command, network, and data-session module.
  src/modules/can_bus/       CAN controller abstraction and frame transport module.
  src/modules/obd2/          Vehicle diagnostic protocol module built above CAN.
  src/modules/api_client/    Cloud API publishing and command transport module.
  src/modules/configuration/ Runtime and build-time configuration module.
  src/modules/logging/       Logging interface and log routing module.
  src/modules/utilities/     Shared helpers with no hardware ownership.
  test/                      Firmware-focused unit and module tests.
```

## Design Rules

- Hardware access must stay behind module boundaries.
- Application code coordinates modules but does not own low-level protocol details.
- Public interfaces should be stable and small.
- Modules should be testable without physical hardware where practical.
- Configuration should be centralized and explicit.
- Logging should be available to all modules without coupling them to a transport.
- No module except Logger may call `Serial.print`, `Serial.println`, or `Serial.begin` directly.
- No module outside Platform should call Arduino `delay()` or `millis()` directly.

## Current Status

Milestone v0.7.0 hardens the Phase 1 firmware foundation under `firmware/FleetTrackerFirmware`.

The Arduino `.ino` entry point delegates to `Application::Initialize()` and `Application::Update()`. Platform owns Arduino timing and ESP32 framework diagnostics calls, Logger owns serial output, Configuration owns early firmware settings, Diagnostics owns boot/runtime health reporting, Module Manager owns future module lifecycle/status coordination, StatusCode owns shared status/error naming, and Application owns orchestration.

The boot counter is currently a volatile placeholder. Persistent boot counting will be added later using ESP32 NVS/flash after storage ownership and flash wear policy are defined.

The hardware watchdog is not enabled yet. Future watchdog work should live behind Platform and report state through Diagnostics.

No GPIO, SPI, CAN, modem AT command, GNSS, LTE, or OBD-II behavior has been implemented yet.

See [BUILD.md](BUILD.md) for compile, upload, and monitor commands.
