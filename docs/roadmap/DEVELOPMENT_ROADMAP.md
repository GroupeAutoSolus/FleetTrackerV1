# Development Roadmap

## Project Phases

| Phase | Focus |
| --- | --- |
| Phase 1 - Foundation | Firmware structure, build system, logging, diagnostics, module manager, project documentation, and development workflow. |
| Phase 2 - Communications | LTE modem, network registration, data sessions, API transport, command polling, and connectivity recovery. |
| Phase 3 - Vehicle | ESP32 TWAI, SN65HVD230 CAN transceiver, OBD-II, vehicle telemetry, diagnostic trouble codes, ignition state, trip events, and odometer sources. |
| Phase 4 - Backend | Telemetry ingestion, device identity, customer/fleet/vehicle records, command delivery, and alert processing. |
| Phase 5 - Dashboard | Operator UI, fleet views, vehicle details, diagnostics, alerts, and technician workflows. |
| Phase 6 - Production | Hardware hardening, provisioning, OTA, enclosure, certifications, manufacturing, support, and field operations. |

## Phase 1 - Foundation

- Establish project structure.
- Position the product as GAS Smart Tracker by Groupe Auto Solus.
- Define firmware layer boundaries.
- Use Arduino CLI with the ESP32 Arduino core as the initial firmware build environment.
- Validate ESP32 compile, upload, and serial boot behavior.
- Add Application, Platform, Logger, Configuration, Diagnostics, and Module Manager foundations.
- Add lightweight status/error code conventions.
- Add boot counter placeholder and watchdog strategy documentation.
- Add SPI platform service foundation before vehicle hardware modules.
- Document current hardware inventory.
- Keep hardware-specific modules out of scope until the foundation is stable.

## Phase 2 - Communications

- Add BuildInfo firmware metadata.
- Keep MCP2515 limited to deprecated Revision A bench experiments unless explicitly revisited.
- Pivot active FleetLink vehicle CAN foundation to ESP32 TWAI plus SN65HVD230.
- Add safe TWAI raw receive scaffolding with default-disabled raw frame logs.
- Add LTE modem service boundaries.
- Validate SIM7600 serial communication.
- Validate SIM state, signal quality, network registration, and data sessions.
- Add API transport placeholders before real backend integration.
- Add connectivity recovery and diagnostic logging.

## Phase 3 - Vehicle

- Validate SN65HVD230 wiring and ESP32 TWAI configuration.
- Add CAN bus service boundaries around ESP32 TWAI.
- Add controlled CAN frame receive validation after a dedicated vehicle or bench-bus test milestone.
- Add OBD-II service boundaries.
- Read selected vehicle PIDs in controlled tests.
- Add diagnostic trouble code, ignition state, trip event, and odometer source handling.

## Phase 4 - Backend

- Create ingestion API.
- Store device telemetry.
- Add customer, fleet, vehicle, and device records.
- Add device identity and authentication model.
- Add command/config delivery.
- Add maintenance and battery alert processing.

## Phase 5 - Dashboard

- Display fleet and vehicle status.
- Show latest location and vehicle detail views.
- Show diagnostic values and maintenance alerts.
- Add device administration.
- Add technician workflow support.

## Phase 6 - Production

- Define production hardware requirements.
- Review automotive electrical protection.
- Plan enclosure, connectors, certifications, and manufacturing.
- Harden firmware update and provisioning flows.
- Establish installation, support, and incident processes.
