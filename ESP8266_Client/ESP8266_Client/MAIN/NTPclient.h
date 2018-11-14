#ifndef __NTPCLIENT_H__
#define __NTPCLIENT_H__

// https://github.com/arduino-libraries/NTPClient

#define NTP_OFFSET    3600                   // In seconds
#define NTP_ADDRESS   "europe.pool.ntp.org"  // Change this to whatever pool is closest (see ntp.org)

extern char *day;
extern char *dayOfYear;

const char* getDay(int delta = 0);
const char* getDayOfYear(int delta = 0);

void timeClientUpdate(void);
void timeClientBegin(void);

#endif /*__NTPCLIENT_H__*/
