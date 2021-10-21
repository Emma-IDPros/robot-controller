#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor) {
	if (LineSensor.LineFollowSense() < 0) {
		rot_speed = LineSensor.LineFollowSense() * 130 + 255;
		Bot.Move(2, 255, FORWARD);
    	Bot.Move(1, rot_speed, FORWARD);
  	}
  	else if (LineSensor.LineFollowSense() > 0) {
		rot_speed = -LineSensor.LineFollowSense() * 130 + 255;
    	Bot.Move(1, 255, FORWARD);
    	Bot.Move(2, rot_speed, FORWARD);
  	}
  	else {
    	Bot.MoveAll(255, FORWARD);
  	}
}