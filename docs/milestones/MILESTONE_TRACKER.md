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
| 0.8 | Device-to-cloud prototype | Add API client, telemetry payload format, retry policy, and backend ingestion prototype. | Planned |
| 0.9 | Backend and dashboard MVP | Store telemetry, show vehicle status, show latest location, and expose basic admin views. | Planned |
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
