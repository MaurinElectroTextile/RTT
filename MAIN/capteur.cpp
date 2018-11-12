#include <Arduino.h>
#include "capteur.h"

bool getMode = false;

void tapSensRequestMode() {
  getMode = true;
}

int tapSens() {
  if (getMode) {
    Wire.requestFrom(SLAVE_ADDR, 1); // request one byte from slave
    while (Wire.available()) {
      return Wire.read();
    }
    getMode = false;
  }
  return 0;
}

void tapSensInit() {
  //pinMode(REQUEST_PIN, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(REQUEST_PIN), tapSensRequestMode, FALLING);
  Wire.begin(SDA_PIN, SCL_PIN);
}
