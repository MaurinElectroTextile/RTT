#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#include "data.h"

#define API_DEBUG 0

#define DATA_API_HOST  "api.rtt.in-net-we-trust.com"
#define DATA_API_PORT  80
#define DATA_API_URL   "/data/v1/combined/"


data_t data[DATA_COUNT];

char *data_when_lookup[] = {
  [DATA_TODAY] = "today",
  [DATA_TOMORROW] = "tomorrow",
  [DATA_YESTERDAY] = "yesterday",
};


void printData(data_t *data_p) {
  /* API Serial Output */
#ifdef DEGUG_API
  Serial.printf("Weather: Temp.: %5.2f\r\n", data_p->weather.temp);
  Serial.printf("Weather: Min. Temp.: %5.2f\r\n", data_p->weather.temp_min);
  Serial.printf("Weather: Max. Temp.: %5.2f\r\n", data_p->weather.temp_max);
  Serial.printf("Weather: Condition ID: %d\r\n", data_p->weather.cond_id);
  Serial.printf("Energy: Fossil ratio : %3.2f\r\n", data_p->energy.fossil_ratio);
  Serial.printf("Energy: Nuclear ratio : %3.2f\r\n", data_p->energy.nuclear_ratio);
  Serial.printf("Energy: Renewable ratio : %3.2f\r\n", data_p->energy.renewable_ratio);
#endif
}

bool parseData(data_t *data_p, String& payload) {
  DynamicJsonBuffer buffer;

  JsonObject& root = buffer.parseObject(payload.c_str());

  if (root.success()) {
    data_p->energy.fossil_ratio = root["data"]["energy"]["fossil_ratio"];
    data_p->energy.nuclear_ratio = root["data"]["energy"]["nuclear_ratio"];
    data_p->energy.renewable_ratio = root["data"]["energy"]["renewable_ratio"];
    data_p->weather.temp = root["data"]["weather"]["temp"];
    data_p->weather.temp_min = root["data"]["weather"]["temp_min"];
    data_p->weather.temp_max = root["data"]["weather"]["temp_max"];
    data_p->weather.cond_id = root["data"]["weather"]["cond_id"];
    // data_p->weather.cond_id = root["data"]["weather"]["clouds"]; // TODO : clouds

    return true;
  } else {
#ifdef DEGUG_API
    Serial.println(F("jsonBuffer.parseObject failed"));
#endif
  }
  return false;
}

bool fetchData(int when) {
  data_t *data_p = &(data[when]);
  bool status = false;
  HTTPClient httpClient;

  httpClient.setTimeout(5000);

  String url = String(DATA_API_URL) + String(data_when_lookup[when]);
  if (!httpClient.begin(DATA_API_HOST, DATA_API_PORT, url.c_str())) {
#ifdef DEGUG_API
    Serial.println(F("ERROR: HTTPClient.begin"));
#endif
    return false;
  }
#ifdef DEGUG_API
  Serial.println("OK: HTTPClient.begin");
#endif
  int httpCode = httpClient.GET();
  if (httpCode > 0) {
    String payload = httpClient.getString();
#ifdef DEGUG_API
    Serial.print("fetchData: payload: ");
    Serial.println(payload);
#endif
    status = parseData(data_p, payload);
    if (status) {
      printData(data_p);
    }
  }
  else {
#ifdef DEGUG_API
    Serial.printf("[HTTP] connection failed: %s\n"), httpClient.errorToString(httpCode).c_str();
#endif
  }
  httpClient.end();
  return status;
}
