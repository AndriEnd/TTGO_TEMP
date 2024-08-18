#include "WiFiManagerConfig.h"
#include <Wire.h>
#include <TFT_eSPI.h>

const int resetButtonPin = 0;

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

void loop(void)
{
  int reading = digitalRead(resetButtonPin);
  Serial.print("Reset button state: ");
  Serial.println(reading);

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