# 🐟 Bio-Inspired Flapping Mechanism Underwater Vehicle

A **bio-inspired, servo-driven underwater vehicle** using **sinusoidal flapping fins** for efficient, low-disturbance propulsion.  
This project demonstrates **gear- and servo-based fin actuation**, **ballast control**, and a **hydrodynamically optimized fuselage** modeled on fish-tail locomotion principles.

---

## 🔍 Problem Addressed
- Conventional underwater vehicles rely on **propellers**, which disturb the surrounding water, reducing visibility.  
- **Underwater inspection**, **surveillance**, and **tracking** are limited by poor maneuverability and turbulence.  
- There is a need for an **energy-efficient**, **stable**, and **low-noise underwater system** for research, monitoring, and exploration tasks.

---

## 🎯 Objectives
- Develop a **lightweight**, **affordable** Remotely Operated Underwater Vehicle (ROUV) for **marine applications**.  
- Achieve **high hydrodynamic efficiency** using **bio-inspired flapping fins** instead of propellers.  
- Enable **underwater vision**, **monitoring**, **intelligence gathering**, and **tracking** through smooth propulsion control.

---

## ⚙️ Proposed Technology / Solution
- Replace traditional **propeller-based propulsion** with **flapping foil mechanisms** that mimic **fish-tail hydrodynamics**.  
- Implement **sinusoidal motion** by tuning amplitude, phase, and frequency to generate thrust and lift.  
- Two flapping mechanisms proposed:  
  - ⚙️ **Gear-based mechanism**  
  - 🔧 **Servo-based mechanism** (fins attached directly to servo horns)  
- The ROV includes **four fins** (two forward, two rear) for stable lift and propulsion.

---

## 🧠 Prototype Block Diagram

```
+----------------------+
|       Arduino        |
+----------------------+
           |
           v
+----------------------+
|  Adafruit PWM Driver |
|  (16-channel)        |
+----------------------+
      |       |       |
      v       v       v
+--------+ +--------+ +--------+
| Servo1 | | Servo2 | ... Servo8
+--------+ +--------+ +--------+
      \         |         /
       \        |        /
        \       |       /
         \      |      /
          +--------------------+
          |     Flapping       |
          |  Motion Control    |
          +--------------------+
           - Sinusoidal motion
           - Phase offsets
           - Amplitude control
           - Mirrored servos
```

---

## ⚡ Block Diagram – Actual Bio-Inspired ROUV Model

```
 ┌──────────────────────────────────────────────────────────────┐
 │                      CONTROL UNIT                            │
 │  • Microcontroller and Processors (Arduino UNO + Raspberry Pi)│
 │  • RMCS2303 Servo Driver Communication                        │
 │  • Sensor Inputs (IMU, Depth, Pressure, etc.)                 │
 │  • Serial / I²C Communication                                 │
 └──────────────────────────────────────────────────────────────┘
                     │                 │
                     │ I²C / Serial    │
                     ▼                 ▼
 ┌────────────────────────────┐   ┌────────────────────────────┐
 │  SERVO DRIVER (PCA9685)   │   │ LINEAR ACTUATOR CONTROL    │
 │ • Controls flapping fins   │   │ • Drives ballast actuator  │
 │ • Generates PWM for 8 servos│  │ • Position/Speed feedback  │
 └────────────────────────────┘   └────────────────────────────┘
          │ │ │ │                         │ │
          ▼ ▼ ▼ ▼                         ▼ ▼
 ┌────────────────────────────┐     ┌────────────────────────────┐
 │   FLAPPING FIN MECHANISM   │     │     BALLAST SYSTEM         │
 │ • 4 fins (2 front, 2 rear) │     │ • Linear actuator & syringes│
 │ • Sinusoidal heave/pitch   │     │ • Controls buoyancy         │
 │ • Generates thrust/lift     │     │ • Controlled via Arduino    │
 └────────────────────────────┘     └────────────────────────────┘
          │
          ▼
 ┌────────────────────────────┐
 │   UNDERWATER VEHICLE BODY  │
 │ • Fuselage & frame (NACA0012 foil) │
 │ • Waterproof electronics housing    │
 │ • Encoder feedback for motion control│
 └────────────────────────────┘
          │
          ▼
 ┌────────────────────────────┐
 │   MONITORING & CONTROL GUI │
 │ • PC-based or Raspberry Pi interface │
 │ • Serial telemetry visualization     │
 │ • Displays fin angles, thrust, sensors│
 └────────────────────────────┘
```

---

## 💻 Code Overview
This project uses **Arduino C++** with **Adafruit PWM driver** and **RMCS2303 motor driver** libraries.

### **Key Functional Blocks**
| Function | Description |
|-----------|-------------|
| `angleToPulse()` | Converts servo angle to PWM pulse width. |
| `finSineWave()` | Generates sinusoidal motion using `sin()` and `atan()`. |
| `rmcs.WRITE_PARAMETER()` | Configures motor driver parameters (control mode, speed, gains). |
| `rmcs.Absolute_position()` | Moves actuator to absolute position. |
| `rmcs.Position_Feedback()` | Reads encoder feedback. |
| `rmcs.SET_HOME()` | Sets zero position reference. |
| `rmcs.ESTOP()` | Emergency stop for motor safety. |

---

## 🤖 Machine Learning Optimization (My Role)
As the **ML Engineer**, I optimized the fin motion parameters (frequency, amplitude, phase offset) to maximize thrust and efficiency:
- **Model:** Trained an **XGBoost regression model** on 810 physical tank trial data points to predict thrust and power (R² 0.95).
- **Optimization:** Ran a fine-grained grid search using the model, reducing physical testing time from months to hours.
- **Deployment:** Deployed the validated optimal parameters as a static lookup table on the embedded controller.

---

## 🧠 Working Principle
- **Four fins** perform **sinusoidal heaving and pitching** motions with **phase differences** (0°, 90°, 180°, 270°).  
- The motion generates **forward thrust** and **lift**, propelling the vehicle smoothly underwater.  
- **Ballast system** adjusts buoyancy for depth control.  
- **Raspberry Pi / PC GUI** monitors data and allows manual or autonomous control.

---
