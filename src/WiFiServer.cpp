#include "WiFiServer.h"

AsyncWebServer server(80);
String inputPassword = "";


const char *htmlForm = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Password Input</title>
</head>
<body>
  <h1>Enter Password</h1>
  <form action="/get">
  <input type="ssid" name="ssid" required>
    <input type="password" name="password" required>
    <input type="submit" value="Submit">
  </form>
</body>
</html>
)rawliteral";

void setupWiFiServer(const char *ssid, const char *password)
{
  // Memulai Serial Monitor
  Serial.begin(115200);

  // Menetapkan hostname
  WiFi.setHostname("ESP32-Test-2481CE9C");

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Menampilkan alamat IP ESP32
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Menginisialisasi server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", htmlForm); });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam("password")) {
      inputPassword = request->getParam("password")->value();
      Serial.println("Password: " + inputPassword);
      request->send(200, "text/html", "Password received. You can close this window.");
    } else {
      request->send(200, "text/html", "Password not received. Try again.");
    } });

  // Menjalankan server
  server.begin();
}

void handleClientRequests()
{
  // Jika Anda memerlukan loop utama untuk server, bisa diletakkan di sini
}
