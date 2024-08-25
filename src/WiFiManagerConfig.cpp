#include "WiFiManagerConfig.h"

WiFiManager wifiManager;
AsyncWebServer server(80);

const int resetButtonPin = 0; // Pin untuk tombol reset (ubah sesuai dengan pin yang digunakan)

void setupWiFi()
{
  // Menambahkan parameter jika diperlukan
  WiFiManagerParameter custom_ssid("ssid", "Enter SSID", "SSID", 40);
  WiFiManagerParameter custom_password("password", "Enter password", "password", 40);
  wifiManager.addParameter(&custom_ssid);
  wifiManager.addParameter(&custom_password);

  // Auto connect dengan nama AP "AutoConnectAP"
  if (!wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("Gagal menghubungkan ke WiFi dan timeout");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Terhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Menampilkan nilai SSID dan password yang dimasukkan
  Serial.print("SSID: ");
  Serial.println(custom_ssid.getValue());
  Serial.print("Password: ");
  Serial.println(custom_password.getValue());
}

void setupWebServer()
{
  server.on("/", HTTP_GET, handleRoot);       // Handle root route dengan fungsi handleRoot
  server.on("/reset", HTTP_GET, handleReset); // Handle route reset WiFi dengan fungsi handleReset
  server.begin();                             // Memulai server web
}

void handleRoot(AsyncWebServerRequest *request)
{
  // Menampilkan form HTML untuk input SSID dan password WiFi
  String html = "<html><body><h1>WiFi Configuration</h1><form method='POST' action='/save'>";
  html += "SSID: <input type='text' name='ssid'><br>";
  html += "Password: <input type='password' name='password'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form>";

  // Menambahkan tombol reset koneksi WiFi
  html += "<br><br><a href='/reset'>Reset WiFi Connection</a>";

  html += "</body></html>";
  request->send(200, "text/html", html); // Mengirimkan halaman HTML ke client
}

void handleReset(AsyncWebServerRequest *request)
{
  resetWiFi();                                                                          // Memanggil fungsi resetWiFi untuk mereset koneksi WiFi
  request->send(200, "text/plain", "Koneksi WiFi telah di-reset. ESP32 akan restart."); // Memberikan respons ke client
}

void resetWiFi()
{
  Serial.println("Mereset konfigurasi WiFi...");
  wifiManager.resetSettings(); // Menghapus konfigurasi WiFi yang disimpan
  ESP.restart();               // Me-restart ESP32
}
