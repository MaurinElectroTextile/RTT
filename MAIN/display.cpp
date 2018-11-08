#include "display.h"
#include "NTPclient.h"

// Maximum width and height: 128 and 296

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io);

/* Initialize GxEPD library */
void initDisplay() {
  display.init();
}
void Draw_EPD() {

  drawBackgroundImage();

  drawText(40, 30, getDayNow(), &Lato_Bold14pt7b);

  drawText(22, 70, String(weatherInfos.minTemp).c_str(), &Lato_Bold12pt7b);
  drawText(80, 70, String(weatherInfos.maxTemp).c_str(), &Lato_Bold12pt7b);
  // drawText(22, 70, String("10").c_str(), &Lato_Bold12pt7b);
  // drawText(80, 70, String("18").c_str(), &Lato_Bold12pt7b);

  drawWeatherIcon(20, 80, weatherInfos.conditionId);
  drawWeatherIcon(75, 80, weatherInfos.conditionId);
  // drawWeatherIcon(20, 80, 200);
  // drawWeatherIcon(75, 80, 300);

  drawText(20, 140, "min", &Lato_Bold10pt7b);
  drawText(70, 140, "max", &Lato_Bold10pt7b);

  drawEnergyIcon(10, 160);

  showDisplay();
}

void drawEnergyIcon(int posX, int posY) {
  /* Draw energy bitmap images */
  display.drawBitmap(LOCALE, posX + 0, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(RENEWABLE, posX + 28, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(CARBON, posX + 56, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(NUCLEAR, posX + 82, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
}

void drawWeatherIcon(int posX, int posY, int conditionId) {
  /* Draw weather bitmap images */
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
  display.drawBitmap(bitmap, posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
}

void drawBackgroundImage() {
  /* Clear screen */
  display.fillScreen(GxEPD_BLACK);
}

void drawText(int posX, int posY, const char* text, const GFXfont * font) {
  display.setRotation(0);
  /* set text color */
  // display.setTextColor(GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  /* set font */
  display.setFont(font);
  /* set position */
  display.setCursor(posX, posY);
  /* print text */
  display.print(text);
}

void drawText(const char* text, const GFXfont * font) {
  /* print text */
  display.setFont(font);
  display.print(text);
}

void showDisplay() {
  /* show frame buffer */
  display.update();
}
