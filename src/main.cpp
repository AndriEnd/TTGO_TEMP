#include "DHT.h"
#include <TFT_eSPI.h>
#include "WiFiManagerConfig.h"

#define DHTPIN 21
#define DHTTYPE DHT11
#define TFT_BL 4

const int resetButtonPin = 23;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
DHT dht(DHTPIN, DHTTYPE);

#define photoTransistor 33
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

// Battery Voltage Pin
#define ADC_PIN 34
int vref = 1100;
float battery_voltage = 0.0;

// Setup for screen
int centerX = 135 / 2;
int centerY = 132;

// Variables for data
float temp = 0.0;
float hum = 0.0;

// Millis timer delay
int waitPeriod = 3500;
unsigned long start = 0;

// A dot to view screen refresh rate
int ball = 0;
int moveAmount = 3;

void drawScreen(float temp, float rh, float battery_voltage);
void displayError(float battery_voltage);

void setup()
{
  Serial.begin(115200);
  setupWiFi();
  setupWebServer();
  dht.begin();
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  pinMode(resetButtonPin, INPUT_PULLUP);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);

  // Menyiapkan captive portal dan mencoba menghubungkan ke jaringan WiFi
}

void loop(void)
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

      if (buttonState == LOW)
      {
        Serial.println("Tombol reset ditekan, mereset WiFi...");
        resetWiFi(); // Mereset WiFi jika tombol ditekan
      }
    }
  }
  lastButtonState = reading;
  // MILLIS timer in place of delay
  if (millis() - start >= waitPeriod)
  {
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    Serial.println(temp);
    Serial.println(hum);
    Serial.println(battery_voltage);

    uint16_t v = analogRead(ADC_PIN);
    battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    start = millis();
  } // END millis timer

  // Adjust screen brightness
  int brightness = map(analogRead(photoTransistor), 0, 4095, 10, 255);
  ledcWrite(pwmLedChannelTFT, brightness);

  // Check if sensor readings are valid
  if (isnan(temp) || isnan(hum))
  {
    displayError(battery_voltage);
  }
  else
  {
    drawScreen(temp, hum, battery_voltage);
  }
  lastButtonState = reading;
}

