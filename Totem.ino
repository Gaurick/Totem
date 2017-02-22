/*dice rolling sketch.
 * an electronic alternative to rolling dice.
 * i still prefer to roll dice, but i wanted to try my hand at programming.
 * 
 * "rolls" 1-9 dice and can roll d2, d4, d6, d8, d10, d12, d20, and percentile dice.
 * 
 * see README for details on wiring, tutorial links, and a better explanation.
 * 
 * Revision history
 * v1.00 - got it running after much trial and tribulations.
 * v1.01 - removed rotary encoder, replaced with buttons, set code for trinket pro.
 * v1.02 - after breaking the trinket pro, adjusted to work on trinket.  changed buttons
 * to function on analog input instead of digital.
 * v1.03 - worked the analog kinks.  turned off input (kinda) when charging to prevent 
 * the analog values to not match up at all. got most of the bugs worked out.
 * v1.04 - switched to the 3v trinket pro and an alpha-numeric display.
 *
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
//libraries to make it work

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
//sets the 7 segment display to be alpha4.[command].

#define diceNumberButton 3
#define diceSidesButton 4
#define rollButton 5
//variables for the pins that the buttons are connected to.

int diceNumberState = 0;
int diceSidesState = 0;
int rollState = 0;
//variables for reading the button presses

int diceNumber = 1;
int diceSidesCounter = 1;
int rollFlag = 0;
//variables to track the button presses.

int diceSides = 0;
int rollArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int result = 0;
//variables to do math things to total the rolls.

void setup(){
  Serial.begin(9600);
  alpha4.begin(0x70);
  //starts up the alpha-numeric display.

  alpha4.setBrightness(1);
  //dims the led's so the display isn't so bright and uses less battery power.

  randomSeed(analogRead(0));
  //starts the random number.

  pinMode(diceNumberButton, INPUT);
  pinMode(diceSidesButton, INPUT);
  pinMode(rollButton, INPUT);
  //sets the button pins to be inputs.
}


void loop(){
  diceNumberState = digitalRead(diceNumberButton);
  diceSidesState = digitalRead(diceSidesButton);
  rollState = digitalRead(rollButton);
  //checks to see if the buttons have been pressed and sets the state.

  if(diceNumberState == HIGH){
    // the number of dice button is being pressed.
    if(diceNumber < 9){
      diceNumber ++;
      delay(250);
    }

    else{
      diceNumber = 1;
      delay(250);
    }
  }

  if(diceSidesState == HIGH){
    //the number of sides of dice button is being pressed.
    if(diceSidesCounter < 8){
      diceSidesCounter ++;
      delay(250);
    }

    else{
      diceSidesCounter = 1;
      delay(250);
    }
  }

  if(rollState == HIGH){
    //the button to roll was pressed.
    //this stuff sets the flag to roll the dice, then clears the results of the last roll.
    rollFlag = 1;
    for(int i = 0; i < 10; i ++){
      rollArray[i] = 0;
    }

    result = 0;
    diceSidesCounter = 0;
    delay(250);
  }
  
  sort();
  rollFlag = 0;
}

void sort(){
  //sort the results, assign the number of sides on the die (or dice) to be rolled.
  switch(diceSidesCounter){
    case 0:
    roll();
    break;
    //case to show the roll.

    case 1:
    diceSides = 2;
    show();
    break;
    //d2 (or a coin...)

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
   //d20

   case 8:
   diceSides = 99;
   show();
   break;
   //percentile
  }
}

void roll(){
  //function to roll the dice and total said roll(s).
  if(rollFlag == 1){
    for(int h = 0; h < (diceNumber); h ++){
      rollArray[h] = random(1, (diceSides + 1));
    }

    for(int j = 0; j < (diceNumber); j ++){
      result = rollArray[j] + result;
    }
  }
  
    alpha4.writeDigitAscii(0, (((result / 1000)% 10)+ 48));
    alpha4.writeDigitAscii(1, (((result / 100)% 10)+ 48));
    alpha4.writeDigitAscii(2, (((result / 10)% 10)+ 48));
    alpha4.writeDigitAscii(3, ((result % 10)+ 48));
    alpha4.writeDisplay();
    //show the total roll.
}

void show(){
  //show what is about to be rolled (number of dice and number of sides on said dice).
  alpha4.writeDigitAscii(0, ((diceNumber)+ 48));
  alpha4.writeDigitAscii(1, '-');
  //dash
  alpha4.writeDigitAscii(2, ((((diceSides / 10)% 10)+ 48)));
  alpha4.writeDigitAscii(3, ((diceSides % 10)+ 48));
  alpha4.writeDisplay();
}
