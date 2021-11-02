#include <LineSensor.h>

/**
 * @brief Set the pins for the line sensor
 *
 * @param line_pin_sense ANALOGUE
 * @param line_detect_pin DIGITAL
 */
void RobotLineSensor::SetPins(byte line_pin_sense, byte line_detect_pin, byte line_junc_detect_pin) {
	line_pin_sense = line_pin_sense;
	line_detect_pin = line_detect_pin;
	line_junc_detect_pin = line_junc_detect_pin;
	pinMode(line_detect_pin, INPUT);
	pinMode(line_junc_detect_pin, INPUT);
}

/**
 * @brief This function can be used to over-ride the
 * default values
 *
 * @param centre_line_val default 461
 * @param max_line_val default 792
 */
void RobotLineSensor::SetThresholdValues(int centre_line_val_inp, int max_line_val_inp) {
	centre_line_val = centre_line_val_inp;
	max_line_val = max_line_val_inp;
};

/**
 * @brief Detects if a line has been found
 *
 * @return true
 * @return false
 */
bool RobotLineSensor::Detect() {
	return digitalRead(line_detect_pin);
};

/**
 * @brief This function returns a float between -1 and 1 to turn left or right
 * and 0 for centerline
 *
 * @return float
 */
float RobotLineSensor::LineFollowSense() {
	float line_val = analogRead(line_pin_sense);
	// Serial.println(String(line_val));
	line_val_analog = line_val;
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

/**
 * @brief Detects junctions
 *
 * @return true if detected, and false if not
 */
bool RobotLineSensor::JunctionDetect() {
	return digitalRead(line_junc_detect_pin);
}



