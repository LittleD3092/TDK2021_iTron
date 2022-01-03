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
	digitalWrite(_leftWheelIN2, (leftSpeed_inRange < 0) );
	digitalWrite(_rightWheelIN2, (rightSpeed_inRange > 0) );
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
			       int yAxisNO1IN1, int yAxisNO1IN2, int yAxisNO1PWM,
			       int yAxisNO2IN1, int yAxisNO2IN2, int yAxisNO2PWM)
{
	pinMode(zAxisNO1IN1, OUTPUT);
	pinMode(zAxisNO1IN2, OUTPUT);
	pinMode(zAxisNO1PWM, OUTPUT);

	pinMode(zAxisNO2IN1, OUTPUT);
	pinMode(zAxisNO2IN2, OUTPUT);
	pinMode(zAxisNO2PWM, OUTPUT);

	pinMode(yAxisNO1IN1, OUTPUT);
	pinMode(yAxisNO1IN2, OUTPUT);
	pinMode(yAxisNO1PWM, OUTPUT);

	pinMode(yAxisNO2IN1, OUTPUT);
	pinMode(yAxisNO2IN2, OUTPUT);
	pinMode(yAxisNO2PWM, OUTPUT);

	_zAxisNO1IN1 = zAxisNO1IN1;
	_zAxisNO1IN2 = zAxisNO1IN2;
	_zAxisNO1PWM = zAxisNO1PWM;

	_zAxisNO2IN1 = zAxisNO2IN1;
	_zAxisNO2IN2 = zAxisNO2IN2;
	_zAxisNO2PWM = zAxisNO2PWM;

	_yAxisNO1IN1 = yAxisNO1IN1;
	_yAxisNO1IN2 = yAxisNO1IN2;
	_yAxisNO1PWM = yAxisNO1PWM;

	_yAxisNO2IN1 = yAxisNO2IN1;
	_yAxisNO2IN2 = yAxisNO2IN2;
	_yAxisNO2PWM = yAxisNO2PWM;
}

void FlagGrip::move(int vy, int vz)
{
	if(vz > 255)		vz = 255;
	if(vz < -255)		vz = -255;

	digitalWrite(_yAxisNO1IN1, vy > 0);
	digitalWrite(_yAxisNO1IN2, vy < 0);
	analogWrite(_yAxisNO1PWM, abs( vy ) );

	digitalWrite(_yAxisNO2IN1, vy > 0);
	digitalWrite(_yAxisNO2IN2, vy < 0);
	analogWrite(_yAxisNO2PWM, abs( vy ) );

	if(vz >= 0)
	{
		analogWrite(_zAxisNO1PWM, vz);
		digitalWrite(_zAxisNO1IN1, LOW);
		digitalWrite(_zAxisNO1IN2, HIGH);

		analogWrite(_zAxisNO2PWM, vz);
		digitalWrite(_zAxisNO2IN1, LOW);
		digitalWrite(_zAxisNO2IN2, HIGH);
	}
	else
	{
		int tempv = -vz;
		analogWrite(_zAxisNO1PWM, tempv);
		digitalWrite(_zAxisNO1IN1, HIGH);
		digitalWrite(_zAxisNO1IN2, LOW);

		analogWrite(_zAxisNO2PWM, tempv);
		digitalWrite(_zAxisNO2IN1, HIGH);
		digitalWrite(_zAxisNO2IN2, LOW);
	}
}

BallGrip::BallGrip(int yAxisIN1, int yAxisIN2, int yAxisPWM,  
				           int zAxisNO1IN1, int zAxisNO1IN2, int zAxisNO1PWM,
				           int zAxisNO2IN1, int zAxisNO2IN2, int zAxisNO2PWM)
{
	pinMode(yAxisIN1, OUTPUT);
	pinMode(yAxisIN2, OUTPUT);
  	pinMode(yAxisPWM, OUTPUT);

	pinMode(zAxisNO1IN1, OUTPUT);
	pinMode(zAxisNO1IN2, OUTPUT);
	pinMode(zAxisNO1PWM, OUTPUT);

	pinMode(zAxisNO2IN1, OUTPUT);
	pinMode(zAxisNO2IN2, OUTPUT);
	pinMode(zAxisNO2PWM, OUTPUT);

	_yAxisIN1 = yAxisIN1;
	_yAxisIN2 = yAxisIN2;
  	_yAxisPWM = yAxisPWM;

	_zAxisNO1IN1 = zAxisNO1IN1;
	_zAxisNO1IN2 = zAxisNO1IN2;
	_zAxisNO1PWM = zAxisNO1PWM;

	_zAxisNO2IN1 = zAxisNO2IN1;
	_zAxisNO2IN2 = zAxisNO2IN2;
	_zAxisNO2PWM = zAxisNO2PWM;
}

void BallGrip::move(int vy, int vz)
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

	if(vy >= 0)
  {
    digitalWrite(_yAxisIN1, HIGH);
    digitalWrite(_yAxisIN2, LOW);
    analogWrite(_yAxisPWM, vy);
  }
  else
  {
    int tempv = -vy;
    digitalWrite(_yAxisIN1, LOW);
    digitalWrite(_yAxisIN2, HIGH);
    analogWrite(_yAxisPWM, tempv);
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

void ClimbBoost::stop()
{
  digitalWrite(_pushIN1, LOW);
  digitalWrite(_pushIN2, LOW);
  analogWrite(_pushPWM, 0);
}
