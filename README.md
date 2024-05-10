# IoT Relay Control System with IR Sensor

## Overview
This project is aimed at controlling four relays wirelessly using an IR sensor. The relays can be used to switch various electrical appliances on or off remotely. The system utilizes an IR sensor to detect infrared signals from a remote control, which triggers the corresponding relay to turn the connected device on or off.

## Features
- Control up to four electrical appliances remotely.
- Use of IR sensor for wireless communication.
- Simple and intuitive interface.

## Components
- Arduino board (e.g., Arduino Uno)
- IR sensor module
- Four-channel relay module
- Infrared remote control
- Electrical appliances/devices to control
- Jumper wires
- Breadboard (optional)

## Installation
1. Connect the IR sensor module to the Arduino board as per the wiring diagram provided.
2. Connect the four-channel relay module to the Arduino board following the wiring diagram.
3. Upload the provided Arduino sketch (`ir-receiver-cooler.ino`) to the Arduino board.
4. Power up the Arduino board.

## Usage
1. Point the infrared remote control towards the IR sensor.
2. Press the corresponding buttons on the remote control to turn the relays on or off.
3. The relay modules will switch the connected electrical appliances/devices accordingly.

## Wiring Diagram
![Wiring Diagram](link_to_wiring_diagram_image)

## Notes
- Ensure that the electrical appliances/devices connected to the relays do not exceed the relay module's maximum load capacity.
- Keep the IR sensor module unobstructed for proper reception of infrared signals from the remote control.
- Customize the Arduino sketch as needed for additional functionality or specific requirements.

## Contributors
- [Deepak Kandpal](deepakkandpal2009@gmail.com) - Project Lead & Developer

## License
This project is licensed under the [MIT License](LICENSE).

---

Markdown is a versatile format for documentation, making it easy to read and edit. Let me know if you need any further adjustments!
