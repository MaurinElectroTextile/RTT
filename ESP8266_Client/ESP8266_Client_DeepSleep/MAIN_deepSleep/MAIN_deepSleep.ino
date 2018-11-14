#include "capteur.h"
#include "data.h"
#include "display.h"
#include "wifi.h"
#include "NTPclient.h"

#define SLEEP

int taps = 0;

/////////////////////////// SETUP
void setup() {
  Serial.begin(115200);
  /* Initialize GxEPD library */
  displayInit();

  Draw_loadingIcon();

  if (!wifiSetup()) {
    while (1);
  }

  /* Initialize NTPClient library */
  timeClientBegin();

  /* Initialize tapSens sensor communication module */
  tapSensInit();

  /* Request taps count from extarnal MCU (Digispark-ATTiny85) */
  taps = tapSensRequest();
  // delay(100);
}

/////////////////////////// LOOP
void loop() {
  bool updateNeeded = false;
  int day_delta = 0;
  int when = -1;

  if (Serial.available()) {
    taps = Serial.parseInt();
    while (Serial.available()) {
      Serial.read();
    }
  }
  switch (taps) {
    case 0:
      //Serial.println("GO_TO_SLEEP");
      //ESP.deepSleep(0);
      break;
    case 1:
      when = DATA_TODAY;
      day_delta = 0;
      updateNeeded = true;
      break;
    case 2:
      when = DATA_TOMORROW;
      day_delta = +1;
      updateNeeded = true;
      break;
    case 3:
      when = DATA_YESTERDAY;
      day_delta = -1;
      updateNeeded = true;
      break;
    default:
      break;
  }
  if (updateNeeded) {
    timeClientUpdate();
    getDay(day_delta);
    Draw_loadingIcon();
    fetchData(when);
    Draw_EPD(when);
    Serial.println("GO_TO_SLEEP");
    ESP.deepSleep(0);
  }
}
