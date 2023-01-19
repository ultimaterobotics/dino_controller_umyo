/*
This is 2-part sketch for Arduino Uno for generating
keyboard events when muscle activation 
is detected by uMyo. It's based on Arduino HID Project
(https://github.com/NicoHood/HID).
Current part runs on atmega16u2 of Arduino Uno, it listens
for 's' symbol from atmega328 and generates UP_ARROW press
when it gets it
*/

#include "Keyboard.h"
#include "HID.h"

void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  Serial1.begin(115200);
  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}

void loop() {
  // Check if any Serial data from the IO MCU was received
  char c = Serial1.read();
  if (c == 's')
  {
    Keyboard.write(KEY_UP_ARROW);
  }
}
