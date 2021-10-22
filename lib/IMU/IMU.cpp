#include <IMU.h>
#include <Arduino_LSM6DS3.h>
#include <RobotMath.h>
#define SAMPLE_RATE 10
int THRESHOLD_ANGLE = 10;

/**
 * @brief Uses the IMU acceleration values to
 * determine if the robot is on the RAMP or not,
 * and which side of the ramp
 *
 * @return RAMP_DIRECTION
 */
RAMP_DIRECTION RobotIMU::DetectRamp() {
	if (pitch > THRESHOLD_ANGLE) {
		return UP;
	}
	else if (pitch < -THRESHOLD_ANGLE) {
		return DOWN;
	}
	else {
		return FLAT;
	}

}

void RobotIMU::UpdateArenaSide() {
	RAMP_DIRECTION ramp_dir = DetectRamp();

	if (arena_side == BEGINNING && ramp_dir == DOWN && prev_ramp == FLAT) {
		arena_side = END;
	}
	else if (arena_side == END && ramp_dir == DOWN && prev_ramp == FLAT) {
		arena_side = BEGINNING;
	}
	prev_ramp = ramp_dir;
}


void RobotIMU::ReadAngles() {
	if (millis() - prevMilliSeconds >= 1000 / SAMPLE_RATE) {


		if (IMU.accelerationAvailable()) {
			IMU.readAcceleration(ax, ay, az);
		}
		if (IMU.gyroscopeAvailable()) {
			IMU.readGyroscope(gx, gy, gz);
		}

		filter.updateIMU(gx, gy, gz, ax, ay, az);

		roll = filter.getRoll();
		pitch = filter.getPitch();
		yaw = filter.getYaw();
		prevMilliSeconds = millis();
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
	filter.begin(SAMPLE_RATE);
}
