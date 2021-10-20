#pragma once
#include <Arduino.h>
#include <Servo.h>

class RobotPickUp {
public:
	Servo servo;
	void SetPins(byte servo_pin);
	void SweepTest();

private:
	byte PU_pin_servo;
}