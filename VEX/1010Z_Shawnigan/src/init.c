/**
 * File for initialization code.
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Copyright(c) 2011 - 2014, Purdue University ACM SIG BOTS.All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and / or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS(http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include <stdlib.h>
#include <string.h>

 /**
  * Runs pre-initialization code.
  *
  * This function will be started in kernel mode one time while the VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
  *
  * The purpose of this function is solely to set the default pin modes (pinMode()) and port states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
  */
void initializeIO() {
}

void ChooseLcd(void * parameter) {

}

Gyro gyro;

const int leftButton = 1;
const int centerButton = 2;
const int rightButton = 4;

char* autoNames[] = {"Skills", "Stars", "Cube"};

int program;

void initialize() {
	gyro = gyroInit(2, 0);

	lcdInit(uart1);
	lcdClear(uart1);

	analogCalibrate(3); // Right line tracker - null ~ 15000, on white 800
	analogCalibrate(4); // Center line tracker - null ~ 3500, on white = -6000
	analogCalibrate(5); // Left line tracker - null ~ 400, on white = -16000

	analogCalibrate(8); // Calibrate x axis input

	encLift = encoderInit(11, 12, true);
	encDriveR = encoderInit(7, 8, false);
	encDriveL = encoderInit(1, 2, true);
	encBackR = encoderInit(3, 5, true);
	encBackL = encoderInit(6, 9, true);

	int autoId[] = {1, 2, 3, 4, 5}; // 1 = Skills, 2 = Cube Auto, 3 = 2 Stars, 4 = Back StarsR, 5 = SkillsLeft, 6 = CubeAutoL, 7 2StarsL, 8 = BackStarsL

	int counter = 0;
	lcdSetText(uart1, 2, "<      OK      >");
	while (true) {
		if (lcdReadButtons(uart1) == 4) {
			counter++;
			// lcdPrint(uart1, 1, "UP %d", counter);
		} else if (lcdReadButtons(uart1) == 1) {
			counter--;
			// lcdPrint(uart1, 1, "DOWN %d", counter);
		}

		if (autoId[counter] == 1) {
			lcdPrint(uart1, 1, "LOAD: Skills");
		} else if (autoId[counter] == 2) {
			lcdPrint(uart1, 1, "LOAD: GCUBE R");
		} else if (autoId[counter] == 3) {
			lcdPrint(uart1, 1, "LOAD: SHIT AUTO");
		} else if (autoId[counter] == 4) {
			lcdPrint(uart1, 1, "LOAD: BackStarsR");
		} else if (autoId[counter] == 5) {
			lcdPrint(uart1, 1, "LOAD: Skills L");
		} else {
			lcdPrint(uart1, 1, "LOAD:  ...  ");
		}

		if (lcdReadButtons(uart1) == 2) {
			if (autoId[counter] == 1) {
				program = 1;
				break;
			} else if (autoId[counter] == 2) {
				program = 2;
				break;
			} else if (autoId[counter] == 3) {
				program = 3;
				break;
			} else if (autoId[counter] == 4) {
				program = 4;
				break;
			} else if (autoId[counter] == 5) {
				program = 5;
				break;
			} else {
				continue;
			}
		}

		delay(150);
	}
}
