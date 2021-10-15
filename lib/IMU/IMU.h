#pragma once
#include <Arduino_LSM6DS3.h>

class RobotIMU {
public:
	float ax, ay, az;
	float vx, vy, vz;
	float x, y, z;
	void ReadAcceleration();
	void Begin();
	void Integrate();
private:
	float prevMilliSeconds = millis();
};
