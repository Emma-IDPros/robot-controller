#include <RobotDecisions.h>
#include <LineSensor.h>

void RobotDecisions::FollowLine(Robot Bot, RobotLineSensor LineSensor) {
	if (LineSensor.Detect()){
		Bot.MoveAll(255, FORWARD);
		Serial.println("STRAIGHT");
	}
	else if (LineSensor.LineFollowSense() < -0.5 && !LineSensor.Detect()) {
		rot_speed = LineSensor.LineFollowSense() * 130 + 200;
		Bot.Move(LEFT, 200, FORWARD);
    	Bot.Move(RIGHT, rot_speed, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense())+ " "+ String(LineSensor.Detect())+" LEFT 200 RIGHT:" + String(rot_speed));
		// Bot.Move(RIGHT, 100, FORWARD);
  	}
  	else if (LineSensor.LineFollowSense() > 0.5 && !LineSensor.Detect()) {
		rot_speed = -LineSensor.LineFollowSense() * 130 + 200;
    	Bot.Move(RIGHT, 200, FORWARD);
    	Bot.Move(LEFT, rot_speed, FORWARD);
		Serial.println(String(LineSensor.LineFollowSense())+ " "+ String(LineSensor.Detect())+" RIGHT 200 LEFT:" + String(rot_speed));

		// Serial.println("LEFT " + String(rot_speed));
		// Bot.Move(LEFT, 100, FORWARD);
  	}

// 	    if (front line sensor = on line && -0.5 < LineSensor.LineFollowSense < 0.5){
//     robot is on junction
//     if (carrying box = true){
//       if (box = metal){
//         Bot.Rotate into red box
//       }
//       else {
//         Bot.Rotate into blue box
//       }
//     }
//     else {
//       Bot.MoveAll();
//     }
//   }
//   else if (front line sensor = off line && -0.5 < LineSensor.LineFollowSense < 0.5) {
//     Bot.StopAll();
//     run IR sensor and sweep
//   }
}