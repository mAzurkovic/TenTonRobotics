/*
 * autoDefaults.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Mattias
 */

#ifndef INCLUDE_AUTODEFAULTS_H_
#define INCLUDE_AUTODEFAULTS_H_

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <main.h>

#define THRESHOLD 20;

//***************************
//		Motor Functions
//***************************

void clearDrive() {
	motorSet(2, 0); // Front Right Drive
	motorSet(1, 0); // Back Right
	motorSet(4, 0); // Front Left
	motorSet(10, 0); // Back Left
}

void motorsForward(float power) {
	motorSet(2, -(power));
	motorSet(1, (power));
	motorSet(4, (power));
	motorSet(10, -(power));
}

void motorsBack(float power) {
	motorSet(2, power * 0.8);
	motorSet(1, -(power * 0.8));
	motorSet(4, -(power));
	motorSet(10, power);
}

void motorsLeft() {
	motorSet(2, -127);
	motorSet(1, -127);
	motorSet(4, -127);
	motorSet(10, -127);
}

void motorsRight() {
	motorSet(2, 127);
	motorSet(1, 127);
	motorSet(4, 127);
	motorSet(10, 127);
}

void motorsPivotLeft(float power) {
	motorSet(2, -power);
	motorSet(1, power);
	motorSet(4, -power);
	motorSet(10, power);
}

void motorsPivotRight(float power) {
	motorSet(2, power);
	motorSet(1, -(power));
	motorSet(4, power);
	motorSet(10, -(power));
}

void clearLift() {
	motorSet(6, 0);
	motorSet(7, 0);
	motorSet(5, 0);
	motorSet(8, 0);
}

void motorsLift() {
	motorSet(6, 127);
	motorSet(7, 127);
	motorSet(5, -127);
	motorSet(8, -127);
}

void motorsDrop() {
	motorSet(6, -127);
	motorSet(7, -127);
	motorSet(5, 127);
	motorSet(8, 127);
}

void motorsClawClear() {
	motorSet(3, 0);
	motorSet(9, 0);
}

void motorsClawClose() {
	motorSet(3, 127);
	motorSet(9, -127);
}

void motorsClawOpen() {
	motorSet(3, -127);
	motorSet(9, 127);
}

void encWipe() {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	encoderReset(encBackL);
	encoderReset(encBackR);
}

//----------------------------

//***********************
//   Movement functions
//***********************

// Main function to drive in direction specified...
void go(int way, int distance, int velocity, int minPower) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	encoderReset(encBackL);
	encoderReset(encBackR);

	imeReset(IME_BL);
	imeReset(IME_BR);

	float outputFL, outputFR, outputBL, outputBR;

	float gain = 0.15;

	float tickChangeFL;
	float tickChangeFR;
	float tickChangeBL;
	float tickChangeBR;

	float tickLastFL = 0;
	float tickLastFR = 0;
	float tickLastBL = 0;
	float tickLastBR = 0;

	float errFL;
	float errFR;
	float errBL;
	float errBR;

	int imeValBL;
	int imeValBR;

	while ( (abs(encoderGet(encDriveL)) + abs(encoderGet(encDriveR)) + abs(imeGet(IME_BL, &imeValBL)) + abs(imeGet(IME_BR, &imeValBR)) / 4) < distance ) {

		tickChangeFL = abs(encoderGet(encDriveL)) - tickLastFL;
		tickChangeFR = abs(encoderGet(encDriveR)) - tickLastFR;
		tickChangeBL = abs(encoderGet(encBackL)) - tickLastBL;
		tickChangeBR = abs(encoderGet(encBackR)) - tickLastBR;

		tickLastFL = abs(encoderGet(encDriveL));
		tickLastFR = abs(encoderGet(encDriveR));
		tickLastBL = abs(imeGet(IME_BL, &imeValBL)*(360/261.333));
		tickLastBR = abs(imeGet(IME_BR, &imeValBR)*(360/261.333));

		errFL = velocity - tickChangeFL;
		errFR = velocity - tickChangeFR;
		errBL = velocity - tickChangeBL;
		errBR = velocity - tickChangeBR;

		if (way == 1) {
			if ( encoderGet(encDriveL) < distance * 0.1 ) {
				outputFL = 75;
				outputFR = 70;
				outputBL = 75;
				outputBR = 70;
			} else {
			outputFL = minPower + (errFL * gain);
			outputFR = minPower + (errFR * gain);
			outputBL = minPower + (errBL * gain);
			outputBR = minPower + (errBR * gain);
			}
		}
		if (way == 2) { // Backwards
			if ( encoderGet(encDriveL) < distance * 0.1 ) {
				outputFL = -75;
				outputFR = -70;
				outputBL = -75;
				outputBR = -70;
			} else {
			outputFL = -(minPower + (errFL * gain));
			outputFR = -(minPower + (errFR * gain));
			outputBL = -(minPower + (errBL * gain));
			outputBR = -(minPower + (errBR * gain));
			}
		}
		if (way == 3) { // Right
			if ( encoderGet(encDriveL) < distance * 0.1 ) {
				outputFL = 75;
				outputFR = -70;
				outputBL = -75;
				outputBR = 70;
			} else {
			outputFL = (minPower + (errFL * gain));
			outputFR = -(minPower + (errFR * gain));
			outputBL = -(minPower + (errBL * gain));
			outputBR = (minPower + (errBR * gain));
			}
		}
		if (way == 3) { // Right
			if ( encoderGet(encDriveL) < distance * 0.1 ) {
				outputFL = -75;
				outputFR = 70;
				outputBL = 75;
				outputBR = -70;
			} else {
				outputFL = -(minPower + (errFL * gain));
				outputFR = (minPower + (errFR * gain));
				outputBL = (minPower + (errBL * gain));
				outputBR = -(minPower + (errBR * gain));
			}
		}

		motorSet(2, -(outputFR));
		motorSet(1, (outputBR));
		motorSet(4, (outputFL));
		motorSet(10, -(outputBL)); // BL, was BR

		delay(50);
	}
	clearDrive();
}

