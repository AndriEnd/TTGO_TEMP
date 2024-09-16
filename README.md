Weather Monitoring with ESP32 TTGO T-Display
Welcome to the Weather Monitoring project! This project is built using the ESP32 TTGO T-Display to display real-time weather data collected from environmental sensors and online weather APIs.

🚀 Project Overview
This project aims to monitor various weather conditions like temperature, humidity, and atmospheric pressure using the ESP32 TTGO T-Display module. The collected data is shown on the device's display and can be further expanded to include data logging or even integration with cloud services.


🧰 Hardware & Software Requirements
Hardware
ESP32 TTGO T-Display (with onboard display)
BME280/BMP180 or similar environmental sensor (for temperature, humidity, pressure)
Jumper wires & breadboard
Optional: Power supply (battery)
Software
Arduino IDE or PlatformIO
Libraries:
TFT_eSPI for display control
Adafruit_BME280 for sensor integration
WiFi and HTTPClient for fetching weather data from APIs
⚙️ Features
Real-time Weather Monitoring: Displays local temperature, humidity, and pressure.
API Integration: Retrieves weather data from online APIs for comparison.
WiFi Connectivity: Uses ESP32's WiFi to fetch real-time data.
Customizable Display: Modify fonts, colors, and displayed data easily.
🛠️ Setup Instructions
Install Required Libraries:

Go to the Arduino Library Manager and install TFT_eSPI and Adafruit_BME280.
Install any necessary sensor or API libraries.
Configure WiFi Credentials: Update your WiFi_SSID and WiFi_PASSWORD in the config.h file.

Upload the Code:

Connect the ESP32 TTGO T-Display to your computer.
Select the appropriate board and COM port in Arduino IDE.
Upload the provided .ino file.
Connect Sensors:

Connect the BME280 sensor using jumper wires to the correct GPIO pins on the ESP32.
Power Up:

Once uploaded, the ESP32 will connect to WiFi, retrieve weather data, and display it on the built-in screen.
📊 Screenshots

📋 To-Do List
 Add historical data logging to SD card or cloud service.
 Improve display layout for better readability.
 Integrate more environmental sensors (e.g., wind speed, UV index).
 Add power-saving modes for battery efficiency.
🤝 Contributing
Feel free to open issues or submit pull requests! Contributions to improve functionality, efficiency, or expand features are welcome.

📄 License
This project is licensed under the MIT License. See the LICENSE file for details.

🌟 Acknowledgments
Thanks to the open-source community for providing awesome libraries and resources!
Inspired by similar IoT weather station projects.
