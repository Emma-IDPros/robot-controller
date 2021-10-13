#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"

Robot Bot;
RobotSensors Sensors;

void setup() {

  Serial.begin(9600);

  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
}

void loop() {
  // float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  // Serial.print("Ultrasound Distance: ");
  // Serial.println(String(ultrasound_distance) + "cm");


  // if (ultrasound_distance < 25) {
  // }
  // else {
  // }
  Bot.StopAll();
  delay(500);
  Bot.MoveAll(255, BACKWARD);
  delay(500);


}