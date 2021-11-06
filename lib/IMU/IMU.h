/**
 * @file IMU.h
 * @author IDPros
 * @brief Header file for the RobotIMU class
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino_LSM6DS3.h>
#include <math.h>
#include <MadgwickAHRS.h>
 // #include <SensorFusion.h>

enum ARENA_SIDE { BEGINNING, END };
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
	ARENA_SIDE arena_side = BEGINNING;
	void UpdateArenaSide();
	void ReadAngles();
	void Begin();
	void Update();
	RAMP_DIRECTION DetectRamp();

private:
	float prevMilliSeconds = millis();
	RAMP_DIRECTION prev_ramp_dir = FLAT;
	Madgwick filter;
};
