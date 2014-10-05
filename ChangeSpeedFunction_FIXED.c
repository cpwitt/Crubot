#pragma config(Motor, port2, leftMotor, tmotorNormal, openLoop)
#pragma config(Motor, port3, rightMotor, tmotorNormal, openLoop, reversed)

/* Two methods for controlling speed of the motors. One requires a press to change
 * speed and the other you hold down continuously (this is the one commented out).
 */

float k=1; //proportionality constant for relation of joystick and motor speed

/*
bool slowed = false;
float slowedDown = 0.3;

 //Changes speed back and forth with a click
float changeSpeedClick()
{
	if(vexRT[Btn5D] == 1 && !slowed)
		{
			slowed = !slowed;
			return slowedDown;
		}
	if(vexRT[Btn5D] == 1 && slowed)
		{
			slowed = !slowed;
			return 1;
		}
	else {
		return k; }
}
*/

//changes the speed only when Btn5D is held down
float changeSpeedHold()
{
	if(vexRT[Btn5D] == 1)
		{ return 0.3; }
	else
		{ return 1;}
}

task main()
{
	while(true)
	{
		motor[leftMotor] = vexRT[Ch3]*k;
		motor[rightMotor] = vexRT[Ch2]*k;

		k = changeSpeedHold();
		//k = changeSpeedClick();
	}

}
