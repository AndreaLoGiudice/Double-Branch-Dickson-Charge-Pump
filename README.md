# Dickson Charge Pump — Frequency-Controlled Voltage Regulator

An interleaved dual-phase Dickson charge pump that steps up 3.3 V to a
regulated output of up to 12 V, controlled by an Arduino Nano 33 IoT and
operable remotely through a custom web dashboard.

The output voltage is regulated by varying the clock frequency driving the
pump — rather than the more common duty-cycle or shunt-regulator approaches —
exploiting the well-known relationship between clock frequency and output
impedance in the Slow Switching Limit (SSL) regime.

This repository accompanies the bachelor's thesis *"Pompa di carica di Dickson a doppio ramo: dalla prototipazione su breadboard all'integrazione su PCB controllata tramite piattaforma IoT"*
(University of Catania, Department of Electrical, Electronics and Computer
Engineering, A.Y. 2025/2026). The full theoretical background, design
rationale, and experimental results are documented in the thesis; this
repository contains the accompanying source files.

## Overview

- **Topology:** Dickson voltage multiplier, dual-phase interleaved (4 stages
  per branch), to reduce output impedance for a non-negligible load current
  (~1 mA @ 12 kΩ).
- **Pumping capacitors:** 2.2 µF X7R (50 V), sized to compensate for DC-bias
  derating.
- **Rectifying diodes:** BAT54 Schottky.
- **Clock buffer:** SN74LVC2G34 dual non-inverting buffer (3.3 V), driving
  each clock line through a series resistor, dimensioned via SPICE
  parametric sweep to stay within the device's absolute maximum ratings.
- **Control:** Arduino Nano 33 IoT reads the output voltage through a
  resistive divider and 12-bit ADC, and adjusts the clock frequency to reach
  a target voltage set remotely.
- **Remote interface:** a web dashboard communicates with the board through
  Firebase Realtime Database, allowing live voltage monitoring and frequency
  control from any browser.

## Repository structure
├── Firmware/         
├── WebApp/            
├── PCB/              
├── Simulation/        
└── README.md

### `Firmware/`
Arduino sketch for the Nano 33 IoT. Generates the complementary CK / CK_INV
clock signals with a non-blocking generator based on `micros()`, reads the
output voltage through the feedback divider, and synchronizes with Firebase
Realtime Database (voltage readout out, target half-period in).

### `WebApp/`
Single-page dashboard (Tailwind CSS + Chart.js) that subscribes to the
output voltage in real time and lets the user set the clock frequency via a
slider, writing directly to the Firebase database node consumed by the
firmware.

### `PCB/`
Altium Designer source project for the two-layer PCB (schematic, layout,
3D view), plus a PDF export of the schematic for quick reference without
Altium installed. 

### `Simulation/`
LTspice netlist used to size the clock buffer's series resistance and
pumping capacitance, with parametric sweeps on both, and to verify peak/
average current against the buffer's datasheet limits before finalizing the
PCB design.


## Results

At 1 kHz clock frequency and a 12 kΩ load, the assembled PCB reaches
**12.4 V** output, closely matching the theoretical SSL model (R_out ≈
1.5 kΩ) derived and verified in simulation. See Chapter 5 of the thesis for
the full frequency characterization and the comparison against the
breadboard prototype.


## Author

Andrea Lo Giudice — Bachelor's Thesis in Electronic Engineering,
University of Catania, A.Y. 2025/2026.
Supervisor: Prof. Andrea Ballo.

