#include <Arduino.h>
#include <RobotSensors.h>

/**
 * @brief Gets the distance from the ultrasound (in cm)
 *
 * @return float distance (cm)
 */
float Ultrasound::GetDistance() {
	digitalWrite(US_pinTrig, LOW);
	delayMicroseconds(3);
	digitalWrite(US_pinTrig, HIGH);//sends out ultrasound signal
	delayMicroseconds(10);
	digitalWrite(US_pinTrig, LOW);
	long timeTaken = pulseIn(US_pinEcho, HIGH);//recieves time taken to get reply
	float calibration = 1.03;//calibration factor
	float intermiediate = timeTaken * 0.049 * calibration / 2;
	float linear_fit = (intermiediate - 0.268) / 1.3633;
	return linear_fit;
}

/**
 * @brief Gets the distance from the A02 IR sensor (in cm)
 * (accuracy +-5cm, range 20-160cm, line of sight)
 *
 * @return float distance (cm)
 */
float IR_A02::GetDistance() {
	int DistanceAdd = 0;
	for (int i = 0; i < 20; i++) {//takes multiple measurements
		int val = analogRead(IR_A02pin);
		DistanceAdd += 2 + 10808 / val; //calculates distance from analog value
		delayMicroseconds(2);
	}
	return DistanceAdd / 20;
}

/**
 * @brief Gets the distance from the A21 IR sensor (in cm)
 * (accuracy +-3cm, range 5-100cm, line of sight)
 *
 * @return float distance (cm)
 */
float IR_A21::GetDistance() {
	int DistanceAdd = 0;
	for (int i = 0; i < 20; i++) {//takes multiple measurements
		int val = analogRead(IR_A21pin);
		DistanceAdd += -5 + 6402 / val; //calculates distance from analog value
		delayMicroseconds(2);
	}
	return DistanceAdd / 20;
}

/**
 * @brief Sets the pins for all the Robot sensors
 *
 * @param US_pinTrig Ultrasound Trigger pin (DIGITAL)
 * @param US_pinEcho Ultrasound Echo pin (DIGITAL)
 * @param IR_A21pin  A21 pin (ANALOGUE)
 * @param IR_A02pin  A02 pin (ANALOGUE)
 */
void RobotSensors::SetPins(int US_pinTrig, int US_pinEcho, int IR_A21pin, int IR_A02pin) {
	Ultrasound.US_pinEcho = US_pinEcho;
	Ultrasound.US_pinTrig = US_pinTrig;
	A21.IR_A21pin = IR_A21pin;
	A02.IR_A02pin = IR_A02pin;

	pinMode(US_pinTrig, OUTPUT);
	pinMode(US_pinEcho, INPUT);
}