# GAS Smart Tracker

GAS Smart Tracker is a custom telematics device and platform by Groupe Auto Solus for commercial fleet service customers in Québec.

The project starts with an ESP32-based prototype and is organized so the firmware, backend, dashboard, hardware documentation, and tests can evolve toward production without a major restructure.

The product direction is no longer a generic fleet tracker. GAS Smart Tracker is being designed around the operating needs of Groupe Auto Solus, a mobile mechanic and fleet service business. The long-term goal is to support customer fleet visibility, proactive maintenance, diagnostic insight, and technician workflows.

This first milestone is intentionally architectural. It creates the repository structure, module boundaries, documentation, and planning artifacts. Hardware-specific implementation will be added in later milestones.

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
- MCP2515 CAN Bus Module
- OBD-II male breakout cable
- 5V automotive buck converter
- Breadboard
- Jumper wires

See [hardware/inventory/HARDWARE_INVENTORY.md](hardware/inventory/HARDWARE_INVENTORY.md) for the maintained inventory.

## Firmware Architecture

The firmware is organized around independent modules:

- GPS
- LTE modem
- CAN bus
- OBD-II
- API client
- Configuration
- Logging
- Utilities

The module layout is described in [firmware/README.md](firmware/README.md) and [docs/architecture/FIRMWARE_ARCHITECTURE.md](docs/architecture/FIRMWARE_ARCHITECTURE.md).

## Planning Documents

- [GAS Smart Tracker Product Spec](docs/product/GAS_SMART_TRACKER_PRODUCT_SPEC.md)
- [Data Model Draft](docs/product/DATA_MODEL_DRAFT.md)
- [Project Journal](docs/JOURNAL.md)
- [Development Roadmap](docs/roadmap/DEVELOPMENT_ROADMAP.md)
- [Milestone Tracker](docs/milestones/MILESTONE_TRACKER.md)
- [Hardware Inventory](hardware/inventory/HARDWARE_INVENTORY.md)
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
