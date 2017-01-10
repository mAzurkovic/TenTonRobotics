/*
 * compDefaults.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Mattias
 */

#ifndef INCLUDE_COMPDEFAULTS_H_
#define INCLUDE_COMPDEFAULTS_H_

void setLift(int speed) {
	// Right side
	motorSet(6, (speed));
	motorSet(7, (speed));
	// Left side
	motorSet(5, -(speed));
	motorSet(8, -(speed));
}

void sensorReset() {
	// Wipe encoders
	encoderReset(encLift);
	encoderReset(encDriveR);
	encoderReset(encDriveL);
	encoderReset(encBackR);
	encoderReset(encBackL);

	// Wipe gyroscope
	gyroReset(gyro);
}

void lcdLoading() {
	lcdSetText(uart1, 1, "1010Z");
}

#endif /* INCLUDE_COMPDEFAULTS_H_ */
