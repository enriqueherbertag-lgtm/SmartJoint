[![License](https://img.shields.io/badge/License-Copyright%20%28c%29%202026%20Enrique%20Aguayo-red)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Prototype%20Phase%201-yellow)](https://github.com/enriqueherbertag-lgtm/SmartJoint)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.19609558.svg)](https://doi.org/10.5281/zenodo.19609558)
[![AI Assistance](https://img.shields.io/badge/AI%20Assistance-DeepSeek-brightgreen)](https://deepseek.com)

# SmartJoint: Multifunctional direct‑drive smart joint

**A low‑cost, high‑precision autonomous actuator for robotics, prosthetics, exoskeletons, aerospace structures and industrial automation.**

SmartJoint is not a generic motor. It is a complete system:

- Direct‑drive motor (no gears, zero backlash)
- Inductive absolute position sensor (AS5715R, <0.075°)
- On‑board STM32F405 controller with PID
- Power driver (48V, 10A)
- Optical fiber communication (1 Mbps serial bus)
- Optional liquid cooling

No external controller is required. Each joint is intelligent and self‑contained.

---

## What problem does it solve?

Today’s robotic joints are either clumsy, expensive or difficult to integrate:

- Geared servomotors suffer from backlash and wear.
- Stepper motors lose steps under load.
- Linear actuators are slow and noisy.
- Industrial systems are closed and costly (thousands of dollars per joint).

SmartJoint is **open, modular and cost‑effective**. An engineer with a 3D printer and basic electronics can build a 4‑DoF prosthetic arm for less than 500 USD.

---

## Industrial applications

| **Aerospace** | Flaps, slats, control surfaces on hybrid aircraft | Low weight, fiber optic (EMI‑immune), zero backlash, enough torque |
| Industry | Example | Why SmartJoint |
|:---|:---|:---|
| **Robotics** | Manipulator arms, mobile robots, drones | Low weight, high torque, local control |
| **Prosthetics & exoskeletons** | Elbows, knees, wrists, ankles | Low cost, smooth control, safety |
| **Aerospace** | Panel deployment, in‑orbit assembly | Optical fiber (EMI‑immune), zero backlash |
| **Automotive** | Assembly lines, steer‑by‑wire | High repeatability, fast response |
| **Defense** | UGVs, EOD manipulators | Secure communication, absolute sensing |
| **Medical** | Surgical robotics, patient positioners | Precise torque control, certified components |
| **Precision agriculture** | Fruit picking, targeted spraying | Low cost, vibration resistant |
| **Entertainment** | Motion simulators, animatronics | Adequate speed, smooth motion |
| **Research & education** | Teaching kits, control experiments | Open source, fully documented |

---

## Technical specifications

| Parameter | Value |
|:---|:---|
| Diameter | 60 mm |
| Length | 80 mm |
| Weight | 400‑500 g |
| Peak torque | 50 Nm / Continuous: 20 Nm |
| Maximum speed | 300 rpm |
| Power supply | 48V DC |
| Idle consumption | 5 W |
| Motion consumption | 50‑200 W peak / 10‑30 W average in oscillatory use* |
| Position accuracy | ±0.1° |
| Sensor resolution | <0.075° |
| Sensor range | 360° absolute |
| Communication | UART over optical fiber or RS‑485 |
| Control frequency | 1 kHz |
| Cooling | Optional liquid (up to 50W peaks)* |

\* *See thermal regime note below.*

---

## Project status

- [x] Concept defined
- [x] Complete technical specifications
- [x] Components selected
- [x] Industrial application cases documented
- [ ] Mechanical design (STEP/STL drawings) (pending)
- [ ] Electronic schematic (KiCad) (pending)
- [ ] Controller PCB (pending)
- [ ] Firmware (C++ for STM32) (pending)
- [ ] Functional prototype (pending)

---

## License

Copyright © 2026 Enrique Aguayo. All rights reserved.

**Permitted:** Non‑commercial use for educational or research purposes. Unmodified distribution with attribution.

**Prohibited without express written authorization:** Commercial use, modification for production environments, distribution of modified versions.

For commercial licenses: eaguayo@migst.cl

---

## Author

**Enrique Aguayo H.** – Mackiber Labs  
Contact: eaguayo@migst.cl  
ORCID: 0009-0004-4615-6825  
GitHub: @enriqueherbertag-lgtm

*Documentation assisted by DeepSeek (AI).*
