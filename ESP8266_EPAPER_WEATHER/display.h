#ifndef __DISPAY_H__
#define __DISPAY_H__

// #include "weather.h"
// weather_t weatherInfos;

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>  // 2.9" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Fonts/DSDIGIT9pt7b.h"
#include "Fonts/DSDIGIT30pt7b.h"

GxIO_Class io(SPI, SS, 0, 2);
GxEPD_Class display(io);

void Draw_EPD(weather_t* weather_ptr);
void drawWeatherIcon(int conditionId);
void drawBackgroundImage();
void drawText(int x, int y, const char* text, const GFXfont * font);
void drawText(const char* text);
void showDisplay();

#endif /*__DISPAY_H__*/
