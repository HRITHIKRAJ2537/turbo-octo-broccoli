#include "dns_sd.h"

// Function to start the mDNS server
void startDNSServer() {
  // Check if Wi-Fi is connected before starting mDNS
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi is not connected. Please connect to Wi-Fi first.");
    return;
  }

  // Start the mDNS responder with the hostname "esp32"
  if (!MDNS.begin("esp32")) {
    Serial.println("Error starting mDNS");
    return;
  }
  Serial.println("mDNS responder started");

  // Add service to mDNS-SD
  if (MDNS.addService("http", "tcp", 80)) {
    Serial.println("Service added to mDNS");
  } else {
    Serial.println("Error adding service to mDNS");
  }
}
