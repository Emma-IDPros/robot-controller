#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"

Robot Bot;
RobotSensors Sensors;
RobotIMU imu;

void setup() {

  Serial.begin(9600);

  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  imu.Begin();

}

void loop() {
  float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  Serial.print("Ultrasound Distance: ");
  Serial.println(String(ultrasound_distance) + "cm");
  // Bot.StopAll();
  // delay(500);
  // Bot.MoveAll(255, BACKWARD);
  // delay(500);

  // char buffer[8];    // string buffer for use with dtostrf() function

  // imu.ReadAcceleration();
  // Serial.print("ax = ");  Serial.print(dtostrf(imu.ax, 4, 1, buffer));  Serial.print(" m/s^2, ");
  // Serial.print("ay = ");  Serial.print(dtostrf(imu.ay, 4, 1, buffer));  Serial.print(" m/s^2, ");
  // Serial.print("az = ");  Serial.print(dtostrf(imu.az, 4, 1, buffer));  Serial.print(" m/s^2, ");
  // Serial.println(" ");

}