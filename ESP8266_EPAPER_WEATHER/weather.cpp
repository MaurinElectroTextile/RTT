#include "weather.h"

/////////////////////////////////// RequestWeatherInfo
boolean requestWeatherInfo() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  /* Connect & Request */
  String url = String("/data/2.5/weather?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&units=metric&appid=") + String(APPID);
  if (!httpClient.begin("api.openweathermap.org", 443, url.c_str()), true) {
    Serial.println("ERROR: HTTPClient.begin");
    return false;
  }
  Serial.println("OK: HTTPClient.begin");

  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseWeatherJson(payload, &weatherInfos);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
  return true;
}

/////////////////////////////////// ParseWeatherJson
void parseWeatherJson(String buffer, weather_t* weather_ptr) {
  int JsonStartIndex = buffer.indexOf('{');
  int JsonLastIndex = buffer.lastIndexOf('}');

  /* Substring JSON string */
  JsonStr = buffer.substring(JsonStartIndex, JsonLastIndex + 1);
  Serial.println("PARSE JSON WEATHER INFORMATION: " + JsonStr);

  /* Clear buffer */
  jsonBuffer.clear();

  /* Parse JSON string */
  JsonObject& root = jsonBuffer.parseObject(JsonStr);

  if (root.success()) {
    /* Get information */
    /*
      double temp = root["main"]["temp"];
      int humidity = root["main"]["humidity"];
      int temp_min = root["main"]["temp_min"];
      int temp_max = root["main"]["temp_max"];
      int speed = root["wind"]["speed"];
      int direction = root["wind"]["direction"];
      int conditionId = root["weather"][0]["id"];
      const char* name = root["name"];
      const char* weather = parseWeatherCondition(conditionId);
    */

    weather_ptr->temp = root["main"]["temp"];
    weather_ptr->humidity = root["main"]["humidity"];
    weather_ptr->temp_min = root["main"]["temp_min"];
    weather_ptr->temp_max = root["main"]["temp_max"];
    weather_ptr->windSpeed = root["wind"]["speed"];
    weather_ptr->windDirection = root["wind"]["direction"];
    weather_ptr->conditionId = root["weather"][0]["id"];
    const char* weatherName = root["name"];
    weather_ptr->weatherName = weatherName;
    weather_ptr->weatherType = parseWeatherCondition(weather_ptr->conditionId);

    /* Serial Output */
    Serial.printf("Temp: %3.1f\r\n", weather_ptr->temp);
    Serial.printf("Humidity: %d\r\n", weather_ptr->humidity);
    Serial.printf("Min. Temp: %d\r\n", weather_ptr->temp_min);
    Serial.printf("Max. Temp: %d\r\n", weather_ptr->temp_max);
    Serial.printf("Wind Speed: %d\r\n", weather_ptr->windSpeed);
    Serial.printf("Wind Direction: %d\r\n", weather_ptr->windDirection);
    Serial.printf("ConditionId: %d\r\n", weather_ptr->conditionId);
    Serial.printf("Name: %s\r\n", weather_ptr->weatherName.c_str());
    Serial.printf("Weather: %s\r\n", weather_ptr->weatherType.c_str());

    /*
      drawBackgroundImage();
      drawWeatherIcon(conditionId);
      drawText(110, 80, String(temp, 1).c_str(), &DSDIGIT30pt7b);
      drawText(5, 115, String(watherName).c_str(), &DSDIGIT9pt7b);
      drawText("\r\n  Humidity: ");
      drawText(String(humidity).c_str());
      drawText("%");
      drawText("\r\n  Min Temp: ");
      drawText(String(temp_min).c_str());
      drawText(" ,Max Temp: ");
      drawText(String(temp_max).c_str());
      drawText("\r\n  Wind Speed: ");
      drawText(String(windSpeed).c_str());
      drawText("\r\n  Wind Direction: ");
      drawText(String(windDirection).c_str());
      showDisplay();
    */
  }
  else {
    Serial.println("jsonBuffer.parseObject failed");
  }
}

boolean requestWeatherForecastInfo() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  /* Connect & Request */
  String url = String("/data/2.5/forecast?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&cnt=8&units=metric&appid=") + String(APPID);
  if (!httpClient.begin("api.openweathermap.org", 80, url.c_str())) {
    Serial.println("ERROR: HTTPClient.begin");
    return false;
  }
  Serial.println("OK: HTTPClient.begin");
  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseWeatherForecastJson(payload, &weatherInfos);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
  return true;
}

void parseWeatherForecastJson(String buffer, weather_t* weather_ptr) {
  int JsonStartIndex = buffer.indexOf('{');
  int JsonLastIndex = buffer.lastIndexOf('}');

  JsonStr = buffer.substring(JsonStartIndex, JsonLastIndex + 1);
  Serial.println("PARSE JSON FORECAST INFORMATION: " + JsonStr);

  jsonBuffer.clear();
  JsonObject& root = jsonBuffer.parseObject(JsonStr);

  if (root.success()) {
    JsonArray& list = root["list"];

    for (auto& item : list) {
      /*
        const char* _time = item["dt_txt"];
        double temp = item["main"]["temp"];
        int humidity = item["main"]["humidity"];
        int conditionId = item["weather"][0]["id"];
        const char* weatherType = parseWeatherCondition(conditionId);
      */
      const char* _time = item["dt_txt"];
      weather_ptr->_time = _time;
      weather_ptr->temp = item["main"]["temp"];
      weather_ptr->humidity = item["main"]["humidity"];
      weather_ptr->conditionId = item["weather"][0]["id"];
      weather_ptr->weatherType = parseWeatherCondition(weather_ptr->conditionId);

      Serial.printf("Time: %s\r\n", weather_ptr->_time.c_str());
      Serial.printf("Temp: %3.1f C\r\n", weather_ptr->temp);
      Serial.printf("Humidity: %d %%\r\n", weather_ptr->humidity);
      Serial.printf("Condition: %d\r\n", weather_ptr->conditionId);
      Serial.printf("Weather: %s\r\n", weather_ptr->weatherType.c_str());
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
