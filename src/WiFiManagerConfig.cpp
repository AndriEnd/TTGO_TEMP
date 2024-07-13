#include "WiFiManagerConfig.h"

WiFiManagerParameter custom_text("<p>Parameter Kustom</p>");           // Definisi variabel custom_text
WiFiManagerParameter custom_param("param", "Enter parameter", "", 20); // Definisi variabel custom_param
AsyncWebServer server(80);

void setupWiFi()
{
  WiFiManager wifiManager;
  wifiManager.addParameter(&custom_text);
  wifiManager.addParameter(&custom_param);

  if (!wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("Gagal menghubungkan ke WiFi dan timeout");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Terhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Custom parameter value: ");
  Serial.println(custom_param.getValue());
}

void setupWebServer()
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();
}

void handleRoot(AsyncWebServerRequest *request)
{
  String html = "<html><body><h1>WiFi Configuration</h1><form method='POST' action='/save'>";
  html += "SSID: <input type='text' name='ssid'><br>";
  html += "Password: <input type='password' name='password'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form></body></html>";
  request->send(200, "text/html", html);
}

void handleSave(AsyncWebServerRequest *request)
{
  if (request->hasParam("ssid", true) && request->hasParam("password", true))
  {
    String ssid = request->getParam("ssid", true)->value();
    String password = request->getParam("password", true)->value();
    Serial.println("Received new WiFi credentials:");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);

    WiFi.begin(ssid.c_str(), password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      Serial.println("Failed to connect. Resetting...");
      delay(3000);
      ESP.restart();
    }
    else
    {
      Serial.println("Connected to new WiFi!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      request->send(200, "text/html", "WiFi credentials updated. ESP will restart.");
      delay(3000);
      ESP.restart();
    }
  }
  else
  {
    request->send(400, "text/html", "Invalid input. Please try again.");
  }
}

void connectToWiFi(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
