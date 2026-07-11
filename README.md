# Dickson Charge Pump — Frequency-Controlled Voltage Regulator

An interleaved dual-phase Dickson charge pump that steps up 3.3 V to a
regulated output of up to 12 V, controlled by an Arduino Nano 33 IoT and
operable remotely through a custom web dashboard.

The output voltage is regulated by varying the clock frequency driving the
pump — rather than the more common duty-cycle or shunt-regulator approaches —
exploiting the well-known relationship between clock frequency and output
impedance in the Slow Switching Limit (SSL) regime.

This repository accompanies the bachelor's thesis *"[Titolo della tesi]"*
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
├── Firmware/         Arduino sketch (clock generation, ADC feedback, Firebase sync)
├── WebApp/            Web dashboard (HTML/CSS/JS, Chart.js, Firebase client)
├── PCB/               Altium Designer project, schematic export, Gerber files
├── Simulation/        LTspice files used for buffer/clock-driver verification
└── README.md
