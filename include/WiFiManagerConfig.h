#ifndef WIFIMANAGERCONFIG_H
#define WIFIMANAGERCONFIG_H

#include <WiFi.h>
#include <WiFiManager.h>
#include <ESPAsyncWebServer.h>

// Deklarasi objek WiFiManager dan server web
extern WiFiManager wifiManager;
extern AsyncWebServer server;

void setupWiFi();
void setupWebServer();
void handleRoot(AsyncWebServerRequest *request);
void handleSave(AsyncWebServerRequest *request);
void handleReset(AsyncWebServerRequest *request);
void resetWiFi();

#endif
