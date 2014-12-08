/*
	GliderLib is created to control the lighting effects,
	(and possibly some other things) for the OSC Glider
	Paper Air plane exhibit. 
	Created by Michael King, 12/8/2014
*/

#include "Arduino.h"
#include "GliderLib.h"

LEDPanel::LEDPanel(int LEDPin)
{
	pinMode(LEDPin, OUTPUT);
	//digitalWrite
	LEDPin_ = LEDPin;
	
}

void LEDPanel::turnOn()
{
	// first check to see if the panel is already on
	// this helps to prevent flicker
	uint8_t pinState = digitalRead(LEDPin_);
	if (!pinState){
		digitalWrite(LEDPin_, HIGH);
	}
}	

void LEDPanel::turnOff()
{
	// first check to see if the panel is already on
	// this helps to prevent flicker
	uint8_t pinState = digitalRead(LEDPin_);
	if (pinState){
		digitalWrite(LEDPin_, LOW);
	}	
}

void LEDPanel::setBrightness()
{
	//will need to write an analog write function
}