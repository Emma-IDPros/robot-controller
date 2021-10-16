#include <WiFiComms.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>
// #define WIFI_EVALUATE_STATUS_CODES

void WiFiComms::Connect() {
	int i = 0;
	while (wl_status != WL_CONNECTED) {
		i++;
		Serial.print("Attempting to connect to Network named: ");
		Serial.println("LAPTOP-HI8GMNAK 7424");

		// Connect to WPA/WPA2 network:
		wl_status = WiFi.begin("LAPTOP-HI8GMNAK 7424", "021E=19t");

		if (i > 5) {
			Serial.println("Failed to connect 5 times, breaking");
			break;
		}
	}
	if (wl_status == WL_CONNECTED) {// print the SSID of the network you're attached to:
		Serial.print("SSID: ");
		Serial.println(WiFi.SSID());

		// print your WiFi shield's IP address:
		IPAddress ip = WiFi.localIP();
		Serial.print("IP Address: ");

		Serial.println(ip);
		client.println();
	}
}

void WiFiComms::Get(String endpoint) {
	client.beginRequest();
	String base_url = "http://" + String("192.168.137.1") + ":" + String(6969);
	client.get(base_url + endpoint);
	client.endRequest();

#ifdef WIFI_EVALUATE_STATUS_CODES
	int status_code = client.responseStatusCode();
	if (status_code == 404) {
		Serial.println("404 Error in making request to " + endpoint);
	}
#endif

}

void WiFiComms::SendCoords(float x, float y) {
	Get("/coord/" + String(x) + "/" + String(y));
}

void WiFiComms::Message(String message) {
	message.replace(" ", "%20");
	Get("/message/" + message);
}