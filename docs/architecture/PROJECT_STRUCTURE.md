# Project Structure

## Top-Level Folders

| Folder | Responsibility |
| --- | --- |
| `firmware/` | Embedded C++ application for the GAS Smart Tracker device. |
| `backend/` | Cloud-side services for telemetry ingestion, storage, APIs, and command delivery. |
| `dashboard/` | Web dashboard for fleet operators and administrators. |
| `hardware/` | Hardware inventory, schematics, datasheets, wiring, and electrical design notes. |
| `docs/` | Project architecture, roadmap, milestone, and decision documentation. |
| `tests/` | Cross-project integration, system, and acceptance test assets. |
| `tools/` | Project utilities, scripts, generators, and developer automation. |
| `.github/` | Future GitHub workflows, issue templates, pull request templates, and automation. |

## Firmware Folders

| Folder | Responsibility |
| --- | --- |
| `firmware/include/FleetTracker/` | Public module interfaces used across firmware components. |
| `firmware/FleetTrackerFirmware/` | Arduino CLI-compatible sketch folder for the ESP32 DevKit V1 baseline firmware. |
| `firmware/FleetTrackerFirmware/src/application/` | Compiled Arduino application lifecycle and update loop. |
| `firmware/FleetTrackerFirmware/src/configuration/` | Compiled Arduino configuration placeholders. |
| `firmware/FleetTrackerFirmware/src/diagnostics/` | Compiled Arduino diagnostics service for boot and runtime health reporting. |
| `firmware/FleetTrackerFirmware/src/logging/` | Compiled Arduino logger and serial output ownership. |
| `firmware/FleetTrackerFirmware/src/modules/` | Compiled Arduino module lifecycle interface and module manager foundation. |
| `firmware/FleetTrackerFirmware/src/platform/` | Compiled Arduino platform abstraction for timing and future framework boundaries. |
| `firmware/FleetTrackerFirmware/src/status/` | Compiled Arduino status/error code conventions. |
| `firmware/src/` | Firmware implementation files. |
| `firmware/src/app/` | Application lifecycle, orchestration, and top-level coordination. |
| `firmware/src/modules/gps/` | GNSS acquisition, fix state, location, speed, heading, and time handling. |
| `firmware/src/modules/lte_modem/` | Cellular modem control, registration, signal state, data sessions, and recovery. |
| `firmware/src/modules/can_bus/` | CAN controller abstraction, bus state, frame send/receive, and error handling. |
| `firmware/src/modules/obd2/` | OBD-II request/response handling and vehicle parameter extraction. |
| `firmware/src/modules/api_client/` | Device-to-cloud API client, telemetry publishing, and future command polling. |
| `firmware/src/modules/configuration/` | Build-time and runtime configuration defaults and validation. |
| `firmware/src/modules/logging/` | Logging API, severity levels, and output sinks. |
| `firmware/src/modules/utilities/` | Shared utility functions that do not own hardware resources. |
| `firmware/test/` | Firmware unit and module tests. |

## Source File Responsibilities

