#pragma once
#include <Arduino.h>
#include <Robot.h>
#include <LineSensor.h>
#include <WiFiComms.h>
#include <RobotSensors.h>
#include <PickUp.h>
#include <IMU.h>
#include <MetalDetector.h>

enum REFIND_LINE_STAGES { ROTATE_LEFT, LEFT_TO_MIDDLE, ROTATE_RIGHT, RIGHT_TO_MIDDLE };

class RobotDecisions {
public:
    void FollowLine_v0(Robot Bot, RobotLineSensor LineSensor);
    void FollowLine(Robot Bot, RobotLineSensor LineSensor, bool use_front_line = false);
    void FollowLineWithWiFi(Robot Bot, RobotLineSensor LineSensor, bool use_front_line, WiFiComms WiFiComm);
    void BlockCollect(Robot Bot, RobotSensors Sensors, RobotPickUp PickUp, RobotIMU BotIMU, RobotLineSensor LineSensor);
    void Junction(Robot Bot, RobotSensors Sensors, RobotPickUp PickUp, RobotIMU BotIMU, RobotLineSensor LineSensor, RobotMetalDetector MetalDetector);
private:
    float rot_speed;
    bool rotate_left = false;
    int prevMillis = millis();
    REFIND_LINE_STAGES recovery_status;
};