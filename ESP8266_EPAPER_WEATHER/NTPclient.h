#ifndef __NTPCLIENT_H__
#define __NTPCLIENT_H__

// https://github.com/arduino-libraries/NTPClient
// Define NTP properties

#define NTP_OFFSET    (60 * 60)              // In seconds
#define NTP_INTERVAL  (60 * 1000)            // In miliseconds
#define NTP_ADDRESS   "europe.pool.ntp.org"  // Change this to whatever pool is closest (see ntp.org)

void timeClientUpdate();
void timeClientBegin();

#endif /*__NTPCLIENT_H__*/
