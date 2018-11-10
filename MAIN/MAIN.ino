#include <ESP8266WiFi.h>

#include "capteur.h"
#include "NTPclient.h"
#include "weather.h"
#include "energy.h"
#include "imagedata.h"
#include "display.h"

#define WIFI_SSID     "Les_Bernards"
#define WIFI_PWD      "michtopatato"

bool configWiFi();

/////////////////////////// SETUP
void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  if (!configWiFi()) {
    Serial.println("ERROR: configESP");
    while (1);
  }

  /* Initialize GxEPD library */
  displayInit();

  /* Initialize NTPClient library */
  timeClientBegin();
  timeClientUpdate();

  tapSensInit();
  Serial.print("DONE_SETUP");
}

/////////////////////////// LOOP
void loop() {

  tapSens();

  switch (incomingByte) {
    case 1:
      Draw_EPD();
      incomingByte = 0;
      Serial.println("Today");
      //
      break;
    case 2:
      Draw_EPD();
      incomingByte = 0;
      Serial.println("Tomorrow");
      //
      break;
    case 3:
      Draw_EPD();
      incomingByte = 0;
      Serial.println("Yesterday");
      //
      break;
    default:
      // default
      break;
  }
}


bool configWiFi() {
  Serial.println();

  if (!WiFi.begin(WIFI_SSID, WIFI_PWD)) {
    Serial.println("ERROR: WiFi.begin");
    return false;
  }
  Serial.println("OK: WiFi.begin");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("OK: WiFi connected");
  return true;
}
