#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <WiFi.h>
#include <WebServer.h>

// Function to initialize light control
void startLightControl();

// Routes for controlling the lights
void handleLightOn();
void handleLightOff();
void handleKitchenOn();
void handleKitchenOff();

#endif
