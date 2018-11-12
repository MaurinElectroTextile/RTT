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

#include "data.h"


#define BARGRAPH_STEPS  20


GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io, RST_PIN, BUSY_PIN);

/* Initialize GxEPD library */
void displayInit() {
  display.init();
}
void Draw_EPD(int when) {
  data_t *data_p = &(data[when]);

  drawBackgroundImage();

  drawText(40, 30, getDayNow(), &Lato_Bold14pt7b);

<<<<<<< HEAD
  drawText(22, 70, String((int)lround(data_p->weather.temp_min)).c_str(), &Lato_Bold11pt7b);
  drawText(80, 70, String((int)lround(data_p->weather.temp_max)).c_str(), &Lato_Bold11pt7b);
  // drawText(22, 70, String("10").c_str(), &Lato_Bold11pt7b);
  // drawText(80, 70, String("18").c_str(), &Lato_Bold11pt7b);

  drawWeatherIcon(20, 80, data_p->weather.cond_id);
  drawWeatherIcon(75, 80, data_p->weather.cond_id);
  // drawWeatherIcon(20, 80, 200);
  // drawWeatherIcon(75, 80, 300);
=======
  drawText(22, 70, String(weatherInfos.minTemp).c_str(), &Lato_Bold11pt7b);
  drawText(80, 70, String(weatherInfos.maxTemp).c_str(), &Lato_Bold11pt7b);

  drawWeatherIcon(20, 80, weatherInfos.conditionId);
  drawWeatherIcon(75, 80, weatherInfos.conditionId);
>>>>>>> sleep test

  drawText(20, 140, "min", &Lato_Bold9pt7b);
  drawText(70, 140, "max", &Lato_Bold9pt7b);

  drawEnergyIcons(10, 160);

  //bargraph(int barWidth, int barHeight, int posX, int posY, int barSteps, int value) {
  bargraph(22, 100, 10, 185, BARGRAPH_STEPS, data_p->weather.cond_id * BARGRAPH_STEPS / 1000); // LOCALE
  bargraph(22, 100, 40, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.renewable_ratio * BARGRAPH_STEPS)); // RENEWABLE
  bargraph(22, 100, 70, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.fossil_ratio * BARGRAPH_STEPS));  // CARBON
  bargraph(22, 100, 100, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.nuclear_ratio * BARGRAPH_STEPS)); // NUCLEAR

  showDisplay();
}

void drawEnergyIcons(int posX, int posY) {
  /* Draw energy bitmap images */
  display.drawBitmap(LOCALE, posX + 0, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(RENEWABLE, posX + 28, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(CARBON, posX + 56, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
  display.drawBitmap(NUCLEAR, posX + 82, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_WHITE, GxEPD::bm_normal);
}

const uint8_t *getWeatherBitmap(int conditionId) {
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
  return bitmap;
}

void drawWeatherIcon(int posX, int posY, int conditionId) {
  const uint8_t* bitmap = getWeatherBitmap(conditionId);
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

//bargraph(22, 120, 20, 10, 160, 8);
void bargraph(int barWidth, int barHeight, int posX, int posY, int barSteps, int value) {
  uint8_t V_SPACE = (int)(barHeight / barSteps);
  uint8_t ledWidth = barWidth;
  uint8_t ledHeight = V_SPACE - 5;

  display.drawRect(posX, posY, barWidth, barHeight, GxEPD_WHITE);

  for (int i = 0; i < value; i++) {
    display.drawRect(posX, (posY + barHeight) - V_SPACE * i, ledWidth, ledHeight, GxEPD_WHITE);
    display.fillRect(posX, (posY + barHeight) - V_SPACE * i, ledWidth, ledHeight, GxEPD_WHITE);
  }
}

void showDisplay() {
  /* show frame buffer */
  display.update();
}
