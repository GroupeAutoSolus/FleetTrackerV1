# Firmware Architecture

## Architectural Intent

GAS Smart Tracker firmware should remain modular as it grows from prototype to production. Each hardware-facing capability is isolated behind a dedicated module. The application layer coordinates modules but does not contain protocol details.

The firmware exists to support a Groupe Auto Solus telematics product, not a generic tracker. Device data should eventually map cleanly to the product domain concepts documented in `docs/product/DATA_MODEL_DRAFT.md`.

## Layers

| Layer | Responsibility |
| --- | --- |
| Application Layer | Owns startup order, update loop, scheduling policy, and high-level state transitions. |
| Service Layer | Future GPS, LTE modem, CAN bus, OBD-II, API client, configuration, logging, and utility services. |
| Platform Layer | Owns framework-facing primitives such as timing, delays, serial ownership boundaries, storage, and future watchdog access. |
| Arduino Framework | ESP32 Arduino core used by the current prototype build. |
| ESP32 Hardware | ESP32 DevKit V1 / ESP32-WROOM-32 prototype board. |

## Current Firmware Foundation

Milestone 0.5 establishes the first compiled firmware foundation inside `firmware/FleetTrackerFirmware`:

| Component | Responsibility |
| --- | --- |
| `FleetTrackerFirmware.ino` | Minimal Arduino entry point that delegates to Application. |
| `Application` | Calls initialization in order and runs the heartbeat update loop. |
| `Configuration` | Holds placeholder firmware settings such as firmware version, device ID, heartbeat interval, future APN, and future server URL. |
| `Logger` | Owns all direct serial output through `Serial.begin`, `Serial.print`, and `Serial.println`. |
| `Platform` | Owns direct Arduino timing calls through `millis()` and `delay()`. |

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

Current rule: no module except Logger may call `Serial.print`, `Serial.println`, or `Serial.begin` directly.

### Utilities

Responsible for shared helpers that do not own hardware, transport, or application state.

### Platform

Responsible for framework boundary functions. Current functions are `Platform::Initialize()`, `Platform::Millis()`, and `Platform::Delay(milliseconds)`.

Current rule: no module outside Platform should call Arduino `delay()` or `millis()` directly.

## Business and Domain Concepts

Firmware should emit data that can be associated with the following product concepts once backend integration exists:

| Concept | Firmware Relevance |
| --- | --- |
| `customer_id` | Assigned by provisioning or backend association; not hard-coded in firmware. |
| `fleet_id` | Assigned by backend association; used to group vehicle telemetry. |
| `vehicle_id` | Assigned when a device is installed in a vehicle. |
| `device_id` | Stable device identity used for provisioning and telemetry attribution. |
| `technician_id` | Used by service workflows; firmware may receive it only through future commands or configuration. |
| `service_interval` | Backend-owned maintenance rule; firmware may provide odometer, runtime, and diagnostic inputs. |
| `maintenance_alert` | Usually backend-generated; firmware may contribute trigger data. |
| `trip_event` | Firmware may eventually detect trip start, update, stop, and summary events. |
| `battery_alert` | Firmware may generate or report low-voltage and power-state observations. |
| `diagnostic_trouble_code` | OBD-II module may report active or stored DTCs. |
| `gps_position` | GPS module provides normalized position and fix metadata. |
| `ignition_state` | Derived from OBD-II, voltage, motion, or future dedicated input. |
| `odometer_source` | Identifies whether odometer data is OBD-derived, GPS-estimated, manual, imported, or corrected. |

Firmware should avoid embedding customer-specific business rules. Business rules belong in backend and product layers unless a device-local safety or reliability requirement demands local handling.

## Design Constraints

- Keep hardware-specific code out of business logic.
- Prefer small interfaces with explicit ownership.
- Avoid global mutable state unless a platform constraint requires it.
- Keep modules independently testable.
- Do not let OBD-II depend on a specific CAN controller implementation.
- Do not let the API client depend directly on a specific modem implementation.
