#include <IMU.h>
#include <Arduino_LSM6DS3.h>

/**
 * @brief Reads the acceleration from the IMU and stores it in the attributes
 * ax, ay, ax
 */
void RobotIMU::ReadAcceleration() {
	if (IMU.accelerationAvailable()) {
		IMU.readAcceleration(ax, ay, az);
		ax *= 9.81;
		ay *= 9.81;
		az *= 9.81;
	}
}

/**
 * @brief Begins the connection to the IMU
 */
void RobotIMU::Begin() {
	if (!IMU.begin()) {
		Serial.println("Failed to initialize IMU!");
		while (1);
	}
}
/**
 * @brief Attempt at performing numerical intergration of acceleration to give
 * velocity and displacement. The velocity and displacement are stored in the
 * attributes as vx, vy, vz and x, y, z
 */
void RobotIMU::Integrate() {
	double delta_t = (millis() - prevMilliSeconds) / 1000;
	if (abs(ax) > 0.03) {
		vx += ax * delta_t; vy += ay * delta_t; vz += az * delta_t;
		x += vx * delta_t;y += vy * delta_t;z += vz * delta_t;
	}
	prevMilliSeconds = millis();
}