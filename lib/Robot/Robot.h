#pragma once
#include <LineSensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

enum ROTATION { CLOCKWISE, ANTICLOCKWISE };
enum MOTOR { LEFT, RIGHT };

// stores the motor speed and direction
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
//	void Rotate(ROTATION rotation, RobotLineSensor LineSensor);
	void Rotate(uint8_t angle, ROTATION rotation);
	bool IsMoving();
private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor* MotorRight = AFMS.getMotor(4);
	Adafruit_DCMotor* MotorLeft = AFMS.getMotor(3);
	Adafruit_DCMotor* MotorFromMotorNumber(MOTOR motor);
	bool ValidateMotorStatus(MOTOR motor, uint8_t speed, uint8_t DIRECTION);
	MotorStatus motor_status_left, motor_status_right;
	float rotation_time;
	static bool rotate_execute;
};

