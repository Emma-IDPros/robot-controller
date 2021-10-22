#pragma once
#include <Arduino.h>
#include <Robot.h>
#include <LineSensor.h>
#include <WiFiComms.h>

class RobotDecisions {
public:
    void FollowLine(Robot Bot, RobotLineSensor LineSensor);
    void FollowLineWithWiFi(Robot Bot, RobotLineSensor LineSensor, WiFiComms WiFiComm);
private:
    float rot_speed;
};