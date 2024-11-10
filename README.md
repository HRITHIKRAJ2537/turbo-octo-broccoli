1. ESP32 Initialization (Access Point Mode)
When the ESP32 is powered on, it begins by initializing the serial monitor for debugging purposes (Serial.begin(115200)).
It then configures itself to run in Access Point mode (WiFi.softAP("ESP32_Setup")), which allows the ESP32 to create its own Wi-Fi network.
The IP address of the ESP32's access point is printed to the serial monitor, so users can connect to it with a device (e.g., smartphone, laptop).
2. Client Connects to the ESP32
The user (client) connects their device (laptop/phone) to the ESP32’s Wi-Fi network, named "ESP32_Setup".
Once connected, the device's browser navigates to the root URL (/) of the ESP32's web server. This is where the user can input their home Wi-Fi network's SSID (network name) and password.
3. Client Submits Wi-Fi Credentials
The user enters the Wi-Fi SSID and password into the form on the root page of the web server and clicks the "Connect" button. This sends the data to the /wifi-setup route on the server.
The web server (server.on("/wifi-setup", handleWiFiSetup)) captures the POST request and extracts the SSID and password from the form.
If both SSID and password are provided, the ESP32 tries to connect to the provided Wi-Fi network using the WiFi.begin() method.
4. Wi-Fi Connection Process
While attempting to connect to the Wi-Fi network, the ESP32 prints . characters to the serial monitor as it waits.
If the ESP32 successfully connects to the Wi-Fi network, it prints a success message with the assigned local IP address to the serial monitor and updates the client web page to show that the Wi-Fi connection was successful.
If the ESP32 fails to connect (e.g., wrong SSID or password), it informs the user via the web page that the connection failed.
5. mDNS Service Activation
Upon successful Wi-Fi connection, the ESP32 starts the mDNS (Multicast DNS) responder by calling the startDNSServer() function. This allows the ESP32 to be accessed by a friendly hostname (esp32.local) instead of an IP address.
The client can then access the ESP32 using http://esp32.local instead of the IP address, making it easier for users to control devices connected to the ESP32.
6. Light Control Routes Setup
Once the ESP32 is connected to Wi-Fi and mDNS is running, the ESP32 initializes the light control functionality (startLightControl()). This sets up the GPIO pins connected to the living room and kitchen lights and defines routes for controlling the lights:
/light-on: Turns the living room light on.
/light-off: Turns the living room light off.
/kitchen-on: Turns the kitchen light on.
/kitchen-off: Turns the kitchen light off.
7. Client Controls Lights
The user can now control the lights using the routes above:
For example, if the user accesses http://esp32.local/light-on, the living room light will turn on, and the web page will display a confirmation message, "Living room light is ON".
Similarly, accessing http://esp32.local/kitchen-on will turn on the kitchen light.
These actions are processed by the server which sends the appropriate responses (e.g., "Living room light is ON").
8. Loop for Continuous Interaction
The loop() function continuously runs and listens for incoming requests from the client (server.handleClient()). The web server is always waiting for interactions, such as turning the lights on or off.
If the user interacts with any light control routes, the corresponding actions are executed, and the web server provides feedback to the client.
Client-Server Communication Recap:
Step 1: ESP32 starts as an access point.
Step 2: User connects to the ESP32 and fills in Wi-Fi details.
Step 3: User submits credentials to connect to the Wi-Fi.
Step 4: ESP32 connects to the Wi-Fi and starts mDNS for easier access.
Step 5: User controls devices (lights) using specific routes.
Step 6: The server keeps running, handling multiple requests as needed.
This flow enables the client to use the web interface to configure the Wi-Fi connection and control the devices attached to the ESP32.
