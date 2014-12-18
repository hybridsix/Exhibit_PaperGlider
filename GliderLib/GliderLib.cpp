/*
	GliderLib is created to control the lighting effects,
	(and possibly some other things) for the OSC Glider
	Paper Air plane exhibit. 
	Created by Michael King, 12/8/2014
*/

#include "Arduino.h"
#include "GliderLib.h"
#include "EEPROM.h"

LEDPanel::LEDPanel(int LEDPin)
{
	//digitalWrite
	LEDPin_ = LEDPin;
	pinMode(LEDPin, OUTPUT);
	brightLevel_ = EEPROM.read(BRIGHT_LVL_EEPROM); // Set the usable current brightness to eeprom val	
}

void LEDPanel::turnOn(){
	// first check to see if the panel is already on
	// this helps to prevent flicker
	pinState_ = digitalRead(LEDPin_);
	if (!pinState_){
		//Serial.println("setting to high");
		analogWrite(LEDPin_, brightLevel_);
	}
}	

void LEDPanel::turnOff(){
	// first check to see if the panel is already on
	// this helps to prevent flicker
	pinState_ = digitalRead(LEDPin_);
	if (pinState_){
		//Serial.println("setting to LOW");
		analogWrite(LEDPin_, LOW);
	}	
}

void LEDPanel::updateBrightness(int runningBrightness){
	//will need to write an analog write function
	runningBrightness_ = runningBrightness;
	analogWrite(LEDPin_, runningBrightness_);
}