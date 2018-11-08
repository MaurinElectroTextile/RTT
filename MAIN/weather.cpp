#include "weather.h"

weather_t weatherInfos;

/////////////////////////////////// RequestWeatherInfo
boolean requestWeatherDaily() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  // http://api.openweathermap.org/data/3.0/measurements?station_id=...&type=...&limit=...

  /* Connect & Request */
  String url = String("/data/2.5/weather?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&units=metric&appid=") + String(APPID);
  if (!httpClient.begin(WEATHER_API_CERT_HOST, WEATHER_API_CERT_PORT, url.c_str(), WEATHER_API_CERT_FP)) {
    Serial.println("ERROR: HTTPClient.begin");
    return false;
  }
  Serial.println("OK: HTTPClient.begin");

  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseWeatherJson(payload);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
  return true;
}

/////////////////////////////////// ParseWeatherJson
void parseWeatherJson(String& buffer) {
  int JsonStartIndex = buffer.indexOf('{');
  int JsonLastIndex = buffer.lastIndexOf('}');

  /* Substring JSON string */
  String JsonStr = buffer.substring(JsonStartIndex, JsonLastIndex + 1);
  Serial.println("PARSE JSON WEATHER INFORMATION: " + JsonStr);

  DynamicJsonBuffer jsonBuffer;

  /* Parse JSON string */
  JsonObject& root = jsonBuffer.parseObject(JsonStr.c_str());

  if (root.success()) {
    /* Get information */
    weatherInfos.temp = root["main"]["temp"];
    weatherInfos.minTemp = root["main"]["temp_min"];
    weatherInfos.maxTemp = root["main"]["temp_max"];
    weatherInfos.conditionId = root["weather"][0]["id"];
    const char* weatherName = root["name"];
    weatherInfos.weatherName = weatherName;
    weatherInfos.weatherType = parseWeatherCondition(weatherInfos.conditionId);

    /* Serial Output */
    Serial.printf("MinTemp: %d\r\n", weatherInfos.minTemp);
    Serial.printf("MaxTemp: %d\r\n", weatherInfos.maxTemp);
    Serial.printf("ConditionId: %d\r\n", weatherInfos.conditionId);
    Serial.printf("Name: %s\r\n", weatherInfos.weatherName.c_str());
    Serial.printf("Weather: %s\r\n", weatherInfos.weatherType.c_str());
  }
  else {
    Serial.println("jsonBuffer.parseObject failed");
  }
}

boolean requestWeatherForecast() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  /* Connect & Request */
  String url = String("/data/2.5/forecast?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&cnt=8&units=metric&appid=") + String(APPID);
  if (!httpClient.begin(WEATHER_API_CERT_HOST, WEATHER_API_CERT_PORT, url.c_str(), WEATHER_API_CERT_FP)) {
    Serial.println("ERROR: HTTPClient.begin");
    return false;
  }
  Serial.println("OK: HTTPClient.begin");
  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseWeatherForecastJson(payload);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
  return true;
}

//////////////////////////////////// The day befor - Do we do it with the API?
boolean requestWeatherPrevious() {
}

void parseWeatherForecastJson(String& buffer) {
  int JsonStartIndex = buffer.indexOf('{');
  int JsonLastIndex = buffer.lastIndexOf('}');

  String JsonStr = buffer.substring(JsonStartIndex, JsonLastIndex + 1);
  Serial.println("PARSE JSON FORECAST INFORMATION: " + JsonStr);

  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(JsonStr.c_str());

  if (root.success()) {
    JsonArray& list = root["list"];

    for (auto& item : list) {
      const char* _time = item["dt_txt"];
      weatherInfos._time = _time;
      weatherInfos.temp = item["main"]["temp"];
      weatherInfos.conditionId = item["weather"][0]["id"];
      weatherInfos.weatherType = parseWeatherCondition(weatherInfos.conditionId);

      Serial.printf("Time: %s\r\n", weatherInfos._time.c_str());
      Serial.printf("Temp: %3.1f C\r\n", weatherInfos.temp);
      Serial.printf("Condition: %d\r\n", weatherInfos.conditionId);
      Serial.printf("Weather: %s\r\n", weatherInfos.weatherType.c_str());
    }
  }
  else {
    Serial.println("jsonBuffer.parseObject failed");
  }
}

const char* parseWeatherCondition(int conditionId) {
  /* Return string for conditionId */
  if (conditionId >= 200 && conditionId < 300) return "Thunderstorm";
  else if (conditionId >= 300 && conditionId < 400) return "Drizzle";
  else if (conditionId >= 500 && conditionId < 600) return "Rain";
  else if (conditionId >= 600 && conditionId < 700) return "Snow";
  else if (conditionId >= 700 && conditionId < 800) return "Fog";
  else if (conditionId == 800) return "Clear";
  else if (conditionId > 800 && conditionId < 900) return "Clouds";
  else return "Unknown condition";
}
