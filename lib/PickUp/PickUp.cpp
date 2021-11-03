#include <PickUp.h>

/**
 * @brief Set pins
 *
 * @param servo_pin Either 9 or 10,
 * use the servo connector on the Motor Shield
 */
void RobotPickUp::SetPins(byte servo_pin) {
	servo.attach(servo_pin);
}

/**
 * @brief Sweeps from current angle,
 * to the angle passed
 *
 * @param to_angle
 */
void RobotPickUp::Sweep(int to_angle) {
	if (angle > to_angle) {
		while (angle > to_angle) {
			servo.write(angle);
			angle--;
			delay(30);
		}
	}
	else {
		while (angle < to_angle) {
			servo.write(angle);
			angle++;
			delay(30);
		}
	}
}

/**
 * @brief Sets initial angle
 *
 * @param angle_inp
 */
void RobotPickUp::SetInitalAngle(int angle_inp) {
	if (!inital_angle_set) {
		angle = angle_inp;
		servo.write(angle);
		delay(300);
		inital_angle_set = true;
	}
}

/**
 * @brief Runs a basic sweep test
 *
 */
void RobotPickUp::SweepTest() {
	int pos;
	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
		servo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		servo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
}