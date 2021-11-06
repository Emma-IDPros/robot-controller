/**
 * @file ToggleSwitch.h
 * @author IDPros
 * @brief Header ile for the RobotToggleSwitch class
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>

class RobotToggleSwitch {
public:
	void SetPins(byte detect_pin_inp, byte led_pin_inp);
	bool GetAndUpdateState();
	int state;
private:
	byte detect_pin, led_pin;
	int prev_state;
	unsigned long prevMillis = millis();
	int debounce = 200;
};