//250 max range (number of sides * number of dice such as 5d100's, 12d20's, 62d4's.)
int sides;
int dice;
int rolls = 50;
//100 max number of rolls.
int err = 0;

int hold [3] = {0, 0};
int totals [51];
int numbers [401];

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  sideSelect();

  if(err == 1){
    sideSelect();
  }
  diceSelect();

  if(err == 1){
    diceSelect();
  }
  rolling();

  if(err == 1){
    rolling();
  }
  resultsSelect();
}

void sideSelect(){
  err = 0;
  Serial.println("How many sides are on the dice you want to roll?");
  Serial.println("1 for d2 (coin)");
  Serial.println("2 for d4");
  Serial.println("3 for d6");
  Serial.println("4 for d8");
  Serial.println("5 for d10");
  Serial.println("6 for d12");
  Serial.println("7 for d20");
  Serial.println("8 for d100 (percentile)");

  while(!Serial.available());
  int x = Serial.read();

  if(x == '1'){
    sides = 2;
  }

  else if(x == '2'){
    sides = 4;
  }

  else if(x == '3'){
    sides = 6;
  }

  else if(x == '4'){
    sides = 8;
  }

  else if(x == '5'){
    sides = 10;
  }

  else if(x == '6'){
    sides = 12;
  }

  else if(x == '7'){
    sides = 20;
  }

  else if(x == '8'){
    sides = 100;
  }

  else{
    error(1);
    err = 1;
  }
}

void diceSelect(){
  err = 0;
  Serial.println("How many dice do you want to roll?");
  Serial.print("Maximum is "); 

  if(sides == 100){
    Serial.println("4");
  }

  else{
    Serial.println("9");
  }

  while(!Serial.available());
  byte y = Serial.read();
  dice = y - 48;
  if(dice > 9){
    error(2);
  }

  else if(dice < 1){
    error(2);
  }

  else if(sides == 100){
    if(dice > 4){
      error(2);
    }
  }
}

void resultsSelect(){
  err = 0;
  Serial.println("Would you rather");
  Serial.println("(R)esults");
  Serial.println("(T)otal of numbers rolled");
  Serial.println("(C)SV");

  while(!Serial.available());
  char z = Serial.read();

  if(z == 'R'){
    results();
  }
  
  else if(z == 'r'){
    results();
  }

  else if(z == 'T'){
    total();
  }

  else if(z == 't'){
    total();
  }

  else if(z == 'C'){
    csv();
  }

  else if(z == 'c'){
    csv();
  }

  else{
    error(3);
  }
}


void rolling(){
  err = 0;
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
}

void results(){
  Serial.print("results of "); 
  Serial.print(rolls); Serial.print(" rolls of "); Serial.print(dice); Serial.print("d"); Serial.println(sides);
  Serial.print("[");
  for(int d = 0; d < rolls; d++){
    Serial.print(totals [d]); Serial.print(", ");
  }
  Serial.println("]");
  delay(10000);
 }

 void total(){
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
 }

 void csv(){
    Serial.println(); Serial.println("CSV form"); Serial.println();
  Serial.println("Result,Total");
  for(int h = dice; h < ((sides * dice) +1); h++){
    Serial.print(h); Serial.print(","); Serial.println(numbers [h]);
  }
  
  delay(10000);
 }
 
void error(int errorNum){
  if(errorNum == 1){
    Serial.println("Please select an option between 1 and 8.");
    delay(1000);
  }

  else if(errorNum == 2){
    if(sides == 100){
      Serial.println("Please select a value between 1 and 5.");
      delay(1000);
    }

    else{
    Serial.println("Please select an option between 1 and 9.");
    }
  }

  else if(errorNum == 3){
    Serial.println("Please select R, T or C.");
    delay(1000);
  }
}
