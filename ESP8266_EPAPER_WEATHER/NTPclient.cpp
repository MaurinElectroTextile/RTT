#include "NTPclient.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void timeClientUpdate() {
  timeClient.update();
}

void timeClientBegin() {
  timeClient.begin();
}
