/*
This is 2-part sketch for Arduino Uno for generating
keyboard events when muscle activation 
is detected by uMyo. It's based on Arduino HID Project
(https://github.com/NicoHood/HID).
Current part runs on atmega328 with connected nRF24
module and sends character 's' when muscle contraction
is detected
*/

#include <uMyo_RF24.h>

int rf_cen = 10; //nRF24 chip enable pin
int rf_cs = 9; //nRF24 CS pin

void setup() {
  Serial.begin(115200);
  uMyo.begin(rf_cs, rf_cen);
}

uint32_t last_print_ms = 0;
uint16_t plvl = 0;
uint16_t p2lvl = 0;
uint16_t p3lvl = 0;

void loop() 
{
  uMyo.run(); //need to call this really often, therefore
  //no delays can be used in the code
  uint32_t ms = millis();
  int dev_count = uMyo.getDeviceCount(); //if more than one device is present, show all of them
  if(dev_count < 1) { delay(3); return; }
  uint16_t lvl = uMyo.getAverageMuscleLevel(0);
  int dd = lvl - p3lvl;
  p3lvl = p2lvl;
  p2lvl = plvl;
  plvl = lvl;
  if(dd > 30) Serial.print('s'); //send to atmega16u2 so it would generate HID event
  delay(2);
}
