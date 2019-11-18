//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>

#define N1 1047
#define N2 31
#define N3 4978

RFID monModuleRFID(10,9);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int UID[5];

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
    SPI.begin();
  monModuleRFID.init();  

}


void loop()
{
             
      if (monModuleRFID.isCard()) {  
          if (monModuleRFID.readCardSerial()) {     
                            for(int i=0;i<=4;i++)
                {
UID[i]=monModuleRFID.serNum[i];
                }
            
             if (UID[0] == 13){
              lcd.setCursor(0,0);   
                 lcd.print("Leo                  ");
              lcd.setCursor(0,1);   
                 lcd.print("                     ");
                 bilibip();
             }
             else {
              lcd.setCursor(0,0);   
              lcd.print("carte non reconnue");
                  lcd.setCursor(0,1);   
                for(int i=0;i<=4;i++)
                {
                    
                    lcd.print(UID[i],DEC);
                    lcd.print(".");
                }
          
            }       
          }   
          monModuleRFID.halt();
    }
    delay(1);    
}


void bilibip()
{
  tone(8, N1, 300);
  tone(8, N2, 300);
  tone(8, N3, 300);
  
}
