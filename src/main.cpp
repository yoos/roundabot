/*! \file omnikiwi.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Main loop.
 *
 *  Details.
 */

#include <Wire.h>
#include <TimerOne.cpp>

#define BAUDRATE 38400
#define MASTER_DT 10000
#define PIN_MOTOR 9
#define PIN_POT 17

int main(void) {
	init();   // For Arduino.

	// Begin Arduino services.
	Wire.begin();

	Serial.begin(BAUDRATE);

	Timer1.initialize(2500);   // 400 Hz PWM on pins 9 and 10 (?).

	pinMode(PIN_MOTOR, OUTPUT);
	pinMode(PIN_POT, INPUT);

	uint64_t nextRuntime = micros();
	uint16_t dc = 0;   // Duty cycle for motor.
	uint16_t loopCount = 0;

	while (1) {
		if (micros() >= nextRuntime) {
			nextRuntime += MASTER_DT;   // Update next loop start time.

			if (loopCount % 10 == 0) {
				dc = analogRead(PIN_POT);
			}

			Timer1.pwm(PIN_MOTOR, dc);

			loopCount++;
			loopCount = loopCount % 1000;
		} // endif
	} // endwhile

	return 0;
}

