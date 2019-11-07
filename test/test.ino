#include <time.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 5;     // the number of the pushbutton pic
const int buttonPin2 = 4;     // the number of the pushbutton pic
const int buttonPin3 = 3;     // the number of the pushbutton pic
const int buttonPin4 = 2;     // the number of the pushbutton pic
const int led1R =  13;      // the number of the LED pin
const int led1G =  12;      // the number of the LED pin
const int led1B =  11;      // the number of the LED pin
const int led2R =  10;      // the number of the LED pin
const int led2G =  9;      // the number of the LED pin
const int led2B =  8;      // the number of the LED pin
const int led3R =  7;      // the number of the LED pin
const int led3G =  6;      // the number of the LED pin
const int led3B =  A3;      // the number of the LED pin
const int led4R =  A0;      // the number of the LED pin
const int led4G =  A1;      // the number of the LED pin
const int led4B =  A2;      // the number of the LED pin
int set = 1;
int reset = 0;
int etape = 1;
int partie = 0;
int tabLed[4] = {0};
int *tabIndications;
int buttonState1 =0 , buttonState2 =0, buttonState3=0,buttonState4=0;
int prevbuttonState1 =0 , prevbuttonState2 =0, prevbuttonState3=0, prevbuttonState4=0;

// variables will change:
int buttonState = 0;
void setup() {
  srand(time(NULL));

  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);

  pinMode(led2R, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2B, OUTPUT);
  
  pinMode(led3R, OUTPUT);
  pinMode(led3G, OUTPUT);
  pinMode(led3B, OUTPUT);

  pinMode(led4R, OUTPUT);
  pinMode(led4G, OUTPUT);
  pinMode(led4B, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT);
}

void loop() {
  if(etape < 8){
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    loadLed();
    indications();
    clicBouton();
  }else
    LoadLedWin();
  affichageLed();
 
}
void clicBouton(){
  
  if(prevbuttonState1 == HIGH && buttonState1 == LOW && (tabIndications[partie] == tabLed[0] || tabIndications[partie] == 5)){
    partie++;
    
  }else if(prevbuttonState2 == HIGH && buttonState2 == LOW && (tabIndications[partie] == tabLed[1] || tabIndications[partie] == 6)){
    partie++;
    
  }else if(prevbuttonState3 == HIGH && buttonState3 == LOW && (tabIndications[partie] == tabLed[2] || tabIndications[partie] == 7)){
    partie++;
   
  }else if(prevbuttonState4 == HIGH && buttonState4 == LOW && (tabIndications[partie] == tabLed[3] || tabIndications[partie] == 8)){
    partie++;
    
  }else if((prevbuttonState1 == HIGH && buttonState1 == LOW) || (prevbuttonState2 == HIGH && buttonState2 ==LOW) || (prevbuttonState3 == HIGH && buttonState3 ==LOW) || (prevbuttonState4 == HIGH && buttonState4 == LOW)){
    reset = 1;
  }
  prevbuttonState1 = buttonState1;
  prevbuttonState2 = buttonState2;
  prevbuttonState3 = buttonState3;
  prevbuttonState4 = buttonState4;
  if(partie == etape){
    set = 1;
    etape++;
    partie = 0;
  }else if(reset == 1){
    reset = 0;
    etape = 1;
    set = 1;
    partie = 0;
  }
}
void indications(){
  int y = 0, nbpos = 0, nb = 8;
  if(set == 1){
    set = 0;
    tabIndications = malloc(etape*sizeof(int));
    Serial.print("Appuyez sur les boutons correspondant à :\n");
    for(int i = 0; i < etape; i++){
      if(etape < 5){
        y = (rand() % 4)+1;
        tabIndications[i] = y;
        if(y == RED){
          Serial.print("LED rouge\n");
        }else if(y == GREEN){
          Serial.print("LED verte\n");
        }else if(y == BLUE){
          Serial.print("LED bleue\n");
        }else if(y == YELLOW){
          Serial.print("LED jaune\n");
        }
      }else{
        if(nbpos == 2){
          nb = 4;
        }
        y = (rand() % nb)+1;
        tabIndications[i] = y;
        if(y == RED){
          Serial.print("LED rouge\n");
        }else if(y == GREEN){
          Serial.print("LED verte\n");
        }else if(y == BLUE){
          Serial.print("LED bleue\n");
        }else if(y == YELLOW){
          Serial.print("LED jaune\n");
        }else if(y > YELLOW){
          nbpos++;
          Serial.print("LED n°");
          if(y != 8)
            Serial.print((y%4));
          else
            Serial.print("4");
          Serial.print("\n");
        }
      }
    }
  }
}
void loadLed(){
  int x = 1, y = 0;
  if(set == 1){
    for(int i=0; i<5; i++){
      tabLed[i] = 0;
    }
    while(x < 5){
      y = rand() % 4;
      if(tabLed[y] == 0){
        tabLed[y] = x;
        x++;
      }
    }
  }
}

