#define LEFT_CLK 4
#define LEFT_CW 5

#define RIGHT_CLK 6
#define RIGHT_CW 7

const int STEP = 1000;

//

void setup()
{
	digitalWrite(LEFT_CW, LOW);
	digitalWrite(RIGHT_CW, LOW);

	for(int i = 0; i < STEP; i++)
	{
	    digitalWrite(LEFT_CLK, HIGH);
	    digitalWrite(RIGHT_CLK, HIGH);
	    delay(1);
	    digitalWrite(LEFT_CLK, LOW);
	    digitalWrite(RIGHT_CLK, LOW);
	    delay(1);
	}
}

void loop()
{
	
}