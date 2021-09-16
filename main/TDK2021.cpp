#include <Arduino.h>
#include "TDK2021.h"
#include <math.h>

TrackChassis::TrackChassis(int leftWheelIN1, int leftWheelIN2, 
					 	   int rightWheelIN1, int rightWheelIN2)
{
	pinMode(leftWheelIN1, OUTPUT);
	pinMode(leftWheelIN2, OUTPUT);

	pinMode(rightWheelIN1, OUTPUT);
	pinMode(rightWheelIN2, OUTPUT);

	_leftWheelIN1 = leftWheelIN1;
	_leftWheelIN2 = leftWheelIN2;
	_rightWheelIN1 = rightWheelIN1;
	_rightWheelIN2 = rightWheelIN2;
}

void TrackChassis::move(int leftSpeed, int rightSpeed)
{
	int leftSpeed_inRange;
	int rightSpeed_inRange;

	//modify speed between range -255 255
	leftSpeed_inRange = inRangePM255(leftSpeed);		
	rightSpeed_inRange = inRangePM255(rightSpeed);		

	//set speed
	analogWrite(_leftWheelIN1, abs(leftSpeed_inRange) );
	analogWrite(_rightWheelIN1, abs(rightSpeed_inRange) );

	//set direction
	digitalWrite(_leftWheelIN2, (leftSpeed_inRange >= 0) );
	digitalWrite(_rightWheelIN2, (rightSpeed_inRange <= 0) );
}

int TrackChassis::inRangePM255(int number)
{
	if(number >= 256)
		number = 255;
	else if(number <= -256)
		number = -255;


	return number;
}

FlagGrip::FlagGrip(int zAxisNO1IN1, int zAxisNO1IN2, int zAxisNO1PWM, 
			       int zAxisNO2IN1, int zAxisNO2IN2, int zAxisNO2PWM, 
			       int yAxisNO1CLK, int yAxisNO1CW,
			       int yAxisNO2CLK, int yAxisNO2CW)
{
	pinMode(zAxisNO1IN1, OUTPUT);
	pinMode(zAxisNO1IN2, OUTPUT);
	pinMode(zAxisNO1PWM, OUTPUT);

	pinMode(zAxisNO2IN1, OUTPUT);
	pinMode(zAxisNO2IN2, OUTPUT);
	pinMode(zAxisNO2PWM, OUTPUT);

	pinMode(yAxisNO1CLK, OUTPUT);
	pinMode(yAxisNO1CW, OUTPUT);

	pinMode(yAxisNO2CLK, OUTPUT);
	pinMode(yAxisNO2CW, OUTPUT);

	_zAxisNO1IN1 = zAxisNO1IN1;
	_zAxisNO1IN2 = zAxisNO1IN2;
	_zAxisNO1PWM = zAxisNO1PWM;

	_zAxisNO2IN1 = zAxisNO2IN1;
	_zAxisNO2IN2 = zAxisNO2IN2;
	_zAxisNO2PWM = zAxisNO2PWM;

	_yAxisNO1CLK = yAxisNO1CLK;
	_yAxisNO1CW = yAxisNO1CW;
	
	_yAxisNO2CLK = yAxisNO2CLK;
	_yAxisNO2CW = yAxisNO2CW;
}

void FlagGrip::move(int stepy, int vz)
{
	if(vz > 255)		vz = 255;
	if(vz < -255)		vz = -255;


	if(stepy >= 0)
	{
		digitalWrite(_yAxisNO1CW, LOW);
		digitalWrite(_yAxisNO2CW, LOW);
		for(int i = 0; i < stepy; i++)
		{
			digitalWrite(_yAxisNO1CLK, HIGH);
			digitalWrite(_yAxisNO2CLK, HIGH);
			delay(100);
			digitalWrite(_yAxisNO1CLK, LOW);
			digitalWrite(_yAxisNO2CLK, LOW);
			delay(100);
		}
	}
	else
	{
		digitalWrite(_yAxisNO1CW, HIGH);
		digitalWrite(_yAxisNO2CW, HIGH);
		for(int i = 0; i < stepy; i++)
		{
			digitalWrite(_yAxisNO1CLK, HIGH);
			digitalWrite(_yAxisNO2CLK, HIGH);
			delay(100);
			digitalWrite(_yAxisNO1CLK, LOW);
			digitalWrite(_yAxisNO2CLK, LOW);
			delay(100);
		}
	}


	if(vz >= 0)
	{
		analogWrite(_zAxisNO1PWM, vz);
		digitalWrite(_zAxisNO1IN1, HIGH);
		digitalWrite(_zAxisNO1IN2, LOW);

		analogWrite(_zAxisNO2PWM, vz);
		digitalWrite(_zAxisNO2IN1, HIGH);
		digitalWrite(_zAxisNO2IN2, LOW);
	}
	else
	{
		int tempv = -vz;
		analogWrite(_zAxisNO1PWM, tempv);
		digitalWrite(_zAxisNO1IN1, LOW);
		digitalWrite(_zAxisNO1IN2, HIGH);

		analogWrite(_zAxisNO2PWM, tempv);
		digitalWrite(_zAxisNO2IN1, LOW);
		digitalWrite(_zAxisNO2IN2, HIGH);
	}
}