void pivot(int way, int angle, int velocity, int minPower) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	encoderReset(encBackL);
	encoderReset(encBackR);
	gyroReset(gyro);

	imeReset(IME_BL);
	imeReset(IME_BR);

	float outputFL, outputFR, outputBL, outputBR;

	float gain = 0.005;

	float tickChangeFL;
	float tickChangeFR;
	float tickChangeBL;
	float tickChangeBR;

	float tickLastFL = 0;
	float tickLastFR = 0;
	float tickLastBL = 0;
	float tickLastBR = 0;

	float errFL;
	float errFR;
	float errBL;
	float errBR;

	int imeValBL;
	int imeValBR;

	while ( gyroGet(gyro) < angle ) {

		tickChangeFL = abs(encoderGet(encDriveL)) - tickLastFL;
		tickChangeFR = abs(encoderGet(encDriveR)) - tickLastFR;
		tickChangeBL = abs(encoderGet(encBackL)) - tickLastBL;
		tickChangeBR = abs(encoderGet(encBackR)) - tickLastBR;

		tickLastFL = abs(encoderGet(encDriveL));
		tickLastFR = abs(encoderGet(encDriveR));
		tickLastBL = abs(imeGet(IME_BL, &imeValBL)*(360/261.333));
		tickLastBR = abs(imeGet(IME_BR, &imeValBR)*(360/261.333));

		errFL = velocity - tickChangeFL;
		errFR = velocity - tickChangeFR;
		errBL = velocity - tickChangeBL;
		errBR = velocity - tickChangeBR;

		if (way == 1) {
			if ( gyroGet(gyro) < angle * 0.1 ) {
				outputFL = 75;
				outputFR = 75;
				outputBL = 75;
				outputBR = 75;
			} else {
			outputFL = minPower + (errFL * gain);
			outputFR = minPower + (errFR * gain) - 5;
			outputBL = minPower + (errBL * gain);
			outputBR = minPower + (errBR * gain) - 5;
			}
		}
		if (way == 2) {
			if ( gyroGet(gyro) < angle * 0.1 ) {
				outputFL = -75;
				outputFR = -70;
				outputBL = -75;
				outputBR = -70;
			} else {
			outputFL = -(minPower + (errFL * gain));
			outputFR = -(minPower + (errFR * gain));
			outputBL = -(minPower + (errBL * gain));
			outputBR = -(minPower + (errBR * gain));
			}
		}

		motorSet(2, -outputBR);
		motorSet(1, outputFR);
		motorSet(4, -outputFL);
		motorSet(10, outputBL);

		delay(50);
	}
	clearDrive();
}

