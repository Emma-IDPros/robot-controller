#pragma once

// Class for the ultrasound
class Ultrasound {
public:
	int US_pinTrig;
	int US_pinEcho;
	float GetDistance();

};

// Class for the IR sensors A02
class IR_A02 {
public:
	int IR_A02pin;

	float GetDistance();

};

// Class for the IR sensors A21
class IR_A21 {
public:
	int IR_A21pin;

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
	void SetPins(int US_pinTrig, int US_pinEcho, int IR_A21pin, int IR_A02pin);
};
