# Hardware Inventory

| Item | Role | Current Use | Notes |
| --- | --- | --- | --- |
| ESP32 Development Board | Main embedded controller | Prototype compute platform | Final production MCU/module selection remains open. |
| Waveshare SIM7600G-H 4G LTE + GNSS HAT | Cellular and GNSS communications | Prototype modem and GNSS source | Future firmware will isolate modem and GPS access behind modules. |
| MCP2515 CAN Bus Module | CAN controller interface | Prototype CAN bus access | Requires later validation for automotive electrical robustness. |
| OBD-II male breakout cable | Vehicle diagnostic connector access | Prototype vehicle interface | Pinout and protection requirements must be documented before vehicle testing. |
| 5V automotive buck converter | Vehicle power conversion | Prototype power supply | Production design will need transient, reverse polarity, and load dump protection. |
| Breadboard | Temporary prototyping | Early wiring experiments | Not suitable for vehicle deployment. |
| Jumper wires | Temporary prototyping | Early module interconnects | Replace with harness or PCB interconnects for field testing. |

## Hardware Policy

- Breadboard assemblies are for bench validation only.
- Any vehicle-connected prototype must be reviewed for power protection, grounding, fusing, and connector safety before use.
- Hardware-specific firmware implementation should not assume final production parts until the architecture stabilizes.
