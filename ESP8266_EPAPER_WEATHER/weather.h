#ifndef __WEATHER_H__
#define __WEATHER_H__

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

extern String JsonStr;
extern DynamicJsonBuffer jsonBuffer;

#define REGION        "paris"
#define COUNTRY       "fr"
#define APPID         "2754590248e99a371c9a0f245a6d9d50"

typedef struct weather {
  double temp;
  int humidity;
  int temp_min;
  int temp_max;
  int windSpeed;
  int windDirection;
  int conditionId;
  String weatherName;
  String weatherType;
  String _time;
} weather_t;

extern weather_t weatherInfos;

boolean requestWeatherInfo();
void parseWeatherJson(String buffer);
boolean requestWeatherForecastInfo();
void parseWeatherForecastJson(String buffer, weather_t* weatherPtr);

const char* parseWeatherCondition(int conditionId);
void drawWeatherIcon(int conditionId);

#endif /*__WEATHER_H__*/
