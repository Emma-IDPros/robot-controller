#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor) {
	if (LineSensor.LineFollowSense() < -0.5) {
		rot_speed = LineSensor.LineFollowSense() * 130 + 200;
		Bot.Move(LEFT, 200, FORWARD);
    	Bot.Move(RIGHT, rot_speed, FORWARD);
  	}
  	else if (LineSensor.LineFollowSense() > 0.5) {
		rot_speed = -LineSensor.LineFollowSense() * 130 + 200;
    	Bot.Move(LEFT, 200, FORWARD);
    	Bot.Move(RIGHT, rot_speed, FORWARD);
  	}
  	else {
    	Bot.MoveAll(255, FORWARD);
  	}
}