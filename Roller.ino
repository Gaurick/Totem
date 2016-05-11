int sides = 20;
int dice = 2;
int rolls = 5;

int hold [3] = {0, 0};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("start.");
  
  for(int y = 0; y < rolls; y++){
    Serial.print("roll number "); Serial.print(y);
    for(int x = 0; x < dice; x++){
      hold [0] = random(1, sides);
      Serial.print("die number "); Serial.print(x); Serial.print(" ="); Serial.println(hold [0]);
      hold [1] = hold [0] + hold [1];
    }
    Serial.print("total= "); Serial.println(hold[1]);
    hold [1] = 0;
    delay(10000);
    Serial.println("end.");
  }
}
