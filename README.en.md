[![License](https://img.shields.io/badge/License-Copyright%20%28c%29%202026%20Enrique%20Aguayo-red)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Hypothesis%20under%20development-yellow)](https://github.com/enriqueherbertag-lgtm/SmartJoint)
[![Documentation](https://img.shields.io/badge/Documentation-SmartJoint-blue)](./docs/)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.19609558.svg)](https://doi.org/10.5281/zenodo.19609558)
[![AI Assistance](https://img.shields.io/badge/AI%20Assistance-DeepSeek-brightgreen)](https://deepseek.com)
# SmartJoint: Direct drive intelligent joint

**Autonomous module for robotics, prosthetics and exoskeletons. Integrates motor, absolute sensor, local controller and high-speed communication.**

SmartJoint is not a generic motor. It is a complete system that includes:

- Direct drive motor (gearless, zero backlash).
- AS5715R inductive position sensor (360° absolute, <0.075°).
- Local STM32F405 controller with PID.
- Power driver (48V, 10A).
- Fiber optic communication (1 Mbps serial bus).
- Optional liquid cooling.

It does not depend on an external controller. Each joint is intelligent.

---

## What problem does it solve?

Current robotic joints are clumsy, expensive or difficult to integrate:

- Geared servomotors have backlash and wear out.
- Stepper motors lose steps under load.
- Linear actuators are slow and noisy.
- Industrial systems are closed and expensive (thousands of dollars per joint).

SmartJoint is open, modular and low cost. An engineer with a 3D printer and basic electronics knowledge can build a 4-joint prosthetic arm for under 500 USD.

---

## Technical specifications

| Parameter | Value |
|---|---|
| Diameter | 60 mm |
| Length | 80 mm |
| Weight | 400-500 g |
| Peak torque | 50 Nm (peak), 20 Nm (continuous) |
| Maximum speed | 300 rpm |
| Supply voltage | 48V DC |
| Idle power consumption | 5 W |
| Moving power consumption | 50-200 W |
| Position accuracy | ±0.1 degrees |
| Sensor resolution | <0.075 degrees |
| Sensor range | 360° absolute |
| Communication | UART over fiber optic or RS-485 |
| Control frequency | 1 kHz |
| Cooling | Liquid (optional, up to 50 W dissipated) |

---

## Position measurement system

SmartJoint uses an **AS5715R inductive sensor** that operates over a **machined conductive tone ring** coupled to the rotor.

This principle is widely used in automotive applications (crankshaft sensors, ABS systems, electric power steering), offering:

- Robustness against dirt, external magnetic fields and vibration.
- Resolution <0.075° and accuracy of ±0.1° with proper alignment.
- Absolute operation (no homing required at power-up).

The tone ring is machined from aluminum or copper with standard automotive industry tolerances (eccentricity <0.1 mm, controlled concentricity). Final assembly can be calibrated in firmware to compensate for minor mechanical deviations.

---

## Control modes

- **Position mode:** Moves to the commanded angle (in degrees).
- **Speed mode:** Rotates at the commanded angular velocity (degrees/second).
- **Torque mode:** Applies the commanded torque (Nm) to the shaft.
- **Safe mode (link failure):** Hardware configurable. Can be set to "hold" (maintains position with reduced torque) or "free" (motor disabled).

---

## Bill of materials (BOM)

| Component | Model | Cost (USD) |
|---|---|---|
| Machined stator and rotor | Custom design (outsourced) | 20-30 |
| N52 neodymium magnets | Various (e.g. SuperMagnetMan) | 10-15 |
| Copper windings | AWG 24 wire | 5-10 |
| Inductive sensor | AS5715R (ams AG) | 12-15 |
| Conductive tone ring | Machined aluminum or copper | 5-10 |
| Microcontroller | STM32F405 (or similar) | 10-15 |
| Motor driver | DRV8320 (Texas Instruments) | 8-12 |
| Voltage regulators | 48V -> 5V -> 3.3V | 5-10 |
| Controller PCB | Custom design (JLCPCB) | 10-15 |
| SFP transceiver (optional) | TP-Link TL-SM311LS | 25-30 |
| Connectors and cables | Various | 10-15 |
| **Approximate total** | | **120-180 USD** |

In volume (>100 units), the cost can drop to 60-100 USD per joint.

---

## Project status

- [x] Concept defined.
- [x] Complete technical specifications.
- [x] Components selected.
- [ ] Mechanical design (STEP/STL files) (pending).
- [ ] Electronic schematic (KiCad) (pending).
- [ ] Controller PCB (pending).
- [ ] Firmware (C++ for STM32) (pending).
- [ ] Functional prototype (pending).
- [ ] Torque, speed and thermal dissipation tests (pending).

---

## Repository structure

- `docs/` - Technical documentation (specifications, guides).
- `hardware/` - Mechanical drawings (STEP/STL) and electronic schematics (KiCad).
- `firmware/` - Source code for the STM32.
- `software/` - Control examples (Python, C++).
- `LICENSE` - Copyright (non-commercial use permitted, commercial use requires a license).

---

## How to contribute

This is an open project (in terms of documentation, not commercial license). You can:

- Open an issue to report errors in the specification.
- Suggest improvements (alternative components, design changes).
- Share your own designs or firmware (under the same license).

Commercial contributions are not accepted without express permission from the author.

---

## Author

**Enrique Aguayo H.** – Mackiber Labs  
Contact: eaguayo@migst.cl  
ORCID: 0009-0004-4615-6825  
GitHub: @enriqueherbertag-lgtm

*Documentation assisted by DeepSeek (AI) for writing and structure.*

---

## License

Copyright © 2026 Enrique Aguayo. All rights reserved.

**Permitted:** Non-commercial use for educational or research purposes. Unmodified distribution with attribution.

**Prohibited without express permission:** Commercial use, modification for production environments, distribution of modified versions.

For commercial licenses: eaguayo@migst.cl
