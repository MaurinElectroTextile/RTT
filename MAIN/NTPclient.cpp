#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET);

char* day = NULL;
char* days[] = {"Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."}; // PROGMEM?

const char* getDay(int delta) {
  return (day = days[(timeClient.getDay() + delta) % 7]);
}

void getTimeNow() {
  timeClient.getFormattedTime();
  // Serial.println(timeClient.getFormattedTime());
}

void timeClientUpdate() {
  timeClient.update();
}

void timeClientBegin() {
  timeClient.begin();
}
