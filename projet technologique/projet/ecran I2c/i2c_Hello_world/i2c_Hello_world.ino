

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address

#define BACKLIGHT_PIN     13

void setup()
{

  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  lcd.begin(16,2);               // initialize the lcd 
  lcd.print("hello, world");
}

void loop()
{

}
