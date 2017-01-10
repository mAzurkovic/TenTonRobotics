#include "main.h"
#include <stdlib.h>

#define THRESHOLD 20
#define PROPORTION 0.25
#define INTEGRAL 0.0
#define DERIVATIVE 0.0

void clawPID(void *ignore) {
	// Target tick count for potentiometer (how high we want it)

	// Total accumuated error
	float errTotal;
	float errLast;

	float target = 2700;

	// Current proportion terms for each side of lift
	float prop;
	float integ;
	float deriv;

	// Threshold that manages when to activate the INTEGRAL portion
	int integAccumulate = 100;
	float integCap = 50 / INTEGRAL;

	// Motor out puts for each side of lift towers
	float output;

	analogCalibrate(1);
	analogCalibrate(7); // Init for PID Setting pot

	while (1) {
		// Initialize the raw potentiometer input
		int currTick = analogRead(1);
		// target = analogRead(7) / -100;

		int err = target - currTick;

		// Manage the INTEGRAL term (only use if close/approaching target)
		if (err < integAccumulate) { errTotal += err; }
		else { errTotal = 0; }

		// INTEGRAL cap (by standard 50 / INTEGRAL term
		if (errTotal > integCap) { errTotal = 50 / INTEGRAL; }

		// Compute P, I, and D terms for both right and left side of lift
		prop = err * PROPORTION;
		integ = errTotal * INTEGRAL;
		deriv = (errTotal - errLast) * DERIVATIVE;
		errLast = err;

		// Set motor output as sum of P, I, and D terms
		output = prop;//+ integ + deriv;

		if (output > 127) { output = 127; }

		if (joystickGetDigital(2, 5, JOY_UP)) {
			motorSet(3, output);
			motorSet(9, -output);
		} else if (joystickGetDigital(2, 5, JOY_DOWN)) {
			motorSet(3, -120);
			motorSet(9, 120);
		}else {
			motorSet(3, 0);
			motorSet(9, 0);
		}
		// Refresh @25
		delay(25);
	}
} */

void liftCheck(int armTick) {

	if (joystickGetDigital(1, 7, JOY_UP)) {
		if (armTick < 300) {
			motorSet(6, 127);
			motorSet(7, 127);
			// Left
			motorSet(5, -127);
			motorSet(8, -127);
		} else {
			motorSet(6, 0);
			motorSet(7, 0);
			// Left
			motorSet(5, 0);
			motorSet(8, 0);
		}
	} else {
		motorSet(6, 0);
		motorSet(7, 0);
		// Left
		motorSet(5, 0);
		motorSet(8, 0);
	}
}

void claw() {
	if (joystickGetDigital(2, 5, JOY_UP)) {
		motorSet(3, 120);
		motorSet(9, -120);
	} else if (joystickGetDigital(2, 5, JOY_DOWN)) {
		motorSet(3, -120);
		motorSet(9, 120);
	} else {
		motorSet(3, 0);
		motorSet(9, 0);
	}
}

void lift(int encArm) {

	// lcdPrint(uart1, 2, "@Arm: %d", encArm);

			if (joystickGetDigital(1, 5, JOY_UP) && encArm < 630) {
				motorSet(6, 127);
				motorSet(7, 127);
				// Left
				motorSet(5, -127);
				motorSet(8, -127);
			} else if (joystickGetDigital(1, 5, JOY_DOWN)) {
				motorSet(6, -120);
				motorSet(7, -120);
				// Left
				motorSet(5, 120);
				motorSet(8, 120);
			} else {
				motorSet(6, 0);
				motorSet(7, 0);
				// Left
				motorSet(5, 0);
				motorSet(8, 0);
			}

}

void operatorControl() {

  // taskCreate(liftPID, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	// taskCreate(clawPID, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	/* if (isAutonomous) {
		taskCreate(clawPID, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	} */

	encoderReset(encLift);

	gyroReset(gyro);

	while (1) {

		lcdClear(uart1);
		lcdSetText(uart1, 1, "1010Z");

		int encArmTick = encoderGet(encLift);
		int gyroTick = gyroGet(gyro);

		lcdPrint(uart1, 2, "@Gyro %d", gyroTick);

		lift(encArmTick);
		// liftCheck(encArmTick);

		int ch1;
		int ch3;
		int ch4;

		// Master Joystick Channels...
		int joy1 = joystickGetAnalog(1, 1);
		int joy2 = joystickGetAnalog(1, 2);
		int joy3 = joystickGetAnalog(1, 3);
		int joy4 = joystickGetAnalog(1, 4);

			// Calculate THRESHOLD: This will prevent unwanted movements
		if (abs(joystickGetAnalog(1, 4)) > THRESHOLD) {
			ch4 = joystickGetAnalog(1, 4);
		} else {
			ch4 = 0;
		}

		if (abs(joystickGetAnalog(1, 3)) > THRESHOLD) {
			ch3 = joystickGetAnalog(1, 3);
		} else {
			ch3 = 0;
		}

		if (abs(joystickGetAnalog(1, 1)) > THRESHOLD) {
			ch1 = joystickGetAnalog(1, 1);
		} else {
			ch1 = 0;
		}

		claw();

		motorSet(2, -(ch3 - ch1 - ch4)); // Front Right Drive
		motorSet(1, (ch3 - ch1 + ch4)); // Back Right
		motorSet(4, (ch3 + ch1 + ch4)); // Front Left
		motorSet(10, -(ch3 + ch1 - ch4)); // Back Left

		delay(20);
	}
}
