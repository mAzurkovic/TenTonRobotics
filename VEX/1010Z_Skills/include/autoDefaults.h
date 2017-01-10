/*
 * autoDefaults.h
 *
 *  Created on: Jan 9, 2017
 *      Author: Mattias
 */

#ifndef INCLUDE_AUTODEFAULTS_H_
#define INCLUDE_AUTODEFAULTS_H_

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <main.h>

void sensorReset() {
	encoderReset(encLift);
	analogCalibrate(1);
}

void clearDrive() {
	motorSet(FRONT_RIGHT, 0);
	motorSet(BACK_RIGHT, 0);
	motorSet(FRONT_LEFT, 0);
	motorSet(BACK_LEFT, 0);
}

void motorsDrive(power) {
	motorSet(FRONT_RIGHT, power);
	motorSet(BACK_RIGHT, power);
	motorSet(FRONT_LEFT, power);
	motorSet(BACK_LEFT, power);
}

void motorsPivot(power) {
	motorSet(FRONT_RIGHT, -(power));
	motorSet(BACK_RIGHT, -(power));
	motorSet(FRONT_LEFT, power);
	motorSet(BACK_LEFT, power);
}

void clearLift() {
	motorSet(R_BOT_LIFT, 0);
	motorSet(R_LIFT, 0);
	motorSet(L_BOT_LIFT, 0);
	motorSet(L_LIFT, 0);
}

void motorsLift(power) {
	motorSet(R_BOT_LIFT, power);
	motorSet(R_LIFT, power);
	motorSet(L_BOT_LIFT, -(power));
	motorSet(L_LIFT, -(power));
}

void motorsClaw(power) {
	motorSet(CLAW_RIGHT, power);
	motorSet(CLAW_LEFT, -(power);
}

// Functions to drive, pivot, lift, etc...

// Main function to drive in direction specified...

void go(int way, int distance, int velocity, int minPower) {
	imeReset(IME_BL);
	imeReset(IME_BR);

	float outputFL, outputFR, outputBL, outputBR;

	float gain = 0.15;

	float tickChangeBL;
	float tickChangeBR;

	float tickLastBL = 0;
	float tickLastBR = 0;

	float errBL;
	float errBR;

	int imeValBL;
	int imeValBR;

	while ( (abs(imeGet(IME_BL, &imeValBL)) + abs(imeGet(IME_BR, &imeValBR)) / 2) < distance ) {

		tickChangeBL = abs(imeGet(IME_BL, &imeValBL)*(360/261.333)) - tickLastBL;
		tickChangeBR = abs(imeGet(IME_BR, &imeValBL)*(360/261.333)) - tickLastBR;

		tickLastBL = abs(imeGet(IME_BL, &imeValBL)*(360/261.333));
		tickLastBR = abs(imeGet(IME_BR, &imeValBR)*(360/261.333));

		errBL = velocity - tickChangeBL;
		errBR = velocity - tickChangeBR;

		if (way == 1) {
			outputBL = minPower + (errBL * gain);
			outputBR = minPower + (errBR * gain);
		}
		if (way == 2) { // Backwards
			outputBL = -(minPower + (errBL * gain));
			outputBR = -(minPower + (errBR * gain));
		}

		motorSet(FRONT_RIGHT, outputFR);
		motorSet(BACK_RIGHT, outputBR);
		motorSet(FRONT_LEFT, outputFL);
		motorSet(BACK_LEFT, outputBL);

		delay(50);
	}
	clearDrive();
}

#endif /* INCLUDE_AUTODEFAULTS_H_ */
