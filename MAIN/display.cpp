#include "display.h"
#include "NTPclient.h"
#include "Adafruit_GFX.h"

/*
  https://github.com/ZinggJM/GxEPD (Version.3.0.2)
  2.9inch e-Paper_Module
  Width : 296 pixels
  Height : 128 pixels
  Résolution : 112 DPI
  Width : 2.90 cm
  Height : 6.71 cm
*/

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io, RST_PIN, BUSY_PIN);

/* Initialize GxEPD library */
void displayInit() {
  display.init();
}
void Draw_EPD() {
  int val = 5;

  drawBackgroundImage();

  drawText(40, 30, getDayNow(), &Lato_Bold14pt7b);

  drawText(22, 70, String(weatherInfos.minTemp).c_str(), &Lato_Bold11pt7b);
  drawText(80, 70, String(weatherInfos.maxTemp).c_str(), &Lato_Bold11pt7b);
  // drawText(22, 70, String("10").c_str(), &Lato_Bold11pt7b);
  // drawText(80, 70, String("18").c_str(), &Lato_Bold11pt7b);

  drawWeatherIcon(20, 80, weatherInfos.conditionId);
  drawWeatherIcon(75, 80, weatherInfos.conditionId);
  // drawWeatherIcon(20, 80, 200);
  // drawWeatherIcon(75, 80, 300);

  drawText(20, 140, "min", &Lato_Bold9pt7b);
  drawText(70, 140, "max", &Lato_Bold9pt7b);

  drawEnergyIcon(10, 160);

  //bargraph(int barWidth, int barHeight, int barSteps, int posX, int posY, int value) {
  bargraph(20, 200, 10, 10, 200, 8); // LOCALE
  bargraph(20, 200, 10, 40, 200, 8); // RENEWABLE
  bargraph(20, 200, 10, 70, 200, 8); // CARBON
  bargraph(20, 200, 10, 100, 200, 8); // NUCLEAR

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
  display.setTextColor(GxEPD_WHITE); // Set text color
  display.setFont(font);             // Set typo type
  display.setCursor(posX, posY);     // Set text position
  display.print(text);               // print text
}

void drawText(const char* text, const GFXfont * font) {
  /* print text */
  display.setFont(font);
  display.print(text);
}

//  bargraph(20, 200, 10, 220, 10, 8);
void bargraph(int barWidth, int barHeight, int barSteps, int posX, int posY, int value) {
  uint8_t V_SPACE = (int)(barHeight / barSteps);
  uint8_t ledWidth = barWidth - 4;
  uint8_t ledHeight = V_SPACE - 10;

  for (int i = 0; i < value; i++) {
    display.drawRect(posX, (posY + V_SPACE * barSteps) - (value * V_SPACE), ledWidth, ledHeight, GxEPD_WHITE);
    display.fillRect(posX, (posY + V_SPACE * barSteps) - (value * V_SPACE), ledWidth, ledHeight, GxEPD_WHITE);
  }
}

void showDisplay() {
  /* show frame buffer */
  display.update();
}