void driveForward(int encTarget, float Kp, int timeOut) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	long startTime = millis();
	float power;
	float error;
	while(encoderGet(encDriveL) < encTarget) { //encLeft
		error = encTarget - encoderGet(encDriveL);
		//power = 120;
		/*if ((encoderGet(encDriveL) - encoderGet(encDriveR)) > 0) {
			motorSet(2, -(power));
			motorSet(1, power);
			motorSet(4, (power * 0.7));
			motorSet(10, -(power * 0.7));
		} else if ((encoderGet(encDriveL) - encoderGet(encDriveR)) < 0) {
			motorSet(2, -(power * 0.7));
			motorSet(1, (power * 0.7));
			motorSet(4, power);
			motorSet(10, -(power));
		} else {
			power = error * Kp;
	 		motorsForward(power);
		}*/
		if (encoderGet(encDriveL) < encTarget * 0.1) {
			power = 75;
			motorsForward(power);
		} else {
			power = error * Kp;
			motorsForward(127);
		}
		if ((millis() - startTime) > timeOut) { break; }
	}
	clearDrive();
}

void pidForward(int encTarget, float Kp, float Ki, float Kd, int timeOut) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	long startTime = millis();
	float power;
	float error;
	float sumErr;
	float prop;
	float integ;
	float deriv;
	float errLast;
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) < (encTarget / 3) ) {
			// power += 1;
		power = (power * 0.5) + power + 1;
		motorsForward(power);
		if (power > 127) { power = 127; }
		delay(100);
	}
	encWipe();
	while(encoderGet(encDriveL) < (encTarget * 0.666) ) { //encLeft
		error = encTarget - encoderGet(encDriveL);
		sumErr += error;
		prop = error * Kp;
		integ = sumErr * Ki;
		deriv = (sumErr - errLast) * Kd;
		errLast = error;
		motorsForward((prop + integ + deriv));
		if ((millis() - startTime) > timeOut) { break; }
	}
	clearDrive();
}

void mpForward(int encTarget, float aGain) {
	int power = 0;
	encWipe();
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) < (encTarget / 3)) {
		// power += 1;
		power = (power * aGain) + power + 1;
		motorsForward(power);
		if (power > 127) { power = 127; }
		delay(100);
	}
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) < (encTarget / 3)) {
		motorsForward(120);
	}
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) < (encTarget / 3)) {
		power = 50;
		motorsForward(power);
		if (power < 0) { power = 0; }
		delay(25);
	}
	clearDrive();

}

void pidBack(int encTarget, float Kp, float Ki, float Kd, int timeOut) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	encoderReset(encBackL);
	encoderReset(encBackR);
	long startTime = millis();
	float power;
	float error;
	float sumErr;
	float prop;
	float integ;
	float deriv;
	float errLast;

	float turnErr;
	float turnGain;
	/*while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) > (encTarget / 3) ) {
		power = (power * 0.5) + power + 1;
		motorsBack(power);
		if (power > 127) { break; }
		delay(100);
	} */
	// ( (abs(encodeGet(encDriveL)) + abs(encodeGet(encDriveR)) + abs(encoderGet(encBackL)) + abs(encdoeGet(encBackR))) / 4)
	while( (abs(encoderGet(encDriveL)) + abs(encoderGet(encDriveR) + abs(encoderGet(encBackL)) + abs(encoderGet(encBackR))) / 4) < encTarget) { //encLeft
		error = encTarget - (abs(encoderGet(encDriveL)) + abs(encoderGet(encDriveR) + abs(encoderGet(encBackL)) + abs(encoderGet(encBackR))) / 4);
		sumErr += error;
		prop = error * Kp;
		integ = sumErr * Ki;
		deriv = (sumErr - errLast) * Kd;
		errLast = error;
		// Check if left side is going faster
		/*if ( (abs(encoderGet(encDriveL) + abs(encoderGet(encBackL)) / 2)) > (abs(encoderGet(encDriveR) + abs(encoderGet(encBackR)) / 2)) ) {
			// power = (prop + integ + deriv);
			turnErr = (abs(encoderGet(encDriveL) + abs(encoderGet(encBackL)) / 2)) - (abs(encoderGet(encDriveR) + abs(encoderGet(encBackR)) / 2));
			power = 120;
			motorSet(2, ( turnErr * turnGain ));
			motorSet(1, -( power )); // Front Left
			motorSet(4, -( power ));
			motorSet(10, ( turnErr * turnGain )); // Back Left
		} else if ( (abs(encoderGet(encDriveR) + abs(encoderGet(encBackR)) / 2)) > (abs(encoderGet(encDriveL) + abs(encoderGet(encBackL)) / 2)) ) {
			turnErr = (abs(encoderGet(encDriveR) + abs(encoderGet(encBackR)) / 2)) - (abs(encoderGet(encDriveL) + abs(encoderGet(encBackL)) / 2));
			power = 120;
			motorSet(2, (power));
			motorSet(1, -( turnErr * turnGain )); // Front Left
			motorSet(4, -( turnErr * turnGain ));
			motorSet(10, (power)); // Back Left
		} else {
			motorsBack(prop + integ + deriv);
		} */
		motorsBack(120);

		if ((millis() - startTime) > timeOut) { break; }
		delay(75);
	}
	clearDrive();
}

