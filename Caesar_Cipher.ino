#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorPin = A0;
int sensorValue = 0;
const byte numChars = 32;
char receivedChars[numChars];
int newArray[5];
int betterArray[5];
int count = 0;
boolean newData = false;
int a[26][10]={
               {0,0,0,1,0,1,1,1,1,1},  //A
               {0,0,0,1,1,1,1,1,1,1},  //B
               {0,0,0,0,1,1,0,1,1,0},  //C
               {0,0,0,1,1,1,0,1,1,1},  //D
               {0,0,0,0,1,1,1,1,1,0},  //E
               {0,0,0,0,0,1,1,1,1,0},  //F
               {0,0,0,1,1,1,1,1,1,0},  //G
               {0,0,0,1,0,1,1,1,0,0},  //H
               {0,0,0,1,0,0,0,0,0,1},  //I
               {0,0,0,1,1,0,0,0,0,1}, //J
               {0,0,0,1,0,1,1,1,0,1}, //K
               {0,0,0,0,1,1,0,1,0,0},  //L
               {0,0,0,1,0,1,0,1,1,1},  //M
               {0,0,0,1,0,1,0,0,1,0},  //N
               {0,0,0,1,1,1,0,1,1,1},  //0
               {0,0,0,0,0,1,1,1,1,1},  //P
               {0,0,0,0,1,1,0,1,1,1},  //Q
               {0,0,0,0,1,1,1,1,1,1},  //R
               {0,0,0,1,1,0,1,1,1,0},  //S
               {0,0,0,1,0,0,0,0,1,1},  //T
               {0,0,0,1,1,1,0,1,0,1},  //U
               {0,0,0,1,1,1,1,1,1,1},  //V
               {0,0,0,1,1,1,1,1,0,1},  //W
               {0,0,0,1,0,1,0,1,0,1},  //X
               {0,0,0,1,0,0,1,1,0,1},  //Y
               {0,0,0,0,1,1,1,0,1,1},};  //Z


int inp = 0; 
int letter = 0;
int s = 2;
String code = "";

char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void setup(){
  Serial.begin(9600);  
  pinMode(0, INPUT);
  lcd.begin(16,2);
  lcd.print("Caesar Cipher");
  for (int i=3;i<=25;i++) {  
    pinMode(i,OUTPUT);  
  }
}
void printf(int v){  
  for (int i=3;i<=9;i++){  
    digitalWrite(i,a[v][i]);  
  }  
}
void ddecode(char receivedChars[], int s){
  for(int i=0; i < 5; i++){
    for(int j = 0; j < sizeof(alphabet); j++){
      Serial.println(j);
      if (receivedChars[i]== alphabet[j]){
        Serial.println("match");
        newArray[i] = j;
        code.concat(j);
      }
      else{
        Serial.println("Does not match");
      }
    }
  }
  for(int j = 0; j < 5; j++){
    if(newArray[j] - s < 0){
      newArray[j] = (newArray[j]-s) + 26;
    }
    else{
      newArray[j] = newArray[j] - s;
    }
}
  }
void encode(char receivedChars[],int s){ 
 for(int i=0; i < 5; i++){
    for(int j = 0; j < sizeof(alphabet); j++){
      Serial.println(j);
      if (receivedChars[i]== alphabet[j]){
        Serial.println("match");
        newArray[i] = j;
        //code.concat(alphabet[j]);
      }
      else{
        Serial.println("Does not match");
      }
    }
  }
  for(int j = 0; j < 5; j++){
    if(newArray[j] + s > 25){
      newArray[j] = (newArray[j]+s) - 26;
      betterArray[j] = (newArray[j]+s) - 26;
    }
    else{
      newArray[j] = newArray[j] + s;
      betterArray[j] = newArray[j] + s;
    }
}
  }
void loop(){
  recvWithEndMarker();
  sensorValue = analogRead(sensorPin);
  s = analogRead(sensorPin);
  showNewData();
 
  }
 void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}
void newMessage(){
  for(int i=0; i < 5; i++){
        code.concat(alphabet[newArray[i]]);
      }
      count = count + 1;
}

void showNewData() {
    if (newData == true) {
        //ddecode(receivedChars,s);
        encode(receivedChars,s);
     for(int i = 0; i < 5; i++){
         //Serial.println(newArray[i]);
         Serial.println(newArray[i]);
         Serial.println("break");
         Serial.println(betterArray[i]);
         printf(newArray[i]);
         delay(1000);
     }
    newMessage();
    if (count > 0){
      lcd.setCursor(0,1);
      lcd.clear();
    }
    lcd.clear();
    lcd.print(code);
    lcd.setCursor(0,2);
    lcd.print(s);
    newData = false;
    }
}
