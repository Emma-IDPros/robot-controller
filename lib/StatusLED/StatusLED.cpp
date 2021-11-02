#include <StatusLED.h>

/**
 * @brief Setting pins
 *
 * @param S_LED_pin_inp Amber led pin
 */
void RobotStatusLED::SetPins(byte S_LED_pin_inp) {
	pinMode(S_LED_pin_inp, OUTPUT);
	S_LED_pin = S_LED_pin_inp;
}

/**
 * @brief Blinks an LED for a given frequency and on/off state
 *
 * @param frequency Frequency of blinking (Hz)
 * @param on true of you want it on and false if you want it off
 */
void RobotStatusLED::Blink(int frequency, bool on) {
	if (millis() - prevMillis > 1 / (float)frequency * 1000 && on) {
		S_LED_state = S_LED_state == LOW ? HIGH : LOW;
		digitalWrite(S_LED_pin, S_LED_state);
		prevMillis = millis();
	}
	else if (!on) {
		digitalWrite(S_LED_pin, LOW);
		S_LED_state = LOW;
	}
}