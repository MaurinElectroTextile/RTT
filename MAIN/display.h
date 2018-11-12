#ifndef __DISPAY_H__
#define __DISPAY_H__

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "weather.h"
#include "imagedata.h"

// #define LED_BUILTIN  D0

#define BUSY_PIN  D6 // SPI MISO_PIN -> D6_GPIO12
#define RST_PIN   D0 // LED_BUILTIN - CONFLICT 
#define DC_PIN    D3 // 
#define CS_PIN    D8 // SPI SS_PIN -> D8_GPIO15
#define CLK_PIN   D5 // SPI CLK_PIN -> D5_GPIO14
#define DIN_PIN   D7 // SPI MOSI_PIN -> D7_GPIO13

#include "Fonts/Lato_Bold9pt7b.h"
#include "Fonts/Lato_Bold11pt7b.h"
#include "Fonts/Lato_Bold14pt7b.h"

#define DISPLAY_WIDTH  128 
#define DISPLAY_HEIGHT 296

#define WEATHER_ICON_WIDTH  39
#define WEATHER_ICON_HEIGHT 37
#define ENERGY_ICON_WIDTH   20
#define ENERGY_ICON_HEIGHT  22

void displayInit();
void Draw_EPD();
void drawWeatherIcon(int posX, int posY, int conditionId);
void drawEnergyIcon(int posX, int posY);
void drawBackgroundImage();
void drawText(int posX, int posY, const char* text, const GFXfont * font);
void drawText(const char* text, const GFXfont * font);
void bargraph(int barWidth, int barHeight, int posX, int posY, int barSteps, int value);
void showDisplay();

#endif /*__DISPAY_H__*/
