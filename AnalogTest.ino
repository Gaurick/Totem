/*since the Trinket doesn’t have serial output (or input?) here’s a quick way to get analog readings
on an attached 4 digit 7 segment LED display.

need to list links and stuff to make this work and how to wire it all together?*/

#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

#define analogButtons 2
int analogValue = 0;
int analogMin = 0;
int analogMax = 0;

void setup(){
  //Serial.begin(9600);
  
  matrix.begin(0x71);
  //starts up the seven segment display.
}


void loop(){
  analogValue = analogRead(analogButtons);

  //uncomment this to show the analog reading (0-1024ish).
  /*matrix.print(analogValue);
  matrix.writeDisplay();*/

  //uncomment this to track and show the lowest value that the trinket reads.
  /*if(analogValue < analogMin){
    analogMin = analogValue;
  }
  
  matrix.print(analogMin);
  matrix.writeDisplay();*/

  //uncomment this to track and show the highest value that the trinket reads.
  /*if(analogValue > analogMax){
    analogMax = analogValue;
  }

  matrix.print(analogMax);
  matrix.writeDisplay();*/
}


