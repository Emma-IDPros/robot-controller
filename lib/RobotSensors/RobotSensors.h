/**
 * @file RobotSensors.h
 * @author IDPros
 * @brief Header file for the RobotSensors
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

 // Class for the ultrasound
class Ultrasound {
public:
	byte US_pinTrig;
	byte US_pinEcho;
	float GetDistance();

};

// Class for the IR sensors A02
class IR_A02 {
public:
	byte IR_A02pin;

	float GetDistance();

};

// Class for the IR sensors A21
class IR_A21 {
public:
	byte IR_A21pin;

	float GetDistance();

};

// Class for both IR sensors
class IR {
public:
	IR_A21 A21;
	IR_A02 A02;

};

// Class for all the sensors
class RobotSensors {
public:
	Ultrasound Ultrasound;
	IR_A21 A21;
	IR_A02 A02;
	void SetPins(byte US_pinTrig, byte US_pinEcho, byte IR_A21pin, byte IR_A02pin);
};
