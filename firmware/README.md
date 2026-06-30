# Firmware

The firmware folder contains the embedded software for the GAS Smart Tracker device. It is structured as a modular C++ codebase rather than a single Arduino sketch.

## Source Layout

```text
firmware/
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

## Current Status

This milestone only creates placeholders. No GPIO, UART, SPI, CAN, modem AT command, GNSS, or OBD-II behavior has been implemented yet.
