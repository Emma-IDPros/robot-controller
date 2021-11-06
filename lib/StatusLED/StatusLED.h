/**
 * @file StatusLED.h
 * @author IDPros
 * @brief Header file for the RobotStatusLED class
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>

class RobotStatusLED {
public:
	void SetPins(byte S_LED_pin_inp, byte MD_LED_pin_on_inp, byte MD_LED_pin_off_inp);
	void Blink(int frequency, bool on);
	void LightUpMetalDetectorLED(bool on);
	void TurnOffMetalDetectorLED();
	void TurnOffAmberLight();
private:
	byte S_LED_pin, MD_LED_pin_on, MD_LED_pin_off;
	unsigned long prevMillis = millis();
	PinStatus S_LED_state = LOW;
};