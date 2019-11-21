import controlP5.*; // import comtrolP5 library
import processing.serial.*;

Serial port;
ControlP5 cp5;

PFont font;
int inValue;
int previousInValue;

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
  previousInValue = inValue;
  inValue = port.read();
  println(inValue);
  if (previousInValue != inValue)
  {
    if (inValue == 13 || (inValue == 219 && previousInValue == 219))
    {
      port.write('1');
      port.write('2');
      port.write("Leo");
      port.write('3');
      port.write("GUICHARNAUD");
    }
    else {
      port.write('0');
      port.write('3');
      port.write('2');
      port.write("Carte inconnue");    
    }
  }
  println(inValue);
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