void displayError(float battery_voltage)
{
  spr.createSprite(135, 280);
  spr.fillSprite(TFT_BLACK);
  spr.setTextDatum(TC_DATUM);
  spr.setTextColor(TFT_YELLOW);
  spr.drawString("Error", centerX, centerY, 4);

  // Show battery voltage
  int percent = map(analogRead(ADC_PIN), 1690, 2370, 0, 100);
  String voltage = String(battery_voltage) + "V";
  String percentText = String(percent) + "%";

  spr.setTextDatum(TL_DATUM);
  spr.fillRect(4, 4, 28, 2, TFT_DARKGREY);  // TOP
  spr.fillRect(4, 16, 28, 2, TFT_DARKGREY); // BOTTOM
  spr.fillRect(4, 4, 2, 12, TFT_DARKGREY);  // LEFT
  spr.fillRect(32, 4, 2, 14, TFT_DARKGREY); // RIGHT
  spr.fillRect(34, 8, 3, 6, TFT_DARKGREY);  // TIP

  spr.setTextSize(1);
  spr.setTextColor(TFT_WHITE);

  if (percent <= 100)
  {
    spr.drawString(percentText, 45, 8, 1);
  }
  else
  {
    spr.drawString(voltage, 45, 8, 1);
  }

  if (battery_voltage <= 2.99)
  {
    spr.fillRect(4, 4, 28, 2, TFT_RED);
    spr.fillRect(4, 16, 28, 2, TFT_RED);
    spr.fillRect(4, 4, 2, 14, TFT_RED);
    spr.fillRect(32, 4, 2, 14, TFT_RED);
    spr.fillRect(34, 8, 3, 6, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.0)
  {
    spr.fillRect(6, 6, 4, 10, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.2)
  {
    spr.fillRect(6, 6, 6, 10, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.4)
  {
    spr.fillRect(6, 6, 11, 10, TFT_YELLOW);
  } // END IF
  if (battery_voltage >= 3.6)
  {
    spr.fillRect(6, 6, 16, 10, TFT_YELLOW);
  } // END IF
  if (battery_voltage >= 3.8)
  {
    spr.fillRect(6, 6, 21, 10, TFT_GREEN);
  } // END IF
  if (battery_voltage >= 4.0)
  {
    spr.fillRect(6, 6, 26, 10, TFT_GREEN);
  } // END IF
  if (battery_voltage >= 4.60)
  {
    spr.fillRect(6, 6, 26, 10, TFT_GREEN);
    spr.setTextColor(TFT_BLACK, TFT_GREEN);
    spr.drawString("CHG", 10, 7, 1);
  } // END IF
  if (battery_voltage >= 4.85)
  {
    spr.fillRect(6, 6, 26, 10, TFT_SKYBLUE);
    spr.setTextColor(TFT_BLACK, TFT_SKYBLUE);
    spr.drawString("USB", 10, 7, 1);
  } // END IF

  spr.pushSprite(0, 0);
  spr.deleteSprite();
}

void drawScreen(float temp, float rh, float battery_voltage)
{
  spr.createSprite(135, 280);
  spr.fillSprite(TFT_BLACK);

  // 3.00V == 1690, 4.20V == 2370
  // The TTGO powered off at around 2.50V
  int percent = map(analogRead(ADC_PIN), 1690, 2370, 0, 100);
  String voltage = String(battery_voltage) + "V";
  String percentText = String(percent) + "%";

  // Battery Icon
  spr.setTextDatum(TL_DATUM);
  spr.fillRect(4, 4, 28, 2, TFT_DARKGREY);  // TOP
  spr.fillRect(4, 16, 28, 2, TFT_DARKGREY); // BOTTOM
  spr.fillRect(4, 4, 2, 12, TFT_DARKGREY);  // LEFT
  spr.fillRect(32, 4, 2, 14, TFT_DARKGREY); // RIGHT
  spr.fillRect(34, 8, 3, 6, TFT_DARKGREY);  // TIP

  spr.setTextSize(1);
  spr.setTextColor(TFT_WHITE);

  // Show battery Voltage if on Battery power
  // Else show current voltage
  if (percent <= 100)
  {
    spr.drawString(percentText, 45, 8, 1);
  }
  else
  {
    spr.drawString(voltage, 45, 8, 1);
  }

  if (battery_voltage <= 2.99)
  {
    spr.fillRect(4, 4, 28, 2, TFT_RED);
    spr.fillRect(4, 16, 28, 2, TFT_RED);
    spr.fillRect(4, 4, 2, 14, TFT_RED);
    spr.fillRect(32, 4, 2, 14, TFT_RED);
    spr.fillRect(34, 8, 3, 6, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.0)
  {
    spr.fillRect(6, 6, 4, 10, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.2)
  {
    spr.fillRect(6, 6, 6, 10, TFT_RED);
  } // END IF
  if (battery_voltage >= 3.4)
  {
    spr.fillRect(6, 6, 11, 10, TFT_YELLOW);
  } // END IF
  if (battery_voltage >= 3.6)
  {
    spr.fillRect(6, 6, 16, 10, TFT_YELLOW);
  } // END IF
  if (battery_voltage >= 3.8)
  {
    spr.fillRect(6, 6, 21, 10, TFT_GREEN);
  } // END IF
  if (battery_voltage >= 4.0)
  {
    spr.fillRect(6, 6, 26, 10, TFT_GREEN);
  } // END IF
  if (battery_voltage >= 4.60)
  {
    spr.fillRect(6, 6, 26, 10, TFT_GREEN);
    spr.setTextColor(TFT_BLACK, TFT_GREEN);
    spr.drawString("CHG", 10, 7, 1);
  } // END IF
  if (battery_voltage >= 4.85)
  {
    spr.fillRect(6, 6, 26, 10, TFT_SKYBLUE);
    spr.setTextColor(TFT_BLACK, TFT_SKYBLUE);
    spr.drawString("USB", 10, 7, 1);
  } // END IF

  // Write the Data centered in the screen
  spr.setTextDatum(TC_DATUM);
  spr.setTextColor(TFT_RED);
  spr.drawString("Temp", centerX, 40, 4);
  spr.drawNumber(int(temp), centerX, 75, 6);

  spr.setTextColor(TFT_BLUE);
  spr.drawString("Humidity", centerX, centerY + 15, 4);
  spr.drawNumber(int(rh), centerX, centerY + 50, 6);

  // Move the ball
  tft.fillCircle(ball, 230, 2, TFT_WHITE);
  ball = ball + moveAmount;

  // Reverse the direction of the ball at the ends:
  if (ball <= 0 || ball >= 135)
  {
    moveAmount = -moveAmount;
  }

  // Now push the sprite to the TFT at position 0,0 on screen
  spr.pushSprite(0, 0);
  // And then clear the memory
  spr.deleteSprite();

} // END drawScreen(temp, rh, battery_voltage)
