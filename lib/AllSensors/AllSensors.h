#pragma once

class Ultrasound {
public:
	int US_pinTrig;
	int US_pinEcho;
	float getDistance();

};

class IR_A02 {
public:
	int IR_A02pin;

	float getDistance();

};
class IR_A21 {
public:
	int IR_A21pin;

	float getDistance();

};

class IR {
public:
	IR_A21 A21;
	IR_A02 A02;

};

class AllSensors {
public:
	Ultrasound Ultrasound;
	IR_A21 A21;
	IR_A02 A02;
	void setPins(int US_pinTrig, int US_pinEcho, int IR_A21pin, int IR_A02pin);
};
