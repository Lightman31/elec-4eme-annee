import controlP5.*; // import comtrolP5 library
import processing.serial.*;

Serial port;
ControlP5 cp5;

PFont font;
int inValue;
long value;
int recievingState = 0;
int cpt;

long previousInValue;

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


void serialEvent(Serial port)
{
  previousInValue = inValue;
  inValue = port.read();
  println(inValue);
  
  if (recievingState == 0)
  {
    recievingState = inValue;
    if (recievingState == 49) cpt = 5;
    if (recievingState == 50) cpt = 3;
  }
  else 
  {
    if (recievingState == 49) value = value*1000 + inValue;
    if (recievingState == 50) value = value*100 + inValue;
    cpt = cpt -1;
   // println(value);
  }
  if (cpt == 0) 
  {
    //println(value);
    
    
    if (previousInValue != inValue)
    {
      if (recievingState == 49)
      {
        
        if ( value == 13044059091065L)
        {
          port.write('1');
          port.write('2');
          port.write("Leo");
          port.write('3');
          port.write("GUICHARNAUD");
        }
        
        else if ( value == 233209166135025L)
        {
          port.write('1');
          port.write('2');
          port.write("Carte");
          port.write('3');
          port.write("n°1");
        }
        else {
          port.write('0');
          port.write('3');
          port.write('2');
          port.write("Carte inconnue");    
        }
      }
      if (recievingState == 50)
      {
        if ( value == 106459)
        {
          port.write('1');
          port.write('2');
          port.write("Leo");
          port.write('3');
          port.write("GUICHARNAUD");
        }
        else if ( value == 123456)
        {
          port.write('1');
          port.write('2');
          port.write("Carte");
          port.write('3');
          port.write("n°1");
        }
        else {
          port.write('0');
          port.write('3');
          port.write('2');
          port.write("Carte inconnue");    
        }
      }
    }
    
    
    
    previousInValue = value;
    recievingState = 0;
    value = 0;
  }
  
  
  
  /*
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
  */

}



void draw()
{
  background(0,0,0);
  
  fill(255,255,255);
  textFont(font);
  text("HELLO ECE :", 90,30);
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
