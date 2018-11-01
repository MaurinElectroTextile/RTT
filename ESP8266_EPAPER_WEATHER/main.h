#ifndef __MAIN_H__
#define __MAIN_H__

#include <ArduinoJson.h>
#include <Ticker.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <Fonts/DSDIGIT9pt7b.h>
#include <Fonts/DSDIGIT30pt7b.h>

#include "imagedata.h"

#define WIFI_SSID     "Chevrette"
#define WIFI_PWD      "ch0c0latchienjaune"
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

/* BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO5, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V */
/* I've changed CS pin from GPIO15 to GPIO5 as Waveshare EPD makes GPIO15 high when NodeMCU restarts. */
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
