#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <LineSensor.h>

enum ROTATION { CLOCKWISE, ANTICLOCKWISE };
enum MOTOR { LEFT, RIGHT };

struct MotorStatus
{
	int speed, DIRECTION;
};

// Robot Class
class Robot {
public:

	void MotorShieldTest();
	void Move(MOTOR motor, uint8_t speed, uint8_t DIRECTION);
	void MoveAll(uint8_t speed, uint8_t DIRECTION);
	void Stop(MOTOR motor);
	void StopAll();
	// void Rotate(ROTATION rotation, RobotLineSensor LineSensor);
private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor* MotorRight = AFMS.getMotor(3);
	Adafruit_DCMotor* MotorLeft = AFMS.getMotor(4);
	Adafruit_DCMotor* MotorFromMotorNumber(MOTOR motor);
	MotorStatus motor_status_left, motor_status_right;
	bool ValidateMotorStatus(MOTOR motor, uint8_t speed, uint8_t DIRECTION);
	float rotation_time;
	static bool rotate_execute;
};

