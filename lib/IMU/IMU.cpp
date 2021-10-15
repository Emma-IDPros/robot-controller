#include <IMU.h>
#include <Arduino_LSM6DS3.h>

void RobotIMU::ReadAcceleration() {
	if (IMU.accelerationAvailable()) {
		IMU.readAcceleration(ax, ay, az);
		ax *= 9.81;
		ay *= 9.81;
		az *= 9.81;
	}
}

void RobotIMU::Begin() {
	if (!IMU.begin()) {
		Serial.println("Failed to initialize IMU!");
		while (1);
	}
}

void RobotIMU::Integrate() {
	double delta_t = (millis() - prevMilliSeconds) / 1000;
	vx += ax * delta_t; vy += ay * delta_t; vz += az * delta_t;
	x += vx * delta_t;y += vy * delta_t;z += vz * delta_t;
	prevMilliSeconds = millis();
}