# IR LED Control with Arduino

This project involves setting up 5 IR transmitters around a room to control the corresponding LEDs on a handheld device. The LEDs will turn on when the device is within range of an "on" signal transmitter and turn off when it moves into the range of the "off" transmitter. The setup mimics the child's game "Hot or Cold."

## Hardware Components

- 1 Arduino Uno R3
- 6 Arduino Nanos (5 for "on" transmitters and 1 for the "off" transmitter)
- TSOP1738 IR receivers
- IR LEDs
- Regular LEDs
- Breadboard and jumper wires
- Custom 3D-printed handheld device (optional for prototype)

## Software Components

- Arduino IDE
- IRremote library

## Project Setup
`led on the receiver is arranged on pin 4 through to 8`