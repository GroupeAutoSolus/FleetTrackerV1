# GAS Smart Tracker Product Spec

## Product Purpose

GAS Smart Tracker is a custom telematics device and platform for Groupe Auto Solus, a mobile mechanic and fleet service business in Québec.

The product is intended to help Groupe Auto Solus monitor customer fleet vehicles, understand vehicle usage, detect maintenance needs, and support proactive service operations.

The long-term vision is a commercial telematics platform that combines GPS tracking, vehicle diagnostics, maintenance intelligence, and service workflow support for fleet customers.

## Target Users

| User | Needs |
| --- | --- |
| Groupe Auto Solus owner/operator | Visibility into customer fleet condition, service opportunities, and operational status. |
| Fleet customer manager | Vehicle location, usage, alerts, and maintenance status. |
| Mobile technician | Vehicle context, diagnostics, maintenance history, and service priorities. |
| System administrator | Device provisioning, customer setup, fleet setup, and support diagnostics. |

## First Prototype Goals

- Establish a modular embedded firmware architecture.
- Validate ESP32-based device feasibility.
- Validate LTE connectivity with the SIM7600G-H module.
- Validate GNSS position acquisition.
- Validate CAN/OBD-II data access on a controlled bench setup before vehicle use.
- Define the first cloud telemetry payloads.
- Document GAS-specific product concepts before backend and dashboard implementation begins.

## Future Commercial Goals

- Provide fleet customers with reliable vehicle tracking.
- Detect maintenance needs based on service intervals, odometer data, diagnostic trouble codes, battery state, and vehicle usage.
- Support Groupe Auto Solus technician workflows.
- Enable customer, fleet, vehicle, and device management.
- Support scalable telemetry ingestion and long-term vehicle history.
- Prepare a production hardware path with automotive power protection, secure provisioning, and field update capability.

## Core Telemetry Data

- `device_id`
- `vehicle_id`
- `customer_id`
- `fleet_id`
- `gps_position`
- `ignition_state`
- `trip_event`
- `diagnostic_trouble_code`
- `battery_alert`
- `maintenance_alert`
- `service_interval`
- `odometer_source`
- Network status
- Timestamp

## GAS-Specific Features

- Customer and fleet hierarchy for Groupe Auto Solus commercial accounts.
- Vehicle-to-device assignment tracking.
- Technician-aware service workflows using `technician_id`.
- Maintenance alerts tied to service intervals and observed vehicle data.
- Diagnostic trouble code tracking for service prioritization.
- Battery alerts for vehicles at risk of no-start conditions.
- Trip events to understand vehicle usage patterns.
- Odometer source tracking to distinguish dashboard-entered, OBD-derived, GPS-estimated, or manually corrected odometer values.

## Intentionally Out of Scope for V1

- Insurance scoring.
- Driver behavior scoring as a primary product feature.
- Consumer vehicle tracking.
- In-app billing and payment processing.
- Full work order management.
- Parts inventory management.
- Advanced route optimization.
- Remote vehicle immobilization.
- Production PCB design.
- Certification-ready automotive hardware.
- Finished mobile apps.
