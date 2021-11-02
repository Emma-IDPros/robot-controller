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

int i = 0;
void loop() {

  // Exit loop if toggle switch is toggled off
  // if (!ToggleSwitch.GetAndUpdateState()) { Bot.StopAll(); return; }

  // setting inital conditions
  PickUp.SetInitalAngle(180); // this only runs once

  // Updates --------------------------
  BotIMU.Update();
  // Serial.println(String(Bot.IsMoving()));
  StatusLED.Blink(4, Bot.IsMoving());
  // ----------------------------------


  //Decisions.FollowLine(Bot, LineSensor, false);


  if (BotIMU.arena_side == 1){
      if (Sensors.A02.GetDistance() <= 21) {

        Bot.StopAll();
        delay(10);
        //Bot.Rotate(180, ANTICLOCKWISE);
      }
      else {
        Bot.Move(LEFT, 235, BACKWARD);
        Bot.Move(RIGHT, 255, BACKWARD);
      }
  }
  else {

    Bot.Move(LEFT, 235, BACKWARD);
    Bot.Move(RIGHT, 255, BACKWARD);
  }
  Serial.println(String(Sensors.A02.GetDistance()) + " " + String(BotIMU.arena_side));


#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {

    // WiFiComm.Message(String(ultrasound_distance));

  }
#endif
}