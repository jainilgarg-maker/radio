# Static Jr.
* A premium, retro-style FM radio built from an ESP32-C3 supermini.

## 

## Overview
This project is part of a 
### Key Features
* **Industrial Controls:** Uses RV24YN20S potentiometers for a smooth, weighted tuning feel.
* **Premium Power:** 16mm Latching stainless steel button (no LED for a clean retro look).
* **Signal Strength:** 76cm telescoping antenna for 1/4 wave resonance.

## Hardware
### Pin Configuration
Due to the PCB layout, the I2C pins for the OLED and Radio module are:
* **SCL:** GPIO 8
* **SDA:** GPIO 9

### Main Components
* **MCU:** ESP32-C3 SuperMini
* **Radio:** RDA5807M FM Module
* **Amp:** PAM8403 (driving 2x 3W Cavity Speakers)

## Repository Map
* `/Hardware`: Contains the EasyEDA JSON and Gerber files.
* `/Code`: Arduino sketch and required libraries.
* `/Docs`: Wiring diagrams and 3D case renders.

## BOM (Bill of Materials)
| Part | Description | Source |
| :--- | :--- | :--- |
| ESP32-C3 | Microcontroller | [Link] |
| RV24YN20S | 10k Potentiometer | [Link] |
| ... | ... | ... |
