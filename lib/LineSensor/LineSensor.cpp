#include <LineSensor.h>
void RobotLineSensor::SetPins(byte line_pin_sense, byte line_detect_pin) {
	line_pin_sense = line_pin_sense;
	line_detect_pin = line_detect_pin;
	pinMode(line_detect_pin, INPUT);
}