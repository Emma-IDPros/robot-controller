#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class Robot {
public:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor* Motor1 = AFMS.getMotor(3);
	Adafruit_DCMotor* Motor2 = AFMS.getMotor(4);


	void move(uint8_t motor_number, uint8_t speed, uint8_t DIRECTION);
	void move_all(uint8_t speed, uint8_t DIRECTION);
	void release(uint8_t motor_number);
	void release_all();
	Adafruit_DCMotor* motor_from_motor_number(uint8_t motor_number);
};