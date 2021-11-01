#include <ToggleSwitch.h>

void RobotToggleSwitch::SetPins(byte detect_pin_inp, byte led_pin_inp) {
	detect_pin = detect_pin_inp;
	led_pin = led_pin_inp;

	pinMode(detect_pin, INPUT);
	pinMode(led_pin, OUTPUT);

}

void RobotToggleSwitch::UpdateState() {
	int reading = digitalRead(detect_pin);
	if (reading == HIGH && prev_state == LOW && millis() - prevMillis > debounce) {
		if (state == HIGH)
			state = LOW;
		else
			state = HIGH;

		prevMillis = millis();
	}
	prev_state = reading;

	digitalWrite(led_pin, state);
}