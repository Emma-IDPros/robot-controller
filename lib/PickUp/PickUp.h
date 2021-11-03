#pragma once
#include <Arduino.h>
#include <Servo.h>

class RobotPickUp {
public:
	Servo servo;
	int angle;
	void SetPins(byte servo_pin);
	void SweepTest();
	void Sweep(int to_angle);

	void SetInitalAngle(int angle);
	bool inital_angle_set = false;

private:
	byte PU_pin_servo;
};