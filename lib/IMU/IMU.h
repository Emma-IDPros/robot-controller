#pragma once
#include <Arduino_LSM6DS3.h>

/**
 * @brief Class for the Inertial Measurement Unit
 */
class RobotIMU {
public:
	// IMU acceleration
	float ax, ay, az;
	// velocity
	float vx, vy, vz;
	// positon
	float x, y, z;
	void ReadAcceleration();
	void Begin();
	void Integrate();
private:
	float prevMilliSeconds = millis();
};
