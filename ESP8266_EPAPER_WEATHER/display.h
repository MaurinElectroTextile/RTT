#ifndef __DISPAY_H__
#define __DISPAY_H__

#include "weather.h"
#include "imagedata.h"

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

/*
  BUSY    D2-GPIO4
  RST     D4-GPIO2
  DC      D3-GPIO0
  CS      D1-GPIO5 (I've changed CS pin from GPIO15 to GPIO5 as Waveshare EPD makes GPIO15 high when NodeMCU restarts).
  CLK     D5-GPIO14
  DIN     D7-GPIO13
  GND     GND
  3.3V    3.3V
*/

#define CS_PIN    D1
#define DC_PIN    D3
#define RST_PIN   D4

#include "Fonts/DSDIGIT9pt7b.h"
#include "Fonts/DSDIGIT30pt7b.h"

#define WEATHER_ICON_WIDTH  72
#define WEATHER_ICON_HEIGHT 72

void initDisplay();
void Draw_EPD();
void drawWeatherIcon(int conditionId);
void drawBackgroundImage();
void drawText(int x, int y, const char* text, const GFXfont * font);
void drawText(const char* text);
void showDisplay();

#endif /*__DISPAY_H__*/