| File | Responsibility |
| --- | --- |
| `firmware/src/main.cpp` | Minimal firmware entry point that delegates work to `Application`. |
| `firmware/FleetTrackerFirmware/FleetTrackerFirmware.ino` | Minimal Arduino CLI sketch that delegates to `Application::Initialize()` and `Application::Update()`. |
| `firmware/FleetTrackerFirmware/src/application/Application.h` | Application layer interface. |
| `firmware/FleetTrackerFirmware/src/application/Application.cpp` | Application startup sequence and heartbeat update loop. |
| `firmware/FleetTrackerFirmware/src/configuration/Configuration.h` | Configuration settings interface and placeholder fields. |
| `firmware/FleetTrackerFirmware/src/configuration/Configuration.cpp` | Current firmware configuration placeholder values. |
| `firmware/FleetTrackerFirmware/src/diagnostics/Diagnostics.h` | Diagnostics service interface. |
| `firmware/FleetTrackerFirmware/src/diagnostics/Diagnostics.cpp` | Boot report and heartbeat diagnostics logging. |
| `firmware/FleetTrackerFirmware/src/logging/Logger.h` | Logger interface for info, warning, error, and debug messages. |
| `firmware/FleetTrackerFirmware/src/logging/Logger.cpp` | Serial-backed logger implementation. |
| `firmware/FleetTrackerFirmware/src/modules/Module.h` | Future firmware module lifecycle interface. |
| `firmware/FleetTrackerFirmware/src/modules/ModuleManager.h` | Module manager interface. |
| `firmware/FleetTrackerFirmware/src/modules/ModuleManager.cpp` | Module manager placeholder implementation and health summary. |
| `firmware/FleetTrackerFirmware/src/platform/Platform.h` | Platform abstraction interface for initialization, milliseconds, and delay. |
| `firmware/FleetTrackerFirmware/src/platform/Platform.cpp` | Arduino-backed platform implementation. |
| `firmware/FleetTrackerFirmware/src/status/StatusCode.h` | Shared firmware status/error code interface. |
| `firmware/FleetTrackerFirmware/src/status/StatusCode.cpp` | Shared firmware status/error code string conversion. |
| `firmware/BUILD.md` | Firmware compile, upload, monitor, and board configuration documentation. |
| `firmware/include/FleetTracker/Application.hpp` | Public application lifecycle interface. |
| `firmware/src/app/Application.cpp` | Application initialization and scheduler-loop placeholder. |
| `firmware/include/FleetTracker/Gps.hpp` | Public GNSS module interface. |
| `firmware/src/modules/gps/Gps.cpp` | GNSS module implementation placeholder. |
| `firmware/include/FleetTracker/LteModem.hpp` | Public LTE modem module interface. |
| `firmware/src/modules/lte_modem/LteModem.cpp` | LTE modem module implementation placeholder. |
| `firmware/include/FleetTracker/CanBus.hpp` | Public CAN bus module interface. |
| `firmware/src/modules/can_bus/CanBus.cpp` | CAN bus module implementation placeholder. |
| `firmware/include/FleetTracker/Obd2.hpp` | Public OBD-II module interface. |
| `firmware/src/modules/obd2/Obd2.cpp` | OBD-II module implementation placeholder. |
| `firmware/include/FleetTracker/ApiClient.hpp` | Public cloud API client interface. |
| `firmware/src/modules/api_client/ApiClient.cpp` | API client implementation placeholder. |
| `firmware/include/FleetTracker/Configuration.hpp` | Public configuration interface. |
| `firmware/src/modules/configuration/Configuration.cpp` | Configuration implementation placeholder. |
| `firmware/include/FleetTracker/Logging.hpp` | Public logging interface. |
| `firmware/src/modules/logging/Logging.cpp` | Logging implementation placeholder. |
| `firmware/include/FleetTracker/Utilities.hpp` | Public shared utility declarations. |
| `firmware/src/modules/utilities/Utilities.cpp` | Shared utility implementation placeholder. |

## Non-Firmware Placeholder Files

| File | Responsibility |
| --- | --- |
| `backend/README.md` | Defines future backend responsibilities. |
| `backend/src/.gitkeep` | Preserves the backend source folder until implementation begins. |
| `backend/tests/.gitkeep` | Preserves the backend test folder until implementation begins. |
| `dashboard/README.md` | Defines future dashboard responsibilities. |
| `dashboard/src/.gitkeep` | Preserves the dashboard source folder until implementation begins. |
| `dashboard/tests/.gitkeep` | Preserves the dashboard test folder until implementation begins. |
| `hardware/README.md` | Defines hardware documentation responsibilities. |
| `hardware/inventory/HARDWARE_INVENTORY.md` | Maintained list of current hardware and engineering notes. |
| `hardware/schematics/README.md` | Placeholder for wiring diagrams and schematic artifacts. |
| `hardware/datasheets/README.md` | Placeholder for datasheets and vendor references. |
| `docs/README.md` | Defines documentation folder responsibilities. |
| `docs/JOURNAL.md` | Chronological project decisions and milestone notes. |
| `docs/development/ARDUINO_CLI_SETUP.md` | Manual Arduino CLI and ESP32 Arduino core setup instructions for macOS. |
| `docs/product/GAS_SMART_TRACKER_PRODUCT_SPEC.md` | Product purpose, users, prototype goals, commercial goals, telemetry scope, GAS-specific features, and V1 exclusions. |
| `docs/product/DATA_MODEL_DRAFT.md` | Early draft of core GAS Smart Tracker product entities and domain identifiers. |
| `docs/architecture/PROJECT_STRUCTURE.md` | Explains every folder and source file created in Version 0.1. |
| `docs/architecture/FIRMWARE_ARCHITECTURE.md` | Defines firmware module boundaries and design principles. |
| `docs/roadmap/DEVELOPMENT_ROADMAP.md` | Long-term development roadmap. |
| `docs/milestones/MILESTONE_TRACKER.md` | Version 0.1 through Version 1.0 milestone tracker. |
| `tests/README.md` | Defines system-level test responsibilities. |
| `tests/firmware/.gitkeep` | Preserves system firmware test folder. |
| `tests/backend/.gitkeep` | Preserves system backend test folder. |
| `tests/dashboard/.gitkeep` | Preserves system dashboard test folder. |
| `tools/README.md` | Defines the purpose of the tools folder. |
| `tools/firmware/compile.sh` | Arduino CLI compile helper for the firmware sketch. |
| `tools/firmware/upload.sh` | Arduino CLI upload helper using a configured serial port. |
| `tools/firmware/monitor.sh` | Arduino CLI serial monitor helper using a configured serial port and baud rate. |
| `.github/README.md` | Defines the purpose of future GitHub automation configuration. |
