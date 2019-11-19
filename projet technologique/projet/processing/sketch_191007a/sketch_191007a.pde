import controlP5.*; // import comtrolP5 library
import processing.serial.*;

Serial port;
ControlP5 cp5;

PFont font;
int adcValue;

void setup()
{
 size(300,250);
 printArray(Serial.list());
 port = new Serial(this, Serial.list()[0],9600);
 
 cp5 = new ControlP5(this);
 font = createFont("ACaslonPro-Bold",20);
 
 cp5.addButton("ON")
   .setPosition(140,50)
   .setSize(120,70)
   .setFont(font)
 ; 
 
 cp5.addButton("OFF")
   .setPosition(140,150)
   .setSize(120,70)
   .setFont(font)
 ;

 
}

void draw()
{
  background(0,0,0);
  
  fill(255,255,255);
  textFont(font);
  text("HELLO ECE :", 90,30);
}

void serialEvent(Serial port)
{
  adcValue = port.read();
  if (adcValue == 13)
  {
    port.write('1');
    port.write("Léo");
  }
  else {
    port.write('0');
    port.write("Carte inconnue");    
  }
      println(adcValue);
}

void controlEvent(ControlEvent theEvent)
{
  if(theEvent.isController())
  {
    if (theEvent.getController().getName()=="ON")
    {
      port.write('1');
      println("ON");
    }
    if (theEvent.getController().getName()=="OFF")
    {
      port.write('0');
      println("OFF");
    }
  }
}
