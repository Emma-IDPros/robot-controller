#pragma once
#include <Arduino.h>

class RobotStatusLED {
public:
	void SetPins(byte S_LED_pin_inp, byte MD_LED_pin);
	void Blink(int frequency, bool on);
	void LightUpMetalDetectorLED(bool on);
private:
	byte S_LED_pin, MD_LED_pin;
	unsigned long prevMillis = millis();
	PinStatus S_LED_state = LOW;
};