/* Paper airplane Exhibit (Glider) main control software
  mainly used to turn the exhibit on and off, and to set brightness
*/

/***********************************************************
*                         INCLUDES                         *
***********************************************************/
#include <EEPROM.h>
#include <GliderLib.h>



/***********************************************************
*                         DEFINES                          *
***********************************************************/
#define BRIGHT_LVL_EEPROM     0		// Memory address for eeprom
#define PWM_PIN3              3     // pin mapping for panel control. Section A is closest 
#define PWM_PIN5              5     // to launchers, section C is furthest. L/R is from
#define PWM_PIN6              6     // user POV.
#define PWM_PIN9              9		
#define PWM_PIN10             10
#define PWM_PIN11             11	// end pin mapping for PWM
#define DIAG_PIN              13	// onboard LED Diag
#define REMOTE_A_PIN          A0	// next 4 pins are for the remote input
#define REMOTE_B_PIN          A1	// they are reversed on the receiver board (as normal)
#define REMOTE_C_PIN          A2
#define REMOTE_D_PIN          A3
#define BRIGHT_INCRIMENT_VAL  25	// set how many "steps" of brightness you'll have

/***********************************************************
*                      GLOBAL VARS                         *
***********************************************************/
uint8_t  remoteBtnA_state = 0;       // Init variables and Set initial button states
uint8_t  remoteBtnB_state = 0;       // Init variables and Set initial button states
uint8_t  remoteBtnC_state = 0;       // Init variables and Set initial button states
uint8_t  remoteBtnD_state = 0;       // Init variables and Set initial button states
uint8_t  systemState      = 0;       // Used to track system intended state for light control
uint8_t  runningBrightVal;

//LED Panel/GliderLib Object Inits
LEDPanel Panel_AL (PWM_PIN3,  "AL");		// panels are labeled according to section 
LEDPanel Panel_AR (PWM_PIN5,  "AR");       // on the glider. A, B, C sections
LEDPanel Panel_BL (PWM_PIN6,  "BL");       // Section A is closest to launchers          	
LEDPanel Panel_BR (PWM_PIN9,  "BR");       // Then its just Left/right (from user pos)      
LEDPanel Panel_CL (PWM_PIN10, "CL");              
LEDPanel Panel_CR (PWM_PIN11, "CR");

/***********************************************************
*                          SETUP                           *
***********************************************************/
void setup(){
	digitalWrite(DIAG_PIN, HIGH);
		Serial.begin(9600);
		runningBrightVal = EEPROM.read(BRIGHT_LVL_EEPROM); // Set the usable current brightness to eeprom val	
		delay(1000);
	digitalWrite(DIAG_PIN, LOW);
}


/***********************************************************
*                          LOOP                            *
***********************************************************/
void loop(){
  readRemoteButtonStates() ;
  
  if (remoteBtnA_state){            // If A button is being pressed
    Serial.println("Remote Button A Detected");
      startUp();                    // run the startUp function
  }

  if (remoteBtnB_state){            // If D button is being pressed
    Serial.println("Remote Button D Detected");
      toggleBrightness();           // toggles through brightness values
  }

  if (remoteBtnC_state){            // If D button is being pressed
    Serial.println("Remote Button D Detected");
      shutDown();                   // run the shutDown function
	  brightLevelWrite();			// write brigthness value to eeprom
  }

  if (remoteBtnD_state){            // If D button is being pressed
    Serial.println("Remote Button D Detected");
      shutDown();                   // run the shutDown function
	  brightLevelWrite();			// write brigthness value to eeprom
	  }
  
}

/***********************************************************
*                 readRemoteButtonStates                   *
***********************************************************/
void readRemoteButtonStates(){
  // Read both digitial inputs for the RF remote buttons and store as state
	remoteBtnA_state = digitalRead(REMOTE_A_PIN);
	remoteBtnB_state = digitalRead(REMOTE_B_PIN);
	remoteBtnC_state = digitalRead(REMOTE_C_PIN);
	remoteBtnD_state = digitalRead(REMOTE_D_PIN);
}

/***********************************************************
*                        startUp                           *
***********************************************************/
void startUp(){                      // system start up sequence
	digitalWrite(DIAG_PIN, HIGH);
	Serial.println("Startup sequence started");
		void turnAllPanelsOn();	
		delay(5000);
	digitalWrite(DIAG_PIN, LOW);
  
  systemState = 1;                // Set the system state representation to on


 }
 
/***********************************************************
*                       shutDown                           *
***********************************************************/
void shutDown(){

	Serial.println("Shutdown sequence started");

  // Activates the onboard LED to show that the system is busy. 
  // also pauses for 5 seconds to make sure there are not repeat remote commands sent
		digitalWrite(DIAG_PIN, HIGH);
			turnAllPanelsOff();			// turns the panels off
			brightLevelWrite();			// eeprom brightness write 
			delay(5000);
		digitalWrite(DIAG_PIN, LOW);
  
  systemState = 0;                      // Set system state represenation to off
}

/***********************************************************
*                   turnAllPanelsOn                        *
***********************************************************/
void turnAllPanelsOn(){

	// turn on all the led panels in sequence? at least its sorta fancy. 
	Panel_CL.turnOn();
	Panel_CR.turnOn();
	delay (250);		// delay for some effect
	Panel_BL.turnOn();
	Panel_BR.turnOn();
	delay (250);
	Panel_AL.turnOn();
	Panel_AR.turnOn();
	delay (100); 		// delay before dropping back to program
}

/***********************************************************
*                   turnAllPanelsOff                       *
***********************************************************/
void turnAllPanelsOff(){

	// turn off all the led panels in sequence? at least its sorta fancy. 
	Panel_CL.turnOff();
	Panel_CR.turnOff();
	delay (250);		// delay for some effect
	Panel_BL.turnOff();
	Panel_BR.turnOff();
	delay (250);
	Panel_AL.turnOff();
	Panel_AR.turnOff();
	delay (100); 		// delay before dropping back to program
}

/***********************************************************
*                 brightLevelWrite();                      *
***********************************************************/
void brightLevelWrite(){
	// Writes out current brightness for next start up time
	EEPROM.write(BRIGHT_LVL_EEPROM, runningBrightVal);	
}

/***********************************************************
*                 toggleBrigthtness();                      *
***********************************************************/
void toggleBrightness(){
	if (runningBrightVal < 255){
		runningBrightVal += (BRIGHT_INCRIMENT_VAL);
		if (255 - runningBrightVal < BRIGHT_INCRIMENT_VAL){
			runningBrightVal = (255);		// max it out if the next step won't get it there
		}
	}
	else {
		runningBrightVal = (BRIGHT_INCRIMENT_VAL);		// reset to lowest value
	}
	// pass the new brightness level to the objects/panels
		Panel_CL.updateBrightness(runningBrightVal);
		Panel_CR.updateBrightness(runningBrightVal);
		Panel_BL.updateBrightness(runningBrightVal);
		Panel_BR.updateBrightness(runningBrightVal);
		Panel_AL.updateBrightness(runningBrightVal);
		Panel_AR.updateBrightness(runningBrightVal);
}
