#pragma config(Sensor, dgtl1,  boomMax,        sensorTouch)
#pragma config(Sensor, dgtl2,  boomMin,        sensorTouch)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           boomMotor,        tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           servoA,    tmotorNormal, openLoop)
#pragma config(Motor,  port7,           servoB,    tmotorNormal, openLoop)

/* Two methods for controlling speed of the motors. One requires a press to change
 * speed and the \other you hold down continuously (this is the one commented out).
 */

float k1=1; //proportionality constant for relation of joystick and motor speed
float k2 = 1;
float currentAngle6 = 0;
float currentAngle7 = 0;

float deltaAngle6 = 1; //how much the angle changes each iteration
float deltaAngle7 = 1;
int pause = 4;  // delay between iterations
//ratio of deltaAngle & delay determines how fast the servo turns (50 degs/s right now)

//increases the speed only when Btn5D is held down
float changeSpeedHold()
{
	if(vexRT[Btn5D] == 1)
		{ return 1; }
	else
		{ return 0.2;}
}

void servoPort6()
{
	motor[servoA] = currentAngle6;
		if(vexRT[Btn5D] == 1 && currentAngle6 > -127 + deltaAngle6)
		{ //runs when 5D is pressed and the angle won't hit the minimum (it resets to 0 when it does)
			currentAngle6 -= deltaAngle6;
			sleep(pause);
		}
		if(vexRT[Btn5U] == 1 && currentAngle6 < 127 - deltaAngle6)
		{ //runs when 5U is pressed and the angle won't hit the maximum
			currentAngle6 += deltaAngle6;
			sleep(pause);
		}
}

void servoPort7()
{
	motor[servoB] = currentAngle7;
		if(vexRT[Btn6D] == 1 && currentAngle7 > -127 + deltaAngle7)
		{ //runs when 6D is pressed and the angle won't hit the minimum (it resets to 0 when it does)
			currentAngle7 -= deltaAngle7;
			sleep(pause);
		}
		if(vexRT[Btn6U] == 1 && currentAngle7 < 127 - deltaAngle7)
		{ //runs when 6U is pressed and the angle won't hit the maximum
			currentAngle7 += deltaAngle7;
			sleep(pause);
		}
}

task main()
{
	while(true)
	{
		int boomControlIn = vexRT[Ch1]; //channel one, right joystick, left-right from -127 to 127
		int boomControlOut = 0;
		int motorControlInRight = vexRT[Ch2]; //channel two, right joystick, down-up from -127 to 127
		int motorControlOutRight = 0;
		int motorControlInLeft = vexRT[Ch3]; //channel three, left joystick, down-up from -127 to 127
		int motorControlOutLeft = 0;

		// ignore the joystick until it is at least halfway pushed
		// creates dead space
		if (boomControlIn < -63) {
			boomControlOut = boomControlIn + 63;

			if (SensorValue(boomMin) == 1) { //if limit "Min" switch is hit, motor turns off
				boomControlOut = 0;
			}
	  }
		else if (boomControlIn > 63) { //boom is going up
			boomControlOut = boomControlIn - 63;

			if (SensorValue(boomMax) == 1) { //if limit switch "Max" is hit, motor turns off
				boomControlOut = 0;
			}
		}
		else {
			boomControlOut  = 0;
		}
		if (motorControlInRight < -63) {
			motorControlOutRight = motorControlInRight + 63;
		}
		else if (motorControlInRight > 63) {
			motorControlOutRight = motorControlInRight - 63;
		}
		else {
			motorControlOutRight = 0;
		}

		if (motorControlInLeft < -63) {
			motorControlOutLeft = motorControlInLeft + 63;
		}
		else if (motorControlInLeft > 63) {
			motorControlOutLeft = motorControlInLeft - 63;
		}
		else {
			motorControlOutLeft = 0;
		}
		motor[leftMotor] = vexRT[Ch3]*k1;
		motor[rightMotor] = vexRT[Ch2]*k1;
		motor[boomMotor] = boomControlOut *k2 * 2; //vexRT[Ch1]*k2; (motor for arm)

		servoPort6();
		servoPort7();

		k1 = k2 = changeSpeedHold();

	}

}
