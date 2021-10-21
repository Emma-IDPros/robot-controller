#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor) {
	if (LineSensor.LineFollowSense() < -0.5) {
		rot_speed = LineSensor.LineFollowSense() * 130 + 200;
		Bot.Move(2, 200, FORWARD);
    	Bot.Move(1, rot_speed, FORWARD);
  	}
  	else if (LineSensor.LineFollowSense() > 0.5) {
		rot_speed = -LineSensor.LineFollowSense() * 130 + 200;
    	Bot.Move(1, 200, FORWARD);
    	Bot.Move(2, rot_speed, FORWARD);
  	}
  	else if (LineSensor.LineFollowSense() <= 0.5 && LineSensor.LineFollowSense() >= -0.5) {
    	Bot.MoveAll(255, FORWARD);
  	}
}