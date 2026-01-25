# Static Jr.
* A premium, retro-style FM radio built from an ESP32-C3 supermini.

## The Vision
Most radios these days are either cheap kid's toys, or annoying phone apps that drain your data, so it occured to me to make a radio that is based upon what the retro radio was really about: Raw Mechanical Interaction. In order to fulfill this goal, I tried to make this radio feel as physically pleasing as possible. This radio, featured with industrial-grade metal controls and an expandable telescopic antennae, is a device on which every click is satisfying, every note is deep, and every frequency change is felt. You see, a radio isn't just about listening to music, its about the satification of operating a high-performance machine.



## Overview
This project is part of a Blueprint project, and so i was limited to a budget of $50, which is still plenty of money to make this radio high-quality. For this project, a 3-d printed enclosure is going to house all the elctronic, and its going to have a headphone jack and usb c cable poking out of it for charging. It offers a retro look and feel, while maintaining high sound clarity with not only one but two stereo speakers. It also features a 0.96'' OLED screen allowing for battery, volume, and even radio channel indicators. Two rotary encoders allow to tune the radio aswell as change the volume.
### Key Features
* **Industrial Controls:** Uses RV24YN20S potentiometers for a smooth, weighted tuning feel.
* **Premium Power:** stainless steel buttons have a clicky and premium feel.
* **Signal Strength:** telescopinc antenna for better sound clarity.

### Design Screenshots

<img width="560" height="320" alt="Screenshot 2026-01-17 194256" src="https://github.com/user-attachments/assets/e2d222f7-c158-4158-94b5-45e2f982d574" />

<img width="308" height="398" alt="Screenshot 2026-01-17 194440" src="https://github.com/user-attachments/assets/9994423d-2732-42f0-888c-05250d7d82cb" />

<img width="684" height="467" alt="image" src="https://github.com/user-attachments/assets/7e1a2c33-1996-4839-b761-29b6ce4404fe" />


### Main Components
* **Microcontroller:** ESP32-C3 SuperMini
* **Radio:** RDA5807M FM Module
* **Amp:** PAM8403 (driving 2x 3W 4ohm Speakers)
* **0.96'' OLED** (displays information)

## Repository Map
* `/Hardware`: Contains the EasyEDA JSON and Gerber files.
* `/Code`: Arduino sketch.
* `/Docs`: Wiring diagram, Bill of Material, 3D printed case, and case with components adjusted in it.


<img width="1321" height="393" alt="Screenshot 2026-01-17 194653" src="https://github.com/user-attachments/assets/5d8e04ca-9514-4477-8ca8-db2066ad6b52" />

