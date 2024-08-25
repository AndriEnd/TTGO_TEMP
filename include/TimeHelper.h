#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>

class TimeHelper {
public:
    TimeHelper(const char* nptServer, long utcOffsetInSecconds);
    void begin();
    void updateTime();
    String getFormatedTime();

private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
};

#endif