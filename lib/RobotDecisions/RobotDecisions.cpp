#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor, bool use_front_line = false) {
	int MAXSPEED = 250;
	int SWING = 50;
	int DEADZONE = 0.01;
	int DELAY = 1000;
	if (!LineSensor.Detect() && use_front_line) {
		bool move_left = recovery_status == ROTATE_LEFT || recovery_status == RIGHT_TO_MIDDLE;

		Bot.Move(LEFT, 255, move_left ? BACKWARD : FORWARD);
		Bot.Move(RIGHT, 255, move_left ? FORWARD : BACKWARD);

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

	// proportional control
	if (LineSensor.LineFollowSense() < -DEADZONE) {
		rot_speed = LineSensor.LineFollowSense() * SWING + (MAXSPEED - SWING);
		Bot.Move(LEFT, int(rot_speed), FORWARD);
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT: " + String((1 - DEADZONE) * MAXSPEED) + " LEFT: " + String(rot_speed) + " Analogue input: " + String(LineSensor.line_val_analog));

	}
	else if (LineSensor.LineFollowSense() > DEADZONE) {
		rot_speed = (-LineSensor.LineFollowSense() * SWING) + (MAXSPEED - SWING);
		Bot.Move(RIGHT, int(rot_speed), FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT: " + String((1 - DEADZONE) * MAXSPEED) + " RIGHT: " + String(rot_speed) + " Analogue input: " + String(LineSensor.line_val_analog));

	}
	else {
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
	}
}

// FollowLineWithWifi has the same code as above, but outputs to the laptop over wifi
void RobotDecisions::FollowLineWithWiFi(Robot Bot, RobotLineSensor LineSensor, bool use_front_line = false, WiFiComms WiFiComm) {
	int MAXSPEED = 250;
	int SWING = 50;
	int DEADZONE = 0.01;
	int DELAY = 1000;
	if (!LineSensor.Detect() && use_front_line) {
		bool move_left = recovery_status == ROTATE_LEFT || recovery_status == RIGHT_TO_MIDDLE;

		Bot.Move(LEFT, 255, move_left ? BACKWARD : FORWARD);
		Bot.Move(RIGHT, 255, move_left ? FORWARD : BACKWARD);

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
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT: " + String((1 - DEADZONE) * MAXSPEED) + " LEFT: " + String(rot_speed) + " Analogue input: " + String(LineSensor.line_val_analog));
		WiFiComm.Message(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " RIGHT: " + String((1 - DEADZONE) * MAXSPEED) + " LEFT: " + String(rot_speed) + " Analogue input: " + String(LineSensor.line_val_analog));

	}
	else if (LineSensor.LineFollowSense() > DEADZONE) {
		rot_speed = (-LineSensor.LineFollowSense() * SWING) + (MAXSPEED - SWING);
		Bot.Move(RIGHT, int(rot_speed), FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT " + String((1 - DEADZONE) * MAXSPEED) + " RIGHT: " + String(rot_speed) + " Analogue input: " + String(LineSensor.line_val_analog));
		WiFiComm.Message(String(LineSensor.LineFollowSense()) + " " + String(LineSensor.Detect()) + " LEFT " + String((1 - DEADZONE) * MAXSPEED) + " RIGHT: " + String(rot_speed) + " Analogue input :" + String(LineSensor.line_val_analog));

	}
	else {
		Bot.Move(RIGHT, (1 - DEADZONE) * MAXSPEED, FORWARD);
		Bot.Move(LEFT, (1 - DEADZONE) * MAXSPEED, FORWARD);
	}
}

/**
* @brief if ir sensor detects <25cm then it'll stop and rotate until the front line sensor detects the line again
* BlockCollect should only be used when it is on the collection side and the collection servo is up (to avoid ir sensor detecting ramnp)
*
*/
void RobotDecisions::BlockCollect(Robot Bot, RobotSensors Sensors, RobotPickUp PickUp, RobotIMU BotIMU, RobotLineSensor LineSensor) {
	if (PickUp.angle != 90 && BotIMU.arena_side == END) {
		if (Sensors.A02.GetDistance() <= 25) {
			Bot.StopAll();

			delay(10);
			// Bot.Rotate(CLOCKWISE, LineSensor);
			delay(10);
			PickUp.Sweep(90);
		}
	}
}

void RobotDecisions::Junction(Robot Bot, RobotSensors Sensors, RobotPickUp PickUp, RobotIMU BotIMU, RobotLineSensor LineSensor, RobotMetalDetector MetalDetector) {
	static bool leaving_start = true;

	// only run junction detection when it is not leaving the starting box 
	// will begin once it has crossed to the other side
	if (BotIMU.arena_side == END) {
		leaving_start = false;

	}

	// returning to starting side from having collected a block
	if (leaving_start == false && BotIMU.arena_side == BEGINNING){
		if (LineSensor.JunctionDetect() == true){
			Bot.StopAll();

			delay(10);
			if (MetalDetector.detected == true) {
				Bot.Rotate(ANTICLOCKWISE, LineSensor); // rotates the other direction to the deposit box, to reverse and deposit block
				Bot.MoveAll(100, BACKWARD);
				delay(100);
				Bot.StopAll();

				PickUp.Sweep(180);
				//while (LineSensor.JunctionDetect == false){
					//FollowLine(Bot, LineSensor, false);
				//}
				

			}



		}
	}

}