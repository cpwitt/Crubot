#pragma config(Sensor, dgtl1, boomMax, sensorTouch) //Sensors
#pragma config(Sensor, dgtl2, boomMin, sensorTouch)
#pragma config(Motor,  port2, leftMotor, tmotorNomral, openLoop) //Motors
#pragma config(Motor,  port3, rightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4, boomMotor, tmotorNomral, openLoop, reversed)
#pragma config(Motor,  port6, wristServo, tmotorNormal, openLoop) //Servos
#pragma config(Motor,  port7, clawServo, tmotorNormal, openLoop)

float k1 = 1; //proportionality constant for relation of joystick and motor speed
float k2 = 0;

float currentWristAngle = 0;
float currentClawAngle = 0;
float deltaWristAngle = 1; //how much the angle changes each iteration
float deltaClawAngle = 1;
int pause = 4;  // delay between iterations
//ratio of deltaAngle & delay determines how fast the servo turns (50 degs/s right now)

//increases the speed only when Btn5D is held down

void kValues()
{
	k1 = 1;
	k2 = 0;
	if(vexRT[Btn5D] == 1)
	{ //wheels are slowed down
		k1 = 0.3;
		k2 = 0;
	}
	if(vexRT[Btn8R] == 1)
	{ //boom turned on, wheels off
		k1 = 0;
		k2 = 1;
	}
}

void wristServoMove()
{
	motor[wristServo] = currentWristAngle;
	if(vexRT[Btn8D] == 1 && currentWristAngle > -127 + deltaWristAngle)
	{ //runs when 5D is pressed and the angle won't hit the minimum (it resets to 0 when it does)
		currentWristAngle -= deltaWristAngle;
		sleep(pause);
	}
	if(vexRT[Btn8U] == 1 && currentWristAngle < 127 - deltaWristAngle)
	{ //runs when 5U is pressed and the angle won't hit the maximum
		currentWristAngle += deltaWristAngle;
		sleep(pause);
	}
}

void clawServoMove()
{
	motor[clawServo] = currentClawAngle;
	if(vexRT[Btn6D] == 1 && currentClawAngle > -127 + deltaClawAngle)
	{ //runs when 6D is pressed and the angle won't hit the minimum (it resets to 0 when it does)
		currentClawAngle -= deltaClawAngle;
		sleep(pause);
	}
	if(vexRT[Btn6U] == 1 && currentClawAngle < 127 - deltaClawAngle)
	{ //runs when 6U is pressed and the angle won't hit the maximum
		currentClawAngle += deltaClawAngle;
		sleep(pause);
	}
}

void checkSensors()
{
//	if(SensorValue(boomMin) == 1 && vexRT[Ch3]<0)
//	{ k2=0; }
	if(SensorValue(boomMin) == 1 && vexRT[Ch3]<0)
	{
		k2 = 0;
	}
	if(SensorValue(boomMax) == 1 && vexRT[Ch3]>0)
	{
		k2 = 0;
	}
}
task main()
{
	while(true)
	{
		motor[leftMotor] = vexRT[Ch3]*k1;
		motor[rightMotor] = vexRT[Ch2]*k1;
		motor[boomMotor] = vexRT[Ch3]*k2;

		wristServoMove();
		clawServoMove();

		kValues();
		checkSensors();
	}
}
