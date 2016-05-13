//250 max range (number of sides * number of dice such as 5d100's, 12d20's, 62d4's.)
int sides = 10;
int dice = 1;
int rolls = 100;
//100 max number of rolls.

int hold [3] = {0, 0};
int totals [101];
int numbers [501];

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("start.");

  Serial.println("How many sides are on the die or dice you want to roll?");
  Serial.println("1 for d2 (coin)");
  Serial.println("2 for d4");
  Serial.println("3 for d6");
  Serial.println("4 for d8");
  Serial.println("5 for d10");
  Serial.println("6 for d12");
  Serial.println("7 for d20");
  Serial.println("8 for d100 (percentile)");

  while(!Serial.available());
  char x = Serial.read();

  switch(x){
    case '1':{
      sides = 2;
      Serial.println("d2 or a coin");
      break;
    }

    case '2':{
      sides = 4;
      Serial.println("d4");
      break;
    }

    case '3':{
      sides = 6;
      Serial.println("d6");
      break;    
    }

    case '4':{
      sides = 8;
      Serial.println("d8");
      break;
    }

    case '5':{
      sides = 10;
      Serial.println("d10");
      break;
    }

    case '6':{
      sides = 12;
      Serial.println("d12");
      break;
    }

    case '7':{
      sides = 20;
      Serial.println("d20");
      break;
    }

    case '8':{
      sides = 100;
      Serial.println("d100 or percentile.");
      break;
    }
  }

  Serial.println();
  Serial.println("How many dice do you want to roll?");
  Serial.print("Maximum is "); 

  if(sides == 100){
    Serial.println("5");
  }

  else{
    Serial.println("9");
  }

  while(!Serial.available());
  byte y = Serial.read();
  dice = y - 48;
  
  Serial.print("rolling "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.println();
  for(int a = 0; a < rolls; a++){
    totals [a] = 0;
    numbers [a] = 0;
  }
  
  for(int b = 0; b < rolls; b++){
    //Serial.print("roll number "); Serial.println(b);
    for(int c = 0; c < dice; c++){
      hold [0] = random(1, (sides + 1));
      //Serial.print("die number"); Serial.print(c); Serial.print(" ="); Serial.println(hold [0]);
      hold [1] = hold [0] + hold [1];
    }
    //Serial.print("total= "); Serial.println(hold[1]); Serial.println();
    totals [b] = hold [1];
    hold [1] = 0;
  }

  for(int e = 0; e < rolls; e++){
    for(int f = 0; f < ((sides * dice) + 1); f++){
      if(totals [e] == f){
        numbers [f] ++;
      }
    }
  }

  Serial.println("Would you rather");
  Serial.println("(H)uman readable?");
  Serial.println("or");
  Serial.println("(C)SV");

  while(!Serial.available());
  char z = Serial.read();

  if(z == 'H'){
    human();
  }

  else if(z == 'C'){
    csv();
  }

  else if(z == 'h'){
    human();
  }

  else if(z == 'c'){
    csv();
  }

  else{
    Serial.println("Error.");
  }
}

 void human(){
  Serial.print("results of "); 
  Serial.print(rolls); Serial.print(" rolls of "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.print("[");
  for(int d = 0; d < rolls; d++){
    Serial.print(totals [d]); Serial.print(", ");
  }
  Serial.println("]");

  Serial.print("totals of numbers rolled with "); 
  Serial.print(rolls); Serial.print(" rolls of "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.print("{");
  for(int g = dice; g < ((sides * dice) + 1); g++){
    if(numbers [g] != 0){
      Serial.print(g); Serial.print("=");
      Serial.print(numbers [g]); Serial.print(", ");
    }
  }
  Serial.println("}");
  delay(10000);
  Serial.println(); Serial.println("end."); Serial.println();
 }

 void csv(){
    Serial.println(); Serial.println("CSV form"); Serial.println();
  Serial.println("Result,Total");
  for(int h = dice; h < ((sides * dice) +1); h++){
    Serial.print(h); Serial.print(","); Serial.println(numbers [h]);
  }
  
  delay(10000);
  Serial.println(); Serial.println("end."); Serial.println(); 
 }
 
