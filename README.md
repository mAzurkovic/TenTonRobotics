# 1010 Robotics Repo

> Welcome to the 1010 Ten Ton Robotics code base

## Regarding `autoDefaults.h`
File that provides some autonomous commands.

### Prerequisites
> Note: You are going to need to tune some settings in the file and also make sure you have a similar motor configuration.

* Encoders on wheels
* Potentiomenter on claw
* Gyro on base

### Defenitions
Here is a list of what each function does and its parameters...

* `driveForward(int encTarget, float Kp, int timeOut)`
* `driveBack(int encTarget, float Kp, int timeOut)`
* `mpForward(int encTarget, float aGain)`
* `mpBack(int encTarget, float aGain)`
* `pivotLeft(int gyroTarget, float Kp, int timeOut)`
* `pivotRight(int gyroTarget, float Kp, int timeOut)`
* `driveLeft(int encTarget)`
* `driveRight(int encTarget)`
* `liftArm(int encTarget)`
* `encDropArm(int encTarget)`
* `closeClaw(int potTarget, int timeOut)`
* `openClaw(int potTarget, int timeOut)`
