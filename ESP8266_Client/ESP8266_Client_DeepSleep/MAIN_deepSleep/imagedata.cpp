#include "imagedata.h"
#include <avr/pgmspace.h>

/*
  Include custom images
  Image tool : http://javl.github.io/image2cpp/
  Set brightness threshold: 125
*/

//////////////////////////////////// PICTOS WEATHER

// 'CLOUDY', 39x37px
const unsigned char CLOUDY [] PROGMEM = {
  0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 
  0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 
  0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 
  0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 
  0x01, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'FOG', 39x37px
const unsigned char FOG [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 
  0x01, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x03, 
  0xff, 0xe0, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 
  0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 
  0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x3f, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1e, 0x03, 0xc0, 0x00, 0x00, 0x3f, 0xe3, 0xfe, 0x00, 0x00, 0x3f, 0xe3, 
  0xfc, 0x00, 0x00, 0x01, 0xe0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'RAIN', 39x37px
const unsigned char RAIN [] PROGMEM = {
  0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 
  0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 
  0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 
  0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 
  0x01, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0xc6, 0x30, 0x00, 0x00, 0x1c, 0xe6, 0x70, 0x00, 0x00, 0x1c, 0xe6, 
  0x70, 0x00, 0x00, 0x1c, 0xe6, 0x70, 0x00, 0x00, 0x1c, 0xe6, 0x70, 0x00, 0x00, 0x08, 0x40, 0x20, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x39, 0xc0, 0x00, 
  0x00, 0x03, 0x39, 0xc0, 0x00, 0x00, 0x03, 0x39, 0xc0, 0x00, 0x00, 0x03, 0x39, 0xc0, 0x00, 0x00, 
  0x03, 0x19, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'SNOW', 39x37px
const unsigned char SNOW [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 
  0x03, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 
  0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 
  0xfe, 0x00, 0x01, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 
  0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0x80, 
  0x03, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x38, 0xc7, 0x38, 0x00, 0x00, 0x10, 0x02, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x07, 0x38, 0xc0, 
  0x00, 0x00, 0x02, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'STORM', 39x37px
const unsigned char STORM [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 
  0x01, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x03, 
  0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 
  0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 
  0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 
  0x7f, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x21, 0x0c, 0x00, 0x00, 0x1c, 0x73, 0x9c, 0x00, 0x00, 0x1c, 0xe3, 
  0x9c, 0x00, 0x00, 0x1c, 0xe7, 0x3c, 0x00, 0x00, 0x18, 0xe7, 0x18, 0x00, 0x00, 0x10, 0x02, 0x10, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'SUNNY', 39x37px
const unsigned char SUNNY [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x00, 0x00, 0x00, 0x30, 0x1c, 0x04, 0x00, 0x00, 0x38, 0x18, 0x1c, 0x00, 0x00, 0x3c, 
  0x00, 0x1c, 0x00, 0x00, 0x1c, 0x00, 0x3c, 0x00, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xc0, 
  0x00, 0x07, 0xc3, 0xff, 0xe1, 0xf0, 0x07, 0xe3, 0xff, 0xe3, 0xe0, 0x01, 0xc7, 0xff, 0xe1, 0x80, 
  0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x00, 0x00, 0xf0, 0xff, 0x87, 0x00, 0x01, 0xf0, 
  0x7e, 0x07, 0x80, 0x01, 0xe0, 0x00, 0x03, 0xc0, 0x00, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x81, 0xc0, 0x00, 0x00, 0x01, 0xc1, 0xc0, 0x00, 0x00, 0x03, 0x81, 0xc0, 
  0x00, 0x00, 0x03, 0x81, 0xc0, 0x00, 0x00, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'SUNNY_CLOUDY', 39x37px
const unsigned char SUNNY_CLOUDY [] PROGMEM = {
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 
  0x00, 0x03, 0x80, 0x00, 0x00, 0x07, 0x03, 0x81, 0xc0, 0x00, 0x07, 0x81, 0x03, 0xc0, 0x00, 0x03, 
  0x80, 0x03, 0x80, 0x00, 0x03, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xc0, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x03, 0x87, 0xfc, 
  0x3c, 0x00, 0x0f, 0xe3, 0xfc, 0x7e, 0x00, 0x1f, 0xf3, 0xfc, 0x7c, 0x00, 0x3f, 0xf1, 0xfc, 0x00, 
  0x00, 0x3f, 0xf9, 0xfc, 0x00, 0x00, 0x3f, 0xf8, 0x3c, 0x00, 0x00, 0x3f, 0xf8, 0x1c, 0x00, 0x03, 
  0xff, 0xff, 0x08, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x40, 0x0f, 0xff, 0xff, 0xe0, 0xf0, 0x1f, 0xff, 
  0xff, 0xe0, 0xf8, 0x1f, 0xff, 0xff, 0xf0, 0x38, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 
  0xf0, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xc0, 
  0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//////////////////////////////////// PICTOS ENERGY
// 'CARBON', 20x22px
const unsigned char CARBON [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x3f, 0x00, 0x00, 0xff, 0x80, 0x00, 0xff, 0xc0, 0x00, 
  0xff, 0xc0, 0x08, 0xff, 0xc0, 0x38, 0xff, 0xe0, 0x78, 0xff, 0xc0, 0x7c, 0xff, 0xc0, 0xfc, 0x7f, 
  0x80, 0xfe, 0x3e, 0x00, 0xff, 0x00, 0x00, 0xff, 0x80, 0x60, 0x7f, 0xc1, 0xe0, 0x7f, 0x8f, 0xe0, 
  0x1f, 0x0f, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xe0, 0x00, 0x3f, 0xc0, 0x00, 0x0f, 0x80, 0x00, 
  0x00, 0x00
};
// 'LOCALE', 20x22px
const unsigned char LOCALE [] PROGMEM = {
  0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x07, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0x0f, 0x80, 0x1c, 
  0x07, 0x80, 0x3c, 0x03, 0x80, 0x38, 0x03, 0xc0, 0x38, 0x01, 0xc0, 0x38, 0x03, 0xc0, 0x3c, 0x03, 
  0x80, 0x1c, 0x03, 0x80, 0x1e, 0x07, 0x80, 0x0f, 0xff, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc, 0x00, 
  0x03, 0xfc, 0x00, 0x01, 0xf8, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x00
};
// 'NUCLEAR', 20x22px
const unsigned char NUCLEAR [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x7f, 0x00, 0x00, 0xe3, 0x80, 0x01, 0xc0, 0xc0, 0x07, 
  0x80, 0xe0, 0x1f, 0x00, 0x60, 0x3b, 0x00, 0x60, 0x63, 0x00, 0x60, 0x61, 0x80, 0x60, 0x61, 0x80, 
  0xe0, 0xc0, 0xe1, 0xe0, 0x40, 0x7f, 0x60, 0x60, 0x3e, 0x30, 0x70, 0x30, 0x30, 0x38, 0xf0, 0x30, 
  0x1f, 0xc0, 0x60, 0x07, 0xc0, 0x60, 0x00, 0x71, 0xc0, 0x00, 0x3f, 0x80, 0x00, 0x1f, 0x00, 0x00, 
  0x00, 0x00
};
// 'RENEWABLE', 20x22px
const unsigned char RENEWABLE [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x3f, 
  0xc0, 0x00, 0x7f, 0xe0, 0x40, 0x70, 0xf0, 0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x3f, 0xc0, 0x00, 0x0f, 
  0x00, 0x06, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x3f, 0xe0, 0x00, 0x79, 0xf0, 0xe0, 0x70, 0xff, 0xe0, 
  0x00, 0x7f, 0xc0, 0x00, 0x3f, 0x80, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00
};

// 'PICTO-BLEU-IMAGE', 100x100px
const unsigned char HOURGLASS [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf8, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
  0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
  0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};