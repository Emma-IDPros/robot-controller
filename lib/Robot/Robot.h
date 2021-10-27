#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <LineSensor.h>

enum ROTATION { CLOCKWISE, ANTICLOCKWISE };
enum MOTOR {LEFT, RIGHT};

// Robot Class
class Robot {
public:
	// Adafruit Motor Shield Object
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor* MotorRight = AFMS.getMotor(3);
	Adafruit_DCMotor* MotorLeft = AFMS.getMotor(4);

	void MotorShieldTest();
	void Move(MOTOR motor, uint8_t speed, uint8_t DIRECTION);
	void MoveAll(uint8_t speed, uint8_t DIRECTION);
	void Stop(MOTOR motor);
	void StopAll();
	void Rotate(ROTATION rotation);
	float rotation_time;
	static bool rotate_execute;
	Adafruit_DCMotor* motor_from_motor_number(MOTOR motor);
};