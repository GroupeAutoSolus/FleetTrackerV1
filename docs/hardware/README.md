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

## Current Vehicle CAN Direction

FleetLink Revision B is the preferred prototype direction: ESP32 built-in TWAI plus SN65HVD230.

Planned default wiring:

| SN65HVD230 | ESP32 / Later Vehicle Connection |
| --- | --- |
| 3.3V | ESP32 3V3 |
| GND | ESP32 GND |
| CTX | ESP32 GPIO21 |
| CRX | ESP32 GPIO22 |
| CANH | Vehicle CAN High later |
| CANL | Vehicle CAN Low later |

Do not connect to a vehicle CAN bus until TWAI bench validation is complete.
