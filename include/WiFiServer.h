#ifndef WIFISERVER_H
#define WIFISERVER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

void setupWiFiServer(const char *ssid, const char *password);
void handleClientRequests();

#endif
