# Hardware

The hardware folder contains non-firmware hardware documentation for prototype and production device development.

FleetLink is the physical in-vehicle telematics device. FleetTracker is the broader platform, and GAS Smart Tracker is the product initiative.

## Folder Responsibilities

- `inventory/`: Maintained list of available hardware, purpose, and project status.
- `schematics/`: Wiring diagrams, pin maps, and future PCB schematics.
- `datasheets/`: Component datasheets and vendor references.

## Current SPI Planning

Milestone v0.8.0 defined the ESP32 SPI pin plan before MCP2515-specific CAN logic was added.

Current engineering decision: MCP2515 is deprecated for the main ESP32 vehicle CAN path due to 5V logic compatibility risk. The preferred path is ESP32 built-in TWAI with an SN65HVD230 CAN transceiver.

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
