# Milestone Tracker

| Version | Milestone | Scope | Status |
| --- | --- | --- | --- |
| 0.1 | Project foundation | Repository structure, placeholders, documentation, roadmap, hardware inventory, milestone tracker. | Complete |
| 0.2 | GAS product architecture update | Position product as GAS Smart Tracker, add product spec, data model draft, journal, tools folder, and GitHub placeholder folder. | Complete |
| 0.3 | Firmware build baseline | Use Arduino CLI with ESP32 Arduino core, add setup docs, add minimal serial heartbeat sketch, and add helper scripts. | Complete |
| 0.4 | ESP32 firmware boot test | Compile the baseline firmware, upload it to ESP32 DevKit V1, and verify serial boot and heartbeat output. | Complete |
| 0.5 | Firmware platform layer and logging foundation | Add Application, Platform, Logger, and Configuration foundation while keeping the Arduino entry point small. | Complete |
| 0.6 | Diagnostics and module manager | Add diagnostics reporting and module manager foundation while staying in Phase 1. | Complete |
| 0.7 | Phase 1 hardening | Add status/error conventions, improved module status formatting, boot counter placeholder, watchdog planning, and clearer heartbeat diagnostics. | Complete |
| 0.8 | SPI platform service foundation | Add SPI abstraction, default ESP32 SPI pin configuration, and MCP2515 wiring documentation without CAN logic. | Complete |
| 0.9 | First external hardware detection | Add BuildInfo and verify ESP32-to-MCP2515 SPI communication without CAN frame reading. | Complete |
| 0.10 | MCP2515 electrical validation | Harden MCP2515 SPI detection with retry logic and detailed electrical validation logs before applying VCC. | Complete |
| 0.10.1 | FleetLink naming and hardware revision update | Introduce FleetLink device naming, document hardware revisions, and choose ESP32 TWAI + SN65HVD230 for the main CAN path. | Complete |
| 0.11 | FleetLink TWAI CAN architecture pivot | Register ESP32 TWAI + SN65HVD230 as the active vehicle CAN foundation while keeping MCP2515/SPI historical. | Complete |
| 0.11-hw | FleetLink Revision B hardware architecture | Document the official Revision B wiring plan, safety warnings, and bench-test sequence before more firmware behavior. | Complete |
| 0.12 | TWAI raw CAN receive scaffold | Add safe nonblocking TWAI receive polling and default-disabled raw frame logging without vehicle connection or OBD-II decoding. | Complete |
| 1.0 | Commercial baseline | Stable firmware/backend/dashboard release with documentation and support procedures. | Planned |

## Version 0.1 Acceptance Criteria

- Top-level folders exist: `firmware`, `backend`, `dashboard`, `hardware`, `docs`, and `tests`.
- Firmware source tree exists with independent module folders.
- Placeholder source and header files exist for each planned firmware module.
- README documentation exists at the project root and in major folders.
- Development roadmap exists.
- Hardware inventory exists.
- Milestone tracker covers Version 0.1 through Version 1.0.
- No hardware-specific implementation has been added.

## Version 0.2 Acceptance Criteria

- Project is clearly positioned as GAS Smart Tracker by Groupe Auto Solus.
- `tools/` exists with documentation.
- `.github/` exists with documentation.
- `docs/JOURNAL.md` exists.
- Product spec exists under `docs/product/`.
- Data model draft exists under `docs/product/`.
- Architecture documentation includes GAS Smart Tracker domain concepts.
- No firmware logic, backend code, or dashboard code has been added.

## Version 0.3 Acceptance Criteria

- Arduino CLI is selected as the initial firmware build system.
- ESP32 Arduino core and ESP32 DevKit V1 FQBN are documented.
- Minimal Arduino sketch exists under `firmware/FleetTrackerFirmware`.
- Sketch initializes serial at `115200`.
- Sketch prints `GAS Smart Tracker booting...`.
- Sketch prints a heartbeat every 2 seconds.
- Sketch does not use SIM7600, CAN, OBD-II, or external hardware.
- Helper scripts exist for compile, upload, and monitor.
- Manual setup commands are documented.
- No backend code or dashboard code has been added.

## Version 0.4 Acceptance Criteria

