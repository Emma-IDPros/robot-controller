/**
 * @file PickUp.h
 * @author IDPros
 * @brief Header file for the RobotPickUp class
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>
#include <Servo.h>

class RobotPickUp {
public:
	Servo servo;
	int angle = 90;
	void SetPins(byte servo_pin);
	void SweepTest();
	void Sweep(int to_angle);

	void SetInitalAngle(int angle);
	bool inital_angle_set = false;

private:
	byte PU_pin_servo;
};