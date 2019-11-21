  

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

RFID monModuleRFID(10,9);
  
int UID[5];
  
int potVal;
int potValTemp;
char SerialVal;

void setup() 
{
  pinMode(8, OUTPUT);   //set D10 pin as output (LED)
  pinMode(A0, INPUT);   //set pin A0 as input (potentiometer)
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
    lcd.setCursor(0,0);
    lcd.print(SerialVal);
    lcd.print("       ");
    if(SerialVal == '1') digitalWrite(8, HIGH); //turn ON the LED
    if(SerialVal == '0') digitalWrite(8, LOW); //turn OFF the LED      
  }



      if (monModuleRFID.isCard()) {  
          if (monModuleRFID.readCardSerial()) {     
                            for(int i=0;i<=4;i++)
                {
UID[i]=monModuleRFID.serNum[i];
                }
            Serial.write(UID[0]);     
          }   
          monModuleRFID.halt();
    }
    delay(1);   


  
}




  
