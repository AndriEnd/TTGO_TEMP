#include "WiFiManagerConfig.h"
#include "TimeHelper.h"
#include <Wire.h>
#include <TFT_eSPI.h>
#include <TimeHelper.h>

const int resetButtonPin = 0;

const char *ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 25200;

TimeHelper timeHelper(ntpServer, utcOffsetInSeconds);

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

  pinMode(resetButtonPin, INPUT_PULLUP);

  Serial.println("Setup complete");
}
void koneksi()
{
  int reading = digitalRead(resetButtonPin);

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
        Serial.print("Reset button state: ");
        Serial.println(reading);
        resetWiFi();
      }
    }
  }
  lastButtonState = reading;
}
void jam()
{
  timeHelper.updateTime();
  Serial.print("JAM  : ");
  Serial.println(timeHelper.getFormatedTime());
  delay(1000);
}
void loop(void)
{
  jam();
  koneksi();
}