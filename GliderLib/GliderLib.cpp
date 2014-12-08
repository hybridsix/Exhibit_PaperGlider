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
	//digitalWrite
	LEDPin_ = LEDPin;
	pinMode(LEDPin, OUTPUT);	
}

void LEDPanel::turnOn()
{
	// first check to see if the panel is already on
	// this helps to prevent flicker
	pinState_ = digitalRead(LEDPin_);
	if (!pinState_){
		digitalWrite(LEDPin_, HIGH);
	}
}	

void LEDPanel::turnOff()
{
	// first check to see if the panel is already on
	// this helps to prevent flicker
	pinState_ = digitalRead(LEDPin_);
	if (pinState_){
		digitalWrite(LEDPin_, LOW);
	}	
}

void LEDPanel::setBrightness()
{
	//will need to write an analog write function
}