/*
	GliderLib is created to control the lighting effects,
	(and possibly some other things) for the OSC Glider
	Paper Air plane exhibit. 
	Created by Michael King, 12/8/2014
*/


#ifndef GliderLib_h
#define GliderLib_h

#include "Arduino.h"
#define BRIGHT_LVL_EEPROM 0 // Location of the global brightness Level

class LEDPanel				// This is a class essentially to control a lot of
{							// LED panels on an exhibit.
	public:
		LEDPanel(int LEDPin);
		void turnOn();
		void turnOff();
		void updateBrightness();
		void setMaxBrightness();		

	private:
		uint8_t LEDPin_;
		uint8_t pinState_;
		uint8_t brightLevel_; 
		uint8_t runningBrightness_;

};	


void DigitalSignageCtrl();


void DisplayPwrCtrl();

#endif