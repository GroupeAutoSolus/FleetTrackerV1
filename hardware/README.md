# Hardware

The hardware folder contains non-firmware hardware documentation for prototype and production device development.

FleetLink is the physical in-vehicle telematics device. FleetTracker is the broader platform, and GAS Smart Tracker is the product initiative.

## Folder Responsibilities

- `inventory/`: Maintained list of available hardware, purpose, and project status.
- `schematics/`: Wiring diagrams, pin maps, and future PCB schematics.
- `datasheets/`: Component datasheets and vendor references.

## FleetLink Revision B Hardware Architecture

The preferred FleetLink prototype hardware uses:

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

## Historical SPI Planning

Milestone v0.8.0 defined the ESP32 SPI pin plan before MCP2515-specific CAN logic was added.

Current engineering decision: MCP2515 is deprecated for the main ESP32 vehicle CAN path due to 5V logic compatibility risk. SPI remains documented for future peripherals and historical Revision A MCP2515 bench reference, but it is no longer the primary vehicle CAN path.

Default ESP32 SPI pin configuration:

| Signal | ESP32 Pin |
| --- | --- |
| SCK | GPIO18 |
| MISO / SO | GPIO19 |
| MOSI / SI | GPIO23 |
| Default CS for future MCP2515 | GPIO5 |
| Future MCP2515 INT | GPIO4 |

Planned MCP2515 header mapping:

| MCP2515 Header | ESP32 / Power |
| --- | --- |
| INT | GPIO4 |
| SCK | GPIO18 |
| SI | GPIO23 |
| SO | GPIO19 |
| CS | GPIO5 |
| GND | GND |
| VCC | 5V or 3.3V pending hardware validation |

Warning: do not physically wire MCP2515 VCC until the exact MCP2515 module voltage requirements and logic-level compatibility are verified. Some MCP2515 breakout boards are 5V modules and may not be safe for direct 3.3V ESP32 logic without level shifting or board-specific validation.

See [docs/hardware/mcp2515/MCP2515_SPI_VALIDATION_CHECKLIST.md](../docs/hardware/mcp2515/MCP2515_SPI_VALIDATION_CHECKLIST.md) for the bench validation checklist.

See [docs/hardware/HARDWARE_REVISIONS.md](../docs/hardware/HARDWARE_REVISIONS.md) for Revision A, Revision B, and Revision C hardware direction.
