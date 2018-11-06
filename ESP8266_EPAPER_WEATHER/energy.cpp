#include "energy.h"

#include <Arduino.h>
#include <ArduinoJson.h>

String energyAuthToken = "";
bool energyAuthTokenExpired = true;

String energyClientSecret64 = "YTBjYzMyODQtYzE5Yi00YzZjLTk1YTMtNGFmYmUxY2ViZjlhOmJhNzViYzFkLWI4NWEtNDUwMS05ZjVmLTZjYzdjNGE0YTlmMg==";

bool energyUpdate() {
  HTTPClient httpClient;

  httpClient.setReuse(true);
  httpClient.setTimeout(2000);

  if (energyAuthTokenExpired) {
    energyFetchAuthToken(&httpClient);
  }

  energyFetchActualGen(&httpClient);

  return true;
}

bool energyFetchActualGen(HTTPClient *httpClient) {
  bool status = false;

  if (!httpClient->begin(ENERGY_API_HOST, ENERGY_API_PORT, ENERGY_API_URL, ENERGY_API_CERT_FP)) {
    Serial.println("energyFetchActualGen/INIT");
    return false;
  }

  httpClient->addHeader("Authorization", "Bearer " + energyAuthToken);

  int httpCode = httpClient->GET();

  if (httpCode > 0) {
    status = energyParseActualGen(httpClient->getString());
  } else {
    Serial.printf("energyFetchActualGen/GET: %s", httpClient->errorToString(httpCode).c_str());
  }
  httpClient->end();

  return status;
}

bool energyParseActualGen(String payload) {
  Serial.println("energyParseActualGen:");
  Serial.println(payload);

  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.parseObject(payload);

  return true;
}

bool energyParseAuthToken(String payload) {
  Serial.println("energyParseAuthToken:");
  Serial.println(payload);

  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.parseObject(payload);

  energyAuthToken = String((const char *)root["access_token"]);

  return true;
}

bool energyFetchAuthToken(HTTPClient *httpClient) {
  bool status = false;

  if (!httpClient->begin(ENERGY_OAUTH_HOST, ENERGY_OAUTH_PORT, ENERGY_OAUTH_URL, ENERGY_OAUTH_CERT_FP)) {
    Serial.println("energyGetAuthToken/INIT");
    return false;
  }

  httpClient->addHeader("Authorization", "Basic " + energyClientSecret64);

  int httpCode = httpClient->POST(NULL, 0);

  if (httpCode > 0) {
    status = energyParseAuthToken(httpClient->getString());
  } else {
    Serial.printf("energyGetAuthToken/POST: %s", httpClient->errorToString(httpCode).c_str());
  }
  httpClient->end();

  return status;
}
