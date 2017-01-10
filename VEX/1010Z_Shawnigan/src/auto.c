#include "main.h"
#include "autoDefaults.h"

#define FORWARD 1
#define BACK 2
#define LEFT 4
#define RIGHT 3

#define SPEED 48
#define MIN_POWER 90


//---------------------------------------------------\\
//		   	  Auto Predefined Functions				 \\
//---------------------------------------------------\\

/*****************************************************\
|
|	driveForward(int encoderTarget, float Kp, int timeOut)
|	driveBack(int encoderTarget, float Kp, int timeOut)
|
|	pivotLeft(int +gyroTarget, float Kp, int timeOut)
|	pivotRight(int -gyroTarget, float Kp, int timeOut)
|
|	liftArm(int encoderTarget)
|	dropArm(int milliseconds)
|
|	closeClaw(int potentiometerTarget, int timeOut)
|	openClaw(int potentiometerTarget, int timeOut)
|
\*****************************************************/

int checkClaw = 0;

// Task that simontaniousley opens the claw when the arm is lifting
void timeClaw(void * parameter) {
  while(true) {
	if (encoderGet(encLift) > 525) {
		motorSet(3, -127);
		motorSet(9, 127);
		if (analogRead(1) < 1800) {
			motorSet(3, 0);
			motorSet(9, 0);
		}
	}
    delay(25);
  }
}

