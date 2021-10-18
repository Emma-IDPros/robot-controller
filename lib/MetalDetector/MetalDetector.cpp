#include <MetalDetector.h>

void RobotMetalDetector::SetPins(byte pin_pulse, byte pin_cap = 1, byte pin_LED1 = 12, byte pin_LED2 = 11) {
	pin_pulse = pin_pulse;
	pin_cap = pin_cap;
	pin_LED1 = pin_LED1;
	pin_LED2 = pin_LED2;

	pinMode(pin_pulse, OUTPUT);
	digitalWrite(pin_pulse, LOW);
	pinMode(pin_cap, INPUT);
	pinMode(pin_LED1, OUTPUT);
	digitalWrite(pin_LED1, LOW);
	pinMode(pin_LED2, OUTPUT);
	digitalWrite(pin_LED2, LOW);
}