void affichageLed(){
  if(tabLed[0] == RED){
    digitalWrite(led1R, LOW);
    digitalWrite(led1G, HIGH);
    digitalWrite(led1B, HIGH);
  }else if(tabLed[0] == GREEN){
    digitalWrite(led1R, HIGH);
    digitalWrite(led1G, LOW);
    digitalWrite(led1B, HIGH);
  }else if(tabLed[0] == BLUE){
    digitalWrite(led1R, HIGH);
    digitalWrite(led1G, HIGH);
    digitalWrite(led1B, LOW);
  }else if(tabLed[0] == YELLOW){
    digitalWrite(led1R, LOW);
    digitalWrite(led1G, LOW);
    digitalWrite(led1B, HIGH);
  }
  if(tabLed[1] == RED){
    digitalWrite(led2R, LOW);
    digitalWrite(led2G, HIGH);
    digitalWrite(led2B, HIGH);
  }else if(tabLed[1] == GREEN){
    digitalWrite(led2R, HIGH);
    digitalWrite(led2G, LOW);
    digitalWrite(led2B, HIGH);
  }else if(tabLed[1] == BLUE){
    digitalWrite(led2R, HIGH);
    digitalWrite(led2G, HIGH);
    digitalWrite(led2B, LOW);
  }else if(tabLed[1] == YELLOW){
    digitalWrite(led2R, LOW);
    digitalWrite(led2G, LOW);
    digitalWrite(led2B, HIGH);
  }
  if(tabLed[2] == RED){
    digitalWrite(led3R, LOW);
    digitalWrite(led3G, HIGH);
    analogWrite(led3B, 255);
  }else if(tabLed[2] == GREEN){
    digitalWrite(led3R, HIGH);
    digitalWrite(led3G, LOW);
    analogWrite(led3B, 255);
  }else if(tabLed[2] == BLUE){
    digitalWrite(led3R, HIGH);
    digitalWrite(led3G, HIGH);
    analogWrite(led3B, 0);
  }else if(tabLed[2] == YELLOW){
    digitalWrite(led3R, LOW);
    digitalWrite(led3G, LOW);
    analogWrite(led3B, 255);
  }
  if(tabLed[3] == RED){
    analogWrite(led4R, 0);
    analogWrite(led4G, 255);
    analogWrite(led4B, 255);
  }else if(tabLed[3] == GREEN){
    analogWrite(led4R, 255);
    analogWrite(led4G, 0);
    analogWrite(led4B, 255);
  }else if(tabLed[3] == BLUE){
    analogWrite(led4R, 255);
    analogWrite(led4G, 255);
    analogWrite(led4B, 0);
  }else if(tabLed[3] == YELLOW){
    analogWrite(led4R, 0);
    analogWrite(led4G, 0);
    analogWrite(led4B, 255);
  }
}
void LoadLedWin(){
  for(int i=0; i<5; i++){
    tabLed[i] = GREEN;
  }
}
