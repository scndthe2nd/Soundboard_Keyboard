/*

Work In Progress.

This is using a super cheap Leonardo 6 pin setup, but could easily be used with
any 32u4 microcontroller board, I think. The MCP adds some extra inputs for 
buttons and other junk, maybe a display or funny LEDs or something.


::OPERATION::

Chris will select audio files via up and down buttons.

On Que, Chris presses the Select Button, which sends the command to play the 
audio file to the computer.

::Issues::
 
I know I could better use the board by having a dac or audio files directly on 
the board. This would solve some problems with latency. It would also mean that 

I'm using this particular keypad because I have it, not because it's the best 
way I could do this.

I also don't have any diodes or resistors for debouncing. This doesn't have
to be a problem, because of the 100K pulldown that's included on the MCP. I just
have to make sure I don't burn these out for whatever reason.


::CONCLUSIONS::
I could feasably work out a better scheme for a 'production level' device if i 
had some better components. As long as this is just a proof of concept and gets
us into a working space, I'll be happy enough.

*/
// CODED WITH INTENT FOR ATMEGA32u8. USE LEONARDO FOR ENCODING.


//PINS
const int outputPin = 13;
const int upButton = 1; // REASSIGN THIS PIN
const int downButton = 2; // REASSIGN THIS PIN
const int selectButton = 3; // REASSIGN THIS PIN

//FILE SELECTION
int fileSelect = 0;

//TIMER VALUES
unsigned long timeout = 0;

const long timerResetLength = 1000;

//BUTTON STATES
int upButtonState = LOW;
int downButtonState=LOW;
int ledState = LOW;
int selectButtonState=LOW;


void setup()
{
  	pinMode(outputPin, OUTPUT);  // outputPin for LED
	pinMode(upButton, INPUT); 
	pinMode(downButton, INPUT);
	pinMode(selectButton, INPUT);
}

void loop()
{
	
// TIMER FUNCTION
	unsigned long timer = millis();
	unsigned long timeout = 0;
	if (timer - timeout >= timerResetLength) {
			timeout = timer;
			blinkFunction(fileSelect);
	}
	
// BUTTON PRESSES
	if (upButtonState == HIGH){
		// IF BUTTON UP IS PRESSED
		// INCRIMENT FILE SELECT VARIABLE
		// DELAY 50 FOR DEBOUNCE
		// AND RESET THE BLINK TIMER
		fileSelect ++;
		delay(50);
		timeout = timer;
		blinkFunction(fileSelect);
	}
	if (downButtonState == HIGH){
		// IF BUTTON DOWN IS PRESSED
		// REDUCE FILE SELECT VARIABLE
		// DELAY 50 FOR DEBOUNCE
		// AND RESET THE BLINK TIMER
		fileSelect --;
		delay(50);
		timeout = timer;
		blinkFunction(fileSelect);
	}
	if (selectButtonState == HIGH) {
		// IF BUTTON SELECT IS PRESSED
		// SEND INFO TO COMPUTER AS KEYBOARD
		// DELAY 250 FOR DEBOUNCE AND ACCIDENTAL STEP
		// RESET THE BLINK TIMER
		// RESET FILE SELECT VARIABLE TO ZERO
		
    	Keyboard.println(fileSelect); // THIS HAS TO BE REDEFINED TO SEND ACTUAL KEYS
    	//Serial.println(fileSelect); // THIS WAS FOR TESTING VIA SERIAL
    	delay(250);
		timeout = timer;
    	fileSelect=0;
	}
	
	
	
} // LOOP END


// BLINK FUNCTION
// INSERT NUMBER OF BLINKS
int blinkFunction(int y){
	for(int x=0; x<y; x++){
		// DEFINE TIMER, INTERVAL AND CURRENT TIME
		unsigned long currentMillis = millis();
		unsigned long previousMillis = 0;
		const long interval = 50;
		// IF THE CURRENT TIME IS 
		if (currentMillis - previousMillis >= interval) {
			previousMillis = currentMillis;
			if (ledState == LOW) {
				ledState = HIGH;
				}
				else {
				ledState = LOW;
			}
		}
	}
}
