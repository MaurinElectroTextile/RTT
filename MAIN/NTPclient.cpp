#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET);

char* days[] = {"Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam.", "Dim."}; // PROGMEM?

char* getDayNow() {
  return days[timeClient.getDay() - 1];
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
