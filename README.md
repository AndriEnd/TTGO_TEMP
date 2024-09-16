# Weather Monitoring with ESP32 TTGO T-Display

Welcome to the **Weather Monitoring** project! This project is built using the **ESP32 TTGO T-Display** to display real-time weather data collected from environmental sensors and online weather APIs.

## 🚀 Project Overview

This project aims to monitor various weather conditions like temperature, humidity, and atmospheric pressure using the ESP32 TTGO T-Display module. The collected data is shown on the device's display and can be further expanded to include data logging or even integration with cloud services.

## 🧰 Hardware & Software Requirements

### Hardware

- **ESP32 TTGO T-Display** (with onboard display)
- **BME280/BMP180** or similar environmental sensor (for temperature, humidity, pressure)
- Jumper wires & breadboard
- Optional: Power supply (battery)

### Software

- Arduino IDE or PlatformIO
- Libraries:
  - `TFT_eSPI` for display control
  - `Adafruit_BME280` for sensor integration
  - `WiFi` and `HTTPClient` for fetching weather data from APIs
