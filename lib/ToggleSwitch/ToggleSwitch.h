#pragma once
#include <Arduino.h>

class RobotToggleSwitch {
public:
	void SetPins(byte detect_pin_inp, byte led_pin_inp);
	void UpdateState();
	int state;
private:
	byte detect_pin, led_pin;
	int prev_state;
	unsigned long prevMillis = millis();
	int debounce = 200;
};