#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  port7,  tmotorNormal, openLoop)

int currentAngle = 0;
int deltaAngle = 5;

task main()
{
	setServo(port7, currentAngle);
	while(true)
	{
		setServo(port7, currentAngle);
		if(vexRT[Btn6D] == 1 && currentAngle > -125)
		{
			currentAngle -= deltaAngle;
			while(vexRT[Btn6D] == 1) {}
		}
		if(vexRT[Btn6U] == 1 && currentAngle < 125)
		{
			currentAngle += deltaAngle;
			while(vexRT[Btn6U] == 1) {}
		}

		if(vexRT[Btn8U] == 1)
		{
			deltaAngle = 20;
		}


	}


	}
