/*
	GliderLib is created to control the lighting effects,
	(and possibly some other things) for the OSC Glider
	Paper Air plane exhibit. 
	Created by Michael King, 12/8/2014
*/

#include "Arduino.h"
#include "GliderLib.h"
#include "EEPROM.h"

LEDPanel::LEDPanel(uint8_t LEDPin, String objName)
{
	//digitalWrite
	LEDPin_ = LEDPin;
	objName_ = objName; 
	pinMode(LEDPin, OUTPUT);
	brightLevel_ = EEPROM.read(BRIGHT_LVL_EEPROM); // Set the usable current brightness to eeprom val	
		Serial.print("Object ");
		Serial.print(objName_);
		Serial.print(" EEPROM Read Level:  ");	
		Serial.println(brightLevel_);
}

void LEDPanel::turnOn(){
	// first check to see if the panel is already on
	// this helps to prevent flicker
	//pinState_ = digitalRead(LEDPin_);
	//if (!pinState_){
		Serial.print("Setting ");
		Serial.print(objName_);
		Serial.print(" to on - last level");
		analogWrite(LEDPin_, brightLevel_);
	//}
}	

void LEDPanel::turnOff(){
	// first check to see if the panel is already on
	// this helps to prevent flicker
//	pinState_ = digitalRead(LEDPin_);
//	if (pinState_){
		Serial.print("Setting ");
		Serial.print(objName_);
		Serial.print(" to off / LOW");
		digitalWrite(LEDPin_, LOW);
//	}	
}

void LEDPanel::updateBrightness(uint8_t runningBrightness){
	//will need to write an analog write function
	runningBrightness_ = runningBrightness;
	analogWrite(LEDPin_, runningBrightness_);
		Serial.print("Setting ");
		Serial.print(objName_);
		Serial.print(" to brightness level ");
		Serial.println(runningBrightness_);
}
