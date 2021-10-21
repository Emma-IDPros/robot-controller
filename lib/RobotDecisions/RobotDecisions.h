#pragma once
#include <Arduino.h>
#include <Robot.h>
#include <LineSensor.h>

class RobotDecisions{
    public:
        void FollowLine(Robot Bot, RobotLineSensor LineSensor);

    private:
        float rot_speed;
};