#include <PickUp.h>

void RobotPickUp::SetPins(byte servo_pin) {
	servo.attach(servo_pin);
}

void RobotPickUp::Sweep(int to_angle) {
	if (angle > to_angle) {
		while (angle > to_angle) {
			servo.write(angle);
			angle--;
		}
	}
	else {
		while (angle < to_angle) {
			servo.write(angle);
			angle++;
		}
	}
}

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