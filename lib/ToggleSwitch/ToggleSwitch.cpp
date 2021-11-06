/**
 * @file ToggleSwitch.cpp
 * @author IDPros
 * @brief Methods that are used to toggle the robot on and off using
 * a toggle switch
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <ToggleSwitch.h>

 /**
  * @brief Set the pins
  *
  * @param detect_pin_inp DIGITAL input pin
  * @param led_pin_inp  DIGITAL output pin
  */
void RobotToggleSwitch::SetPins(byte detect_pin_inp, byte led_pin_inp) {
	detect_pin = detect_pin_inp;
	led_pin = led_pin_inp;

	pinMode(detect_pin, INPUT);
	pinMode(led_pin, OUTPUT);

}

/**
 * @brief Detects to see if the toggle switch was pressed,
 * if so it switches its state attribute. The func hen returns its state value
 *
 * @return true or false
 */
bool RobotToggleSwitch::GetAndUpdateState() {
	int reading = digitalRead(detect_pin);
	if (reading == HIGH && prev_state == LOW && millis() - prevMillis > debounce) {
		state = state == HIGH ? LOW : HIGH;
		prevMillis = millis();
	}
	prev_state = reading;

	digitalWrite(led_pin, state);
	return state;
}