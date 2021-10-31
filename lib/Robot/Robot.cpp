#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Robot.h>
#include "LineSensor.h"


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

	if (ValidateMotorStatus(motor_side, speed, DIRECTION)) {
		Adafruit_DCMotor* motor = MotorFromMotorNumber(motor_side);
		motor->setSpeed(speed);
		motor->run(DIRECTION);
	}
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

	if (ValidateMotorStatus(LEFT, speed, DIRECTION) && ValidateMotorStatus(RIGHT, speed, DIRECTION)) {
		MotorLeft->setSpeed(speed);
		MotorLeft->run(DIRECTION);
	}
	if (ValidateMotorStatus(RIGHT, speed, DIRECTION)) {
		MotorRight->setSpeed(speed);
		MotorRight->run(DIRECTION);
	}
};

/**
 * @brief Stops a specific motor from moving
 *
 * @param motor_number
 * The motor that you want to stop (1 or 2)
 */
void Robot::Stop(MOTOR motor_side) {

	if (ValidateMotorStatus(motor_side, 0, RELEASE)) {
		Adafruit_DCMotor* motor = MotorFromMotorNumber(motor_side);
		motor->run(RELEASE);
	}
};

/**
 * @brief Stops all motors from moving
 */
void Robot::StopAll() {

	if (ValidateMotorStatus(LEFT, 0, RELEASE)) {
		MotorLeft->run(RELEASE);
	}
	if (ValidateMotorStatus(RIGHT, 0, RELEASE)) {
		MotorRight->run(RELEASE);
	}
};

/**
 * @brief moves motors at max speed in opposite directions to rotate
 *
 * @param clockwise
 * Direction of robot rotation (either true for clockwise or false for anticlockwise)
 */

 // void Robot::Rotate(ROTATION rotation, RobotLineSensor LineSensor) {
 // 	rotation_time = 0;
 // 	if (rotation == CLOCKWISE) {
 // 		while (rotation_time < 50) {
 // 			Move(RIGHT, 255, BACKWARD);
 // 			Move(LEFT, 255, FORWARD);
 // 			delay(10);
 // 			rotation_time++;
 // 		}
 // 		while (LineSensor.Detect() == 0) {
 // 			Move(RIGHT, 255, BACKWARD);
 // 			Move(LEFT, 255, FORWARD);
 // 			delay(10);
 // 		}
 // 		StopAll();
 // 	}
 // 	else {
 // 		while (rotation_time < 50) {
 // 			Move(RIGHT, 255, FORWARD);
 // 			Move(LEFT, 255, BACKWARD);
 // 			delay(10);
 // 			rotation_time++;
 // 		}
 // 		while (LineSensor.Detect() == 0) {
 // 			Move(RIGHT, 255, FORWARD);
 // 			Move(LEFT, 255, BACKWARD);
 // 			delay(10);
 // 		}
 // 		StopAll();
 // 	}
 // }

 /**
  * @brief Returns an Adafruit_DCMotor pointer given a motor number
  *
  * @param motor_number
  * The motor you want
  * @return Adafruit_DCMotor*
  * Returns a pointer to that specific motor
  */
Adafruit_DCMotor* Robot::MotorFromMotorNumber(MOTOR motor) {
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

/**
 * @brief Validating the motor status.
 * When trying to update the speed or direction of a motor
 * it will first check to see if the motor's speed or direction
 * has changed from its previous state. If so, it will return true
 * and change the motot status. Otherwise it will return false.
 *
 * The purpose of this function is to reduce the number of times
 * we are signalling the MotorShield to run the motor even if the speed
 * has not changed.
 *
 *
 * @param motor_side
 * The motor that you want to move (LEFT or RIGHT)
 * @param speed
 * 8 bit int (0-255) to set the speed of rotation
 * @param DIRECTION
 * Direction of rotation.
 * Either FORWARDS or BACKWARDS or RELEASE
 * @return true or false
 */
bool Robot::ValidateMotorStatus(MOTOR motor, uint8_t speed, uint8_t DIRECTION) {
	switch (motor)
	{
	case LEFT:
		if (motor_status_left.speed != speed || motor_status_left.DIRECTION != DIRECTION) {

			motor_status_left.speed = speed;
			motor_status_left.DIRECTION = DIRECTION;
			return true;
		}
		else {
			return false;
		}
		break;
	case RIGHT:
		if (motor_status_right.speed != speed || motor_status_right.DIRECTION != DIRECTION) {

			motor_status_right.speed = speed;
			motor_status_right.DIRECTION = DIRECTION;
			return true;
		}
		else {
			return false;
		}
		break;

	default:
		break;
	}
}