#include "capteur.h"
#include "data.h"
#include "display.h"
#include "wifi.h"
#include "NTPclient.h"

/////////////////////////// SETUP
void setup() {
  Serial.begin(115200);

  if (!wifiSetup()) {
    while (1);
  }

  /* Initialize GxEPD library */
  displayInit();

  /* Initialize NTPClient library */
  timeClientBegin();

  /* Initialize tapSens sensor communication module */
  tapSensInit();
}

/////////////////////////// LOOP
void loop() {
  bool updateNeeded = false;
  int day_delta = 0;
  int when = -1;
  int taps = tapSens();

  if (Serial.available()) {
    taps = Serial.parseInt();
    while (Serial.available()) {
      Serial.read();
    }
  }
  switch (taps) {
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
  }
}
