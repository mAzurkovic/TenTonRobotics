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
	motorSet(CLAW_LEFT, -(power));
}

// Functions to drive, pivot, lift, etc...

// Main function to drive in direction specified...

void drive(int distance) {
	imeReset(IME_L);
	imeReset(IME_R);

	int imeValR;
	int imeValL;

	while ( (abs(imeGet(IME_L, &imeValL)) + abs(imeGet(IME_R, &imeValR)) / 2) < distance ) {

		printf("hdhd %d", abs(imeGet(IME_L, &imeValL)));

		motorSet(FRONT_RIGHT, 127);
		motorSet(BACK_RIGHT, -(127));
		motorSet(FRONT_LEFT, 127);
		motorSet(BACK_LEFT, 127);

		delay(50);
	}
	clearDrive();
}

#endif /* INCLUDE_AUTODEFAULTS_H_ */
