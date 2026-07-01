# Firmware Build

GAS Smart Tracker firmware uses Arduino CLI with the ESP32 Arduino core for Milestone 0.3.

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

## Minimal Firmware Behavior

The Milestone 0.3 sketch:

- Initializes serial output at `115200`.
- Prints `GAS Smart Tracker booting...` once during startup.
- Prints `GAS Smart Tracker heartbeat` every 2 seconds.
- Does not use SIM7600.
- Does not use CAN.
- Does not use OBD-II.
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