void programmingSkillsLeft() {
	lcdClear(uart1);
	lcdSetText(uart1, 1, "Prog. Skills");

	// Clear fence
	driveForward(750, 0.75, 1500);
	liftArm(325);
	closeClaw(1000, 500);
	driveForward(750, 0.75, 1750);
	// Turn and get first set of pre-load stars
	driveBack(-850, 0.5, 1000);
	openClaw(700, 500); // was 750
	dropArm(800);
	pivotLeft(180, 1.1, 2000);
	driveForward(450, 0.25, 1500);

	// Drive back and dump
	//closeClaw(2800, 1000);
	closeClawTime(1000);
	liftArm(100);
	//pivotLeft(10, 1.8);
	//pivotLeftCorrect(5);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1900, 600);

	// Go back and get the first pre-load cube
	dropArm(900);
	driveBack(-450, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(1000);
	liftArm(300);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 600);

	// Go back and get second cube pre-load
	dropArm(800);
	driveBack(-500, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(750);
	liftArm(300);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 600);

	// Go back and get last pair of star pre-loads
	dropArm(800);
	driveBack(-500, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(750);
	liftArm(200);
	driveBack(-775, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 1000);
	closeClaw(1750, 1000);

	// 40 Seconds

	// Part II: Get stars in back
	dropArm(900);
	pivotRight(50, 1.1, 1500);
	mpForward(300, 0.5);
	openClaw(1750, 1000);
	driveForward(600, 0.25, 1000);
	closeClawTime(1750);
	liftArm(200);
	driveBack(-750, 0.25, 2000);
	closeClawTime(500);
	liftArm(200);
	pivotRight(-70, 1.1, 1000);
	closeClawTime(500);
	driveBack(-300, 0.25, 1000);
	liftArm(600);
	openClaw(1000, 1000);
}

// OLD!!! Programming skills autonomous code
void programmingSkills() {
	lcdClear(uart1);
	lcdSetText(uart1, 1, "Prog. Skills");

	// Clear fence
	driveForward(750, 0.75, 1500);
	liftArm(325);
	closeClaw(1000, 500);
	driveForward(750, 0.75, 1750);
	// Turn and get first set of pre-load stars
	driveBack(-850, 0.5, 1000);
	openClaw(700, 500); // was 750
	dropArm(800);
	pivotLeft(180, 1.1, 2000);
	driveForward(450, 0.25, 1500);

	// Drive back and dump
	//closeClaw(2800, 1000);
	closeClawTime(1000);
	liftArm(100);
	//pivotLeft(10, 1.8);
	//pivotLeftCorrect(5);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1900, 600);

	// Go back and get the first pre-load cube
	dropArm(900);
	driveBack(-450, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(1000);
	liftArm(300);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 600);

	// Go back and get second cube pre-load
	dropArm(800);
	driveBack(-500, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(750);
	liftArm(300);
	driveBack(-800, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 600);

	// Go back and get last pair of star pre-loads
	dropArm(800);
	driveBack(-500, 0.5, 500);
	driveForward(900, 0.25, 1500);
	closeClawTime(750);
	liftArm(200);
	driveBack(-775, 0.5, 1500);
	liftArm(600);
	openClaw(1500, 1000);
	closeClaw(1750, 1000);

	// 40 Seconds

	// Part II: Get stars in back
	dropArm(900);
	pivotRight(-50, 1.1, 1500);
	mpForward(300, 0.5);
	openClaw(1750, 1000);
	driveForward(600, 0.25, 1000);
	closeClawTime(1750);
	liftArm(200);
	driveBack(-750, 0.25, 2000);
	closeClawTime(500);
	liftArm(200);
	pivotLeft(70, 1.1, 1000);
	closeClawTime(500);
	driveBack(-300, 0.25, 1000);
	liftArm(600);
	openClaw(1000, 1000);
}

// Match autonomous A: Grab stars in back and flip them over fence
void getCubeAuto() {
	driveRight(500);
	closeClaw(1500, 1000);
	openClaw(1700, 1000);
	driveForward(600, 0.25, 1500); // was 700
	closeClawTime(1250);
	liftArm(200);
	driveBack(-500, 0.25, 1000);
	closeClawTime(500);
	liftArm(200);
	pivotLeft(90, 1.1, 1000);
	closeClawTime(500);
	driveBack(-750, 0.25, 2000);
	liftArm(600);
	openClaw(1500, 1500);

}

void getCubeAutoLeft() {
	driveLeft(500);
	closeClaw(1500, 1000);
	openClaw(1700, 1000);
	driveForward(600, 0.25, 1500); // was 700
	closeClawTime(1250);
	liftArm(200);
	driveBack(-500, 0.25, 1000);
	liftArm(200);
	pivotRight(-90, 1.1, 1000);
	driveBack(-750, 0.25, 2000);
	liftArm(600);
	openClaw(1500, 1500);

}

void backStarsLeft() {
	driveLeft(500);
	driveBack(-200, 0.25, 1000);
	closeClaw(1500, 1000);
	driveRight(-470);
	openClaw(2100, 1000);
	driveForward(1300, 0.25, 2500);
	closeClaw(2700, 2000);
	closeClawTime(500);

	liftArm(200);
	driveBack(-1000, 0.25, 2000);
	closeClawTime(500);
	liftArm(200);
	closeClawTime(500);
	driveLeft(500);
	pivotRight(-100, 1.1, 1500);
	closeClawTime(500);
	liftArm(200);
	driveBack(-900, 0.25, 2000);
	liftArm(600);
	openClaw(1600, 2000);

}

// Match autonomous B: Grab cube in back and flip them over fence
void backStarsRight() {
	/*driveRight(500);
	driveBack(-200, 0.25, 1000);
	closeClaw(1500, 1000);
	driveLeft(-470);
	openClaw(2100, 1000);
	driveForward(1300, 0.25, 2500);
	closeClaw(2700, 2000);
	closeClawTime(500);*/

	closeClaw(1500, 1500);
	pivotLeft(50, 1.1, 1000);
	openClaw(2100, 1000);
	driveForward(1300, 0.25, 1500);
	closeClawTime(1500);
	liftArm(200);
	driveBack(-1000, 0.25, 1000);
	closeClawTime(500);
	liftArm(200);
	closeClawTime(500);
	driveRight(500);
	pivotLeft(100, 1.1, 1000);
	closeClawTime(500);
	liftArm(200);
	driveBack(-900, 0.25, 2000);
	liftArm(600);
	openClaw(1600, 2000);

}

void twoStars() {
	driveLeft(-500);
	closeClaw(1500, 1000);
	driveRight(400);
	openClaw(1800, 1000);
	driveForward(400, 0.25, 1000);
	closeClaw(2700, 2000);
	liftArm(100);
	driveLeft(-500);
	liftArm(100);
	closeClawTime(250);
	pivotRight(-90, 1.1, 1000);
	closeClawTime(250);
	liftArm(100);
	driveBack(-700, 0.25, 1000);
	liftArm(600);
	openClaw(1700, 1000);
}

void gladstoneCubeRight() {
	go(RIGHT, 470, 48, 90);
	closeClaw(1500, 500);
	go(FORWARD, 125, 48, 90);
	openClaw(1500, 750);
	go(FORWARD, 250, 48, 90);
	closeClawTime(1500);
	liftArm(300);
	//go(BACK, 180, 48, 90);
	closeClawTime(500);
	pivotLeft(110, 0.45, 2000);
	delay(250);
	openClaw(1800, 1000);
	dropArm(100);
	closeClawTime(1000);
	liftArm(100);
	go(BACK, 450, 48, 90);
	liftArm(605);
}

void shitAuto() {
	go(BACK, 300, 48, 90);
	//delay(500);
	closeClaw(1800, 1000);
	go(FORWARD, 75, 48, 90);
	closeClaw(2700, 750);
	go(BACK, 75, 48, 90);
	closeClawTime(250);
	liftArm(150);
	go(BACK, 850, 48, 90);
	dropArm(100);
	closeClawTime(250);
	liftArm(605);
	delay(500);
}

// Current programming skills for the DECEMEBER 10th Competition
void pgSkills() {
	/*go(FORWARD, 625, 48, 90);
	liftArm(200);
	closeClaw(700, 1000);
	delay(500);
	go(FORWARD, 200, 48, 90);
	liftArm(175);
	// go(BACK, 50, 48, 90);
	openClaw(800, 750);
	dropArm(800);
	pivot(1, 165, 48, 25);*/
	go(BACK, 300, 48, 90);
	//delay(500);
	closeClaw(1800, 1000);
	go(FORWARD, 75, 48, 90);
	closeClaw(2700, 750);
	go(BACK, 75, 48, 90);
	closeClawTime(250);
	liftArm(200);
	go(BACK, 850, 48, 90);
	closeClawTime(250);
	liftArm(610);
	delay(500);
	dropArm(800);
	delay(250);
	driveBack(-250, 0.25, 500);

	go(FORWARD, 800, 48, 90);
	closeClawTime(1000);
	liftArm(200);
	go(BACK, 900, 48, 90);
	liftArm(610);
	delay(500);
	dropArm(800);
	delay(250);
	driveBack(-250, 0.25, 500);
	pivotRight(-10, 1.1, 1000);

	go(FORWARD, 800, 48, 90);
	closeClawTime(1000);
	liftArm(200);
	go(BACK, 900, 48, 90);
	liftArm(610);
	delay(500);
	dropArm(800);
	delay(250);
	driveBack(-250, 0.25, 500);
	pivotRight(-10, 1.1, 1000);

	go(FORWARD, 800, 48, 90);
	closeClawTime(1000);
	liftArm(200);
	go(BACK, 900, 48, 90);
	liftArm(610);
	delay(500);
	dropArm(800);
	delay(250);
	driveBack(-250, 0.25, 500);
	pivotRight(-10, 1.1, 1000);

	// END of Pre-Loads ~ 35 seconds
	// Go and retrieve middle cube and stars
	dropArm(800);
	go(FORWARD, 475, 48, 90);
	openClaw(800, 1000);
	pivotLeft(110, 0.5, 2000);
	closeClaw(1500, 1000);
	go(FORWARD, 175, 48, 90);
	openClaw(1900, 1000);
	go(FORWARD, 425, 48, 90);
	closeClawTime(1500);
	liftArm(200);
	pivotRight(-140, 0.6, 2000);
	closeClawTime(500);
	liftArm(100);
	go(BACK, 575, 48, 90);
	closeClawTime(500);
	liftArm(595);
	delay(500);
}

void autonomous() {
	// Wipe encoders
	encoderReset(encLift);
	encoderReset(encDriveR);
	encoderReset(encDriveL);
	// Wipe gyroscope
	gyroReset(gyro);

	TaskHandle clawTaskHandler = taskCreate(timeClaw, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	// Call autonomous program:

	/*go(RIGHT, 200, 48, 90);
	delay(250);
	go(BACK, 50, 48, 90);
	openClaw(1700, 1000);
	openClaw()*/

	// pgSkills();
	/*dropArm(800);
	go(FORWARD, 475, 48, 90);
	openClaw(800, 1000);
	pivotLeft(105, 0.5, 2000);
	closeClaw(1500, 1000);
	go(FORWARD, 175, 48, 90);
	openClaw(1500, 1000);
	go(FORWARD, 275, 48, 90);
	closeClawTime(1500);
	liftArm(400);
	pivotRight(-170, 0.6, 2000);
	openClaw(800, 1000);
	dropArm(100);
	go(BACK, 1350, 48, 90);
	pivotLeft(105, 0.45, 2000);*/

	// LCD chooser
	if (program == 1) {
		pgSkills();
	} else if (program == 2) {
		gladstoneCubeRight();
	} else if (program == 3) {
		shitAuto();
	} else if (program == 4) {
		backStarsRight();
	} else if (program == 5) {
		programmingSkillsLeft();
	}

	/*dropArm(800);
	delay(250);

	// Go get cube in corner ...
	go(FORWARD, 500, 48, 90);
	openClaw(800, 750);
	go(RIGHT, 525, 48, 90);
	go(FORWARD, 350, 48, 90);
	closeClawTime(1500);
	go(BACK, 100, 48, 90);
	closeClawTime(500);
	liftArm(300);
	go(BACK, 850, 48, 90);
	liftArm(610);*/

	taskDelete(clawTaskHandler);
}
