/*
So this was my attempt to create an electronic set of dice.
It allows 1-9 dice to be rolled at a time and totals the result into one value.
It can roll d2, d4, d6, d10, d12, d20, and percentiles.
This requires an arduino micro controller, lipo battery and charger, 3 push buttons, and a seven segment LED display with an i2c converter on it.

Wiring
i2c seven segment backpack
c = 2
d = 0
+=5v
-=ground

buttons
button1 = 3
button2 = 4
button3 = 1

LiPo backpack 
bat = BAT+
g = ground
5v = USB +

tutorials used to make it work,
https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack
https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack/pinouts

questions, comments, or advice can be directed at BulletProofHooker@gmail.com

Revision history
v1.00 - got it running.
v1.01 - removed rotary encoder, replaced with buttons, set code for trinket and/or trinket pro.

to do
fix bug when going from a roll to setting the dice to roll (doesn't remember dice value last used, goes to d4).
add success/failure counter.
heads or tails (HEAD vs TAIL *should* display on the seven segments.
add + or - to rolls (for the super lazy…)
maybe add second seven segment display to increase options of stuff.
*/
 
//#include <Wire.h>
#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
//libraries needed for the seven segment led display.

Adafruit_7segment matrix = Adafruit_7segment();
//sets the seven segment display to the name "matrix".

#define numberButton 3
//pin used for the button to select the number of dice to roll.
#define sideButton 4
//pin used for the button to select the number of sides on the dice to roll.
#define rollButton 1
//pin used for the button to actually roll the dice.

int diceNumber = 1;
//variable for the number of dice to "roll".
int diceSides = 2;
//variable for the number of sides on the dice to "roll".
int diceSidesCounter = 1;
//variable to to track where in the switch case the sides of the roll is, to set the number of die sides.
int result = 0;
//variable for the result of the roll.
int rollArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//array to hold the rolls.
int rollFlag = 0;
//flag to keep from infina-rolling.

void setup(){
  //Serial.begin(9600);
  
  pinMode(numberButton, INPUT_PULLUP);
  //set the rotary button pin to input and use the internal pullup resistor.
  pinMode(sideButton, INPUT_PULLUP);
  //set the rotary spinner pin to input and use the internal pullup resistor.
  pinMode(rollButton, INPUT_PULLUP);
  //set the pressy button as an input and use the internal pullup resistor.
  
  matrix.begin(0x71);
  //starts up the seven segment display.
  
  randomSeed(analogRead(0));
  //start the random string of numbers with the noise on an unattached pin 0.
}

void loop(){
  if(digitalRead(numberButton) == LOW){
  //reading and doing the correct action for when the numberButton is pressed.
    if(diceNumber ==9){
      diceNumber = 1;
    }

    else{
      diceNumber = diceNumber ++;
    }

  delay(250);
  }
    
  if(digitalRead(sideButton) == LOW){
  //reading and doing the correct action for when the sideButton is pressed.
    if(diceSidesCounter == 8){
      diceSidesCounter = 1;
    }

    else{
      diceSidesCounter = diceSidesCounter ++;
    }
 
    delay(250);
    }

  if(digitalRead(rollButton) == LOW){  
  //finally what happens when the roll button is pressed.
    rollFlag = 1;
    for(int i = 0; i < 10; i  ++){
      rollArray[i] = 0;
      //clear the roll array.
    }
    
    result = 0;
    diceSidesCounter = 0;
    delay(250);
  }
  
  sort();
  rollFlag = 0; 
}

void sort(){
  switch(diceSidesCounter){
    case 0:
    roll();
    break;
    //case to display the "roll"
    
    case 1:
    diceSides = 2;
    show();
    break;
    //d2
    
    case 2:
    diceSides = 4;
    show();
    break;
    //d4
    
    case 3:
    diceSides = 6;
    show();
    break;
    //classic d6
    
    case 4:
    diceSides = 8;
    show();
    break;
    //d8
    
    case 5:
    diceSides = 10;
    show();
    break;
    //d10
    
    case 6:
    diceSides = 12;
    show();
    break;
    //d12
    
    case 7:
    diceSides = 20;
    show();
    break;
    //famous d20
    
    case 8:
    diceSides = 99;
    show();
    break;
    //percentile
  }
}

void roll(){
  if(rollFlag == 1){
    for(int h = 0; h < (diceNumber); h ++){
      rollArray[h] = random(1, (diceSides + 1));
    }
    //the actual "rolling" of the "dice".  
 
    for(int j = 0; j < (diceNumber); j ++){
      result = result + rollArray[j];
    }
    //totaling the rolls into one number.
    
    matrix.print(result);
    matrix.writeDisplay();
    //print the results on the seven segments.
  }
}

void show(){
  matrix.writeDigitNum(0, (diceNumber));
  //writes the number of dice to be rolled.
  matrix.writeDigitRaw(1, 64);
  //writes the dash to the seven segment display.
  matrix.writeDigitNum(3, (diceSides / 10) % 10);
  //writes the 10's place of the number of sides on the dice to be rolled.
  matrix.writeDigitNum(4, (diceSides % 10));
  //writes the 1's place of the number of sides on the dice to be rolled.
  matrix.writeDisplay();
  //actually sends the above stuff to be displayed.
}






