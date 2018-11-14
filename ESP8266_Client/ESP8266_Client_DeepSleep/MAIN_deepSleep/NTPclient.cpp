#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET);

char* day = NULL;
char* dayOfYear = NULL;

char* days[] = {"Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."}; // PROGMEM?

const char* getDay(int delta) {
  return (day = days[(timeClient.getDay() + delta) % 7]);
}

const char* getDayOfYear(int delta) {
  return (dayOfYear = timeClient.getEpochTime() / 86400L + 4);
}

void timeClientUpdate(void) {
  timeClient.update();
}

void timeClientBegin(void) {
  timeClient.begin();
}
