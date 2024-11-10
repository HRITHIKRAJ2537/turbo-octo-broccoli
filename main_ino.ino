#include <WiFi.h>
#include <WebServer.h>
#include "dns_sd.h"  // Include the header file for startDNSServer
#include "lightControl.h"  // Include the header file for light control

WebServer server(80);  // Create a web server on port 80

void setup() {
  Serial.begin(115200);

  // Start the ESP32 in Access Point mode
  WiFi.softAP("ESP32_Setup");
  Serial.println("Access Point Started");

  // Print the IP address of the ESP32 in AP mode
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.softAPIP());

  // Define routes for the web server
  server.on("/", handleRoot);
  server.on("/wifi-setup", handleWiFiSetup);

  server.begin();  // Start the web server
}

// Handle the root page, showing a simple Wi-Fi setup form
void handleRoot() {
  server.send(200, "text/html", 
    "<form action='/wifi-setup'>"
    "<label>SSID: <input name='ssid'></label><br><br>"
    "<label>Password: <input name='password' type='password'></label><br><br>"
    "<button type='submit'>Connect</button>"
    "</form>"
  );
}

// Handle the Wi-Fi setup when the form is submitted
void handleWiFiSetup() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  // Check if SSID and password are provided
  if (ssid != "" && password != "") {
    WiFi.begin(ssid.c_str(), password.c_str());  // Connect to Wi-Fi

    server.send(200, "text/html", "Connecting to Wi-Fi... Please wait and check the Serial Monitor.");
    Serial.print("Connecting to Wi-Fi: ");
    Serial.println(ssid);

    // Wait for connection
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {
      delay(500);
      Serial.print(".");  // Print dots while waiting
    }

    // Check if connected
    if (WiFi.status() == WL_CONNECTED) {
      server.send(200, "text/html", "Connected to Wi-Fi! IP: " + WiFi.localIP().toString());
      Serial.println("\nConnected to Wi-Fi!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());

      // Call the startDNSServer function after successful connection
      startDNSServer();
      startLightControl();  // Call the light control function
    } else {
      server.send(200, "text/html", "Failed to connect to Wi-Fi. Please check your SSID and password.");
      Serial.println("Failed to connect to Wi-Fi.");
    }
  } else {
    server.send(200, "text/html", "SSID and Password must not be empty.");
  }
}

void loop() {
  server.handleClient();  // Handle incoming web server requests
}
