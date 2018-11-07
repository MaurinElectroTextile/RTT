#ifndef __WEATHER_H__
#define __WEATHER_H__

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define WEATHER_API_CERT_HOST  "api.openweathermap.org"
#define WEATHER_API_CERT_PORT  443
#define WEATHER_API_CERT_FP    "6C 9D 1E 27 F1 13 7B C7 B6 15 90 13 F2 D0 29 97 A4 5B 3F 7E"

#define REGION        "paris"
#define COUNTRY       "fr"
#define APPID         "2754590248e99a371c9a0f245a6d9d50"

typedef struct weather {
  double temp;
  int humidity;
  int temp_min;
  int temp_max;
  // int windSpeed;
  // int windDirection;
  int conditionId;
  String weatherName;
  String weatherType;
  String _time;
} weather_t;

extern weather_t weatherInfos;

boolean requestWeatherDaily();
void parseWeatherJson(String& buffer);
boolean requestWeatherForecast();
void parseWeatherForecastJson(String& buffer);
boolean requestWeatherPrevious(); // TODO

const char* parseWeatherCondition(int conditionId);
void drawWeatherIcon(int conditionId);

#endif /*__WEATHER_H__*/
