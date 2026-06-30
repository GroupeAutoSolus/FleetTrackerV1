# Milestone Tracker

| Version | Milestone | Scope | Status |
| --- | --- | --- | --- |
| 0.1 | Project foundation | Repository structure, placeholders, documentation, roadmap, hardware inventory, milestone tracker. | In progress |
| 0.2 | Firmware build baseline | Select build system, add compiler config, add formatting/linting, add first build target. | Planned |
| 0.3 | Platform abstraction | Define platform interfaces for serial, SPI, GPIO, timers, storage, and watchdog. | Planned |
| 0.4 | Hardware bring-up | Validate ESP32, SIM7600G-H, GNSS, MCP2515, and power wiring on the bench. | Planned |
| 0.5 | Telemetry module baseline | Implement initial GPS, modem, CAN, OBD-II, configuration, and logging behavior. | Planned |
| 0.6 | Device-to-cloud prototype | Add API client, telemetry payload format, retry policy, and backend ingestion prototype. | Planned |
| 0.7 | Backend and dashboard MVP | Store telemetry, show vehicle status, show latest location, and expose basic admin views. | Planned |
| 0.8 | Reliability and field-test readiness | Add buffering, watchdog behavior, reconnect logic, diagnostics, and safer prototype wiring. | Planned |
| 0.9 | Production candidate architecture | Refine hardware requirements, security model, provisioning, OTA strategy, and operational tooling. | Planned |
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
