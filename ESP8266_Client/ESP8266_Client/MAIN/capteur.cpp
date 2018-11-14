#include <Arduino.h>
#include <Wire.h>

#include "capteur.h"

#define REQUEST_PIN   D4  // ESP8266 ALL except D0 (GPIO16)
#define SDA_PIN       D1  // ESP8266 D1-GPIO5 is I2C SDA_PIN Go to Digispark P0_PIN
#define SCL_PIN       D2  // ESP8266 D2-GPIO4 is I2C SDA_PIN Go to Digispark P2_PIN

#define SLAVE_ADDR    0x27


bool getMode;


void tapSensRequestMode(void) {
  getMode = true;
}

int tapSens(void) {
  if (getMode) {
    getMode = false;
    Wire.requestFrom(SLAVE_ADDR, 1); // request one byte from slave
    while (Wire.available()) {
      return Wire.read();
    }
  }
  return 0;
}

void tapSensInit(void) {
  getMode = false;
  pinMode(REQUEST_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REQUEST_PIN), tapSensRequestMode, FALLING);
  Wire.begin(SDA_PIN, SCL_PIN);
}
