# MCP2515 SPI Validation Checklist

Milestone v0.9.0 verifies SPI communication between the ESP32 DevKit V1 and the MCP2515 controller only.

This milestone does not read CAN frames, does not connect to a vehicle, and does not implement OBD-II.

## Wiring Plan

| MCP2515 Header | ESP32 / Power |
| --- | --- |
| INT | GPIO4 |
| SCK | GPIO18 |
| SO | GPIO19 |
| SI | GPIO23 |
| CS | GPIO5 |
| GND | GND |
| VCC | 5V or 3.3V pending hardware validation |

## Required Validation Before Power

- Verify the MCP2515 module operating voltage from the exact board markings or datasheet.
- Verify whether the breakout board includes level shifting or expects 5V logic.
- Verify ESP32 logic compatibility before connecting SPI pins.
- Verify SPI wiring against the table above.
- Verify common ground between ESP32 and MCP2515 module.
- Do not connect the module to a vehicle or CAN bus for this milestone.

## Pass Criteria

- Firmware compiles.
- Firmware uploads to ESP32.
- Startup log shows SPI initialization.
- Startup log reports MCP2515 detected successfully.

## Fail Criteria

- Startup log reports MCP2515 not detected.
- ESP32 repeatedly resets after wiring.
- MCP2515 module becomes hot.
- Any voltage or logic-level compatibility is uncertain.
