/*
	GliderLib is created to control the lighting effects,
	(and possibly some other things) for the OSC Glider
	Paper Air plane exhibit. 
	Created by Michael King, 12/8/2014
*/


#ifndef GliderLib_h
#define GliderLib_h

#include "Arduino.h"

class LEDPanel
{
	public:
		LEDPanel(int LEDPin);
		void turnOn();
		void turnOff();
		void setBrightness();
		void setMaxBrightness();
	
	private:
		int LEDPin_;
};	

#endif