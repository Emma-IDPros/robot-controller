#include <IMU.h>
#include <Arduino_LSM6DS3.h>
#include <RobotMath.h>

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
 * @brief Uses the IMU acceleration values to
 * determine if the robot is on the RAMP or not,
 * and which side of the ramp
 *
 * @return RAMP_DIRECTION
 */
RAMP_DIRECTION RobotIMU::DetectRamp() {
	if (RobotMath.IsWithIn(ax, -3, 0.3) && RobotMath.IsWithIn(az, 9.3, 0.3)) {
		return UP;
	}
	else if (RobotMath.IsWithIn(ax, 3, 0.3) && RobotMath.IsWithIn(az, 9.3, 0.3)) {
		return DOWN;
	}
	else {
		return FLAT;
	}

}


void RobotIMU::ReadAngles() {
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

}

/**
 * @brief Begins the connection to the IMU
 */
void RobotIMU::Begin() {
	if (!IMU.begin()) {
		Serial.println("Failed to initialize IMU!");
		while (1);
	}
	filter.begin(10);
}
/**
 * @brief Attempt at performing numerical intergration of acceleration to give
 * velocity and displacement. The velocity and displacement are stored in the
 * attributes as vx, vy, vz and x, y, z
 */
void RobotIMU::Integrate() {
	// cumulative trapezium
	double delta_t = (millis() - prevMilliSeconds) / 1000;
	if (abs(ax) > 0.03) { // acceleration threshold
		vx += RobotMath.TrapeziumArea(prev_ax, ax, delta_t);
		vy += RobotMath.TrapeziumArea(prev_ay, ay, delta_t);
		vz += RobotMath.TrapeziumArea(prev_az, az, delta_t);
		x += RobotMath.TrapeziumArea(prev_vx, vx, delta_t);
		y += RobotMath.TrapeziumArea(prev_vy, vy, delta_t);
		z += RobotMath.TrapeziumArea(prev_vz, vz, delta_t);

		prev_ax = ax; prev_ay = ay; prev_az = az;
		prev_vx = vx; prev_vy = vy; prev_vz = vz;
	}
	prevMilliSeconds = millis();
}



// verlet integrator for just the z axis
void RobotIMU::VerletInt() {
	double delta_t = (millis() - prevMilliSeconds) / 1000;

	if (abs(az) > 0.03) { // acceleration threshold

		if (counter == 0) {
			position = 0;
			velocity = 0;
			new_position = position + velocity * delta_t;
			velocity = velocity + az * delta_t;
		}
		else {
			new_position = 2 * position - prev_position + delta_t * delta_t * az;
			velocity = (new_position - position) / delta_t;
		}

		prev_position = position;
		position = new_position;

		counter++;


	}

	prevMilliSeconds = millis();
}