- Working directory is confirmed as `/Users/Nik/Documents/FleetTrackerV1`.
- Arduino CLI project structure is verified.
- ESP32 DevKit V1 FQBN is verified as `esp32:esp32:esp32doit-devkit-v1`.
- Default helper-script serial port is `/dev/cu.usbserial-0001`.
- Baseline firmware compiles successfully.
- Firmware uploads successfully to the ESP32.
- Serial monitor at `115200` shows `GAS Smart Tracker booting...`.
- Serial monitor shows `GAS Smart Tracker heartbeat` every 2 seconds.
- No SIM7600, CAN, or OBD-II code has been added.

## Version 0.5 Acceptance Criteria

- Firmware is organized into Application, Service, Platform, Arduino Framework, and ESP32 Hardware layers.
- Main Arduino sketch remains small and delegates to Application.
- `Platform::Initialize()`, `Platform::Millis()`, and `Platform::Delay(milliseconds)` exist.
- `Logger::Initialize()`, `Logger::Info()`, `Logger::Warn()`, `Logger::Error()`, and `Logger::Debug()` exist.
- Only Logger directly calls `Serial.begin`, `Serial.print`, or `Serial.println`.
- Application exposes `Application::Initialize()` and `Application::Update()`.
- Configuration includes placeholders for firmware version, device ID, heartbeat interval, future APN, and future server URL.
- Firmware logs boot, firmware version, platform initialization, configuration loading, application initialization, and heartbeat messages.
- No SIM7600, CAN, OBD-II, GPS, LTE, backend, or dashboard code has been added.
- Firmware compiles successfully with the existing helper script.

## Version 0.6 Acceptance Criteria

- Project phases are documented as Foundation, Communications, Vehicle, Backend, Dashboard, and Production.
- Module Manager foundation exists.
- Future module lifecycle shape is documented as `Initialize()`, `Update()`, `GetName()`, `GetStatus()`, and `GetLastError()`.
- Diagnostics reports firmware version, device ID, uptime, free heap memory, reset reason, boot status, and module status summary placeholder.
- Application boot flow logs boot, firmware version, device ID, reset reason, free heap memory, platform initialized, configuration loaded, module manager initialized, diagnostics initialized, and application initialized.
- Heartbeat logs include uptime, free heap memory, and module health summary placeholder.
- Logger remains the only code that uses Serial directly.
- Platform remains the only code that uses Arduino timing directly.
- No SIM7600, GPS, LTE, CAN, OBD-II, backend, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.7 Acceptance Criteria

- Firmware status/error code convention exists with `OK`, `WARNING`, `ERROR`, `NOT_INITIALIZED`, `TIMEOUT`, and `HARDWARE_UNAVAILABLE`.
- Module status formatting includes module name, status, last error, initialized yes/no, and registered module count placeholder.
- Boot counter placeholder exists without persistent storage.
- Documentation explains future persistent boot count via ESP32 NVS/flash.
- Documentation explains future watchdog strategy without enabling the hardware watchdog.
- Heartbeat diagnostics are easier to read and include uptime, free heap, and module health.
- Logger remains the only code that uses Serial directly.
- Platform remains the only code that uses Arduino timing directly.
- Application remains responsible for orchestration.
- No SIM7600, GPS, LTE, CAN, OBD-II, backend, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.8 Acceptance Criteria

- SPI service/platform abstraction exists.
- Default ESP32 SPI pin configuration is defined: SCK GPIO18, MISO/SO GPIO19, MOSI/SI GPIO23, CS GPIO5, future MCP2515 INT GPIO4.
- Hardware documentation maps future MCP2515 header pins to ESP32 pins.
- Hardware documentation warns that MCP2515 VCC and logic compatibility must be validated before wiring.
- Application boot flow initializes SPI service.
- Startup logs include SPI service initialization and SPI pin configuration.
- Logger remains the only code that uses Serial directly.
- Platform remains the owner of Arduino timing calls.
- No MCP2515 driver logic, CAN frame reading, OBD-II, SIM7600, GPS, LTE, backend, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.9 Acceptance Criteria

- BuildInfo subsystem exists.
- Startup logs include firmware version, git commit placeholder, build date, build time, board, hardware, and build type.
- Previous hardcoded firmware version is removed from Configuration.
- MCP2515 is managed as the first hardware module in Module Manager.
- MCP2515 SPI detection attempts controller communication.
- Firmware continues running whether detection succeeds or fails.
- Hardware validation checklist documents operating voltage, logic compatibility, SPI wiring, and common ground.
- No CAN frame reading, OBD-II, vehicle communication, SIM7600, GPS, LTE, backend, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.10 Acceptance Criteria

