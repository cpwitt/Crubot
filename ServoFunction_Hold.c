#pragma config(Motor,  port7,  tmotorNormal, openLoop)

/* Different from the other method because the button is held down continuously
 * with small delays and small increments.
 */

int currentAngle = 0;

float deltaAngle = 0.5; //how much the angle changes each iteration
int pause = 10;  // delay between iterations
//ratio of deltaAngle & delay determines how fast the servo turns (50 degs/s right now)

task main()
{
	setServo(port7, currentAngle); //reset the servo to begin

	while(true)
	{

		if(vexRT[Btn6D] == 1 && currentAngle > -127 + deltaAngle)
		{ //runs when 6D is pressed and the angle won't hit the minimum (it resets to 0 when it does)
			currentAngle -= deltaAngle;
			wait1Msec(pause);
		}
		if(vexRT[Btn6U] == 1 && currentAngle < 127 - deltaAngle)
		{ //runs when 6U is pressed and the angle won't hit the maximum
			currentAngle += deltaAngle;
			wait1Msec(pause);
		}

		setServo(port7, currentAngle);
	}
}
