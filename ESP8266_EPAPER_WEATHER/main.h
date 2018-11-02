#ifndef __MAIN_H__
#define __MAIN_H__

#include <ArduinoJson.h>
#include <Ticker.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Fonts/DSDIGIT9pt7b.h"
#include "Fonts/DSDIGIT30pt7b.h"

#include "imagedata.h"

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

GxIO_Class io(SPI, SS, 0, 2);
GxEPD_Class display(io);

void tickerHandler();
bool configWiFi();
void requestWeatherInfo();
void parseWeatherJson(String buffer);
void requestWeatherForecastInfo();
void parseWeatherForecastJson(String buffer);
const char* parseWeatherCondition(int conditionId);

#endif /*__MAIN_H__*/
