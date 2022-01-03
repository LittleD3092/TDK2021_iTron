#ifndef _TDK2021_H_
#define _TDK2021_H_


#include <Arduino.h>

class TrackChassis 
{
	public:
		TrackChassis(int leftWheelIN1, int leftWheelIN2,
					 int rightWheelIN1, int rightWheelIN2);
		void move(int leftSpeed, int rightSpeed);

	private:
		int inRangePM255(int number);

		int _leftWheelIN1;				//speed
		int _leftWheelIN2;				//direc
		int _rightWheelIN1;				//speed
		int _rightWheelIN2;				//direc
};

class FlagGrip
{
	public:
		FlagGrip(int zAxisNO1IN1, int zAxisNO1IN2, int zAxisNO1PWM, 
			     int zAxisNO2IN1, int zAxisNO2IN2, int zAxisNO2PWM, 
			     int yAxisNO1IN1, int yAxisNO1IN2, int yAxisNO1PWM, 
				 int yAxisNO2IN1, int yAxisNO2IN2, int yAxisNO2PWM);
		void move(int vy, int vz);

	private:
		//up & down
		int _zAxisNO1IN1;
		int _zAxisNO1IN2;
		int _zAxisNO1PWM;

		int _zAxisNO2IN1;
		int _zAxisNO2IN2;
		int _zAxisNO2PWM;

		//foward backward NO.1
		int _yAxisNO1IN1;
		int _yAxisNO1IN2;
		int _yAxisNO1PWM;
		//NO.2
		int _yAxisNO2IN1;
		int _yAxisNO2IN2;
		int _yAxisNO2PWM;

};

class BallGrip
{
	public:
		BallGrip(int yAxisIN1, int yAxisIN2, int yAxisPWM, 
				     int zAxisNO1IN1, int zAxisNO1IN2, int zAxisNO1PWM, 
				     int zAxisNO2IN1, int zAxisNO2IN2, int zAxisNO2PWM);
		void move(int vy, int vz);

	private:
		int _yAxisIN1;
		int _yAxisIN2;
    int _yAxisPWM;

		int _zAxisNO1IN1;
		int _zAxisNO1IN2;
		int _zAxisNO1PWM;

		int _zAxisNO2IN1;
		int _zAxisNO2IN2;
		int _zAxisNO2PWM;
};

class ClimbBoost
{
	public:
		ClimbBoost(int pushIN1, int pushIN2, int pushPWM);

		void push();
		void pull();
    void stop();

	private:
		int _pushIN1;
		int _pushIN2;
		int _pushPWM;
};


#endif
