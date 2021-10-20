#include <MetalDetector.h>

/**
 * @brief Sets the pins
 *
 * @param pin_pulse DIGITAL
 * @param pin_cap ANALOGUE
 * @param pin_LED1 DIGITAL
 * @param pin_LED2 DIGITAL
 */
void RobotMetalDetector::SetPins(byte pin_pulse, byte pin_cap = 1, byte pin_LED1 = 12, byte pin_LED2 = 11) {
	pin_pulse = pin_pulse;
	pin_cap = pin_cap;
	pin_LED1 = pin_LED1;
	pin_LED2 = pin_LED2;

	pinMode(pin_pulse, OUTPUT);
	digitalWrite(pin_pulse, LOW);
	pinMode(pin_cap, INPUT);
	pinMode(pin_LED1, OUTPUT);
	digitalWrite(pin_LED1, LOW);
	pinMode(pin_LED2, OUTPUT);
	digitalWrite(pin_LED2, LOW);
}

/**
 * @brief Runs the metal detector
 * and stores the detected state in the classes'
 * attribute called detected
 *
 */
void RobotMetalDetector::Detect() {
	int minval = 1023;
	int maxval = 0;

	//perform measurement
	long unsigned int sum = 0;
	for (int imeas = 0; imeas < nmeas + 2; imeas++) {
		//reset the capacitor
		pinMode(pin_cap, OUTPUT);
		digitalWrite(pin_cap, LOW);
		delayMicroseconds(20);
		pinMode(pin_cap, INPUT);
		//apply pulses
		for (int ipulse = 0; ipulse < npulse; ipulse++) {
			digitalWrite(pin_pulse, HIGH); //takes 3.5 microseconds
			delayMicroseconds(3);
			digitalWrite(pin_pulse, LOW);  //takes 3.5 microseconds
			delayMicroseconds(3);
		}
		//read the charge on the capacitor
		int val = analogRead(pin_cap); //takes 13x8=104 microseconds
		minval = min(val, minval);
		maxval = max(val, maxval);
		sum += val;

		//determine if LEDs should be on or off
		long unsigned int timestamp = millis();
		byte ledstat = 0;
		if (timestamp < prev_flash + 10) {
			if (diff > 0)
			{
				ledstat = 1;
				count += 1;
			}
			if (diff < 0)ledstat = 2;
		}
		if (timestamp > prev_flash + flash_period) {
			if (diff > 0)ledstat = 1;
			if (diff < 0)ledstat = 2;
			prev_flash = timestamp;
		}
		if (flash_period > 1000)ledstat = 0;
		//switch the LEDs to this setting

		if (ledstat == 0) {
			digitalWrite(pin_LED1, LOW);
			digitalWrite(pin_LED2, LOW);
		}
		if (ledstat == 1) {
			digitalWrite(pin_LED1, HIGH);
			digitalWrite(pin_LED2, LOW);
		}
		if (ledstat == 2) {
			digitalWrite(pin_LED1, LOW);
			digitalWrite(pin_LED2, HIGH);
		}

	}
	//subtract minimum and maximum value to remove spikes
	sum -= minval; sum -= maxval;

	//process
	if (sumsum == 0) sumsum = sum << 6; //set sumsum to expected value
	long int avgsum = (sumsum + 32) >> 6;
	diff = sum - avgsum;
	if (abs(diff) < avgsum >> 10) {      //adjust for small changes
		sumsum = sumsum + sum - avgsum;
		skip = 0;
	}
	else {
		skip++;
	}
	if (skip > 64) {     // break off in case of prolonged skipping
		sumsum = sum << 6;
		skip = 0;
	}
	// one permille change = 2 ticks/s
	if (diff == 0) flash_period = 1000000;
	else flash_period = avgsum / (2 * abs(diff));
	if (millis() - lastMillis >= 500)
	{
		lastMillis = millis();
		freq = count;
		count = 0;
		detected = freq > 50;
	}

}

/**
 * @brief Debug func to print
 * detected, count, freq
 *
 */
void RobotMetalDetector::Debug() {
	Serial.print(detected);
	Serial.print(" ");
	Serial.print(count);
	Serial.print(" ");
	Serial.print(freq);
	Serial.println();
}