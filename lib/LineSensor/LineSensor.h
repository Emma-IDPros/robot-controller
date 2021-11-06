/**
 * @file LineSensor.h
 * @author IDPros
 * @brief Header for the RobotLineSensor class
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>


class RobotLineSensor {
public:
	void SetPins(byte line_pin_sense, byte line_detect_pin, byte line_junc_detect_pin);
	void SetThresholdValues(int centre_line_val, int max_line_val);
	bool Detect();
	bool JunctionDetect();
	float LineFollowSense();
	float line_val_analog;
private:
	const byte line_pin_sense = 2;
	const byte line_detect_pin = 7;
	const byte line_junc_detect_pin = 6;
	int centre_line_val = 461;
	int max_line_val = 792;

};