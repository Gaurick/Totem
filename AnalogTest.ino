/* An analog reader for the Trinket.
 *  
* required to calibrate the dice totem and get it up and running.
* display shows '8888' to let you get ready, then checks the analog value on pin 2.
* it then saves the minimum and maximum value read over 9,999 checks.
* after that it displays the minimum value followed by the maximum value.
* 
* go through and find out the values when the totem is 
* plugged into usb and charging, 
* and with the totem running off of battery and each of the buttons held down.
* make a note of the min and max values and then plug them into the totem program if
* it needs to be calibrated.
*  
*/

#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
//libraries to make it work

Adafruit_7segment matrix = Adafruit_7segment();
//sets the 7 segment display to be matrix.[command].

#define analogButtons 2
int analogValue = 0;
int analogMin;
int analogMax;

void setup(){
  matrix.begin(0x71);
  //starts up the seven segment display.
}


void loop(){
  matrix.print(8888);
  matrix.writeDisplay();
  delay(5000);

  check();
}

void check(){
  analogMin = 1025;
  analogMax = 0;
  //reset the min and max.
  
  for(int t = 0; t < 9999; t++){
    analogValue = analogRead(analogButtons);
    //check the button

    if(analogValue < analogMin){
      analogMin = analogValue;
      //check to see if the value is less than the minimum, then set it as the minimum if so.
    }

    else if(analogValue > analogMax){
      analogMax = analogValue;
      //check to see if it's less than the max, then set it as the max if so.
    }

    matrix.print(t);
    matrix.writeDisplay();
  }

  matrix.print(analogMin);
  matrix.writeDisplay();
  delay(5000);

  matrix.print(analogMax);
  matrix.writeDisplay();
  delay(5000);
}

