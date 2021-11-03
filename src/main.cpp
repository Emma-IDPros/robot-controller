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
  MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  LineSensor.SetPins(line_pin_sense, line_detect_pin, line_junc_detect_pin);
  PickUp.SetPins(PU_servo_pin);
  BotIMU.Begin();
  ToggleSwitch.SetPins(T_detect_pin, T_led_pin);
  StatusLED.SetPins(amber_led_pin, MD_led_pin_on, MD_led_pin_off);

  LineSensor.SetThresholdValues(253, 480);

#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

enum STAGES { GOING_TO_COLLECTION, STOP_AT_COLLECTION, ROTATE_180, PICKUP_DROP, RUN_METAL_SENSOR, MOVE_TO_START };

STAGES stages = GOING_TO_COLLECTION;
int metal_detector_start_time;
void loop() {

  // Exit loop if toggle switch is toggled off
  if (!ToggleSwitch.GetAndUpdateState()) {
    Bot.StopAll(); BotIMU.arena_side = BEGINNING;
    stages = GOING_TO_COLLECTION; PickUp.inital_angle_set = false;
    return;
  }

  // setting inital conditions
  PickUp.SetInitalAngle(180); // this only runs once

  // Updates --------------------------
  BotIMU.Update();
  // Serial.println(String(Bot.IsMoving()));
  StatusLED.Blink(2, Bot.IsMoving());
  StatusLED.LightUpMetalDetectorLED(MetalDetector.detected);
  // ----------------------------------


  //Decisions.FollowLine(Bot, LineSensor, false);
  switch (stages)
  {
  case GOING_TO_COLLECTION:
    Bot.Move(LEFT, 235, BACKWARD);
    Bot.Move(RIGHT, 255, BACKWARD);
    break;
  case STOP_AT_COLLECTION:
    Bot.StopAll();
    delay(1000);
    break;
  case ROTATE_180:
    Bot.Rotate(180, ANTICLOCKWISE);
    delay(100);
    break;
  case PICKUP_DROP:
    PickUp.Sweep(90);
    delay(100);
  case RUN_METAL_SENSOR:
    MetalDetector.Detect();
    metal_detector_start_time = millis();
  case MOVE_TO_START:
    Bot.Move(LEFT, 235, BACKWARD);
    Bot.Move(RIGHT, 255, BACKWARD);
    delay(100);
    break;

  default:
    break;
  }


  if (BotIMU.arena_side == END) {
    int distance = Sensors.A02.GetDistance();
    if (distance <= 21 && distance > 0) {
      if (stages == GOING_TO_COLLECTION) { stages = STOP_AT_COLLECTION; }
    }
    else {
      switch (stages)
      {
      case STOP_AT_COLLECTION:
        stages = ROTATE_180;
        break;
      case ROTATE_180:
        stages = PICKUP_DROP;
        break;
      case PICKUP_DROP:
        stages = RUN_METAL_SENSOR;
        break;
      case  RUN_METAL_SENSOR:
        if (millis() - metal_detector_start_time > 5000) {
          stages = MOVE_TO_START;
        }
        break;

      default:
        break;
      }
    }
  }
  else {

    Bot.Move(LEFT, 235, BACKWARD);
    Bot.Move(RIGHT, 255, BACKWARD);
  }
  Serial.println(String(Sensors.A02.GetDistance()) + " " + String(BotIMU.arena_side) + " " + String(stages));


#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {

    // WiFiComm.Message(String(ultrasound_distance));

  }
#endif
}