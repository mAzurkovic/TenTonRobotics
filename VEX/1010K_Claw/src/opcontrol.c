/**
 * File for operator control code.
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 ********************************************************************************/

#include "main.h"

#define PROPORTION 0.095
#define INTEGRAL 0.01
#define DERIVATIVE 0.2

void clawPID(void *ignore) {
	// Target tick count for potentiometer (how high we want it)

	// Total accumuated error
	float errTotal;
	float errLast;

	float target = 2262;

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

	while (1) {
		// Initialize the raw potentiometer input
		int currTick = analogRead(1);
		printf("Pot RIGHT: %d", currTick);

		int err = target - currTick;

		// Manage the INTEGRAL term (only use if close/approaching target)
		/*if (errLeft < integAccumulate) { errTotalLeft += errLeft; }
		else { errTotalLeft = 0; }
		if (errRight < integAccumulate) { errTotalRight += errRight; }
		else { errTotalLeft = 0; } */

		// INTEGRAL cap (by standard 50 / INTEGRAL term
		//if (errTotalLeft > integCap) { errTotalLeft = 50 / INTEGRAL; }
		// if (errTotalRight > integCap) { errTotalRight = 50 / INTEGRAL; }
		// Compute P, I, and D terms for both right and left side of lift
		prop = err * PROPORTION;

		integ = errTotal * INTEGRAL;

		deriv = (errTotal - errLast) * DERIVATIVE;

		errLast = err;

		// Set motor output as sum of P, I, and D terms
		output = prop;

		if (output > 127) { output = 127; }

		//printf("Prop LEFT: %d   ", output);

		if (joystickGetDigital(1, 6, JOY_UP)) {
			motorSet(5, output);
			motorSet(6, output);
		} else if (joystickGetDigital(1, 6, JOY_DOWN)) {
			motorSet(5, -120);
			motorSet(6, -120);
		}else {
			motorSet(5, 0);
			motorSet(6, 0);
		}
		// Refresh @25
		delay(25);
	}
}


// CLAW PORTS: 5, 6;

void operatorControl() {
    taskCreate(clawPID, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	while (true)
	{
		printf("FFF");

		delay(25);
	}
}
