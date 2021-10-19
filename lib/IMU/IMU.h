#pragma once
#include <Arduino_LSM6DS3.h>
#include <SensorFusion.h>

enum RAMP_DIRECTION { UP, DOWN, FLAT };

/**
 * @brief Class for the Inertial Measurement Unit
 */
class RobotIMU {
public:
	// IMU acceleration
	float ax, ay, az;
	// gyroscope
	float gx, gy, gz;
	// angles
	float pitch, yaw, roll;
	// velocity
	float vx, vy, vz;
	// positon
	float x, y, z;
	void ReadAcceleration();
	void ReadAngles();
	void Begin();
	void Integrate();
	RAMP_DIRECTION DetectRamp();
	void VerletInt();
	float new_position, prev_position, position, velocity;

private:
	float prevMilliSeconds = millis();
	float prev_ax, prev_ay, prev_az;
	float prev_vx, prev_vy, prev_vz;
	float TrapeziumArea(float a, float b, float h);
	bool IsWithIn(float number, float range);
	float deltat;
	SF fusion;


	float counter;
};
