#include <Arduino.h>
#include "Robot.h"
#include "RobotSensors.h"
#include "configs.h"
#include "IMU.h"
#include "MetalDetector.h"
#include "LineSensor.h"
#include "PickUp.h"
#include "RobotDecisions.h"
#include "ToggleSwitch.h"
#include "StatusLED.h"
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
RobotToggleSwitch ToggleSwitch;
RobotStatusLED StatusLED;

void setup() {

  Serial.begin(9600);
  Bot.MotorShieldTest(); // Test to see if board can be detected
  Sensors.SetPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);
  // MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  LineSensor.SetPins(line_pin_sense, line_detect_pin, line_junc_detect_pin);
  PickUp.SetPins(PU_servo_pin);
  BotIMU.Begin();
  ToggleSwitch.SetPins(T_detect_pin, T_led_pin);
  StatusLED.SetPins(amber_led_pin);

  LineSensor.SetThresholdValues(253, 480);

#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {

  // Exit loop if toggle switch is toggled off
  if (!ToggleSwitch.GetAndUpdateState()) { Bot.StopAll(); return; }

  // setting inital conditions
  PickUp.SetInitalAngle(180); // this only runs once

  // Updates --------------------------
  BotIMU.Update();
  StatusLED.Blink(2, Bot.IsMoving());
  // ----------------------------------


  Decisions.FollowLine(Bot, LineSensor, false);


#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {

    // WiFiComm.Message(String(ultrasound_distance));

  }
#endif
  }