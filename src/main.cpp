#include <Arduino.h>
#include "Robot.h"
#include "AllSensors.h"
#include "configs.h"

Robot robot;
AllSensors sensors;

void setup() {

  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!robot.AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  sensors.setPins(US_pinTrig, US_pinEcho, IR_A21pin, IR_A02pin);

}

void loop() {
  float ultrasound_distance = sensors.Ultrasound.getDistance();

  if (ultrasound_distance < 25) {
    robot.release_all();
  }
  else {
    robot.move_all(255, BACKWARD);
  }
  delay(500);

  Serial.print("IR Distance: ");
  Serial.println(String(ultrasound_distance) + "cm");

  Serial.print("Ultrasound Distance: ");
  Serial.println(String(ultrasound_distance) + "cm");

}