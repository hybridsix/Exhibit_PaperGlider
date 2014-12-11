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
#define BRIGHT_LVL_EEPROM     0
#define PWM_PIN3              3     // pin mapping for panel control. Section A is closest 
#define PWM_PIN5              5     // to launchers, section C is furthest. L/R is from
#define PWM_PIN6              6     // user POV.
#define PWM_PIN9              9
#define PWM_PIN10             10
#define PWM_PIN11             11
#define DIAG_PIN              13
#define REMOTE_A_PIN          A0
#define REMOTE_B_PIN          A1
#define REMOTE_C_PIN          A2
#define REMOTE_D_PIN          A3

/***********************************************************
*                      GLOBAL VARS                         *
***********************************************************/
boolean  remoteBtnA_state = 0;       // Init variables and Set initial button states
boolean  remoteBtnB_state = 0;       // Init variables and Set initial button states
boolean  remoteBtnC_state = 0;       // Init variables and Set initial button states
boolean  remoteBtnD_state = 0;       // Init variables and Set initial button states
boolean  systemState      = 0;       // Used to track system intended state for light control

//LED Panel/GliderLib Object Inits
LEDPanel Panel_AL (PWM_PIN3);
LEDPanel Panel_AR (PWM_PIN5);                  
LEDPanel Panel_BL (PWM_PIN6);                 
LEDPanel Panel_BR (PWM_PIN9);             
LEDPanel Panel_CL (PWM_PIN10);              
LEDPanel Panel_CR (PWM_PIN11);

/***********************************************************
*                          SETUP                           *
***********************************************************/
void setup(){
Serial.begin(9600);


}


/***********************************************************
*                          LOOP                            *
***********************************************************/
void loop(){
  readRemoteButtonStates() ;
  
  if (remoteBtnA_state) {           // If A button is being pressed
    Serial.println("Remote Button A Detected");
      //startUp();                    // run the startUp function
  }
      
  if (remoteBtnD_state){            // If D button is being pressed
    Serial.println("Remote Button D Detected");
      //shutDown();                   // run the shutDown function
  }
  
Panel_AL.turnOn();
delay(1000);
Panel_AL.turnOff();
delay(1000);

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
 
  Serial.println("Startup sequence started");
//    digitalWrite(FANS_CONTROL, HIGH); // Turns on the clear case fans (red light)
//    digitalWrite(AMP_SLEEP, LOW);     // Takes the amplifier out of sleep state
 //
  //Send the computer's power on button low
//  turnOnComputer();                   // function to turn on the computer
  
  // Activates the onboard LED to show that the system is busy. 
  // also pauses for 5 seconds to make sure there are not repeat remote commands sent
  digitalWrite(DIAG_PIN, HIGH);
    delay(5000);
  digitalWrite(DIAG_PIN, LOW);
  
  systemState = 1;                // Set the system state representation to on
  moboLightsWhite();              // turn the motherboard lights to white after all has been completed

/***********************************************************
*                       shutDown                           *
***********************************************************/

void shutDown(){

  Serial.println("Shutdown sequence started");
//    digitalWrite(FANS_CONTROL, LOW); // Turns off the clear case fans(red)
//    digitalWrite(AMP_SLEEP, HIGH);   // Mutes and sleeps the audio amplifier
 
  //Send the computer's power on button low
//  turnOffComputer();                 // function to turn computer off

  // Initialize all lighting strips to off

  
  // Activates the onboard LED to show that the system is busy. 
  // also pauses for 5 seconds to make sure there are not repeat remote commands sent
  digitalWrite(DIAG_PIN, HIGH);
  delay(5000);
  digitalWrite(DIAGPIN, LOW);
  
  systemState = 0;                      // Set system state represenation to off


}

}

