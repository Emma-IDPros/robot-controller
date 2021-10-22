#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Robot.h>

/**
 * @brief Runs the Adafruit Test Script for the
 * Motor Shield.
 */
void Robot::MotorShieldTest() {
	Serial.println("Adafruit Motorshield v2 - DC Motor test!");
	if (!AFMS.begin()) {
		Serial.println("Could not find Motor Shield. Check wiring.");
		while (1);
	}
	Serial.println("Motor Shield found.");
};

/**
 * @brief Makes a specifc motor move
 *
 * @param motor_side
 * The motor that you want to move (LEFT or RIGHT)
 * @param speed
 * 8 bit int (0-255) to set the speed of rotation
 * @param DIRECTION
 * Direction of rotation.
 * Either FORWARDS or BACKWARDS
 */
void Robot::Move(MOTOR motor_side, uint8_t speed, uint8_t DIRECTION) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_side);
	motor->setSpeed(speed);
	motor->run(DIRECTION);
};

/**
 * @brief Makes both motors move
 *
 * @param speed
 * 8 bit int (0-255) to set the speed of rotation
 * @param DIRECTION
 * Direction of rotation.
 * Either FORWARDS or BACKWARDS
 */
void Robot::MoveAll(uint8_t speed, uint8_t DIRECTION) {
	MotorRight->setSpeed(speed);
	MotorRight->run(DIRECTION);
	MotorLeft->setSpeed(speed);
	MotorLeft->run(DIRECTION);
};

/**
 * @brief Stops a specific motor from moving
 *
 * @param motor_number
 * The motor that you want to stop (1 or 2)
 */
void Robot::Stop(MOTOR motor_side) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_side);
	motor->run(RELEASE);
};

/**
 * @brief Stops all motors from moving
 */
void Robot::StopAll() {
	MotorLeft->run(RELEASE);
	MotorRight->run(RELEASE);
};

/**
 * @brief moves motors at max speed in opposite directions to rotate
 *
 * @param angle
 * Angle either 90 degrees or 180 degrees
 *
 * @param clockwise
 * Direction of robot rotation (either true for clockwise or false for anticlockwise)
 */
void Robot::Rotate(uint8_t angle, ROTATION rotation) {
	rotation_time = 0;

	if (angle == 90) {
		if (rotation == CLOCKWISE) {
			while (rotation_time < 160) {
				Move(RIGHT, 255, BACKWARD);
				Move(LEFT, 255, FORWARD);
				delay(10);
				rotation_time++;
			}
			StopAll();
		}
		else {
			while (rotation_time < 160) {
				Move(RIGHT, 255, FORWARD);
				Move(LEFT, 255, BACKWARD);
				delay(10);
				rotation_time++;
			}
			StopAll();
		}
	}
	else if (angle == 180) {
		if (rotation == CLOCKWISE) {
			while (rotation_time < 320) {
				Move(RIGHT, 255, BACKWARD);
				Move(LEFT, 255, FORWARD);
				delay(10);
				rotation_time++;
			}
			StopAll();
		}
		else {
			while (rotation_time < 320) {
				Move(RIGHT, 255, FORWARD);
				Move(LEFT, 255, BACKWARD);
				delay(10);
				rotation_time++;
			}
			StopAll();
		}
	}
}
/**
 * @brief Returns an Adafruit_DCMotor pointer given a motor number
 *
 * @param motor_number
 * The motor you want
 * @return Adafruit_DCMotor*
 * Returns a pointer to that specific motor
 */
Adafruit_DCMotor* Robot::motor_from_motor_number(MOTOR motor) {
	switch (motor)
	{
	case LEFT:
		return MotorLeft;
		break;
	case RIGHT:
		return MotorRight;
		break;

	default:
		break;
	}
}