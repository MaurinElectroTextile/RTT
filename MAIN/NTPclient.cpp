#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET);

char* days[] = {"Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam.", "Dim."}; // PROGMEM?
  
char getDayNow(char* daysPtr) {
  return daysPtr[timeClient.getDay()];
}

void getTimeNow() {
  Serial.println(timeClient.getFormattedTime());
}

void timeClientUpdate() {
  timeClient.update();
}

void timeClientBegin() {
  timeClient.begin();
}