- MCP2515 implementation has been reviewed and prepared for immediate detection once VCC is connected.
- MCP2515 detection attempts run three times.
- Each detection attempt is logged.
- Detailed errors report SPI initialization failure, MCP2515 timeout, MCP2515 not responding, and unknown SPI device.
- Firmware continues booting when MCP2515 detection fails.
- MCP2515 is not required to be present or powered.
- No CAN functionality, OBD-II, SIM7600, GPS, LTE, backend, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.10.1 Acceptance Criteria

- Documentation introduces FleetLink as the physical in-vehicle telematics device.
- Documentation clarifies FleetTracker as the broader platform.
- Documentation clarifies GAS Smart Tracker as the product initiative.
- Hardware revisions are documented:
  - Revision A: ESP32 + MCP2515 + SIM7600 + buck converter.
  - Revision B: ESP32 + SN65HVD230 + SIM7600 + buck converter.
  - Revision C: future custom PCB.
- Engineering decision is documented: use ESP32 built-in TWAI + SN65HVD230 instead of MCP2515 for the main vehicle CAN path.
- MCP2515 is marked deprecated for the ESP32 prototype main CAN path due to 5V logic compatibility risk.
- No firmware behavior, SIM7600 code, or CAN code has been added.

## Version 0.11 Acceptance Criteria

- Working directory is confirmed as `/Users/Nik/Documents/FleetTrackerV1`.
- Firmware version is `0.11.0-dev`.
- `CanInterface` exists as the controller-neutral CAN abstraction.
- `TwaiCanInterface` exists as the ESP32 TWAI implementation.
- `TwaiCanInterface` supports `Initialize()`, `Update()`, `GetName()`, `GetStatus()`, `GetLastError()`, and `IsInitialized()`.
- `TwaiCanInterface` is registered with Module Manager as the active vehicle CAN module.
- MCP2515 files remain in the repository for historical Revision A bench reference.
- `Mcp2515Module` is not registered as the active vehicle CAN module.
- SPI service remains in the repository but is documented as no longer the primary vehicle CAN path.
- Planned SN65HVD230 wiring is documented: 3.3V to ESP32 3V3, GND to ESP32 GND, CTX to GPIO21, CRX to GPIO22, CANH to vehicle CAN High later, and CANL to vehicle CAN Low later.
- Startup logs include TWAI initialization, TX GPIO 21, RX GPIO 22, and success or failure.
- Firmware continues running if TWAI initialization fails.
- No vehicle connection, CAN frame reading, OBD-II decoding, SIM7600 code, GPS code, LTE code, backend code, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.

## Version 0.11 Hardware Architecture Addendum Acceptance Criteria

- FleetLink Revision B hardware is documented as ESP32 DevKit V1, SN65HVD230 3.3V CAN transceiver, SIM7600G-H LTE/GNSS module, 12V to 5V buck converter, OBD-II pigtail connector, and breadboard prototype power distribution.
- Full wiring plan documents OBD-II power into the buck converter, breadboard 5V/GND rails, ESP32 power, SN65HVD230 power/TWAI/CAN pins, and SIM7600 power/UART pins.
- Safety warnings state not to connect OBD-II power before USB bench tests, not to connect CANH/CANL before the vehicle test milestone, that ESP32 GPIO is not 5V tolerant, and that all modules need common ground.
- Bench-test sequence is documented: ESP32 by USB only, SN65HVD230 from ESP32 3V3, TWAI init test, OBD-II CANH/CANL test with no OBD power, standalone buck converter test, and full OBD power test later.
- No firmware behavior, CAN code, SIM7600 code, GPS code, LTE code, backend code, or dashboard code has been added.

## Version 0.12 Acceptance Criteria

- Working directory is confirmed as `/Users/Nik/Documents/FleetTrackerV1`.
- Firmware version is `0.12.0-dev`.
- `TwaiCanInterface::Update()` polls TWAI receive with no blocking wait.
- No-frame receive cycles do not emit log spam.
- Raw CAN frame logging is controlled by a configurable flag and defaults to disabled.
- When raw CAN logging is enabled and a frame is received, logs include CAN ID, DLC, and data bytes in hex.
- Startup logs include `TWAI receive scaffold enabled`.
- Startup logs include `CANH/CANL must remain disconnected until vehicle test milestone`.
- Firmware continues running normally when no CAN bus is connected.
- CANH/CANL remain disconnected for this milestone.
- No OBD-II PID decoding, VIN detection, SIM7600 code, GPS code, LTE code, backend code, or dashboard code has been added.
- Firmware compiles successfully with `./tools/firmware/compile.sh`.
