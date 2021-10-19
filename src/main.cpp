#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"
#include "MetalDetector.h"

#ifdef WIFI_DEBUG
#include "WiFiComms.h"
WiFiComms WiFiComm;
#endif

Robot Bot;
RobotSensors Sensors;
RobotIMU BotIMU;
RobotMetalDetector MetalDetector;

void setup() {

  Serial.begin(9600);
  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  BotIMU.Begin();

#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {
  delay(800);
  // float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  // Serial.println("Ultrasound Distance: " + String(ultrasound_distance));

  // float ir_distance = Sensors.A21.GetDistance();
  // Serial.println(String(ir_distance));

  // if (ultrasound_distance < 20) {
  //   Bot.StopAll();
  // }
  // else {
  //   Bot.MoveAll(255, BACKWARD);
  // }

  BotIMU.ReadAcceleration();
  // BotIMU.Integrate();
  Serial.println("ax = " + String(BotIMU.ax) + " m/s^2, " + "ay = " + String(BotIMU.ay) + " m/s^2, " + "az = " + String(BotIMU.az) + " m/s^2, ");
  // Serial.println("ax = " + String(BotIMU.ax) + " ms^-2, " + "vx = " + String(BotIMU.vx) + " ms^-1, " + "x = " + String(BotIMU.x) + " m, ");

  // BotIMU.VerletInt();
  // Serial.println("az = " + String(BotIMU.az) + " ms^-2, " + "vz = " + String(BotIMU.velocity) + " ms^-1, " + "z = " + String(BotIMU.position) + " m, ");




#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {
    // WiFiComm.Message("Ultrasound Distance: " + String(ultrasound_distance));
    // WiFiComm.Message("ax = " + String(BotIMU.ax) + " ms^-2, " + "vx = " + String(BotIMU.vx) + " ms^-1, " + "x = " + String(BotIMU.x) + " m, ");
    WiFiComm.Message("ax = " + String(BotIMU.ax) + " ms^-2, " + "ay = " + String(BotIMU.ay) + " ms^-2, " + "az = " + String(BotIMU.az) + " ms^-2, ");
    // WiFiComm.SendCoords(BotIMU.ax, BotIMU.ay);
  }
  else {
    Serial.println("WiFi failed to connected, no WiFi logging");
  }
#endif

  // delay(10);
}