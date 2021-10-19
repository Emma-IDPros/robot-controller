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

RAMP_DIRECTION RobotIMU::DetectRamp() {
	if (IsWithIn(ax, -3, 0.3) && IsWithIn(az, 9.3, 0.3)) {
		return UP;
	}
	else if (IsWithIn(ax, 3, 0.3) && IsWithIn(az, 9.3, 0.3)) {
		return DOWN;
	}
	else {
		return FLAT;
	}

}

bool RobotIMU::IsWithIn(float number, float comparator, float range) {
	return (number > comparator - range) && (number < comparator + range);
}

void RobotIMU::ReadAngles() {
	if (IMU.accelerationAvailable()) {
		IMU.readAcceleration(ax, ay, az);
	}
	if (IMU.gyroscopeAvailable()) {
		IMU.readGyroscope(gx, gy, gz);
		gx *= 0.01745329251;
		gy *= 0.01745329251;
		gz *= 0.01745329251;

		// Serial.println(String(gx));
	}
	deltat = fusion.deltatUpdate(); //this have to be done before calling the fusion update
	fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow

	pitch = fusion.getPitch();
	roll = fusion.getRoll();    //you could also use getRollRadians() ecc
	yaw = fusion.getYaw();
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
	// cumulative trapezium
	double delta_t = (millis() - prevMilliSeconds) / 1000;
	if (abs(ax) > 0.03) { // acceleration threshold
		vx += TrapeziumArea(prev_ax, ax, delta_t);
		vy += TrapeziumArea(prev_ay, ay, delta_t);
		vz += TrapeziumArea(prev_az, az, delta_t);
		x += TrapeziumArea(prev_vx, vx, delta_t);
		y += TrapeziumArea(prev_vy, vy, delta_t);
		z += TrapeziumArea(prev_vz, vz, delta_t);

		prev_ax = ax; prev_ay = ay; prev_az = az;
		prev_vx = vx; prev_vy = vy; prev_vz = vz;
	}
	prevMilliSeconds = millis();
}

/**
 * @brief Calculates the area of a trapezium
 *
 * @param a base
 * @param b base
 * @param h height
 * @return float area
 */
float RobotIMU::TrapeziumArea(float a, float b, float h) {
	return 0.5 * (a + b) * h;
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