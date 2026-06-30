# Data Model Draft

This document defines early domain entities for GAS Smart Tracker. It is a product architecture draft, not a database schema or API contract.

## Customer

Represents a commercial customer served by Groupe Auto Solus.

Early fields:

- `customer_id`
- Business name
- Contact information
- Billing/service address
- Account status

## Fleet

Represents a group of vehicles belonging to a customer.

Early fields:

- `fleet_id`
- `customer_id`
- Fleet name
- Operating region
- Fleet status

## Vehicle

Represents a physical vehicle monitored by GAS Smart Tracker.

Early fields:

- `vehicle_id`
- `customer_id`
- `fleet_id`
- VIN
- Year, make, model
- License plate
- Current odometer value
- `odometer_source`
- Service profile

## Device

Represents a GAS Smart Tracker hardware unit.

Early fields:

- `device_id`
- Assigned `vehicle_id`
- Firmware version
- Hardware revision
- SIM/modem identifier
- Provisioning status
- Last communication timestamp

## Technician

Represents a Groupe Auto Solus technician or service operator.

Early fields:

- `technician_id`
- Name
- Contact information
- Role
- Active status

## Trip

Represents vehicle movement between ignition or motion boundaries.

Early fields:

- Trip identifier
- `vehicle_id`
- `device_id`
- Start time
- End time
- Start `gps_position`
- End `gps_position`
- Distance estimate
- Trip status

## TelemetryEvent

Represents a time-stamped event or measurement emitted by a device.

Early fields:

- Event identifier
- `device_id`
- `vehicle_id`
- `customer_id`
- `fleet_id`
- Timestamp
- Event type
- `gps_position`
- `ignition_state`
- Battery voltage
- Network status
- Raw source metadata

## MaintenanceAlert

Represents a maintenance condition requiring review or action.

Early fields:

- Alert identifier
- `customer_id`
- `fleet_id`
- `vehicle_id`
- Optional `technician_id`
- `service_interval`
- Alert severity
- Alert status
- Trigger reason
- Created timestamp
- Resolved timestamp

## DiagnosticCode

Represents a diagnostic trouble code observed from a vehicle.

Early fields:

- Diagnostic code identifier
- `vehicle_id`
- `device_id`
- Code value
- Code family
- Description
- First seen timestamp
- Last seen timestamp
- Active status
- Related `maintenance_alert`

## Core Domain Identifiers

| Concept | Purpose |
| --- | --- |
| `customer_id` | Identifies the commercial customer account. |
| `fleet_id` | Identifies a fleet or vehicle group under a customer. |
| `vehicle_id` | Identifies a physical vehicle. |
| `device_id` | Identifies a deployed GAS Smart Tracker hardware unit. |
| `technician_id` | Identifies a Groupe Auto Solus technician or service operator. |

## Core Event Concepts

| Concept | Purpose |
| --- | --- |
| `service_interval` | Maintenance schedule threshold based on time, odometer, engine hours, or business rule. |
| `maintenance_alert` | Service-related alert generated from intervals, diagnostic data, or observed telemetry. |
| `trip_event` | Start, stop, update, or summary event for vehicle movement. |
| `battery_alert` | Alert related to low voltage or suspected battery/charging issue. |
| `diagnostic_trouble_code` | Vehicle diagnostic code observed through OBD-II or another diagnostic source. |
| `gps_position` | Normalized location point with timestamp and fix metadata. |
| `ignition_state` | Vehicle ignition or inferred engine state. |
| `odometer_source` | Tracks whether odometer data came from OBD-II, manual entry, GPS estimate, import, or correction. |
