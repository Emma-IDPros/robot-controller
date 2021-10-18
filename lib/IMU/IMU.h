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

	void VerletInt();
	float new_position, prev_position, position, velocity;
	
private:
	float prevMilliSeconds = millis();
	float prev_ax, prev_ay, prev_az;
	float prev_vx, prev_vy, prev_vz;
	float TrapeziumArea(float a, float b, float h);


	float counter;
};
