#include <elapsedMillis.h>

#include "capteur.h"
#include "data.h"
#include "display.h"
#include "wifi.h"
#include "NTPclient.h"

elapsedMillis timer;

#define SLEEP_TIME_OUT 10000
int taps = 0;

#define SLEEP_DEBUG 0

/////////////////////////// SETUP
void setup() {

#ifdef SLEEP_DEBUG || WIFI_DEBUG || API_DEBUG
  Serial.begin(115200);
#endif

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
  timer = 0;
}

/////////////////////////// LOOP
void loop() {
  bool updateNeeded = false;
  int day_delta = 0;
  int when = -1;

#ifdef SLEEP_DEBUG || WIFI_DEBUG || API_DEBUG
  if (Serial.available()) {
    taps = Serial.parseInt();
    while (Serial.available()) {
      Serial.read();
    }
  }
#endif

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
  
  if (timer > SLEEP_TIME_OUT) {
#ifdef SLEEP_DEBUG
    Serial.println("GO_TO_SLEEP");
#endif
    ESP.deepSleep(0);
  }
}
