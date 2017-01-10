#include "main.h"

#define PROPORTION 1
#define INTEGRAL 0
#define DERIVATIVE 0

void drivePID(void *ignore) {
	// Target tick count for potentiometer (how high we want it)

	encoderReset(encDrive);

	// Total accumuated error
	float errTotalLeft;
	float errTotalRight;

	float errLastLeft;
	float errLastRight;

	float targetLeft = 1600;
	float targetRight = 1000;

	// Current proportion terms for each side of lift
	float propLeft;
	float propRight;

	float integLeft;
	float integRight;

	float derivLeft;
	float derivRight;

	// Threshold that manages when to activate the INTEGRAL portion
	int integAccumulate = 100;
	float integCap = 50 / INTEGRAL;

	// Motor out puts for each side of lift towers
	float outputLeft;
	float outputRight;

	encoderReset(encRight);
	encoderReset(encLeft);

	while (1) {
		// Initialize the raw potentiometer input
		int currTickRight = encoderGet(encRight);//(3);
		int currTickLeft = encoderGet(encDrive);//analogRead(2) / 10;

		//printf("Pot LEFT: %d", currTickLeft);
		//printf("Pot RIGHT: %d", currTickRight);

		int errLeft = targetLeft - currTickLeft;
		int errRight = targetRight - currTickRight;

		// Manage the INTEGRAL term (only use if close/approaching target)
		if (errLeft < integAccumulate) { errTotalLeft += errLeft; }
		else { errTotalLeft = 0; }
		if (errRight < integAccumulate) { errTotalRight += errRight; }
		else { errTotalLeft = 0; }

		// INTEGRAL cap (by standard 50 / INTEGRAL term
		if (errTotalLeft > integCap) { errTotalLeft = 50 / INTEGRAL; }
		if (errTotalRight > integCap) { errTotalRight = 50 / INTEGRAL; }
		// Compute P, I, and D terms for both right and left side of lift
		propLeft = errLeft * PROPORTION;
		propRight = errRight * PROPORTION;

		integLeft = errTotalLeft * INTEGRAL;
		integRight = errTotalRight * INTEGRAL;

		derivLeft = (errTotalLeft - errLastLeft) * DERIVATIVE;
		derivRight = (errTotalRight - errLastRight) * DERIVATIVE;

		errLastLeft = errLeft;
		errLastRight = errRight;

		// Set motor output as sum of P, I, and D terms
		outputLeft = propLeft; //+ integLeft + derivLeft;
		outputRight = propRight; //+ integRight + derivRight;

		if (outputLeft > 127) { outputLeft = 127; }
		if (outputRight > 127) { outputRight = 127; }

		//printf("Prop LEFT: %d   ", outputLeft);
		//printf("Prop RIGHT: %d   ", outputRight);

		lcdPrint(uart1, 2, "OUTPUT: %d", outputLeft);


			motorSet(10, outputLeft);
			motorSet(6, -outputLeft);
			motorSet(1, -outputLeft);
			motorSet(7, outputLeft);

		// Refresh @25
		delay(25);
	}
}

void autonomous() {

	motorSet(8, -127);
	motorSet(9, -127);
	delay(700);
	motorSet(8, 0);
	motorSet(9, 0);
	motorSet(10, 127);
	motorSet(6, -127);
	motorSet(1, -127);
	motorSet(7, 127);

	delay(1500);

	motorSet(2, 127);
	motorSet(3, -127);
	delay(1250);
	motorSet(2, 0);
	motorSet(3, 0);


	motorSet(10, 127);
	motorSet(6, -127);
	motorSet(1, -127);
	motorSet(7, 127);

	delay(1000);

	motorSet(10, 0);
	motorSet(6, 0);
	motorSet(1, 0);
	motorSet(7, 0);



	delay(500);

	motorSet(10, -127);
	motorSet(6, 127);
	motorSet(1, 127);
	motorSet(7, -127);

	delay(1000);

	motorSet(2, -127);
	motorSet(3, 127);
	delay(500);


	motorSet(10, 0);
	motorSet(6, 0);
	motorSet(1, 0);
	motorSet(7, 0);

	motorSet(2, 0);
	motorSet(3, 0);
	/*motorSet(2, 127);
	motorSet(3, -127);

	delay(500);

    encoderReset(encLeft);
	encoderReset(encDrive); */
}
