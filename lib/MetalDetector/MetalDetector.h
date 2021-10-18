#pragma once
#include <Arduino.h>

class RobotMetalDetector {
public:
	int count, freq; //set up frequency and count variables
	bool detected; //create bool for if metal detected

	void SetPins(byte pin_pulse, byte pin_cap = 1, byte pin_LED1 = 12, byte pin_LED2 = 11);

private:
	const int nmeas = 256;  //measurements to take
	long int sumsum = 0; //running sum of 64 sums 
	long int skip = 0;   //number of skipped sums
	long int diff = 0;        //difference between sum and avgsum
	long int flash_period = 0;//period (in ms) 
	long unsigned int prev_flash = 0; //time stamp of previous flash
	byte npulse = 3;
	byte pin_pulse = 0;
	byte pin_cap = 1;
	byte pin_LED1 = 12;
	byte pin_LED2 = 11;
};