# Firmware Architecture

## Architectural Intent

FleetTracker firmware should remain modular as it grows from prototype to production. Each hardware-facing capability is isolated behind a dedicated module. The application layer coordinates modules but does not contain protocol details.

## Layers

| Layer | Responsibility |
| --- | --- |
| Application | Owns startup order, runtime loop, scheduling policy, and high-level state transitions. |
| Services / Modules | GPS, LTE modem, CAN bus, OBD-II, API client, configuration, logging, and utilities. |
| Hardware Adapters | Future layer for UART, SPI, GPIO, timers, storage, and watchdog integrations. |
| Platform | Future ESP32 framework integration such as ESP-IDF, Arduino core, or PlatformIO environment. |

## Module Boundaries

### GPS

Responsible for GNSS data acquisition and normalized position data. Future responsibilities include fix quality, latitude, longitude, altitude, speed, heading, timestamp, and stale-fix detection.

### LTE Modem

Responsible for modem lifecycle and cellular connectivity. Future responsibilities include power sequencing, AT command transport, SIM state, network registration, signal quality, PDP context, and reconnection policy.

### CAN Bus

Responsible for CAN frame transport. Future responsibilities include controller initialization, bitrate management, frame filtering, error counters, and receive buffering.

### OBD-II

Responsible for vehicle diagnostic requests above CAN. Future responsibilities include PID requests, response parsing, timeouts, retry policy, supported PID discovery, and normalized vehicle telemetry.

### API Client

Responsible for device-to-cloud communication. Future responsibilities include telemetry batching, retry policy, authentication tokens, command polling, and response handling.

### Configuration

Responsible for configuration ownership. Future responsibilities include defaults, validation, persistent settings, device identity, and environment-specific build options.

### Logging

Responsible for firmware observability. Future responsibilities include log levels, structured messages, serial output, remote diagnostic upload, and crash breadcrumbs.

### Utilities

Responsible for shared helpers that do not own hardware, transport, or application state.

## Design Constraints

- Keep hardware-specific code out of business logic.
- Prefer small interfaces with explicit ownership.
- Avoid global mutable state unless a platform constraint requires it.
- Keep modules independently testable.
- Do not let OBD-II depend on a specific CAN controller implementation.
- Do not let the API client depend directly on a specific modem implementation.
