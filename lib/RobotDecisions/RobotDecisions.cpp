#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor) {
	int MAXSPEED = 250;
	int SWING = 50;
	int DEADZONE = 0.01;
	if (LineSensor.Detect() && false) {
		Bot.MoveAll(MAXSPEED, FORWARD);
		Serial.println("STRAIGHT");
	}
	if (LineSensor.LineFollowSense() < -DEADZONE) {
		rot_speed = LineSensor.LineFollowSense() * SWING + (MAXSPEED - SWING);
		Bot.Move(LEFT, int(rot_speed), FORWARD);
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		//Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT 200 RIGHT:" + String(rot_speed));
		// Bot.Move(RIGHT, 100, FORWARD);
	}
	else if (LineSensor.LineFollowSense() > DEADZONE) {
		rot_speed = (-LineSensor.LineFollowSense() * SWING) + (MAXSPEED - SWING);
		Bot.Move(RIGHT, int(rot_speed), FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		//Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT 200 LEFT:" + String(rot_speed));

		// Serial.println("LEFT " + String(rot_speed));
		// Bot.Move(LEFT, 100, FORWARD);
	}
	else {
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
	}
}

void RobotDecisions::FollowLineWithWiFi(Robot Bot, RobotLineSensor LineSensor, WiFiComms WiFiComm) {
	if (LineSensor.Detect()) {
		Bot.MoveAll(255, FORWARD);
		Serial.println("STRAIGHT");
		WiFiComm.Message("STRAIGHT");
	}
	else if (LineSensor.LineFollowSense() < -0.5 && !LineSensor.Detect()) {
		rot_speed = LineSensor.LineFollowSense() * 130 + 200;
		Bot.Move(LEFT, 200, FORWARD);
		Bot.Move(RIGHT, rot_speed, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT 200 RIGHT:" + String(rot_speed));
		WiFiComm.Message(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT 200 RIGHT:" + String(rot_speed));
		// Bot.Move(RIGHT, 100, FORWARD);
	}
	else if (LineSensor.LineFollowSense() > 0.5 && !LineSensor.Detect()) {
		rot_speed = -LineSensor.LineFollowSense() * 130 + 200;
		Bot.Move(RIGHT, 200, FORWARD);
		Bot.Move(LEFT, rot_speed, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT 200 LEFT:" + String(rot_speed));
		WiFiComm.Message(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT 200 LEFT:" + String(rot_speed));

		// Serial.println("LEFT " + String(rot_speed));
		// Bot.Move(LEFT, 100, FORWARD);
	}
}