#include <StatusLED.h>

void RobotStatusLED::SetPins(byte S_LED_pin_inp) {
	pinMode(S_LED_pin_inp, OUTPUT);
	S_LED_pin = S_LED_pin_inp;
}

void RobotStatusLED::Blink(int frequency, bool on) {
	if (millis() - prevMillis > 1 / frequency * 1000 && on) {
		S_LED_state = S_LED_state == LOW ? HIGH : LOW;
		digitalWrite(S_LED_pin, S_LED_state);
	}
	else if (!on) {
		digitalWrite(S_LED_pin, LOW);
		S_LED_state = LOW;
	}
}