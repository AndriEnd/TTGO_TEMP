#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

#include <TFT_eSPI.h>
#include <NTPClient.h>

class DisplayHelper {
public:
    DisplayHelper(TFT_eSPI* tft, NTPClient* timeClient);
    void init();
    void showTime();

private:
    TFT_eSPI *tft;
    NTPClient *timeClient;
};

#endif