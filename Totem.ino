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
 * 
 * To do
 * add success/failure counter (such as rolling for Vampire the Masquerade or Shadowrun).
 * heads or tails (HEAD vs TAIL *should* work on the seven segment display.)
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
//variables for the buttons.

int diceNumber = 1;
int diceSidesCounter = 1;
int rollFlag = 0;
//variables to track the button presses.

int diceSides = 0;
int rollArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int result = 0;
//variables to do math things to total the rolls.

void setup(){
  matrix.begin(0x71);
  //starts up the seven segment display.

  randomSeed(analogRead(3));
  //starts the random number.
}


void loop(){
  analogValue = analogRead(analogButtons);
  //check the button

  if(analogValue > 685){
    // the number of dice button is being pressed.
    //adjust the 685 value based on the results of testing from the analog test.
    if(diceNumber < 9){
      diceNumber = diceNumber ++;
      delay(250);
    }

    else{
      diceNumber = 1;
      delay(250);
    }
  }

  else if(analogValue > 628){
    //the number of sides of dice button is being pressed.
    //adjust the 628 value based on the results of the analog test.
    if(diceSidesCounter < 8){
      diceSidesCounter = diceSidesCounter ++;
      delay(250);
    }

    else{
      diceSidesCounter = 1;
      delay(250);
    }
  }

  else if(analogValue > 594){
    //the button to roll was pressed.
    //adjust the 594 value based on the results of the analog test.
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

    for(int j = 0; j < (diceNumber), j ++;){
      result = rollArray[j] + result;
    }
  }
  
    matrix.print(result);
    matrix.writeDisplay();
    //show the total roll.
}

void show(){
  //show what is about to be rolled (number of dice and number of sides on said dice).
  matrix.writeDigitNum(0, diceNumber);
  matrix.writeDigitRaw(1, 64);
  //dash
  matrix.writeDigitNum(3, (diceSides / 10)% 10);
  matrix.writeDigitNum(4, (diceSides %10));
  matrix.writeDisplay();
}





