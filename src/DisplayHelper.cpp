#include "DisplayHelper.h"

DisplayHelper::DisplayHelper(TFT_eSPI *tft, NTPClient *timeClient)
{
    this->tft = tft;
    this->timeClient = timeClient;
}

void DisplayHelper::init()
{
    tft->begin();
    tft->init();                             // Inisialisasi layar TFT
    tft->setRotation(1);                     // Rotasi layar, ubah jika perlu
    tft->fillScreen(TFT_BLACK);              // Bersihkan layar dengan warna hitam
    tft->setTextColor(TFT_GREEN, TFT_BLACK); // Warna teks hijau di atas latar belakang hitam
    tft->setTextSize(2);                     // Ukuran teks
}

void DisplayHelper::showTime()
{
    timeClient->update();
    String currentTime = timeClient->getFormattedTime();

    tft->fillScreen(TFT_BLACK);
    tft->setCursor(30, 60);
    tft->println(currentTime);
}
