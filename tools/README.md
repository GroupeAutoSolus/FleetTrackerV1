# Tools

This folder is reserved for project utilities, scripts, generators, validation helpers, and developer automation used by the GAS Smart Tracker project.

Examples of future tools include:

- Firmware build helpers.
- Data model validation scripts.
- Hardware documentation generators.
- Test data generators.
- Release and packaging utilities.

No tools are implemented in Milestone 0.2.

## Current Tools

- `firmware/compile.sh`: Compiles the Arduino CLI firmware sketch.
- `firmware/upload.sh`: Uploads the sketch to an ESP32 serial port.
- `firmware/monitor.sh`: Opens the serial monitor at the configured baud rate.
