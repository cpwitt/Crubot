#pragma config(Sensor, dgtl1, boomMax, sensorTouch) //Sensors
#pragma config(Sensor, dgtl2, boomMin, sensorTouch)
#pragma config(Motor,  port2, leftMotor, tmotorNomral, openLoop) //Motors
#pragma config(Motor,  port3, rightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4, boomMotor, tmotorNomral, openLoop, reversed)
#pragma config(Motor,  port6, servoA, tmotorNormal, openLoop) //Servos
#pragma config(Motor,  port7, servoB, tmotorNormal, openLoop)

float k1 = 1; //proportionality constant for relation of joystick and motor speed
float k2 = 0;

float currentAngle6 = 0;
float currentAngle7 = 0;
float deltaAngle6 = 1; //how much the angle changes each iteration
float deltaAngle7 = 1;
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
		motor[leftMotor] = vexRT[Ch3]*k1;
		motor[rightMotor] = vexRT[Ch2]*k1;
		motor[boomMotor] = vexRT[Ch3]*k2;

		servoPort6();
		servoPort7();

		kValues();
		/* if(SensorValue(boomMin) == 1 || SensorValue(boomMax == 1))
			{k2 = 0;} //if limit "Min" or "Max" switch is hit, motor turns off */
	}
}
