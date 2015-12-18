/*since the Trinket doesn’t have serial output (or input?) here’s a quick way to get analog readings
on an attached 4 digit 7 segment LED display.
needed to calibrate what the voltage values of each button press.
shows the maximum value read, then the minimum value read, then it resets the max and minimum.

*/

#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
//libraries to make it work.

Adafruit_7segment matrix = Adafruit_7segment();
//set the display to be matrix.[command].

#define analogButtons 2
int analogValue = 0;
int analogMin = 1025;
int analogMax = 0;
//variables for the buttons and the analog values read.

int t = 0;
//time keeper.

void setup(){
  matrix.begin(0x71);
  //starts up the seven segment display.
}


void loop(){
  analogValue = analogRead(analogButtons);

  if(t < 1000){
    //counter to avoid the use of delay();
    t ++;
  }

  else{
    //reset the timer and the min/max values.
    t = 0;
    analogMin = 1025;
    analogMax = 0;
  }

 if(analogValue < analogMin){
    analogMin = analogValue;
  }
  
  if(analogValue > analogMax){
    analogMax = analogValue;
  }

 
show();
}

void show(){
  //shows the minimum, then switches to the maximum.
  if(t < 300){
    matrix.print(analogMin);
    matrix.writeDisplay();
    delay(10);
  }

  else{
    matrix.print(analogMax);
    matrix.writeDisplay();
  }
}




