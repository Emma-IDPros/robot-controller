#pragma once
#include <Arduino.h>

class RobotLineSensor {
public:
	void SetPins(byte line_pin_sense, byte line_detect_pin);
private:
	const byte line_pin_sense = 0;
	const byte line_detect_pin = 7;
	int centre_line_val = 461;
	int max_line_val = 792;
};