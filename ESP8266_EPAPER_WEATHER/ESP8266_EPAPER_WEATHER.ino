#include <Ticker.h>
#include <ESP8266WiFi.h>

#include "NTPclient.h"
#include "weather.h"
#include "energy.h"
#include "imagedata.h"
#include "display.h"

#define WIFI_SSID     "Chevrette"
#define WIFI_PWD      "ch0c0latchienjaune"

// #define WIFI_SSID     "Flying-Phone-N"
// #define WIFI_PWD      "PASS"

#define REQ_INTERVAL_SEC  20

bool requestFlag = false;
Ticker ticker;

void tickerHandler();
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
  initDisplay();

  /* Initialize NTPClient library */
  timeClientBegin();

  /* Set ticker as 1 minutes */
  ticker.attach(REQ_INTERVAL_SEC, tickerHandler);

}

/////////////////////////// LOOP
void loop() {

  if (requestFlag) {
    if ( requestWeatherDaily() && requestWeatherForecast() && energyUpdate() ) {   // Get informations
      Draw_EPD();
    }
    // delay(3000);
    requestFlag = false;
  }
}

void tickerHandler() {
  /* If you call requestWeatherInfo directly inside ticker callback function, HttpClient doesn't work properly */
  requestFlag = true;
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
