# Hardware Revisions

FleetTracker is the broader platform: firmware, backend, dashboard, mobile tools, and fleet management system.

GAS Smart Tracker is the product initiative for Groupe Auto Solus.

FleetLink is the physical in-vehicle telematics device installed in a vehicle.

## Revision A - ESP32 + MCP2515 Prototype

Purpose: early bench validation using currently available modules.

Components:

- ESP32 DevKit V1 / ESP32-WROOM-32
- MCP2515 + TJA1050 CAN module
- SIM7600 LTE/GNSS module
- Automotive buck converter

Status: deprecated for the main ESP32 vehicle CAN path.

Reason: many MCP2515 + TJA1050 breakout modules are 5V-oriented and may create logic-level compatibility risk with ESP32 3.3V GPIO. Revision A remains useful for controlled SPI bench experiments only if voltage and logic levels are validated.

## Revision B - ESP32 + SN65HVD230 Prototype

Purpose: preferred ESP32 prototype direction for vehicle CAN.

Components:

- ESP32 DevKit V1 / ESP32-WROOM-32
- ESP32 built-in TWAI controller
- SN65HVD230 CAN transceiver
- SIM7600 LTE/GNSS module
- Automotive buck converter

Status: preferred prototype direction.

Engineering decision: use ESP32 built-in TWAI plus SN65HVD230 instead of MCP2515 for the main vehicle CAN path.

Default planned wiring:

| SN65HVD230 | ESP32 / Later Vehicle Connection |
| --- | --- |
| 3.3V | ESP32 3V3 |
| GND | ESP32 GND |
| CTX | ESP32 GPIO21 |
| CRX | ESP32 GPIO22 |
| CANH | Vehicle CAN High later |
| CANL | Vehicle CAN Low later |

Rationale:

- ESP32 already includes a CAN-compatible TWAI controller.
- SN65HVD230 is a 3.3V CAN transceiver better aligned with ESP32 GPIO levels.
- Fewer SPI bus dependencies for the vehicle CAN path.
- Cleaner firmware architecture for CAN because the controller is internal to ESP32 and only the physical transceiver is external.

## Revision C - Future Custom PCB

Purpose: production-oriented FleetLink hardware.

Expected direction:

- Custom PCB
- Automotive power protection
- Production CAN transceiver selection
- LTE/GNSS module integration
- Device identity/provisioning support
- Enclosure and harness strategy

Status: future planning.

## Current Decision Summary

- FleetLink Revision A MCP2515 path is deprecated for the main ESP32 vehicle CAN path.
- FleetLink Revision B with ESP32 TWAI + SN65HVD230 is the preferred prototype path.
- Firmware v0.11.0 registers ESP32 TWAI as the active vehicle CAN module and initializes the TWAI driver only.
- No vehicle CAN firmware should be built around MCP2515 as the primary architecture unless this decision is explicitly revisited.
