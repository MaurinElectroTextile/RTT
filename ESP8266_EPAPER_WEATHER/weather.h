#ifndef __WEATHER_H__
#define __WEATHER_H__

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

String JsonStr;
DynamicJsonBuffer jsonBuffer;

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

weather_t weatherInfos;

boolean requestWeatherInfo();
void parseWeatherJson(String buffer, weather_t* weatherPtr);
boolean requestWeatherForecastInfo();
void parseWeatherForecastJson(String buffer, weather_t* weatherPtr);

const char* parseWeatherCondition(int conditionId);
void drawWeatherIcon(int conditionId);

#endif /*__WEATHER_H__*/
