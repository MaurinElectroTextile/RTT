#include <Ticker.h>
#include <ESP8266WiFi.h>

#include "weather.h"
#include "energy.h"
#include "imagedata.h"
#include "display.h"

// #define WIFI_SSID     "Chevrette"
// #define WIFI_PWD      "ch0c0latchienjaune"

// #define WIFI_SSID     "Chateau_Chirac"
// #define WIFI_PWD      "Chirac_2014"

#define WIFI_SSID     "Flying-Phone-N"
#define WIFI_PWD      "salami42"

#define REGION        "paris"
#define COUNTRY       "fr"
#define APPID         "2754590248e99a371c9a0f245a6d9d50"

#define REQ_INTERVAL_SEC  60

#define WEATHER_ICON_WIDTH  72
#define WEATHER_ICON_HEIGHT 72

bool requestFlag = false;
Ticker ticker;
String JsonStr;
DynamicJsonBuffer jsonBuffer;

/* 
BUSY    D2-GPIO4
RST     D4-GPIO2
DC      D3-GPIO0
CS      D1-GPIO5 (I've changed CS pin from GPIO15 to GPIO5 as Waveshare EPD makes GPIO15 high when NodeMCU restarts).
CLK     D5-GPIO14
DIN     D7-GPIO13
GND     GND
3.3V    3.3V 
*/

void tickerHandler();
bool configWiFi();


void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  if (!configWiFi()) {
    Serial.println("ERROR: configESP");
    while (1);
  }

  /* Initialize GxEPD library */
  display.init();

  /* Set ticker as 10 minutes */
  ticker.attach(REQ_INTERVAL_SEC, tickerHandler);

  /* Get weather information */
  requestWeatherInfo();
  delay(3000);
  requestWeatherForecastInfo();
}

void loop() {
  /* Every 10 minutes */
  if (requestFlag) {
    if ( requestWeatherInfo() ) {
      Draw_EPD(&weatherInfos);
    }
    delay(3000);
    if ( requestWeatherForecastInfo() ) {
      Draw_EPD(&weatherInfos);
      requestFlag = false;
    }
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
