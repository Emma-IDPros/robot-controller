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
int inPin = 2;         // the number of the input pin
int outPin = 13;       // the number of the output pin

int state = HIGH;
int reading;
int previous = LOW;
long time = 0;
long debounce = 200;

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
  // MetalDetector.SetPins(MD_pin_pulse, MD_pin_cap, MD_pin_LED1, MD_pin_LED2);
  LineSensor.SetPins(line_pin_sense, line_detect_pin);
  PickUp.SetPins(PU_servo_pin);
  BotIMU.Begin();

  LineSensor.SetThresholdValues(253, 480);

  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);


#ifdef WIFI_DEBUG
  WiFiComm.Connect();
#endif

}

void loop() {
  // float line_sense = LineSensor.LineFollowSense();
  // bool line_detect = LineSensor.Detect();
  reading = digitalRead(inPin);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }
  previous = reading;

  digitalWrite(outPin, state);

  if (state == HIGH) {
    Serial.println("high");
  }
  else {
    Serial.println("low");
  }

  // Serial.println(String(line_detect) + " " + String(line_sense));

  // Decisions.FollowLine(Bot, LineSensor, true);
  //Serial.println(String(analogRead(line_pin_sense)));
  // Decisions.FollowLineWithWiFi(Bot, LineSensor, WiFiComm);

  //float ir_distance = Sensors.A02.GetDistance();
  //float ultrasound_distance = Sensors.Ultrasound.GetDistance();

  // Serial.println("Ultrasound Dist: " + String(ultrasound_distance) + " IR_Sensor: " + String(ir_distance));

#ifdef WIFI_DEBUG
  if (WiFiComm.wl_status == WL_CONNECTED) {

    // WiFiComm.Message(String(ultrasound_distance));

  }
#endif
}