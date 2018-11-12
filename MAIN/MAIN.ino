#include <ESP8266WiFi.h>

#include "capteur.h"
#include "NTPclient.h"
#include "data.h"
#include "imagedata.h"
#include "display.h"

//#define WIFI_SSID     "Les_Bernards"
//#define WIFI_PWD      "michtopatato"

#define WIFI_SSID     "Chevrette"
#define WIFI_PWD      "ch0c0latchienjaune"

bool configWiFi();

boolean DEBUG_WIFI = true;
boolean DEBUG = true;

#define SLEEP

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
  bool updateNeeded = false;

  int taps = tapSens();

  if (Serial.available()) {
    taps = Serial.parseInt();
    while (Serial.available()) {
      Serial.read();
    }
  }
  switch (taps) {
    case 1:
    case 2:
    case 3:
      updateNeeded = true;
      break;
    default:
      break;
  }
  if (updateNeeded) {
    int when = taps - 1;
    fetchData(when);
    Draw_EPD(when);
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
