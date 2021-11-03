#include <StatusLED.h>

/**
 * @brief Setting pins
 *
 * @param S_LED_pin_inp Amber led pin
 */
void RobotStatusLED::SetPins(byte S_LED_pin_inp, byte MD_LED_pin_on_inp, byte MD_LED_pin_off_inp) {
	pinMode(S_LED_pin_inp, OUTPUT);
	pinMode(MD_LED_pin_on_inp, OUTPUT);
	pinMode(MD_LED_pin_off_inp, OUTPUT);
	S_LED_pin = S_LED_pin_inp;
	MD_LED_pin_on = MD_LED_pin_on_inp;
	MD_LED_pin_off = MD_LED_pin_off_inp;
}

/**
 * @brief Blinks an LED for a given frequency and on/off state
 *
 * @param frequency Frequency of blinking (Hz)
 * @param on true of you want it on and false if you want it off
 */
void RobotStatusLED::Blink(int frequency, bool on) {

	if (millis() - prevMillis > 1 / (float)frequency * 500.0 && on) {
		S_LED_state = S_LED_state == LOW ? HIGH : LOW;
		digitalWrite(S_LED_pin, S_LED_state);
		prevMillis = millis();
	}
	else if (!on) {
		digitalWrite(S_LED_pin, LOW);
		S_LED_state = LOW;
	}
}
void RobotStatusLED::LightUpMetalDetectorLED(bool on) {
	digitalWrite(MD_LED_pin_on, on ? HIGH : LOW);
	digitalWrite(MD_LED_pin_off, !on ? HIGH : LOW);
}
void RobotStatusLED::TurnOffMetalDetectorLED() {
	digitalWrite(MD_LED_pin_on, LOW);
	digitalWrite(MD_LED_pin_off, LOW);
}
void RobotStatusLED::TurnOffAmberLight() {
	digitalWrite(S_LED_pin, LOW);
	S_LED_state = LOW;
}