BallGrip::BallGrip(int yAxisCLK, int yAxisCW, 
				   int zAxisNO1IN1, int zAxisNO1IN2, int zAxisNO1PWM,
				   int zAxisNO2IN1, int zAxisNO2IN2, int zAxisNO2PWM)
{
	pinMode(yAxisCLK, OUTPUT);
	pinMode(yAxisCW, OUTPUT);

	pinMode(zAxisNO1IN1, OUTPUT);
	pinMode(zAxisNO1IN2, OUTPUT);
	pinMode(zAxisNO1PWM, OUTPUT);

	pinMode(zAxisNO2IN1, OUTPUT);
	pinMode(zAxisNO2IN2, OUTPUT);
	pinMode(zAxisNO2PWM, OUTPUT);

	_yAxisCLK = yAxisCLK;
	_yAxisCW = yAxisCW;

	_zAxisNO1IN1 = zAxisNO1IN1;
	_zAxisNO1IN2 = zAxisNO1IN2;
	_zAxisNO1PWM = zAxisNO1PWM;

	_zAxisNO2IN1 = zAxisNO2IN1;
	_zAxisNO2IN2 = zAxisNO2IN2;
	_zAxisNO2PWM = zAxisNO2PWM;
}

void BallGrip::move(int stepy, int vz)
{
	if(vz > 255)		vz = 255;
	if(vz < -255)		vz = -255;

	if(vz >= 0)
	{
		digitalWrite(_zAxisNO1IN1, HIGH);
		digitalWrite(_zAxisNO1IN2, LOW);
		analogWrite(_zAxisNO1PWM, vz);

		digitalWrite(_zAxisNO2IN1, HIGH);
		digitalWrite(_zAxisNO2IN2, LOW);
		analogWrite(_zAxisNO2PWM, vz);
	}
	else
	{
		int tempv = -vz;
		digitalWrite(_zAxisNO1IN1, LOW);
		digitalWrite(_zAxisNO1IN2, HIGH);
		analogWrite(_zAxisNO1PWM, tempv);

		digitalWrite(_zAxisNO2IN1, LOW);
		digitalWrite(_zAxisNO2IN2, HIGH);
		analogWrite(_zAxisNO2PWM, tempv);
	}

	if(stepy >= 0)
	{
		digitalWrite(_yAxisCW, LOW);
		for(int i = 0; i < stepy; i++)
		{
			digitalWrite(_yAxisCLK, HIGH);
			delay(100);
			digitalWrite(_yAxisCLK, LOW);
			delay(100);
		}
	}
	else
	{
		digitalWrite(_yAxisCW, HIGH);
		for(int i = 0; i < -stepy; i++)
		{
			digitalWrite(_yAxisCLK, HIGH);
			delay(100);
			digitalWrite(_yAxisCLK, LOW);
			delay(100);
		}
	}
}

ClimbBoost::ClimbBoost(int pushIN1, int pushIN2, int pushPWM)
{
	pinMode(pushIN1, OUTPUT);
	pinMode(pushIN2, OUTPUT);
	pinMode(pushPWM, OUTPUT);

	_pushIN1 = pushIN1;
	_pushIN2 = pushIN2;
	_pushPWM = pushPWM;
}

void ClimbBoost::push()
{
	digitalWrite(_pushIN1, HIGH);
	digitalWrite(_pushIN2, LOW);
	analogWrite(_pushPWM, 255);
}

void ClimbBoost::pull()
{
	digitalWrite(_pushIN1, LOW);
	digitalWrite(_pushIN2, HIGH);
	analogWrite(_pushPWM, 255);
}