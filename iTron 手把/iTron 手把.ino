#include "Adafruit_Keypad.h"
#include "iTron_controller.h"
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



Potentiometer potentiometer_R1(A7);
Potentiometer potentiometer_R2(A6);
Potentiometer potentiometer_R3(A5);
Potentiometer potentiometer_R16(A4);

Key key1(24);
Key key2(28);
Key key3(32);
Key key4(36);
Key key5(22);
Key key6(26);
Key key7(30);
Key key8(34);

const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = { { '1', '2', '3', 'A' },
						  { '4', '5', '6', 'B' },
						  { '7', '8', '9', 'C' },
						  { '*', '0', '#', 'D' } };
byte rowPins[ROWS] = { 35, 37, 39, 41 };
byte colPins[COLS] = { 43, 45, 47, 49 };
Adafruit_Keypad keypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define pinCE 23
#define pinCSN 25
RF24 radio(pinCE, pinCSN);
#define PALEVEL RF24_PA_LOW
#define DATARATE RF24_2MBPS
const byte ADDRESS[] = "1Node";
#define FREQUENCY 2400

KY023 leftStick(A0, A1, 27);
KY023 rightStick(A2, A3, 29);

ToggleSwitch leftToggle(31);
ToggleSwitch rightToggle(33);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);








void setup()
{
	//intialize all stuff
	keypad.begin();

	radio.begin();
	radio.setPALevel( PALEVEL );
	radio.setDataRate( DATARATE );
	radio.openWritingPipe( ADDRESS );
	radio.stopListening();

	Serial1.begin(9600);

	radio.setChannel( FREQUENCY - 2400 );
}

void loop()
{
	//show manual
	//read all stuff
	byte status[11] = {0};		
	//---
	//potentiometer
	//2 * 4         = 8 byte (0~7)
	//---
	//key
	//8 bit         = 1 byte (8)
	//---
	//ky023
	//4 bit + 4 bit = 1 byte (9)
	//---
	//toggleswitch
	//1 bit + 1 bit = 1 byte (10)
	//---
	status[0] += ( potentiometer_R1.read()  / 256 );
	status[1] += ( potentiometer_R1.read()  % 256 );
	status[2] += ( potentiometer_R2.read()  / 256 );
	status[3] += ( potentiometer_R2.read()  % 256 );
	status[4] += ( potentiometer_R3.read()  / 256 ); 
	status[5] += ( potentiometer_R3.read()  % 256 );
	status[6] += ( potentiometer_R16.read() / 256 );
	status[7] += ( potentiometer_R16.read() % 256 );

	status[8] += ( key1.read() * 128 );
	status[8] += ( key2.read() * 64  );
	status[8] += ( key3.read() * 32  );
	status[8] += ( key4.read() * 16  );
	status[8] += ( key5.read() * 8   );
	status[8] += ( key6.read() * 4   );
	status[8] += ( key7.read() * 2   );
	status[8] += ( key8.read() * 1   );

	status[9] += ( leftStick.readdir() * 16 );
	status[9] += ( rightStick.readdir() );

	status[10] += ( leftToggle.read() * 128 );
	status[10] += ( rightToggle.read() * 64 );


	//transmit message through radio
	radio.write( &status, sizeof( status ) );

	//transmit message through serial1
	Serial1.write( &status, sizeof( status ) );

	delay(50);
}