# Development Roadmap

## Phase 1: Architecture and Repository Foundation

- Establish project structure.
- Define firmware module boundaries.
- Document current hardware inventory.
- Create roadmap and milestone tracker.
- Keep implementation hardware-neutral.

## Phase 1.5: GAS Product Architecture

- Position the product as GAS Smart Tracker by Groupe Auto Solus.
- Define early commercial fleet service domain concepts.
- Draft product purpose, target users, prototype goals, and commercial goals.
- Draft early entities for customers, fleets, vehicles, devices, technicians, trips, telemetry events, maintenance alerts, and diagnostic codes.

## Phase 2: Firmware Build System and Coding Standards

- Use Arduino CLI with the ESP32 Arduino core as the initial firmware build environment.
- Add compiler settings and formatting rules.
- Add static analysis and unit test scaffolding.
- Define embedded coding standards.

## Phase 3: Hardware Bring-Up

- Validate ESP32 development board workflow.
- Validate power supply assumptions on bench power.
- Document wiring and pin map.
- Bring up modem, GNSS, CAN controller, and OBD-II separately.

## Phase 4: Telemetry Prototype

- Read GNSS data.
- Establish LTE data connection.
- Read selected OBD-II PIDs.
- Publish prototype telemetry payloads.
- Add local logging and recovery behavior.

## Phase 5: Backend Prototype

- Create ingestion API.
- Store device telemetry.
- Add device identity and authentication model.
- Add basic command/config delivery.

## Phase 6: Dashboard Prototype

- Display vehicles and latest telemetry.
- Show location history.
- Show diagnostic values.
- Add basic device administration.

## Phase 7: Field-Test Prototype

- Replace breadboard wiring with safer prototype interconnect.
- Add watchdog and power recovery behavior.
- Add telemetry buffering during network outages.
- Test in controlled vehicle conditions.

## Phase 8: Production Planning

- Define production hardware requirements.
- Review automotive electrical protection.
- Plan enclosure, connectors, certifications, and manufacturing.
- Harden firmware update and provisioning flows.

## Phase 9: Version 1.0 Release

- Ship stable device firmware, backend, and dashboard baseline.
- Document installation, operation, diagnostics, and maintenance.
- Establish release, support, and incident processes.
