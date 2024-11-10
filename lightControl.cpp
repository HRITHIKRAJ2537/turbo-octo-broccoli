#include "lightControl.h"

// Create a web server object that listens on port 80
extern WebServer server;

// Pin configurations for the lights
const int livingRoomLightPin = 18; // GPIO 18
const int kitchenLightPin = 19;    // GPIO 19

// Variables to store light statuses
bool livingRoomLightOn = false;
bool kitchenLightOn = false;

void startLightControl() {
  // Set pin modes for lights
  pinMode(livingRoomLightPin, OUTPUT);
  pinMode(kitchenLightPin, OUTPUT);

  // Initialize the lights in OFF state
  digitalWrite(livingRoomLightPin, LOW);
  digitalWrite(kitchenLightPin, LOW);

  // Define the routes for light control
  server.on("/light-on", handleLightOn);
  server.on("/light-off", handleLightOff);
  server.on("/kitchen-on", handleKitchenOn);
  server.on("/kitchen-off", handleKitchenOff);
}

void handleLightOn() {
  livingRoomLightOn = true;
  digitalWrite(livingRoomLightPin, HIGH);  // Turn on the light
  server.send(200, "text/plain", "Living room light is ON");
}

void handleLightOff() {
  livingRoomLightOn = false;
  digitalWrite(livingRoomLightPin, LOW);  // Turn off the light
  server.send(200, "text/plain", "Living room light is OFF");
}

void handleKitchenOn() {
  kitchenLightOn = true;
  digitalWrite(kitchenLightPin, HIGH);  // Turn on the kitchen light
  server.send(200, "text/plain", "Kitchen light is ON");
}

void handleKitchenOff() {
  kitchenLightOn = false;
  digitalWrite(kitchenLightPin, LOW);  // Turn off the kitchen light
  server.send(200, "text/plain", "Kitchen light is OFF");
}