void mpBack(int encTarget, float aGain) {
	int power = 0;
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) > (encTarget / 3)) {
		// power += 1;
		power = (power * aGain) + power + 1;
		motorsBack(power);
		if (power > 127) { power = 127; }
		delay(100);
	}
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) > (encTarget / 3)) {
		motorsBack(120);
	}
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) > (encTarget / 3)) {
		power = 75;
		motorsBack(power);
		if (power < 0) { power = 0; }
		delay(25);
	}
	clearDrive();

}

void driveBack(int encTarget, float Kp, int timeOut) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	long startTime = millis();
	float power;
	float error;
	while( ((encoderGet(encDriveL) + encoderGet(encDriveR)) / 2) > encTarget ) {
		error = encTarget - encoderGet(encDriveL);
		power = 120;
	/*	if ((encoderGet(encDriveL) - encoderGet(encDriveR)) < 0) {
			motorSet(2, (power));
			motorSet(1, -power);
			motorSet(4, -(power * 0.7));
			motorSet(10, (power * 0.7));
		} else if ((encoderGet(encDriveL) - encoderGet(encDriveR)) > 0) {
			motorSet(2, (power * 0.7));
			motorSet(1, -(power * 0.7));
			motorSet(4, -power);
			motorSet(10, (power));
		} else {
			power = -(error) * Kp;
			motorsBack(power);
		}*/
		motorsBack(power);
		if ((millis() - startTime) > timeOut) { break; }
	}
	clearDrive();
}


void pivotLeft(int gyroTarget, float Kp, int timeOut) {
	gyroReset(gyro);
	float power;
	long startTime = millis();
	while (gyroGet(gyro) < gyroTarget) {
		power = (gyroTarget - gyroGet(gyro)) * Kp;
		if ((millis() - startTime) > timeOut) { break; }
		motorsPivotLeft(power);
	}
	clearDrive();
}

void pivotRight(int gyroTarget, float Kp, int timeOut) {
	gyroReset(gyro);
	long startTime = millis();
	float power;
	float error;
	while (gyroGet(gyro) > gyroTarget) {
		error = gyroTarget - gyroGet(gyro);
		power = -(error) * Kp;
		if ((millis() - startTime) > timeOut) { break; }
		motorsPivotRight(power);
	}
	clearDrive();
}

void pivotLeftCorrect(int gyroTarget) {
	gyroReset(gyro);
	while (gyroGet(gyro) < gyroTarget) {
		motorsPivotLeft(120);
	}
	clearDrive();
}

void driveLeft(int encTarget) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	while (encoderGet(encDriveL) > encTarget) {
		motorsLeft();
	}
	clearDrive();
}

void driveRight(int encTarget) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	while (encoderGet(encDriveL) < encTarget) {
		motorsRight();
	}
	clearDrive();
}

void liftArm(int encTarget) {
	encoderReset(encLift);
	while (encoderGet(encLift) < encTarget) {
		motorsLift();
	}
	clearLift();
}

void encDropArm(int encTarget) {
	encoderReset(encLift);
	while (encoderGet(encLift) > encTarget) {
		motorSet(6, -127);
		motorSet(7, -127);
		// Left
		motorSet(5, 127);
		motorSet(8, 127);
	}
	clearLift();
}

/*void dropArm(int encTarget) {
	encoderReset(encLift);
	while (encoderGet(encLift) > encTarget) {
		motorsDrop();
	}
	clearLift();
}*/


void dropArm(int time) {
	motorSet(6, -127);
	motorSet(7, -127);
	// Left
	motorSet(5, 127);
	motorSet(8, 127);
	delay(time);
	clearLift();
}

void openClaw(int potTarget, int timeOut) {
	analogCalibrate(1);
	long startTime = millis();
	while(analogRead(1) > potTarget) {
		motorsClawOpen();
		if ((millis() - startTime) > timeOut) { break; }
	}
	motorsClawClear();
}

void closeClaw(int potTarget, int timeOut) {
	analogCalibrate(1);
	long startTime = millis();
	while(analogRead(1) < potTarget) {
		motorsClawClose();
		if ((millis() - startTime) > timeOut) { break; }
	}
	motorsClawClear();
}

void closeClawTime(int time) {
	motorSet(3, 120);
	motorSet(9, -120);
	delay(time);
	motorSet(3, 0);
	motorSet(9, 0);
}

#endif /* INCLUDE_AUTODEFAULTS_H_ */
