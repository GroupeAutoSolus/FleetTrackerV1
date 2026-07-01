# Arduino CLI Setup

This document describes the manual setup for building GAS Smart Tracker firmware with Arduino CLI on macOS.

Milestone 0.3 uses:

- Board: ESP32 DevKit V1
- Module: ESP32-WROOM-32
- USB-to-serial: CP2102
- Firmware framework: ESP32 Arduino core
- Build tool: Arduino CLI

No project command should install tools automatically. Run the commands below manually from a terminal.

## 1. Install Arduino CLI

Using Homebrew:

```bash
brew install arduino-cli
```

Verify installation:

```bash
arduino-cli version
```

## 2. Initialize Arduino CLI Configuration

```bash
arduino-cli config init
```

## 3. Add ESP32 Package Index

```bash
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Update the package index:

```bash
arduino-cli core update-index
```

## 4. Install ESP32 Arduino Core

```bash
arduino-cli core install esp32:esp32
```

## 5. Confirm ESP32 Boards Are Available

```bash
arduino-cli board listall esp32
```

For ESP32 DevKit V1, this project uses:

```text
esp32:esp32:esp32doit-devkit-v1
```

## 6. Find the Serial Port

Connect the ESP32 DevKit V1 over USB, then run:

```bash
arduino-cli board list
```

On the current ESP32 DevKit V1 with a CP2102 USB-to-serial chip, macOS detects the port as:

```text
/dev/cu.usbserial-0001
```

The exact port can vary by driver and system configuration. Always confirm with `arduino-cli board list`.

## 7. Compile the Firmware

From the repository root:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32doit-devkit-v1 firmware/FleetTrackerFirmware
```

Or use the helper script:

```bash
./tools/firmware/compile.sh
```

## 8. Upload the Firmware

Replace the port with the one shown by `arduino-cli board list`:

```bash
arduino-cli upload \
  --fqbn esp32:esp32:esp32doit-devkit-v1 \
  --port /dev/cu.usbserial-0001 \
  firmware/FleetTrackerFirmware
```

Or use the helper script with the current default port:

```bash
./tools/firmware/upload.sh
```

## 9. Monitor Serial Output

```bash
arduino-cli monitor --port /dev/cu.usbserial-0001 --config baudrate=115200
```

Or use the helper script with the current default port:

```bash
./tools/firmware/monitor.sh
```

Expected output:

```text
GAS Smart Tracker booting...
GAS Smart Tracker heartbeat
GAS Smart Tracker heartbeat
```

## Notes

- The Milestone 0.3 sketch does not use SIM7600, GNSS, CAN, or OBD-II hardware.
- The sketch only requires the ESP32 DevKit V1 connected over USB.
- If upload fails, hold the BOOT button during upload until writing begins, then release it.
- If no serial port appears, install or update the Silicon Labs CP210x driver for macOS.
