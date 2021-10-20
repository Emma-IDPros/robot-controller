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

private:
	byte PU_pin_servo;
};