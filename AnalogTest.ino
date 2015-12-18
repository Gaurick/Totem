/* An analog reader for the Trinket.
* required to calibrate the dice totem and get it up and running.
*/

#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
//libraries to make it work

Adafruit_7segment matrix = Adafruit_7segment();
//sets the 7 segment display to be matrix.[command].

#define analogButtons 2
int analogValue = 0;

int analogMin = 1025;
int t = 0;

void setup(){
  matrix.begin(0x71);
  //starts up the seven segment display.
}


void loop(){
  analogValue = analogRead(analogButtons);
  //check the button

  if(t < 1000){
    t ++;
  }

  else{
    t = 0;
    analogMin = 1025;
  }

  if(analogValue < analogMin){
    analogMin = analogValue;
  }

  sort();
}

void sort(){
  matrix.print(analogMin);
  matrix.writeDisplay();
}
