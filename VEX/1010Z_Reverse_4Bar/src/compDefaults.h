/*
 * compDefaults.h
 *
 *  Created on: Sep 21, 2016
 *      Author: Mattias
 *
 *      Holds default competition methods for simple tasks
 */

#ifndef SRC_COMPDEFAULTS_H_
#define SRC_COMPDEFAULTS_H_

void _motorWipe() {
	for (int i = 1; i < 13; i++) {
		motorSet(i, 0);
	}
}

void _motorClear(int port) {
	motorSet(port, 0);
}

void _driveTank(int portRightA, int portRightB, int portLeftA, int portLeftB) {
	int joyRight = joystickGetAnalog(1, 2);
	int joyLeft = joystickGetAnalog(1, 3);

	// Right and left drives
	motorSet(portRightA, joyRight);
	motorSet(portRightB, -joyRight);
	motorSet(portLeftA, -joyLeft);
	motorSet(portLeftB, joyLeft);
}

void _lcdLoad() {
	lcdSetText(uart1, 1, "BOOT");
	lcdSetText(uart1, 2, "1010Z DO4H");
	delay(500);
}

#endif /* SRC_COMPDEFAULTS_H_ */
