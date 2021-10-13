#include <WiFiComms.h>
#include <Arduino.h>

void WiFiComms::Connect() {
	while (wl_status != WL_CONNECTED) {
		Serial.print("Attempting to connect to Network named: ");
		Serial.println(ssid);

		// Connect to WPA/WPA2 network:
		wl_status = WiFi.begin(ssid, pass);
	}
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");

	Serial.println(ip);
	client.println();
}

void WiFiComms::Get(String endpoint) {
	client.beginRequest();
	String base_url = "http://" + String(serverAddress) + ":" + String(port);
	client.get(base_url + endpoint);
	client.endRequest();
}