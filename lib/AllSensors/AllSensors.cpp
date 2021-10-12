#include <Arduino.h>

class Ultrasound {
public:
	int US_pinTrig = 3;
	int US_pinEcho = 2;
	float getDistance();

};

float Ultrasound::getDistance() {
	digitalWrite(US_pinTrig, LOW);
	delayMicroseconds(3);
	digitalWrite(US_pinTrig, HIGH);//sends out ultrasound signal
	delayMicroseconds(10);
	digitalWrite(US_pinTrig, LOW);
	long timeTaken = pulseIn(US_pinEcho, HIGH);//recieves time taken to get reply
	float calibration = 1.03;//calibration factor
	return timeTaken * 0.0343 * calibration / 2;
}

class IR_A02 {
public:
	int IR_A02pin = 0;

	float getDistance();

};

float IR_A02::getDistance() {
	int DistanceAdd = 0;
	for (int i = 0; i < 20; i++) {//takes multiple measurements
		int val = analogRead(IR_A02pin);
		DistanceAdd += 2 + 10808 / val; //calculates distance from analog value
		delayMicroseconds(2);
	}
	return DistanceAdd / 20;
}


class IR_A21 {
public:
	int IR_A21pin = 0;

	float getDistance();

};

float IR_A21::getDistance() {
	int DistanceAdd = 0;
	for (int i = 0; i < 20; i++) {//takes multiple measurements
		int val = analogRead(IR_A21pin);
		DistanceAdd += 2 + 10808 / val; //calculates distance from analog value
		delayMicroseconds(2);
	}
	return DistanceAdd / 20;
}

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

void AllSensors::setPins(int US_pinTrig, int US_pinEcho, int IR_A21pin, int IR_A02pin) {
	Ultrasound.US_pinEcho = US_pinEcho;
	Ultrasound.US_pinEcho = US_pinEcho;
	A21.IR_A21pin = IR_A21pin;
	A02.IR_A02pin = IR_A02pin;
}