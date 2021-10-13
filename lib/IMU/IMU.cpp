#include <IMU.h>
#include <Arduino_LSM6DS3.h>

void RobotIMU::ReadAcceleration() {
	if (IMU.accelerationAvailable()) {
		IMU.readAcceleration(ax, ay, az);
	}
}
