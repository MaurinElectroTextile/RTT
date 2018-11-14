#include "Adafruit_GFX.h"

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Fonts/Lato_Bold9pt7b.h"
#include "Fonts/Lato_Bold11pt7b.h"
#include "Fonts/Lato_Bold14pt7b.h"

#include "data.h"
#include "display.h"
#include "imagedata.h"
#include "NTPclient.h"


/*
  https://github.com/ZinggJM/GxEPD (Version.3.0.2)
  2.9inch e-Paper_Module
  Width : 296 pixels
  Height : 128 pixels
  Résolution : 112 DPI
  Width : 2.90 cm
  Height : 6.71 cm
*/

// #define LED_BUILTIN  D0

#define BUSY_PIN  D6 // SPI MISO_PIN -> D6_GPIO12
#define RST_PIN   D0 // LED_BUILTIN - CONFLICT
#define DC_PIN    D3 //
#define CS_PIN    D8 // SPI SS_PIN -> D8_GPIO15
#define CLK_PIN   D5 // SPI CLK_PIN -> D5_GPIO14
#define DIN_PIN   D7 // SPI MOSI_PIN -> D7_GPIO13

#define WEATHER_ICON_WIDTH  39
#define WEATHER_ICON_HEIGHT 37
#define ENERGY_ICON_WIDTH   20
#define ENERGY_ICON_HEIGHT  22

#define BARGRAPH_STEPS      20

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io, RST_PIN, BUSY_PIN);

void drawWeatherIcon(int posX, int posY, int conditionId);
void drawEnergyIcons(int posX, int posY);
void drawBackgroundImage(void);
void drawText(int posX, int posY, const char* text, const GFXfont * font);
void drawText(const char* text, const GFXfont * font);
void bargraph(int barWidth, int barHeight, int posX, int posY, int barSteps, int value);
void showDisplay(void);


/* Initialize GxEPD library */
void displayInit(void) {
  display.init();
}

void Draw_EPD(int when) {
  data_t *data_p = &(data[when]);

  drawBackgroundImage();

  drawText(40, 30, day, &Lato_Bold14pt7b);

  drawText(25, 70, String((int)lround(data_p->weather.temp_min)).c_str(), &Lato_Bold11pt7b);
  drawText(80, 70, String((int)lround(data_p->weather.temp_max)).c_str(), &Lato_Bold11pt7b);

  drawWeatherIcon(20, 80, data_p->weather.cond_id);
  drawWeatherIcon(75, 80, data_p->weather.cond_id);

  drawText(25, 130, "min", &Lato_Bold9pt7b);
  drawText(75, 130, "max", &Lato_Bold9pt7b);

  drawEnergyIcons(0, 155);

  //bargraph(int barWidth, int barHeight, int posX, int posY, int barSteps, int value) {
  bargraph(22, 100, 8, 185, BARGRAPH_STEPS, data_p->weather.cond_id * BARGRAPH_STEPS / 1000); // LOCALE
  bargraph(22, 100, 38, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.renewable_ratio * BARGRAPH_STEPS)); // RENEWABLE
  bargraph(22, 100, 68, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.fossil_ratio * BARGRAPH_STEPS));  // CARBON
  bargraph(22, 100, 98, 185, BARGRAPH_STEPS, (int)lround(data_p->energy.nuclear_ratio * BARGRAPH_STEPS)); // NUCLEAR

  showDisplay();
}

void drawEnergyIcons(int posX, int posY) {
  /* Draw energy bitmap images */
  display.drawBitmap(LOCALE, posX + 8, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_default);
  display.drawBitmap(RENEWABLE, posX + 38, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_default);
  display.drawBitmap(CARBON, posX + 68, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_default);
  display.drawBitmap(NUCLEAR, posX + 98, posY, ENERGY_ICON_WIDTH, ENERGY_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_default);
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


void Draw_loadingIcon(void) {
  /* Draw energy bitmap images */
  display.fillScreen(GxEPD_BLACK);
  display.drawBitmap(HOURGLASS, 14, 100, 100, 100, GxEPD_BLACK, GxEPD::bm_default);
  display.updateWindow(0, 0, display.width(), display.height());
}

void drawWeatherIcon(int posX, int posY, int conditionId) {
  const uint8_t* bitmap = getWeatherBitmap(conditionId);
  display.drawBitmap(bitmap, posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, GxEPD_BLACK, GxEPD::bm_default);
}

void drawBackgroundImage(void) {
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

void showDisplay(void) {
  /* show frame buffer */
  //display.updateWindow(0, 0, display.width(), display.height());
  display.update();
}
