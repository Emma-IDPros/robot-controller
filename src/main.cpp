#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"
#include "MetalDetector.h"
#include "LineSensor.h"
#include "PickUp.h"
#include "RobotDecisions.h"
// #define WIFI_DEBUG


#ifdef WIFI_DEBUG
#include "WiFiComms.h"
WiFiComms WiFiComm;
#endif

Robot Bot;
RobotSensors Sensors;
RobotIMU BotIMU;
RobotMetalDetector MetalDetector;
RobotLineSensor LineSensor;
RobotPickUp PickUp;
RobotDecisions Decisions;

void setup() {

  Serial.begin(9600);
  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  LineSensor.SetPins(line_pin_sense, line_detect_pin);
  PickUp.SetPins(PU_servo_pin);
  BotIMU.Begin();


#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {
  // delay(300);
  BotIMU.ReadAngles();
  BotIMU.UpdateArenaSide();
  Serial.println(BotIMU.arena_side);
  // if (i == 1) {
  // if (!PickUp.inital_angle_set) { PickUp.SetInitalAngle(20); }
  // else {
  //   PickUp.Sweep(180);
  // }
  // Serial.println("Setting init");
  // }
  // delay(800);
  // float ultrasound_distance = Sensors.Ultrasound.GetDistance();
  // // Serial.println("Ultrasound Distance: " + String(ultrasound_distance));

  float line_sense = LineSensor.LineFollowSense();
  bool line_detect = LineSensor.Detect();

  Serial.println(String(line_detect) + " " + String(line_sense));

  // // float ir_distance = Sensors.A21.GetDistance();
  // // Serial.println(String(ir_distance));

  // if (ultrasound_distance < 25) {
  //   Bot.StopAll();
  //   // ultrasound should only detect a wall so, move the robot away
  //   Bot.MoveAll(255, BACKWARD);
  //   delay(1000);
  //   Bot.Rotate(90, CLOCKWISE);
  // }
  // else {
  // Bot.MoveAll(255, FORWARD);
  // }

  // line follower (proportional control)
  // need to get the front line sensor to work in tandem
  /*
  if (front line sensor = on line && -0.5 < LineSensor.LineFollowSense < 0.5){
    robot is on junction
    if (carrying box = true){
      if (box = metal){
        Bot.Rotate into red box
      }
      else {
        Bot.Rotate into blue box
      }
    }
    else {
      Bot.MoveAll();
    }
  }
  else if (front line sensor = off line && -0.5 < LineSensor.LineFollowSense < 0.5) {
    Bot.StopAll();
    run IR sensor and sweep
  }

  */



  // Decisions.FollowLine(Bot, LineSensor);
  // Decisions.FollowLineWithWiFi(Bot, LineSensor, WiFiComm);

  // BotIMU.ReadAcceleration();
  // Serial.println(String(BotIMU.DetectRamp()));

  // BotIMU.ReadAngles();
  // BotIMU.Integrate();
  // Serial.println("ax = " + String(BotIMU.ax) + " m/s^2, " + "ay = " + String(BotIMU.ay) + " m/s^2, " + "az = " + String(BotIMU.az) + " m/s^2, ");
  // Serial.println("ax = " + String(BotIMU.ax) + " ms^-2, " + "vx = " + String(BotIMU.vx) + " ms^-1, " + "x = " + String(BotIMU.x) + " m, ");
  // Serial.println("ax = " + String(BotIMU.yaw) + " ms^-2, " + "ay = " + String(BotIMU.roll) + " ms^-2, " + "az = " + String(BotIMU.pitch) + " ms^-2, ");

  // BotIMU.VerletInt();
  // Serial.println("az = " + String(BotIMU.az) + " ms^-2, " + "vz = " + String(BotIMU.velocity) + " ms^-1, " + "z = " + String(BotIMU.position) + " m, ");




#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {
    // WiFiComm.Message(String(BotI?MU.DetectRamp()));

    // WiFiComm.Message(String(ultrasound_distance));
    // WiFiComm.Message("ax = " + String(BotIMU.ax) + " ms^-2, " + "vx = " + String(BotIMU.vx) + " ms^-1, " + "x = " + String(BotIMU.x) + " m, ");
    // WiFiComm.Message("ax = " + String(BotIMU.ax) + " ms^-2, " + "ay = " + String(BotIMU.ay) + " ms^-2, " + "az = " + String(BotIMU.az) + " ms^-2, ");
    // WiFiComm.SendCoords(BotIMU.ax, BotIMU.ay);
    // WiFiComm.Message("ax = " + String(BotIMU.yaw) + " ms^-2, " + "ay = " + String(BotIMU.roll) + " ms^-2, " + "az = " + String(BotIMU.pitch) + " ms^-2, ");

  }
  else {
    Serial.println("WiFi failed to connected, no WiFi logging");
  }
#endif

  // delay(10);
}