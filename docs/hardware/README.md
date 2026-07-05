# Hardware Notes

This folder is reserved for hardware design notes that do not fit cleanly into inventory, schematics, or datasheets.

Future documents may include:

- Vehicle power design notes.
- OBD-II connector notes.
- Automotive protection requirements.
- Prototype test procedures.
- Production hardware requirements.

## Current Hardware Validation Notes

- [Hardware Revisions](HARDWARE_REVISIONS.md)
- [MCP2515 SPI Validation Checklist](mcp2515/MCP2515_SPI_VALIDATION_CHECKLIST.md)

## FleetLink Revision B Hardware Architecture

FleetLink Revision B is the preferred prototype direction:

- ESP32 DevKit V1
- SN65HVD230 3.3V CAN transceiver
- SIM7600G-H LTE/GNSS module
- 12V to 5V buck converter
- OBD-II pigtail connector
- Breadboard for prototype power distribution

### Full Wiring Plan

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

CAN:

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

### Safety Warnings

- Do not connect OBD-II power until USB bench tests are complete.
- Do not connect CANH/CANL to a vehicle until TWAI firmware is ready for the vehicle test milestone.
- ESP32 GPIO is not 5V tolerant.
- All modules must share common ground.

### Bench-Test Sequence

1. ESP32 by USB only.
2. SN65HVD230 powered from ESP32 3V3.
3. TWAI init test.
4. OBD-II CANH/CANL test with no OBD power.
5. Buck converter test standalone.
6. Full OBD power test later.

For the VehicleBusService TWAI initialization milestone, CANH/CANL remain disconnected. The firmware initializes ESP32 TWAI at 500 kbps on TX GPIO21 and RX GPIO22 only.
