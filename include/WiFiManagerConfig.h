#ifndef WIFIMANAGERCONFIG_H
#define WIFIMANAGERCONFIG_H

#include <WiFi.h>
#include <WiFiManager.h>
#include <ESPAsyncWebServer.h>

extern WiFiManagerParameter custom_text;  // Deklarasi variabel custom_text
extern WiFiManagerParameter custom_param; // Deklarasi variabel custom_param // Deklarasi variabel custom_param

void setupWiFi();
void setupWebServer();
void handleRoot(AsyncWebServerRequest *request);
void handleSave(AsyncWebServerRequest *request);
void connectToWiFi(const char *ssid, const char *password);

extern AsyncWebServer server;

#endif
