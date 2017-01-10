//========================================//
//
//   AUTO FUNCTIONS   -  1010 Robotics
//
//========================================//

#ifndef INCLUDE_AUTODEFAULTS_H_
#define INCLUDE_AUTODEFAULTS_H_

#include <stdlib.h>
#include <time.h>

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
	motorSet(1, power);
	motorSet(4, power);
	motorSet(10, -(power));
}

void motorsBack(float power) {
	motorSet(2, power);
	motorSet(1, -(power));
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
}

//----------------------------

//***********************
//   Movement functions
//***********************

void driveForward(int encTarget, float Kp, int timeOut) {
	encoderReset(encDriveL);
	encoderReset(encDriveR);
	long startTime = millis();
	float power;
	float error;
	while(encoderGet(encDriveL) < encTarget) { //encLeft
		error = encTarget - encoderGet(encDriveL);

		if ((encoderGet(encDriveL) - encoderGet(encDriveR)) > 0) {
			motorSet(2, -(power));
			motorSet(1, power);
			motorSet(4, (power * 0.9));
			motorSet(10, -(power * 0.9));
		} else if ((encoderGet(encDriveL) - encoderGet(encDriveR)) < 0) {
			motorSet(2, -(power * 0.9));
			motorSet(1, (power * 0.9));
			motorSet(4, power);
			motorSet(10, -(power));
		} else {
			power = error * Kp;
	 		motorsForward(power);
		}

		if ((millis() - startTime) > timeOut) { break; }
	}
	clearDrive();
}

void mpForward(int encTarget, float aGain) {
	int power = 0;
	encWipe();
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
		motorsForward(120);
	}
	encWipe();
	while( ((encoderGet(encDriveL) + encoderGet(encDriveL)) / 2) > (encTarget / 3)) {
		power = 50;
		motorsForward(power);
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
	while( ((encoderGet(encDriveL) + encoderGet(encDriveR)) / 2) > encTarget) {
		error = encTarget - encoderGet(encDriveL);

		if ((encoderGet(encDriveL) + encoderGet(encDriveR)) < 0) {
			motorSet(2, (power));
			motorSet(1, -power);
			motorSet(4, -(power * 0.9));
			motorSet(10, (power * 0.9));
		} else if ((encoderGet(encDriveL) + encoderGet(encDriveR)) > 0) {
			motorSet(2, (power * 0.9));
			motorSet(1, -(power * 0.9));
			motorSet(4, -power);
			motorSet(10, (power));
		} else {
			power = -(error) * Kp;
			motorsBack(power);
		}
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