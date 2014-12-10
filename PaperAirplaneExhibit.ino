/* Paper airplane Exhibit (Glider) main control software
  mainly used to turn the exhibit on and off, and to set brightness
*/


#include <EEPROM.h>
#include <GliderLib.h>



// Defines
#define BRIGHT_LVL_EEPROM     0
#define PWM_PIN3              3     // pin mapping for panel control. Section A is closest 
#define PWM_PIN5              5     // to launchers, section C is furthest. L/R is from
#define PWM_PIN6              6     // user POV.
#define PWM_PIN9              9
#define PWM_PIN10             10
#define PWM_PIN11             11



// Global Vars




//LED Panel/GliderLib Object Inits
LEDPanel Panel_AL (PWM_PIN3);
LEDPanel Panel_AR (PWM_PIN5);                  
LEDPanel Panel_BL (PWM_PIN6);                 
LEDPanel Panel_BR (PWM_PIN9);             
LEDPanel Panel_CL (PWM_PIN10);              
LEDPanel Panel_CR (PWM_PIN11);


void setup(){
Serial.begin(9600);


}

void loop(){
Panel_AL.turnOn();
delay(1000);
Panel_AL.turnOff();
delay(1000);

}


