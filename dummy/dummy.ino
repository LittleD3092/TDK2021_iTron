#include "iTron_controller.h"
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = { { '1', '2', '3', 'A' },
						  { '4', '5', '6', 'B' },
						  { '7', '8', '9', 'C' },
						  { '*', '0', '#', 'D' } };
byte rowPins[ROWS] = { 35, 37, 39, 41 };
byte colPins[COLS] = { 43, 45, 47, 49 };
//Adafruit_Keypad keypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
*/

#define pinCE 23
#define pinCSN 25
RF24 radio(pinCE, pinCSN);
#define PALEVEL RF24_PA_LOW
#define DATARATE RF24_2MBPS
const byte ADDRESS[] = "1Node";
#define FREQUENCY 2400








void setup()
{
	//intialize all stuff
	//keypad.begin();

	radio.begin();
	radio.setPALevel( PALEVEL );
	radio.setDataRate( DATARATE );
	radio.openWritingPipe( ADDRESS );
	radio.stopListening();

	Serial.begin(9600);

	Serial1.begin(9600);

	radio.setChannel( FREQUENCY - 2400 );
}

void loop()
{
	byte status[11] = {0};


	//chassis go front
	status[9] = 0b00010000;
	//transmit message through radio
	Serial.println("transmitting backward signal through radio");
	radio.write( &status, sizeof( status ) );
	//transmit message through serial1
	Serial.println("transmitting foward signal through serial");
	Serial1.write( status, sizeof( status ) );
	delay(1000);

	Serial.println();

	//chassis go back
	status[9] = 0b01000000;
	//transmit message through radio
	Serial.println("transmitting backward signal through radio");
	radio.write( &status, sizeof( status ) );
	//transmit message through serial1
	Serial.println("transmitting backward signal through serial");
	Serial1.write( status, sizeof( status ) );
	delay(1000);

	Serial.println("");
}