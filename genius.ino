/*
     REFERENCE
  digital 6  --> 0
  digital 7  --> 1
  digital 8  --> 2
  digital 9  --> 3
*/

#define debug false

/* game */
boolean started = false;

/* LEDS */
int ledOnTime = 300;
int highLeds[20];
int yourLeds[20];
int index = 0;
int indexHighLeds = 1;
boolean finishedArray = false;

void randomStartStage();
void startFinishGame();
void startLeds(int port, int code);
void showLEDS();
void getYourLEDS();
void displayLed(int port);
void gameOver();
void restart();

void setup() { 
  for (int i = 6; i < 10; i++){ pinMode(i, OUTPUT); }
  pinMode(10, INPUT_PULLUP);
  for (int i = 2; i <  6; i++){ pinMode(i, INPUT_PULLUP); }
  Serial.begin(9600); 
}


void loop() {
  if(!started){ randomStartStage(); }
  Serial.println("clicado --> ");
  Serial.print(digitalRead(10));
  Serial.print(digitalRead(5));
  Serial.print(digitalRead(4));
  Serial.print(digitalRead(3));
  Serial.print(digitalRead(2));

  if(debug){
    Debug();
  }else{
    if(digitalRead(10) == HIGH && started == false){ startFinishGame(); }
    if(digitalRead(10) == LOW) { 
      Serial.println(" -- started -- ");
      started = true; 
    }
  
    if (started){ 
      if(!finishedArray){ showLEDS();  }
      
      if(index <= indexHighLeds){getYourLEDS(); }
      else{ next(); }
      
      delay(200);
    }
  }
  
}




void randomStartStage(){
  highLeds[0] = random(4);
  highLeds[1] = random(4);
  Serial.println("<----- Random Start Stage ----->");
  Serial.print(highLeds[0]);
  Serial.print(highLeds[1]);
  for (int i = 2; i < 20; i++){ highLeds[i] = -1; }
}

void startFinishGame(){
  for (int i = 6; i < 10; i++){
    digitalWrite(i, HIGH);
    delay(600);
  }
  for (int i = 6; i < 10; i++){
    digitalWrite(i, LOW);
    delay(600);
  } 
}

void gameOver(){
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(3000);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  restart();
}

void restart(){
  started = false;
  
  ledOnTime = 300;
  for(int j = 0; j < 21; j++){
    highLeds[j] = -1;
    yourLeds[j] = -1;
  }
  index = 0;
  indexHighLeds = 1;
  finishedArray = false;
}

void startLeds(int port, int code){
  Serial.println("cosisosososo --> ");
  Serial.print(index, indexHighLeds);
  Serial.print(code);
  if(highLeds[index] != code){ gameOver(); }
  else{
    if(index == 19){ win(); }
    else{
      digitalWrite(port, HIGH);
      yourLeds[index] = code;
      index++;
   }
  }
}
void Debug(){
  
  if(digitalRead(5) == LOW){ 
    digitalWrite(6, HIGH);
    delay(1000);
    digitalWrite(6, LOW);
 }
  
  if(digitalRead(4) == LOW){ 
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
 }
 
 if(digitalRead(3) == LOW){ 
    digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(9, LOW);
 }
 if(digitalRead(2) == LOW){ 
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
 }
}
void next(){
  index = 0;
  indexHighLeds ++;
  int nextLed = random(4);
  highLeds[indexHighLeds] = nextLed;
  finishedArray = false;
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
//6, 8, 9, 7
void win(){
  digitalWrite(6, HIGH);
  delay(600);
  digitalWrite(6, LOW);

  digitalWrite(8, HIGH);
  delay(600);
  digitalWrite(8, LOW);

  digitalWrite(9, HIGH);
  delay(600);
  digitalWrite(9, LOW);

  digitalWrite(7, HIGH);
  delay(600);
  digitalWrite(7, LOW);

  delay(100);
  restart();
}

void showLEDS(){
  delay(500);
  
  int i = 0;
  
  while (!finishedArray){
    if(highLeds[i] == 0){ displayLed(6); }
    else if(highLeds[i] == 1){ displayLed(7); }
    else if(highLeds[i] == 2){ displayLed(8); }
    else if(highLeds[i] == 3){ displayLed(9); }
    else if(highLeds[i] == -1){ finishedArray = true; }
    
    delay(100);
    i ++;
  }
}


void getYourLEDS(){
  Serial.println("index");
  Serial.println(index);
  if(digitalRead(5) == LOW){ startLeds(6, 0); }
  else { digitalWrite(6, LOW); }
  
  if(digitalRead(4) == LOW){ startLeds(8, 2); }
  else { digitalWrite(8, LOW); }
  
  if(digitalRad(3) == LOW){ startLeds(9,  3); }
  else { digitalWrite(9, LOW); }
  
  if(digitalRead(2) == LOW){ startLeds(7, 1); }
  else { digitalWrite(7, LOW); }
}

void displayLed(int port){
  digitalWrite(port, HIGH);
  delay(ledOnTime);
  digitalWrite(port, LOW);
}
