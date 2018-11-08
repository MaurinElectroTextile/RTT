#ifndef __NTPCLIENT_H__
#define __NTPCLIENT_H__

// https://github.com/arduino-libraries/NTPClient

#define NTP_OFFSET    3600                   // In seconds
#define NTP_ADDRESS   "europe.pool.ntp.org"  // Change this to whatever pool is closest (see ntp.org)

extern char* days[];

char* getDayNow();
void getTimeNow();

void timeClientUpdate();
void timeClientBegin();

#endif /*__NTPCLIENT_H__*/
