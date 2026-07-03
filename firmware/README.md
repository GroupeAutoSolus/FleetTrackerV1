# Firmware

The firmware folder contains the embedded software for the GAS Smart Tracker device. It is structured as a modular C++ codebase rather than a single Arduino sketch.

## Source Layout

```text
firmware/
  FleetTrackerFirmware/      Arduino CLI-compatible ESP32 firmware sketch.
  FleetTrackerFirmware/src/application/
                             Application lifecycle and update loop.
  FleetTrackerFirmware/src/build/
                             Firmware build metadata.
  FleetTrackerFirmware/src/configuration/
                             Firmware configuration placeholders.
  FleetTrackerFirmware/src/diagnostics/
                             Boot and runtime diagnostics reporting.
  FleetTrackerFirmware/src/hardware/can/
                             Controller-neutral CAN interface and ESP32 TWAI implementation.
  FleetTrackerFirmware/src/hardware/mcp2515/
                             Deprecated MCP2515 SPI detection module retained for historical reference.
  FleetTrackerFirmware/src/logging/
                             Logger implementation and serial log ownership.
  FleetTrackerFirmware/src/modules/
                             Module interface and module manager foundation.
  FleetTrackerFirmware/src/platform/
                             Arduino/ESP32 timing abstraction.
  FleetTrackerFirmware/src/platform/spi/
                             SPI service foundation for future peripherals, no longer the primary vehicle CAN path.
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

Milestone v0.12.0 adds safe TWAI raw CAN receive scaffolding under `firmware/FleetTrackerFirmware`.

The Arduino `.ino` entry point delegates to `Application::Initialize()` and `Application::Update()`. BuildInfo owns firmware build metadata. Platform owns Arduino timing and ESP32 framework diagnostics calls. SpiService owns SPI bus initialization for non-primary SPI peripherals and historical MCP2515 bench reference. Logger owns serial output. Configuration owns early runtime settings. Diagnostics owns boot/runtime health reporting. Module Manager owns module lifecycle/status coordination. StatusCode owns shared status/error naming. Application owns orchestration.

Default SN65HVD230 wiring plan:

| SN65HVD230 | ESP32 / Later Vehicle Connection |
| --- | --- |
| 3.3V | ESP32 3V3 |
| GND | ESP32 GND |
| CTX | ESP32 GPIO21 |
| CRX | ESP32 GPIO22 |
| CANH | Vehicle CAN High later |
| CANL | Vehicle CAN Low later |

`CanInterface` is the controller-neutral vehicle CAN abstraction. `TwaiCanInterface` is the active implementation registered with Module Manager. It initializes the ESP32 TWAI driver and polls for received TWAI frames without blocking the firmware update loop.

Raw CAN frame logging is controlled by `Configuration::Current().rawCanLoggingEnabled` and defaults to disabled. When enabled, received frames are logged as CAN ID, DLC, and hex data bytes. When no frame is available, no log line is emitted.

Startup logs include:

- `TWAI receive scaffold enabled`
- `CANH/CANL must remain disconnected until vehicle test milestone`

Default ESP32 SPI pin configuration:

- SCK: GPIO18
- MISO/SO: GPIO19
- MOSI/SI: GPIO23
- Default CS for future MCP2515: GPIO5
- Future MCP2515 INT: GPIO4

The boot counter is currently a volatile placeholder. Persistent boot counting will be added later using ESP32 NVS/flash after storage ownership and flash wear policy are defined.

The hardware watchdog is not enabled yet. Future watchdog work should live behind Platform and report state through Diagnostics.

The MCP2515 module remains in the repository for historical Revision A bench reference only. It is deprecated for the main ESP32 vehicle CAN path and is not registered as the active Module Manager vehicle CAN module.

No OBD-II decoding, VIN detection, vehicle communication, modem AT command, GNSS, LTE, backend, or dashboard behavior has been implemented yet. CANH/CANL must remain disconnected until a dedicated vehicle test milestone.

See [BUILD.md](BUILD.md) for compile, upload, and monitor commands.
