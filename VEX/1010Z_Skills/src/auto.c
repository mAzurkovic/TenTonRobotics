#include "main.h"
#include "autoDefaults.h"

#define FORWARD 1
#define BACK 2

int checkClaw = 0;

// Task that simontaniousley opens the claw when the arm is lifting
void timeClaw(void * parameter) {
  while(true) {
	if (encoderGet(encLift) > 525) {
		motorSet(CLAW_RIGHT, 127);
		motorSet(CLAW_LEFT, -(127));
		if (analogRead(1) < 1800) {
			motorSet(CLAW_RIGHT, 0);
			motorSet(CLAW_LEFT, 0);
		}
	}
    delay(25);
  }
}


void programmingSkills() {
//	go(FORWARD, 10, 48, 90);
	drive(100);
}


void autonomous() {
	sensorReset();
	printf("GOING");

	TaskHandle clawTaskHandler = taskCreate(timeClaw, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	programmingSkills();
}
