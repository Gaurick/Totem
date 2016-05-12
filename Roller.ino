//250 max range (number of sides * number of dice such as 5d100's, 12d20's, 62d4's.)
int sides = 10;
int dice = 1;
int rolls = 250;
//250 max number of rolls.

int hold [3] = {0, 0};
int totals [251];
int numbers [501];

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("start.");
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

  Serial.println(); Serial.println("CSV form"); Serial.println();
  Serial.println("Result,Total");
  for(int h = dice; h < ((sides * dice) +1); h++){
    Serial.print(h); Serial.print(","); Serial.println(numbers [h]);
  }
  
  delay(10000);
  Serial.println(); Serial.println("end."); Serial.println(); 
 }
