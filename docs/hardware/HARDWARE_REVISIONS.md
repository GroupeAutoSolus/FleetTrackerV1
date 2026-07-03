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
- SN65HVD230 3.3V CAN transceiver
- SIM7600G-H LTE/GNSS module
- 12V to 5V buck converter
- OBD-II pigtail connector
- Breadboard for prototype power distribution

Status: preferred prototype direction.

Engineering decision: use ESP32 built-in TWAI plus SN65HVD230 instead of MCP2515 for the main vehicle CAN path.

### Revision B Wiring Plan

Power distribution:

| Source | Destination |
| --- | --- |
| OBD-II pin 16 | Buck converter VIN+ |
| OBD-II pin 4 / pin 5 | Buck converter VIN- |
| Buck converter 5V | Breadboard 5V rail |
| Buck converter GND | Breadboard GND rail |
| ESP32 VIN / 5V | Breadboard 5V rail |
| ESP32 GND | Breadboard GND rail |
| SIM7600 5V | Breadboard 5V rail |
| SIM7600 GND | Breadboard GND rail |

CAN transceiver:

| SN65HVD230 | Destination |
| --- | --- |
| 3.3V | ESP32 3V3 |
| GND | Common GND |
| CTX | ESP32 GPIO21 |
| CRX | ESP32 GPIO22 |
| CANH | OBD-II pin 6 |
| CANL | OBD-II pin 14 |

SIM7600 serial:

| SIM7600G-H | ESP32 |
| --- | --- |
| TX | RX2 / GPIO16 |
| RX | TX2 / GPIO17 |

### Revision B Safety Rules

- Do not connect OBD-II power until USB bench tests are complete.
- Do not connect CANH/CANL to a vehicle until TWAI firmware is ready for the vehicle test milestone.
- ESP32 GPIO is not 5V tolerant.
- All modules must share common ground.

### Revision B Bench-Test Sequence

1. Power ESP32 by USB only and verify serial boot.
2. Power SN65HVD230 from ESP32 3V3 with shared ground.
3. Run the TWAI initialization test.
4. Connect OBD-II CANH/CANL only for the CAN test while leaving OBD-II power disconnected.
5. Test the buck converter standalone from a controlled 12V source.
6. Run the full OBD power test later, after USB, TWAI, CANH/CANL, and buck converter checks pass.

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
