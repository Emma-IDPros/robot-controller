#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Robot.h>

void Robot::Move(uint8_t motor_number, uint8_t speed, uint8_t DIRECTION) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_number);
	motor->setSpeed(speed);
	motor->run(DIRECTION);
};

void Robot::MoveAll(uint8_t speed, uint8_t DIRECTION) {
	Motor1->setSpeed(speed);
	Motor1->run(DIRECTION);
	Motor2->setSpeed(speed);
	Motor2->run(DIRECTION);
};

void Robot::Stop(uint8_t motor_number) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_number);
	motor->run(RELEASE);
};

void Robot::StopAll() {
	Motor1->run(RELEASE);
	Motor2->run(RELEASE);
};

Adafruit_DCMotor* Robot::motor_from_motor_number(uint8_t motor_number) {
	switch (motor_number)
	{
	case 1:
		return Motor1;
		break;
	case 2:
		return Motor2;
		break;

	default:
		break;
	}
}