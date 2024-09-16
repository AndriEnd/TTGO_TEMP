#include "WiFiManagerConfig.h"
#include "TimeHelper.h"
#include <Wire.h>
#include <TFT_eSPI.h>

const int resetButtonPin = 0; // Pin untuk tombol reset

const char *ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 25200; // UTC+7 untuk Jakarta
TFT_eSPI tft = TFT_eSPI();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");

  setupWiFi();
  setupWebServer();

  tft.begin();
  tft.print("TEST");

  pinMode(resetButtonPin, INPUT_PULLUP);

  Serial.println("Setup complete");
}

void koneksi()
{
  int reading = digitalRead(resetButtonPin);
  int32_t rssi = WiFi.RSSI();
  Serial.print("Kekuatan sinyal (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == HIGH)
      {
        Serial.println("Reset button pressed, resetting WiFi...");
        resetWiFi();
      }
    }
  }
  lastButtonState = reading;
}

void jam()
{
  timeClient.update(); // Perbarui waktu dari NTP
  Serial.print("JAM : ");
  Serial.println(timeClient.getFormattedTime()); // Perbaiki kesalahan penulisan

  delay(1000); // Tunggu 1 detik sebelum mengulangi
}

void loop(void)
{
  jam();     // Cetak waktu ke Serial Monitor
  koneksi(); // Cek tombol reset
}
