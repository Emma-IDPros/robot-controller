#pragma once
#include <Arduino.h>
#include <Robot.h>
#include <LineSensor.h>
#include <WiFiComms.h>

enum REFIND_LINE_STAGES { ROTATE_LEFT, LEFT_TO_MIDDLE, ROTATE_RIGHT, RIGHT_TO_MIDDLE };

class RobotDecisions {
public:
    void FollowLine(Robot Bot, RobotLineSensor LineSensor, bool use_front_line = false);
    void FollowLineWithWiFi(Robot Bot, RobotLineSensor LineSensor, WiFiComms WiFiComm);
private:
    float rot_speed;
    bool rotate_left = false;
    int prevMillis = millis();
    REFIND_LINE_STAGES recovery_status;
};