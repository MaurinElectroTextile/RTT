#ifndef __DISPAY_H__
#define __DISPAY_H__

#include "weather.h"
#include "imagedata.h"

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Fonts/DSDIGIT9pt7b.h"
#include "Fonts/DSDIGIT30pt7b.h"

#define WEATHER_ICON_WIDTH  72
#define WEATHER_ICON_HEIGHT 72

void initDisplay();
// void Draw_EPD(weather_t* weatherInfos);
void Draw_EPD();
void drawWeatherIcon(int conditionId);
void drawBackgroundImage();
void drawText(int x, int y, const char* text, const GFXfont * font);
void drawText(const char* text);
void showDisplay();

#endif /*__DISPAY_H__*/
