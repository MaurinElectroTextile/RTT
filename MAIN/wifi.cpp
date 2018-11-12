#include <ESP8266WiFi.h>

#include "wifi.h"

#define WIFI_DEBUG  1

#define WIFI_SSID     "SSID"
#define WIFI_PWD      "PASS"


bool wifiSetup(void) {
#ifdef WIFI_DEBUG
  Serial.println();
#endif

  if (!WiFi.begin(WIFI_SSID, WIFI_PWD)) {
#ifdef WIFI_DEBUG
    Serial.println("ERROR: WiFi.begin");
#endif
    return false;
  }
#ifdef WIFI_DEBUG
  Serial.println("OK: WiFi.begin");
#endif

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
#ifdef WIFI_DEBUG
    Serial.print(".");
#endif
  }
#ifdef WIFI_DEBUG
  Serial.println();
  Serial.println("OK: WiFi connected");
#endif
  return true;
}
