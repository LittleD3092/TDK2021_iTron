#include <TDK2021.h>
#include <Servo.h>
#include <PS2X_lib.h>
#include <SPI.h>
#include "RF24.h"
#include "Adafruit_Keypad.h"

//chassis motor
// #define chassis_DCMotorLeftIN1 2
// #define chassis_DCMotorLeftIN2 52
// #define chassis_DCMotorRightIN1 3
// #define chassis_DCMotorRightIN2 53

//flag grip
#define flagGrip_LinearActuator1IN1 8
#define flagGrip_LinearActuator1IN2 9
#define flagGrip_LinearActuator1PWM 2

#define flagGrip_LinearActuator2IN1 10
#define flagGrip_LinearActuator2IN2 11
#define flagGrip_LinearActuator2PWM 3

#define flagGrip_StepMotor1CLK 4
#define flagGrip_StepMotor1CW 5

#define flagGrip_StepMotor2CLK 6
#define flagGrip_StepMotor2CW 7

//ball grip
// #define ballGrip_StepMotorCLK 34
// #define ballGrip_StepMotorCW 35

// #define ballGrip_DCMotor1IN1 38
// #define ballGrip_DCMotor1IN2 39             
// #define ballGrip_DCMotor1PWM 9            

// #define ballGrip_DCMotor2IN1 40             
// #define ballGrip_DCMotor2IN2 41             
// #define ballGrip_DCMotor2PWM 10

// #define ballGrip_Servo1 8
// #define ballGrip_Servo1_OPEN_ANGLE 0
// #define ballGrip_Servo1_CLOSE_ANGLE 180

// //climb boost
// #define climbBoost_LinearActuatorIN1 29
// #define climbBoost_LinearActuatorIN2 31
// #define climbBoost_LinearActuatorPWM 7

// //ps2 controller
// #define PS2_DATA_PORT 48
// #define PS2_COMMAND_PORT 49
// #define PS2_ATTRIBUTE_PORT 50
// #define PS2_CLOCK_PORT 51
// #define SUPPORT_ANALOG_JOYSTICK true
// #define SUPPORT_VIBRATION true
// #define DEAD_AREA 5

// //nRF24L01
// #define PIN_CE 42
// #define PIN_CSN 43
// #define PA_LEVEL RF24_PA_LOW
// #define DATA_RATE RF24_2MBPS
// const byte ADDRESS[] = "1Node";
// byte PIPE = 1;
// #define FREQUENCY 2400

//number pad
/*const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = { {'1', '2', '3', 'A'},
						  {'4', '5', '6', 'B'},
						  {'7', '8', '9', 'C'},
						  {'*', '0', '#', 'D'} };
byte rowPins[ROWS] = {44, 45, 46, 47};
byte colPins[COLS] = {48, 49, 50, 51};*/






// TrackChassis chassis(chassis_DCMotorLeftIN1, chassis_DCMotorLeftIN2, chassis_DCMotorRightIN1, chassis_DCMotorRightIN2);

FlagGrip flaggrip(flagGrip_LinearActuator1IN1, flagGrip_LinearActuator1IN2, flagGrip_LinearActuator1PWM,
				  flagGrip_LinearActuator2IN1, flagGrip_LinearActuator2IN2, flagGrip_LinearActuator2PWM,
				  flagGrip_StepMotor1CLK, flagGrip_StepMotor1CW,
				  flagGrip_StepMotor2CLK, flagGrip_StepMotor2CW);

// BallGrip ballgrip(ballGrip_StepMotorCLK, ballGrip_StepMotorCW,
// 				  ballGrip_DCMotor1IN1, ballGrip_DCMotor1IN2, ballGrip_DCMotor1PWM,
// 				  ballGrip_DCMotor2IN1, ballGrip_DCMotor2IN2, ballGrip_DCMotor2PWM);

// Servo ballgripservo1;

// ClimbBoost climbboost(climbBoost_LinearActuatorIN1, climbBoost_LinearActuatorIN2, climbBoost_LinearActuatorPWM);

// PS2X ps2x;

// RF24 radio(PIN_CE, PIN_CSN);

//Adafruit_Keypad keypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );








void setup()
{
	//serial
	Serial.begin(9600);


	
	//ball grip servo
	// ballgripservo1.attach(ballGrip_Servo1);
 //    ballgripservo1.write(ballGrip_Servo1_OPEN_ANGLE);

    //ps2x config CAUTION: MUST FIND CONTROLLER
    // int error;
    // do
    // {  
    //     error = ps2x.config_gamepad(PS2_CLOCK_PORT, PS2_COMMAND_PORT, PS2_ATTRIBUTE_PORT, PS2_DATA_PORT, SUPPORT_ANALOG_JOYSTICK, SUPPORT_VIBRATION);
    //     if(error == 0)            Serial.println("Controller found");
    //     else if(error == 1)       Serial.println("ERROR: No Controller found");
    //     else if(error == 2)       Serial.println("ERROR: Controller not accepting command");
    //     else if(error == 3)       Serial.println("ERROR: Controller refusing to enter Pressures Mode, may not support it");
    // }while(error != 0);

    digitalWrite(flagGrip_StepMotor1CW, HIGH);
	digitalWrite(flagGrip_StepMotor2CW, HIGH);
	for(int i = 0; i < 6000; i++)
	{
		digitalWrite(flagGrip_StepMotor1CLK, HIGH);
		digitalWrite(flagGrip_StepMotor2CLK, HIGH);

		delay(1);

		digitalWrite(flagGrip_StepMotor1CLK, LOW);
		digitalWrite(flagGrip_StepMotor2CLK, LOW);

		delay(1);
	}
}

void loop()
{
	// digitalWrite(flagGrip_StepMotor1CW, LOW);
	// digitalWrite(flagGrip_StepMotor2CW, LOW);
	// for(int i = 0; i < 1000; i++)
	// {
	// 	digitalWrite(flagGrip_StepMotor1CLK, HIGH);
	// 	digitalWrite(flagGrip_StepMotor2CLK, HIGH);

	// 	delay(1);

	// 	digitalWrite(flagGrip_StepMotor1CLK, LOW);
	// 	digitalWrite(flagGrip_StepMotor2CLK, LOW);

	// 	delay(1);
	// }
	// delay(100);


	// digitalWrite(flagGrip_StepMotor1CW, HIGH);
	// digitalWrite(flagGrip_StepMotor2CW, HIGH);
	// for(int i = 0; i < 1000; i++)
	// {
	// 	digitalWrite(flagGrip_StepMotor1CLK, HIGH);
	// 	digitalWrite(flagGrip_StepMotor2CLK, HIGH);

	// 	delay(1);

	// 	digitalWrite(flagGrip_StepMotor1CLK, LOW);
	// 	digitalWrite(flagGrip_StepMotor2CLK, LOW);

	// 	delay(1);
	// }

}