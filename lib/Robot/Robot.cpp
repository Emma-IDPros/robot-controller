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
 * @param motor_number
 * The motor that you want to move (1 or 2)
 * @param speed
 * 8 bit int (0-255) to set the speed of rotation
 * @param DIRECTION
 * Direction of rotation.
 * Either FORWARDS or BACKWARDS
 */
void Robot::Move(uint8_t motor_number, uint8_t speed, uint8_t DIRECTION) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_number);
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
	Motor1->setSpeed(speed);
	Motor1->run(DIRECTION);
	Motor2->setSpeed(speed);
	Motor2->run(DIRECTION);
};

/**
 * @brief Stops a specific motor from moving
 *
 * @param motor_number
 * The motor that you want to stop (1 or 2)
 */
void Robot::Stop(uint8_t motor_number) {
	Adafruit_DCMotor* motor = motor_from_motor_number(motor_number);
	motor->run(RELEASE);
};

/**
 * @brief Stops all motors from moving
 */
void Robot::StopAll() {
	Motor1->run(RELEASE);
	Motor2->run(RELEASE);
};

/**
 * @brief moves motors at max speed in opposite directions to rotate
 *
 * @param angle
 * Angle either 90 degrees or 180 degrees
 *
 * @param clockwise
 * Direction of robot rotation (either true for clockwise or false for anticlockwise)
 *
 * @param rotating
 * To run the function once when called
 */

void Robot::Rotate(uint8_t angle, ROTATION rotation, ROTATE_ON rotating) {
	rotation_time = 0;
	if (angle == 90, rotation == CLOCKWISE, rotating = ON) {
		while (rotation_time < 160) {
			Move(1, 255, FORWARD);
			Move(2, 255, BACKWARD);
			delay(10);
			rotation_time++;
		}
		StopAll();
		rotating = OFF;
	}
	else if (angle == 90, rotation == ANTICLOCKWISE, rotating = ON) {
		while (rotation_time < 160) {
			Move(1, 255, BACKWARD);
			Move(2, 255, FORWARD);
			delay(10);
			rotation_time++;
		}
		StopAll();
		rotating = OFF;
	}
	else if (angle == 180, rotation == CLOCKWISE, rotating = ON) {
		while (rotation_time < 320) {
			Move(1, 255, FORWARD);
			Move(2, 255, BACKWARD);
			delay(10);
			rotation_time++;
		}
		StopAll();
		rotating = OFF;
	}
	else if (angle == 180, rotation == ANTICLOCKWISE, rotating = ON) {
		while (rotation_time < 320) {
			Move(1, 255, BACKWARD);
			Move(2, 255, FORWARD);
			delay(10);
			rotation_time++;
		}
		StopAll();
		rotating = OFF;
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