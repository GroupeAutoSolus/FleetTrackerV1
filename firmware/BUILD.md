# Firmware Build

GAS Smart Tracker firmware uses Arduino CLI with the ESP32 Arduino core.

## Current Target

| Setting | Value |
| --- | --- |
| Board | ESP32 DevKit V1 |
| Module | ESP32-WROOM-32 |
| USB serial chip | CP2102 |
| Arduino FQBN | `esp32:esp32:esp32doit-devkit-v1` |
| Default serial port | `/dev/cu.usbserial-0001` |
| Serial baud rate | `115200` |
| Sketch path | `firmware/FleetTrackerFirmware` |

## Firmware Behavior

The current firmware:

- Initializes serial output at `115200`.
- Prints `GAS Smart Tracker booting...` once during startup.
- Prints BuildInfo metadata.
- Logs the firmware version.
- Logs platform initialization.
- Logs configuration loading.
- Logs module manager initialization.
- Logs diagnostics initialization.
- Logs SPI service initialization.
- Logs SPI pin configuration.
- Attempts MCP2515 SPI detection through the Module Manager.
- Retries MCP2515 detection three times before reporting failure.
- Continues booting if MCP2515 is missing or unpowered.
- Logs application initialization.
- Prints `GAS Smart Tracker heartbeat` every 2 seconds.
- Logs uptime, free heap, and module health placeholder with each heartbeat.
- Uses lightweight status/error code placeholders for module health.
- Includes a volatile boot counter placeholder.
- Does not use SIM7600.
- Does not read CAN frames.
- Does not use CAN.
- Does not use OBD-II.
- Does not use GPS or LTE services.
- Does not require external hardware.

## Compile

From the repository root:

```bash
./tools/firmware/compile.sh
```

Equivalent direct Arduino CLI command:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32doit-devkit-v1 firmware/FleetTrackerFirmware
```

## Upload

First identify the ESP32 serial port:

```bash
arduino-cli board list
```

Then upload:

```bash
./tools/firmware/upload.sh
```

Equivalent direct Arduino CLI command:

```bash
arduino-cli upload \
  --fqbn esp32:esp32:esp32doit-devkit-v1 \
  --port /dev/cu.usbserial-0001 \
  firmware/FleetTrackerFirmware
```

## Monitor

```bash
./tools/firmware/monitor.sh
```

Equivalent direct Arduino CLI command:

```bash
arduino-cli monitor --port /dev/cu.usbserial-0001 --config baudrate=115200
```

## Helper Script Configuration

The helper scripts use these defaults:

- `FLEETTRACKER_FQBN=esp32:esp32:esp32doit-devkit-v1`
- `FLEETTRACKER_SKETCH=firmware/FleetTrackerFirmware`
- `FLEETTRACKER_PORT=/dev/cu.usbserial-0001`

Override values by setting environment variables before running a script.
