  

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>
#include <Keypad.h>


#define N_F3  175
#define N_FS3 185
#define N_G3  196
#define N_GS3 208
#define N_A3  220
#define N_AS3 233
#define N_B3  247
#define N_C4  262
#define N_CS4 277
#define N_D4  294
#define N_DS4 311
#define N_E4  330
#define N_F4  349
#define N_FS4 370
#define N_G4  392
#define N_GS4 415
#define N_A4  440
#define N_AS4 466
#define N_B4  494
#define N_C5  523
#define N_CS5 554
#define N_D5  587
#define N_DS5 622
#define N_E5  659
#define N_F5  698
#define N_FS5 740
#define N_G5  784
#define N_GS5 831
#define N_A5  880
#define N_AS5 932
#define N_B5  988
#define N_C6  1047
#define N_CS6 1109

int UID[5];

// notes in the melody:
int melody[] = {
  N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8  
};

int melody_len = sizeof(melody)/sizeof(melody[0]);
int here = 0;

long int saisie = 0;
int len_saisie = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3 ,4 ,5 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2,A3}; //connect to the column pinouts of the keypad


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
RFID monModuleRFID(10,9);
  
int potVal;
int potValTemp;
char SerialVal;

void setup() 
{
  Serial.begin(9600);    //start serial communication @9600 bps

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");

  SPI.begin();
  monModuleRFID.init();  

  
 }

void loop()
{
  
  // READ
  if(Serial.available()) // serial data is available to read
  {  
    SerialVal = Serial.read();

  switch(SerialVal)
   {
   case '0':
    badcard();  
   break;
   case '1':
    here = bilibip(here);
   break;
   case '2':
    lcd.setCursor(0,0);
    lcd.print("                      ");
    lcd.setCursor(0,0);
   break;
   case '3':
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
   break;
   case '4':
   break;
   case '5':
   break;
   case '6':
   break;
   case '7':
   break;
   case '8':
   break;
   case '9':
   break; 
   default :
   lcd.print(SerialVal);
  }
  }

// capteur RFID

if (monModuleRFID.isCard()) {  
  if (monModuleRFID.readCardSerial()) {     
    Serial.write('1');  
     for(int i=0;i<=4;i++)
     {
       UID[i]=monModuleRFID.serNum[i];
       Serial.write(UID[i]); 
       } 
     }   
     monModuleRFID.halt();
  }
  delay(1);   


  char customKey = customKeypad.getKey();
  
  if (customKey){
    board (customKey);
  }

  
}



int bilibip(int here)
{
  if (here > melody_len-6) here = 0;
    for (int thisNote = here; thisNote < here+6; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.45;
    delay(pauseBetweenNotes);
    noTone(8);
  }
  return here+6;
  
}


void badcard()
{
  tone(7, N_F3, 500);
}


void board(char customKey)
{

  switch(customKey)
   {
   case '0':
      saisie = saisie*10 + 0;
      len_saisie = len_saisie + 1;
   break;
   case '1':
      saisie = saisie*10 + 1;
      len_saisie = len_saisie + 1;
   break;
   case '2':
   saisie = saisie*10 + 2;
      len_saisie = len_saisie + 1;
   break;
   case '3':
   saisie = saisie*10 + 3;
      len_saisie = len_saisie + 1;
   break;
   case '4':
     saisie = saisie*10 + 4;
      len_saisie = len_saisie + 1;
   break;
   case '5':
     saisie = saisie*10 + 5;
      len_saisie = len_saisie + 1;
   break;
   case '6':
     saisie = saisie*10 + 6;
      len_saisie = len_saisie + 1;
   break;
   case '7':
     saisie = saisie*10 + 7;
      len_saisie = len_saisie + 1;
   break;
   case '8':
     saisie = saisie*10 + 8;
      len_saisie = len_saisie + 1;
   break;
   case '9':
     saisie = saisie*10 + 9;
      len_saisie = len_saisie + 1;
   break; 
   case 'D':
   saisie = 0;
   len_saisie = 0;
   break;
   default:
   return 0;
   }

   lcd.setCursor(0,0);   
   lcd.print(saisie);
   lcd.print("                       ");
   lcd.setCursor(0,1);   
   lcd.print(len_saisie);
   lcd.print("                     ");

   if (len_saisie == 6)
   {
       lcd.setCursor(0,0); 
   lcd.print("Recherche en cours        ");
    
   lcd.setCursor(0,1);   
   lcd.print(saisie);
   lcd.print("                       ");
   Serial.write('2'); 
   Serial.write((saisie - saisie%10000)/10000);
   Serial.write(((saisie - saisie%100)/100)%100);
   Serial.write(saisie%100);
   //Serial.println((saisie - saisie%10000)/10000);
   //Serial.println(((saisie - saisie%100)/100)%100);
   //Serial.println(saisie%100);
   saisie = 0;
   len_saisie = 0;
    
   }
  
}




  
