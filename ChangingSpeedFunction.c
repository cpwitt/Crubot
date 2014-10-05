#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  port7,  tmotorNormal, openLoop)

float k = 1;
float lowSpeed = 0.2;

float changeSpeed()
{
		if(vexRT[Btn5D] == 1)
		{
			if(k == 1)
			{ return lowSpeed; }
			if(k == lowSpeed)
			{ return 1; }
		}
		else
		{ return 1;}
}

task main ()
{
  while(1 == 1)
  {
  	k = changeSpeed();
    motor[leftMotor]  = vexRT[Ch3]*k;
    motor[rightMotor] = vexRT[Ch2]*k;
  }
}
