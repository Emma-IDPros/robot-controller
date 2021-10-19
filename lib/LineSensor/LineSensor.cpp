#include <LineSensor.h>

void RobotLineSensor::SetPins(byte line_pin_sense, byte line_detect_pin) {
	line_pin_sense = line_pin_sense;
	line_detect_pin = line_detect_pin;
	pinMode(line_detect_pin, INPUT);
}

void RobotLineSensor::SetThresholdValues(int centre_line_val, int max_line_val) {
	centre_line_val = centre_line_val;
	max_line_val = max_line_val;
};

bool RobotLineSensor::Detect() {
	return digitalRead(line_detect_pin);
};

float RobotLineSensor::LineFollowSense() {//returns a float between -1 and 1 to turn left or right, 0 for centreline
	float line_val = analogRead(line_pin_sense);
	int turn = 0;
	line_val -= centre_line_val;
	if (line_val < 0) {//go right
		line_val = line_val / centre_line_val;
		if (line_val < -1) {
			line_val = -1;
		}
	}
	else if (line_val > 0) {//go left
		line_val = line_val / (max_line_val - centre_line_val);
		if (line_val > 1) {
			line_val = 1;
		}
	}
	else {//do nothing
		turn = 0;
		line_val = 0;
	}
	return line_val;
}