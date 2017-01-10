#include "main.h"

int clawTick;

void clearDrive() {
	motorSet(2, 0); // Front Right Drive
	motorSet(1, 0); // Back Right
	motorSet(4, 0); // Front Left
	motorSet(10, 0); // Back Left
}

void driveForward(int time) {
	motorSet(2, -127); // Front Right Drive
	motorSet(1, 127); // Back Right
	motorSet(4, 127); // Front Left
	motorSet(10, -127); // Back Left
	delay(time);
	clearDrive();
}

void driveRight(int time) {
	motorSet(2, 127); // Front Right Drive
	motorSet(1, 127); // Back Right
	motorSet(4, 127); // Front Left
	motorSet(10, 127); // Back Left
	delay(time);
	clearDrive();
}

void driveLeft(int time) {
	motorSet(2, -127); // Front Right Drive
	motorSet(1, -127); // Back Right
	motorSet(4, -127); // Front Left
	motorSet(10, -127); // Back Left
	delay(time);
	clearDrive();
}

void pivotRight(int time) {
	motorSet(2, 127); // Front Right Drive
	motorSet(1, -127); // Back Right
	motorSet(4, 127); // Front Left
	motorSet(10, -127); // Back Left
	delay(time);
	clearDrive();
}

void pivotLeft(int time) {
	motorSet(2, -127); // Front Right Drive
	motorSet(1, 127); // Back Right
	motorSet(4, -127); // Front Left
	motorSet(10, 127); // Back Left
	delay(time);
	clearDrive();
}

void driveBack(int time) {
	motorSet(2, 127); // Front Right Drive
	motorSet(1, -127); // Back Right
	motorSet(4, -127); // Front Left
	motorSet(10, 127); // Back Left
	delay(time);
	clearDrive();
}

void closeClaw(int time) {
	motorSet(3, 120);
	motorSet(9, -120);
	delay(time);
	motorSet(3, 0);
	motorSet(9, 0);
}

void openClaw(int time) {
	motorSet(3, -120);
	motorSet(9, 120);
	delay(time);
	motorSet(3, 0);
	motorSet(9, 0);
}

void clearArm() {
	motorSet(6, 0);
	motorSet(7, 0);
	// Left
	motorSet(5, 0);
	motorSet(8, 0);
}

void liftArm(int time) {
	motorSet(6, 127);
	motorSet(7, 127);
	// Left
	motorSet(5, -127);
	motorSet(8, -127);
	delay(time);
	clearArm();
}

void dropArm(int time) {
	motorSet(6, -127);
	motorSet(7, -127);
	// Left
	motorSet(5, 127);
	motorSet(8, 127);
	delay(time);
	clearArm();
}

void matchAuto() {
	int gyroTick = gyroGet(gyro);
	delay(5000);

	driveBack(500);
	driveRight(1250);
	closeClaw(800);
	openClaw(400);
	driveForward(1100);
	closeClaw(1000);
	liftArm(500);
	pivotLeft(750);
	driveBack(1000);
	liftArm(1500);
	openClaw(750);
	dropArm(1000);
	driveForward(1100);
	closeClaw(1000); //
	liftArm(500);
	driveBack(1250);
	liftArm(1250);
	openClaw(750);

}

void matchAutoB() {
	/*driveBack(500);
	driveRight(1250);
	closeClaw(800);
	driveForward(1250);
	driveForward(1000);
	driveBack(2250);
	driveLeft(900); */
	driveRight(700);
	closeClaw(1000);
	driveLeft(700);
	openClaw(500);
	driveForward(1000);
	openClaw(500);
	driveForward(1000);
	closeClaw(750);
	liftArm(500);
	driveBack(1000);
	closeClaw(500);
	driveRight(700);
	pivotLeft(700);
	driveBack(1000);
	pivotLeft(400);
	driveBack(500);
	driveForward(500);
	driveBack(1000);
	liftArm(2000);
	openClaw(1000);

}

void programmingSkills() {
	driveBack(1000);
	closeClaw(600);
	driveForward(500);
	closeClaw(750);
	liftArm(250);
	driveBack(1500);
	liftArm(1500);
	openClaw(500);
	dropArm(1200);
	openClaw(1000);
	driveForward(1000);
	//driveRight(200);
	driveForward(1500);

	driveBack(1000);
	closeClaw(600);
	driveForward(500);
	closeClaw(750);
	liftArm(250);
	driveBack(1500);
	liftArm(1500);
	openClaw(750);
	dropArm(1200);
	openClaw(750);
	driveRight(100);
	driveForward(1000);
	pivotLeft(50);
	//driveRight(200);
	driveForward(1250);

	driveBack(1000);
	closeClaw(600);
	driveForward(500);
	closeClaw(750);
	liftArm(250);
	driveBack(750);
	pivotLeft(100);
	driveBack(750);
	liftArm(1500);
	openClaw(750);
	dropArm(1200);
	openClaw(750);
	// driveLeft(50);
	driveForward(1000);
	// pivotRight(100);
	driveForward(1250);

	driveBack(1000);
	closeClaw(600);
	driveForward(500);
	closeClaw(750);
	liftArm(250);
	driveBack(750);
	pivotLeft(100);
	driveBack(750);
	liftArm(1500);
	openClaw(750);
	dropArm(1200);
	openClaw(750);

}

void matchAutoC() {
	driveRight(500);
	closeClaw(1000);
	driveLeft(500);
	openClaw(200);
	driveForward(1500);
	closeClaw(750);
	liftArm(500);
	driveBack(1000);
	driveRight(700);
	pivotLeft(300);
	driveBack(750);
	pivotLeft(500);
	closeClaw(500);
	liftArm(200);
	driveBack(1400);
	liftArm(1500);
	openClaw(500);
}

void progSkillsA() {
	driveBack(1000);
	closeClaw(500);
	driveForward(750);
	closeClaw(500);
	liftArm(500);
	driveBack(1750);
	liftArm(1500);
	openClaw(750);
	dropArm(1500);

	driveForward(1500);
	openClaw(500);
}

void autonomous() {

	// GOOD SKILLZ
	// programmingSkills();
	lcdClear(uart1);
	gyroReset(gyro);
// WITH 2G
	//matchAuto();


	 // matchAutoB();

	// GOOD ATUO
	// matchAutoC();


	// progSkillsA();

}
