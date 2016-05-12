int sides = 20;
int dice = 5;
int rolls = 100;

int hold [3] = {0, 0};
int totals [101];
int numbers [101];

void setup() {
  Serial.begin(9600);
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
    Serial.print("roll number "); Serial.println(b);
    for(int c = 0; c < dice; c++){
      hold [0] = random(1, (sides + 1));
      Serial.print("die number "); Serial.print(c); Serial.print(" ="); Serial.println(hold [0]);
      hold [1] = hold [0] + hold [1];
    }
    Serial.print("total= "); Serial.println(hold[1]); Serial.println();
    totals [b] = hold [1];
    hold [1] = 0;
  }
  
  Serial.print("results of "); 
  Serial.print(rolls); Serial.print(" rolls of "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.print("[");
  for(int d = 0; d < rolls; d++){
    Serial.print(totals [d]); Serial.print(", ");
  }
  Serial.println("]");

  for(int e = 0; e < rolls; e++){
    for(int f = 0; f < ((sides * dice) + 1); f++){
      if(totals [e] == f){
        numbers [f] ++;
      }
    }
  }

  Serial.print("totals of numbers rolled with "); 
  Serial.print(rolls); Serial.print(" rolls of "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.print("{");
  for(int g = dice; g < ((sides * dice) + 1); g++){
    Serial.print(g); Serial.print("=");
    Serial.print(numbers [g]); Serial.print(", ");
  }
  Serial.println("}");
  
  delay(10000);
  Serial.println("end."); Serial.println();
}
