#include <ESP8266WiFi.h>

#include "capteur.h"
#include "NTPclient.h"
#include "weather.h"
#include "energy.h"
#include "imagedata.h"
#include "display.h"

//#define WIFI_SSID     "Les_Bernards"
//#define WIFI_PWD      "michtopatato"

#define WIFI_SSID     "Chevrette"
#define WIFI_PWD      "ch0c0latchienjaune"

bool configWiFi();

boolean DEBUG_WIFI = true;
boolean DEBUG = true;

// #define SLEEP 

/////////////////////////// SETUP
void setup() {
  if (DEBUG_WIFI) Serial.begin(115200);

  if (!configWiFi()) {
    if (DEBUG_WIFI) Serial.println("ERROR: configESP");
    while (1);
  }

  /* Initialize GxEPD library */
  displayInit();

  /* Initialize NTPClient library */
  timeClientBegin();
  timeClientUpdate();

  tapSensInit();
}

/////////////////////////// LOOP
void loop() {

  tapSens();

  switch (incomingByte) {
    case 1:
      if (DEBUG) Serial.println("Today");
      Draw_EPD();
#ifdef SLEEP
      if (DEBUG) Serial.println("GO_TP_SLEEP");
      ESP.deepSleep(0);
      if (DEBUG) Serial.println("WAKE_UP");
#endif /*__SLEEP__*/
      incomingByte = 0;
      break;
    case 2:
      if (DEBUG) Serial.println("Tomorrow");
      Draw_EPD();
#ifdef SLEEP
      if (DEBUG) Serial.println("GO_TP_SLEEP");
      ESP.deepSleep(0);
      if (DEBUG) Serial.println("WAKE_UP");
#endif /*__SLEEP__*/
      incomingByte = 0;
      break;
    case 3:
      if (DEBUG) Serial.println("Yesterday");
      Draw_EPD();
#ifdef SLEEP
      if (DEBUG) Serial.println("GO_TP_SLEEP");
      ESP.deepSleep(0);
      if (DEBUG) Serial.println("WAKE_UP");
#endif /*__SLEEP__*/
      incomingByte = 0;
      break;
    default:
      // default
      break;
  }
}

bool configWiFi() {
  if (DEBUG_WIFI) Serial.println();

  if (!WiFi.begin(WIFI_SSID, WIFI_PWD)) {
    if (DEBUG_WIFI) Serial.println("ERROR: WiFi.begin");
    return false;
  }
  if (DEBUG_WIFI) Serial.println("OK: WiFi.begin");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    if (DEBUG_WIFI) Serial.print(".");
  }
  if (DEBUG_WIFI) Serial.println();
  if (DEBUG_WIFI) Serial.println("OK: WiFi connected");
  return true;
}
