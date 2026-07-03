# GAS Smart Tracker

GAS Smart Tracker is a custom telematics product initiative by Groupe Auto Solus for commercial fleet service customers in Québec.

FleetTracker is the broader platform: firmware, backend, dashboard, mobile tools, and the fleet management system.

FleetLink is the physical in-vehicle telematics device installed in a vehicle.

The project starts with an ESP32-based FleetLink prototype and is organized so the firmware, backend, dashboard, hardware documentation, and tests can evolve toward production without a major restructure.

The product direction is no longer a generic fleet tracker. GAS Smart Tracker is being designed around the operating needs of Groupe Auto Solus, a mobile mechanic and fleet service business. The long-term goal is to support customer fleet visibility, proactive maintenance, diagnostic insight, and technician workflows.

The project is currently in Phase 1, focused on firmware foundation and architecture. Hardware-specific services will be added in later phases.

## Repository Layout

```text
FleetTrackerV1/
  firmware/   Embedded firmware for the telematics device.
  backend/    Server-side ingestion, storage, APIs, and operations services.
  dashboard/  Web dashboard for fleet operators and system administrators.
  hardware/   Hardware inventory, schematics, wiring notes, and datasheets.
  docs/       Architecture, roadmap, milestone, and design documentation.
  tests/      Cross-project integration and system-level test assets.
  tools/      Project utilities and developer automation.
  .github/   Future GitHub workflows, templates, and automation.
```

## Product Architecture

GAS Smart Tracker uses a business domain model centered on:

- `customer_id`
- `fleet_id`
- `vehicle_id`
- `device_id`
- `technician_id`
- `service_interval`
- `maintenance_alert`
- `trip_event`
- `battery_alert`
- `diagnostic_trouble_code`
- `gps_position`
- `ignition_state`
- `odometer_source`

See [docs/product/GAS_SMART_TRACKER_PRODUCT_SPEC.md](docs/product/GAS_SMART_TRACKER_PRODUCT_SPEC.md) and [docs/product/DATA_MODEL_DRAFT.md](docs/product/DATA_MODEL_DRAFT.md).

## Current Hardware

- ESP32 Development Board
- Waveshare SIM7600G-H 4G LTE + GNSS HAT
- SN65HVD230 CAN transceiver for the preferred ESP32 TWAI CAN path
- MCP2515 CAN Bus Module, deprecated for the main ESP32 vehicle CAN path and retained for historical Revision A bench reference
- OBD-II male breakout cable
- 5V automotive buck converter
- Breadboard
- Jumper wires

See [hardware/inventory/HARDWARE_INVENTORY.md](hardware/inventory/HARDWARE_INVENTORY.md) for the maintained inventory.

## Firmware Architecture

The firmware is organized around layers:

1. Application Layer
2. Service Layer
3. Platform Layer
4. Arduino Framework
5. ESP32 Hardware

Current foundation services include:

- Application
- Platform
- Logger
- Configuration
- Diagnostics
- Module Manager
- Status/error code conventions

Future hardware services include:

- GPS
- LTE modem
- CAN bus
- OBD-II
- API client
- Configuration
- Logging
- Utilities

The module layout is described in [firmware/README.md](firmware/README.md) and [docs/architecture/FIRMWARE_ARCHITECTURE.md](docs/architecture/FIRMWARE_ARCHITECTURE.md).

## Project Phases

| Phase | Focus |
| --- | --- |
| Phase 1 - Foundation | Firmware structure, build system, logging, diagnostics, module manager, and documentation. |
| Phase 2 - Communications | LTE modem, network registration, data sessions, API transport, and connectivity recovery. |
| Phase 3 - Vehicle | CAN bus, OBD-II, vehicle telemetry, diagnostic trouble codes, ignition state, and odometer sources. |
| Phase 4 - Backend | Telemetry ingestion, device identity, customer/fleet/vehicle records, command delivery, and alert processing. |
| Phase 5 - Dashboard | Operator UI, fleet views, vehicle detail pages, diagnostics, alerts, and technician workflows. |
| Phase 6 - Production | Hardware hardening, provisioning, OTA, enclosure, certifications, manufacturing, and field operations. |
 
Current phase: Phase 2 - Communications and external hardware validation.

Milestone v0.11.0 pivots the active FleetLink vehicle CAN firmware path to ESP32 built-in TWAI plus SN65HVD230. `TwaiCanInterface` is now registered as the active vehicle CAN module through `ModuleManager`; MCP2515 files remain in the repository for historical Revision A reference but are no longer registered as the active CAN path.

Planned SN65HVD230 wiring:

| SN65HVD230 | ESP32 / Later Vehicle Connection |
| --- | --- |
| 3.3V | ESP32 3V3 |
| GND | ESP32 GND |
| CTX | ESP32 GPIO21 |
| CRX | ESP32 GPIO22 |
| CANH | Vehicle CAN High later |
| CANL | Vehicle CAN Low later |

This milestone initializes the TWAI driver only. It does not connect to a vehicle, read CAN frames, decode OBD-II, add SIM7600/GPS/LTE code, or add backend/dashboard behavior.

## Planning Documents

- [GAS Smart Tracker Product Spec](docs/product/GAS_SMART_TRACKER_PRODUCT_SPEC.md)
- [Data Model Draft](docs/product/DATA_MODEL_DRAFT.md)
- [Project Journal](docs/JOURNAL.md)
- [Arduino CLI Setup](docs/development/ARDUINO_CLI_SETUP.md)
- [Firmware Build Guide](firmware/BUILD.md)
- [Development Roadmap](docs/roadmap/DEVELOPMENT_ROADMAP.md)
- [Milestone Tracker](docs/milestones/MILESTONE_TRACKER.md)
- [Hardware Inventory](hardware/inventory/HARDWARE_INVENTORY.md)
- [Hardware Revisions](docs/hardware/HARDWARE_REVISIONS.md)
- [Project Structure](docs/architecture/PROJECT_STRUCTURE.md)

## Milestone 0.1 Scope

Version 0.1 establishes the project organization only:

- Create the repository structure.
- Create placeholder source files.
- Document folder and file responsibilities.
- Create the initial roadmap.
- Create the hardware inventory.
- Create a milestone tracker from Version 0.1 through Version 1.0.

No hardware-specific firmware code is included in this milestone.
