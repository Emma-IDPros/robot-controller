#pragma once
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>


class WiFiComms {
public:
	WiFiClient wifi;
	HttpClient client = HttpClient(wifi, "192.168.137.1", 6969);
	int wl_status = WL_IDLE_STATUS;
	void Connect();
	void Get(String endpoint);
	void SendCoords(float x, float y);
	void Message(String message);

};