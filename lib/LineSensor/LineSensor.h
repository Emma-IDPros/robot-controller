#pragma once
#include <Arduino.h>

class RobotLineSensor {
public:
	void SetPins(byte line_pin_sense, byte line_detect_pin);
	void SetThresholdValues(int centre_line_val, int max_line_val);
	bool Detect();
	float LineFollowSense();
private:
	const byte line_pin_sense = 2;
	const byte line_detect_pin = 7;
	int centre_line_val = 461;
	int max_line_val = 792;
};