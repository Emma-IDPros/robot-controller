#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"

#ifdef WIFI_DEBUG
#include "WiFiComms.h"
WiFiComms WiFiComm;
#endif

Robot Bot;
RobotSensors Sensors;
RobotIMU BotIMU;

void setup() {

  Serial.begin(9600);
  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  BotIMU.Begin();

#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {

  float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  Serial.println("Ultrasound Distance: " + String(ultrasound_distance));

  if (ultrasound_distance < 20) {
    Bot.StopAll();
  }
  else {
    Bot.MoveAll(255, BACKWARD);
  }

  BotIMU.ReadAcceleration();
  Serial.println("ax = " + String(BotIMU.ax) + " m/s^2, " + "ay = " + String(BotIMU.ay) + " m/s^2, " + "az = " + String(BotIMU.az) + " m/s^2, ");

#ifdef WIFI_DEBUG
  WiFiComm.Message("Ultrasound Distance: " + String(ultrasound_distance));
  WiFiComm.Message("ax = " + String(BotIMU.ax) + " m/s^2, " + "ay = " + String(BotIMU.ay) + " m/s^2, " + "az = " + String(BotIMU.az) + " m/s^2, ");
  WiFiComm.SendCoords(BotIMU.ax, BotIMU.ay);
#endif

  delay(500);
}