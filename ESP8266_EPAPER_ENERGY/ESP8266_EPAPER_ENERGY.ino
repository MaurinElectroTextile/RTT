#include "main.h"

void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  if (!configWiFi()) {
    Serial.println("ERROR: configESP");
    while (1);
  }

  /* Initialize GxEPD library */
  display.init();

  /* Set ticker as 10 minutes */
  ticker.attach(REQ_INTERVAL_SEC, tickerHandler);

  /* Get weather information */
  requestEnergyInfo();
  delay(3000);
  requestEnergyForecastInfo();
}

void loop() {
  /* Every 10 minutes */
  if (requestFlag) {
    requestEnergyInfo();
    delay(3000);
    requestEnergyForecastInfo();
    requestFlag = false;
  }
}

void tickerHandler() {
  /* If you call requestWeatherInfo directly inside ticker callback function, HttpClient doesn't work properly */
  requestFlag = true;
}

bool configWiFi() {
  Serial.println();

  if (!WiFi.begin(WIFI_SSID, WIFI_PWD)) {
    Serial.println("ERROR: WiFi.begin");
    return false;
  }

  Serial.println("OK: WiFi.begin");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("OK: WiFi connected");

  return true;
}

/////////////////////////////////// RequestWeatherInfo
void requestEnergyInfo() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  /* Connect & Request */
  // https://digital.iservices.rte-france.com/open_api/actual_generation/v1
  String url = String("/data/2.5/weather?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&units=metric&appid=") + String(APPID);
  if (!httpClient.begin("api.openweathermap.org", 80, url.c_str())) {
    Serial.println("ERROR: HTTPClient.begin");
    return;
  }
  Serial.println("OK: HTTPClient.begin");

  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseEnergyJson(payload);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
}


/////////////////////////////////// ParseWeatherJson
void parseEnergyJson(String buffer) {
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
    double temp = root["main"]["temp"];
    int humidity = root["main"]["humidity"];
    int temp_min = root["main"]["temp_min"];
    int temp_max = root["main"]["temp_max"];
    int speed = root["wind"]["speed"];
    int direction = root["wind"]["direction"];
    int conditionId = root["weather"][0]["id"];
    const char* name = root["name"];
    const char* weather = parseEnergyCondition(conditionId);

    /* Serial Output */
    Serial.printf("Temp: %3.1f\r\n", temp);
    Serial.printf("Humidity: %d\r\n", humidity);
    Serial.printf("Min. Temp: %d\r\n", temp_min);
    Serial.printf("Max. Temp: %d\r\n", temp_max);
    Serial.printf("Wind Speed: %d\r\n", speed);
    Serial.printf("Wind Direction: %d\r\n", direction);
    Serial.printf("ConditionId: %d\r\n", conditionId);
    Serial.printf("Name: %s\r\n", name);
    Serial.printf("Weather: %s\r\n", weather);
    
    /* Draw EPD */
    /*
    drawBackgroundImage();
    drawWeatherIcon(conditionId);
    drawText(110, 80, String(temp, 1).c_str(), &DSDIGIT30pt7b);
    drawText(5, 115, String(name).c_str(), &DSDIGIT9pt7b);
    drawText("\r\n  Humidity: ");
    drawText(String(humidity).c_str());
    drawText("%");
    drawText("\r\n  Min Temp: ");
    drawText(String(temp_min).c_str());
    drawText(" ,Max Temp: ");
    drawText(String(temp_max).c_str());
    drawText("\r\n  Wind Speed: ");
    drawText(String(speed).c_str());
    drawText("\r\n  Wind Direction: ");
    drawText(String(direction).c_str());
    showDisplay();
    */
  }
  else {
    Serial.println("jsonBuffer.parseObject failed");
  }
}

void requestEnergyForecastInfo() {
  HTTPClient httpClient;
  httpClient.setTimeout(2000);

  /* Connect & Request */
  String url = String("/data/2.5/forecast?q=") + String(REGION) + String(",") + String(COUNTRY) + String("&cnt=8&units=metric&appid=") + String(APPID);
  if (!httpClient.begin("api.openweathermap.org", 80, url.c_str())) {
    Serial.println("ERROR: HTTPClient.begin");
    return;
  }
  Serial.println("OK: HTTPClient.begin");
  int httpCode = httpClient.GET();

  /* Check response */
  if (httpCode > 0) {
    Serial.printf("[HTTP] request from the client was handled: %d\n", httpCode);
    String payload = httpClient.getString();
    parseEnergyForecastJson(payload);
  }
  else {
    Serial.printf("[HTTP] connection failed: %s\n", httpClient.errorToString(httpCode).c_str());
  }
  httpClient.end();
}

void parseEnergyForecastJson(String buffer) {
  int JsonStartIndex = buffer.indexOf('{');
  int JsonLastIndex = buffer.lastIndexOf('}');

  JsonStr = buffer.substring(JsonStartIndex, JsonLastIndex + 1);
  Serial.println("PARSE JSON FORECAST INFORMATION: " + JsonStr);

  jsonBuffer.clear();
  JsonObject& root = jsonBuffer.parseObject(JsonStr);

  if (root.success()) {
    JsonArray& list = root["list"];

    for (auto& item : list) {
      const char* time = item["dt_txt"];
      double temp = item["main"]["temp"];
      int humidity = item["main"]["humidity"];
      int conditionId = item["weather"][0]["id"];
      const char* weather = parseEnergyCondition(conditionId);

      Serial.printf("Time: %s\r\n", time);
      Serial.printf("Temp: %3.1f C\r\n", temp);
      Serial.printf("Humidity: %d %%\r\n", humidity);
      Serial.printf("Condition: %d\r\n", conditionId);
      Serial.printf("Weather: %s\r\n", weather);
    }
  }
  else {
    Serial.println("jsonBuffer.parseObject failed");
  }
}

const char* parseEnergyCondition(int conditionId) {
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

void drawBackgroundImage() {
  /* Clear screen */
  display.fillScreen(GxEPD_WHITE);
  /* Draw bitmap */
  display.drawBitmap(FRAME, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK, GxEPD::bm_normal);
}


void drawWeatherIcon(int conditionId) {
  /* Draw bitmap image for conditionId */
  const uint8_t* bitmap;
  if (conditionId >= 200 && conditionId < 300) {
    bitmap = STORM;
  }
  else if (conditionId >= 300 && conditionId < 400) {
    bitmap = RAIN;
  }
  else if (conditionId >= 500 && conditionId < 600) {
    bitmap = RAIN;
  }
  else if (conditionId >= 600 && conditionId < 700) {
    bitmap = SNOW;
  }
  else if (conditionId >= 700 && conditionId < 800) {
    bitmap = FOG;
  }
  else if (conditionId == 800) {
    bitmap = SUNNY;
  }
  else if (conditionId > 800 && conditionId < 900) {
    bitmap = SUNNY_CLOUDY;
  }
  else {
    bitmap = SUNNY;
  }
  display.drawBitmap(bitmap, 14, 14, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_normal);
}

void drawText(int x, int y, const char* text, const GFXfont* font) {
  /* set text color */
  display.setTextColor(GxEPD_BLACK);
  /* set font */
  display.setFont(font);
  /* set position */
  display.setCursor(x, y);
  /* print text */
  display.print(text);
}

void drawText(const char* text) {
  /* print text */
  display.print(text);
}

void showDisplay() {
  /* show frame buffer */
  display.update();
}
