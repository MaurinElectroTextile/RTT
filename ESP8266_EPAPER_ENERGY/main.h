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

// ID Client a0cc3284-c19b-4c6c-95a3-4afbe1cebf9a
// ID Secret ba75bc1d-b85a-4501-9f5f-6cc7c4a4a9f2 
#define APPID         "ba75bc1d-b85a-4501-9f5f-6cc7c4a4a9f2"

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
void requestEnergyInfo();
void parseEnergiJson(String buffer);
void requestEnergyForecastInfo();
void parseEnergyForecastJson(String buffer);
const char* parseEnergyCondition(int conditionId);

#endif /*__MAIN_H__*/
