#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor, bool use_front_line = false) {
	int MAXSPEED = 250;
	int SWING = 50;
	int DEADZONE = 0.01;
	int DELAY = 1000;
	if (!LineSensor.Detect() && use_front_line) {
		bool move_left = recovery_status == ROTATE_LEFT || recovery_status == RIGHT_TO_MIDDLE;

		Bot.Move(LEFT, 50, move_left ? BACKWARD : FORWARD);
		Bot.Move(RIGHT, 50, move_left ? FORWARD : BACKWARD);

		if (millis() - prevMillis > DELAY) {
			switch (recovery_status)
			{
			case ROTATE_LEFT:
				recovery_status = LEFT_TO_MIDDLE;
				break;
			case LEFT_TO_MIDDLE:
				recovery_status = ROTATE_RIGHT;
				break;
			case ROTATE_RIGHT:
				recovery_status = RIGHT_TO_MIDDLE;
				break;
			case RIGHT_TO_MIDDLE:
				recovery_status = ROTATE_LEFT;
				break;
			default:
				break;
			}
			prevMillis = millis();
		}
		Serial.println(recovery_status);
		return;
	}
	if (LineSensor.LineFollowSense() < -DEADZONE) {
		rot_speed = LineSensor.LineFollowSense() * SWING + (MAXSPEED - SWING);
		Bot.Move(LEFT, int(rot_speed), FORWARD);
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT 200 RIGHT:" + String(rot_speed) + " " + String(LineSensor.line_val_analog));
		// Bot.Move(RIGHT, 100, FORWARD);
	}
	else if (LineSensor.LineFollowSense() > DEADZONE) {
		rot_speed = (-LineSensor.LineFollowSense() * SWING) + (MAXSPEED - SWING);
		Bot.Move(RIGHT, int(rot_speed), FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT 200 LEFT:" + String(rot_speed) + " " + String(LineSensor.line_val_analog));


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