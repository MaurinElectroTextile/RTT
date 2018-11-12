#include <Arduino.h>
#include "capteur.h"

bool getMode = false;
uint8_t incomingByte = 0;

void tapSensRequestMode() {
  getMode = true;
}

void tapSens() {
  if (getMode) {
    Wire.requestFrom(SLAVE_ADDR, 1); // request one byte from slave
    while (Wire.available()) {
      incomingByte = Wire.read();
    }
    getMode = false;
  }
}

void tapSensInit() {
  pinMode(REQUEST_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REQUEST_PIN), tapSensRequestMode, FALLING);
  Wire.begin(SDA_PIN, SCL_PIN);
}
