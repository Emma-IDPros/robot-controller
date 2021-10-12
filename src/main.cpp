#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"

Robot robot;
RobotSensors Sensors;

void setup() {

  Serial.begin(9600);

  robot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.setPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
}

void loop() {
  float ultrasound_distance = Sensors.Ultrasound.GetDistance();

  if (ultrasound_distance < 25) {
    robot.StopAll();
  }
  else {
    robot.MoveAll(255, BACKWARD);
  }
  delay(500);

  Serial.print("Ultrasound Distance: ");
  Serial.println(String(ultrasound_distance) + "cm");

}