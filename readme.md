# IR LED Control with Arduino

This project involves setting up 5 IR transmitters around a room to control the corresponding LEDs on a handheld device. The LEDs will turn on when the device is within range of an "on" signal transmitter and turn off when it moves into the range of the "off" transmitter. The setup mimics the child's game "Hot or Cold."

## Hardware Components

- 1 Arduino Uno R3
- 6 Arduino Nanos (5 for "on" transmitters and 1 for the "off" transmitter)
- TSOP1738 IR receivers
- IR LEDs
- Regular LEDs
- Resistors (for LEDs and IR LEDs)
- Breadboard and jumper wires
- Custom 3D-printed handheld device (optional for prototype)

## Software Components

- Arduino IDE
- IRremote library

## Project Setup

### IR Transmitter Code

Each transmitter will emit a specific IR signal. Use the following code for the IR transmitters:

```cpp
#include <IRremote.h>

// Define the IR transmitter pin
int irPin = 3;

// Define unique IR codes for each transmitter
unsigned long irCodeOn = 0x10;  // Example code for "on" transmitter
unsigned long irCodeOff = 0x1FE58A7; // Example code for "off" transmitter

IRsend irsend;

void setup() {
  pinMode(irPin, OUTPUT);
  irsend.begin();
}

void loop() {
  // Change the IR code and delay as needed for each transmitter
  irsend.sendNEC(irCodeOn, 32);  // For "on" transmitter
  // irsend.sendNEC(irCodeOff, 32); // For "off" transmitter

  delay(100);  // Adjust delay as needed
}
