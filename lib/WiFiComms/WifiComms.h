#pragma once
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>
#include <wifi_details.h>

class WiFiComms {
public:
	WiFiClient wifi;
	HttpClient client = HttpClient(wifi, serverAddress, port);
	int wl_status = WL_IDLE_STATUS;
	void Connect();

};