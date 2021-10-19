#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Robot Class
class Robot {
public:
	// Adafruit Motor Shield Object
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor* Motor1 = AFMS.getMotor(3);
	Adafruit_DCMotor* Motor2 = AFMS.getMotor(4);

	void MotorShieldTest();
	void Move(uint8_t motor_number, uint8_t speed, uint8_t DIRECTION);
	void MoveAll(uint8_t speed, uint8_t DIRECTION);
	void Stop(uint8_t motor_number);
	void StopAll();
	void Rotate(uint8_t angle, bool clockwise);
	float rotation_time;
	
	Adafruit_DCMotor* motor_from_motor_number(uint8_t motor_number);
};