#ifndef __CAPTEUR_H__
#define __CAPTEUR_H__

#include <Wire.h>

#define REQUEST_PIN   D4  // ESP8266 ALL except D0 (GPIO16)
#define SDA_PIN       D1  // ESP8266 D1-GPIO5 is I2C SDA_PIN Go to Digispark P0_PIN
#define SCL_PIN       D2  // ESP8266 D2-GPIO4 is I2C SDA_PIN Go to Digispark P2_PIN

#define SLAVE_ADDR    0x27

extern bool setMode;
extern uint8_t incomingByte;

void tapSensInit();
void tapSens();
void tapSensRequestMode();

#endif /*__CAPTEUR_H__*/
