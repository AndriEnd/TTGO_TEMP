#include "TimeHelper.h"

TimeHelper::TimeHelper(const char* ntpServer, long utcOffsetInSeconds)
    : timeClient(ntpUDP, ntpServer, utcOffsetInSeconds) {}

void TimeHelper::begin()
{
    timeClient.begin();
    timeClient.update();
}

void TimeHelper::updateTime()
{
    timeClient.update();
}
String TimeHelper::getFormatedTime()
{

    return timeClient.getFormattedTime();
}
