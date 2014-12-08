#include <GliderLib.h>

LEDPanel panel(13);



void setup(){
Serial.begin(9600);

}

void loop(){
panel.turnOn();
delay(1000);
panel.turnOff();
delay(1000);

}


