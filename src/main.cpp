#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"
#include "Logger.h"



Robot Bot;
RobotSensors Sensors;
RobotIMU imu;
Logger Log;

void setup() {

  Serial.begin(9600);

  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  imu.Begin();
  Log.Connect();


}

void loop() {

  float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  Log.PrintLn("Ultrasound Distance: " + String(ultrasound_distance));

  if (ultrasound_distance < 20) {
    Bot.StopAll();
  }
  else {
    Bot.MoveAll(255, BACKWARD);
  }

  imu.ReadAcceleration();
  Serial.print("ax = ");  Serial.print(String(imu.ax));  Serial.print(" m/s^2, ");
  Serial.print("ay = ");  Serial.print(String(imu.ay));  Serial.print(" m/s^2, ");
  Serial.print("az = ");  Serial.print(String(imu.az));  Serial.print(" m/s^2, ");
  Serial.println(" ");



  delay(500);
}