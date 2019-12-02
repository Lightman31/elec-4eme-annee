/*A Theme - Tetris 
  with Bass
  Uses Arduino tone library pitches.h [http://arduino.cc/en/Tutorial/tone ]
       by electricmango
  https://electricmango.github.io
  
  Thanks to Gori Fater for uploading the sheet music on Google.
  http://www.gamemusicthemes.com/sheetmusic/gameboy/tetris/
  
  Version 1.0.4
  -------------------------------------------------------------------------
  A Theme - Tetris with Bass is licensed under the
  
  Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
  
  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  for any purpose, even commercially.
  The licensor cannot revoke these freedoms as long as you follow the license terms.
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
  No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
  The full license is available at https://creativecommons.org/licenses/by-sa/4.0/legalcode
  
  Copyright (c) 2012 ~ 2015 electricmango
  -------------------------------------------------------------------------
  A_Theme___Tetris_with_Bass.ino
*/
/* Changed to use Esplora board Dec 2015 - LeRoy Miller */

#include "pitches.h"

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//notes in the melody:
int melody_tetris[] = {
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
};
int melody_death[] = {
  //NOTE_E5, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_E3, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_E3, NOTE_E5,
};
int noteDurations_tetris[] = {
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};
int pushButton0 = 6;
int pushButton1 = 9;
int pushButton2 = 10;
int pushButton3 = 13;
//note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations_death[] = {
  8,6,4,2,1,
};
int pos_tetris = 0;
int pos_death = 0;
int cekispasse = 0;

void setup(){
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton0, INPUT);
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Score : ");
}

void loop(){ 

  if (cekispasse == 0)
  {
    pos_tetris = tetris(pos_tetris);
    if(pos_tetris == 64) pos_tetris = 0;
  }
  if (cekispasse == 1){
    pos_death = death(pos_death);
    if(pos_death == 5) 
    {
      pos_death = 0;
      cekispasse = 0; 
    }
  }

    // read the input pin:
  int buttonState0 = digitalRead(pushButton0);
  // print out the state of the button:

  delay(1);        // delay in between reads for stability


  if ( buttonState0 == 0 ){
    cekispasse = 1;
  }
  int buttonState1 = digitalRead(pushButton1);
    int buttonState2 = digitalRead(pushButton2);
      int buttonState3 = digitalRead(pushButton3);
      int score = 0;
   score = buttonState1 + (2*buttonState2) + (4*buttonState3);
     Serial.println(score);
    lcd.setCursor(8, 0);
    lcd.print(score);

  
 
}


int tetris(int pos)
{
    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    */
    int noteDuration = 1000/noteDurations_tetris[pos];
    tone(8, melody_tetris[pos], noteDuration);
    
    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
   
    noTone(8); //stop the tone playing:
  
  digitalWrite(8,LOW);
  pos = pos + 1 ;
  return pos;
}



int death(int pos)
{
    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    */
    int noteDuration = 1000/noteDurations_death[pos];
    tone(7, melody_death[pos], noteDuration);
    
    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
   
    noTone(7); //stop the tone playing:
  
  digitalWrite(7,LOW);
  pos = pos + 1 ;
  return pos;
}
