#include "display.h"

// Maximum width and height: 128 and 296

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io);

/* Initialize GxEPD library */
void initDisplay() {
  display.init();
}

//void Draw_EPD(weather_t* weatherInfos) {
void Draw_EPD() {

  drawBackgroundImage();
  drawWeatherIcon(weatherInfos.conditionId);
  drawText(110, 80, String(weatherInfos.temp, 1).c_str(), &DSDIGIT30pt7b);
  drawText(5, 115, String(weatherInfos.weatherName).c_str(), &DSDIGIT9pt7b);
  drawText("\r\n  Humidity: ");
  drawText(String(weatherInfos.humidity).c_str());
  drawText("%");
  drawText("\r\n  Min Temp: ");
  drawText(String(weatherInfos.temp_min).c_str());
  drawText(" ,Max Temp: ");
  drawText(String(weatherInfos.temp_max).c_str());
  drawText("\r\n  Wind Speed: ");
  drawText(String(weatherInfos.windSpeed).c_str());
  drawText("\r\n  Wind Direction: ");
  drawText(String(weatherInfos.windDirection).c_str());
  showDisplay();
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

void drawBackgroundImage() {
  /* Clear screen */
  display.fillScreen(GxEPD_WHITE);
  /* Draw bitmap */
  display.drawBitmap(FRAME, 0, 0, GxEPD_HEIGHT, GxEPD_WIDTH, GxEPD_BLACK, GxEPD::bm_normal);
}

void drawText(int x, int y, const char* text, const GFXfont * font) {
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
