#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET);

void timeClientUpdate() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
}

void timeClientBegin() {
  timeClient.begin();
}
