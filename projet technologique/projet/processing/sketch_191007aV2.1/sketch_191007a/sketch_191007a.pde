import controlP5.*; // import comtrolP5 library
import processing.serial.*;

Serial port;
ControlP5 cp5;

static int TAILLETAB = 25;

int nb_lignes = 0;
PFont font;
int inValue;
long value;
int recievingState = 0;
int cpt;

int choixTD = 2;

long previousInValue;
Table table;

int table_presence[] = new int [TAILLETAB];
int table_TD[] = new int [TAILLETAB];
long table_id[] = new long [TAILLETAB];
long table_NE[] = new long [TAILLETAB];
String table_prenom[] = new String [TAILLETAB];
String table_nom[] = new String [TAILLETAB];

void setup()
{
  
    int i = 0;
  table = loadTable("ING4_uid_main.csv", "header");
  
  println(table.getRowCount() + " total rows in table");
nb_lignes = table.getRowCount();
  for (TableRow row : table.rows()) {

    int id1 = row.getInt("id1");
    int id2 = row.getInt("id2");
    long id = id1*1000000000L + id2;
    String species = row.getString("Nom");
    String name = row.getString("Prenom");
    long numE = row.getInt("NumEtudiant");
    int TD = row.getInt("TD");
    table_id[i] = id;
    table_TD[i] = TD;
    table_NE[i] = numE;
    table_prenom[i] = name;
    table_nom[i] = species;
    table_presence[i] = 0;

    println(name + " (" + species + ") has an ID of " + id + "num Etudiant : " + numE);
    i = i+1;
  }
  
 size(1000,700);
 printArray(Serial.list());
 port = new Serial(this, Serial.list()[0],9600);
 
 cp5 = new ControlP5(this);
 font = createFont("Times New Roman",20);
 
 cp5.addButton("Reset")
   .setPosition(750,50)
   .setSize(120,70)
   .setFont(font)
 ; 
 cp5.addButton("TD2")
   .setPosition(750,150)
   .setSize(120,70)
   .setFont(font)
 ; 
 cp5.addButton("TD4")
   .setPosition(750,250)
   .setSize(120,70)
   .setFont(font)
 ; 
 cp5.addButton("blanc")
   .setPosition(750,550)
   .setSize(120,70)
   .setFont(font)
 ; 
 

 
}


void serialEvent(Serial port)
{
  int carteconnue = 0;
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
        carteconnue  = 0;
        for (int i = 0 ; i  < TAILLETAB ; i ++)
        {
          if (table_id[i] == value && table_presence[i] == 0 && table_TD[i] == choixTD)
          {
            port.write('1');
            port.write('2');
            port.write(table_prenom[i]);
            port.write('3');
            port.write(table_nom[i]);
            table_presence[i] = 1;
            carteconnue = 1;
          }
          if (table_id[i] == value && table_presence[i] == 1 )
          {
            carteconnue = 1;
          }
          
          
        }
        if (carteconnue == 0)
        {
          port.write('0');
          port.write('3');
          port.write('2');
          port.write("Carte inconnue");   
        }
        
      }
      if (recievingState == 50)
      {
        carteconnue  = 0;
        for (int i = 0 ; i  < TAILLETAB ; i ++)
        {
          if (table_NE[i] == value && table_presence[i] == 0 )
          {
            carteconnue = 1;
            port.write('1');
            port.write('2');
            port.write(table_prenom[i]);
            port.write('3');
            port.write(table_nom[i]);
            table_presence[i] = 1;
          }
          if (table_NE[i] == value && table_presence[i] == 1 )
          {
            carteconnue = 1;
          }
          
          
        }
        if (carteconnue == 0)
        {
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
  

}



void draw()
{
  background(0,0,0);
  
  fill(255,255,255);
  textFont(font);
  
  
  
  
  int y_pos = 70;
  
  text("NOM" , 50,30);
  text("PRENOM", 260,30);
  text("TD en cours : " + choixTD,400,30);
  
  for (int i = 0 ; i < nb_lignes ; i++)
  {
    if (table_TD[i] == choixTD)
    {
    text(table_nom[i],50,y_pos);
    y_pos+=30;
    }
  }
  y_pos = 70;
  for (int i = 0 ; i < nb_lignes ; i++)
  {    if (table_TD[i] == choixTD)
    {
    text(table_prenom[i],260,y_pos);
    y_pos+=30;
    }
  }
  y_pos = 25;
  for (int i = 0 ; i < nb_lignes ; i++)
  {
    if (table_TD[i] == choixTD)
    {
      if (table_presence[i] == 0)
      {
        fill(255,0,0);
        y_pos+=30;
      }
      if (table_presence[i] == 1)
      {
        fill(0,255,0);
        y_pos+=30;
      }
    rect(25,y_pos,15,15);
    }
  }
  
  
  
}


void controlEvent(ControlEvent theEvent)
{
  if(theEvent.isController())
  {
      if (theEvent.getController().getName()=="Reset")
      {
       for (int i = 0 ; i < nb_lignes ; i++)
          table_presence[i] = 0;
      }
      if (theEvent.getController().getName()=="blanc")
      {
         choixTD = 0;
      }
      if (theEvent.getController().getName()=="TD2")
      {
         choixTD = 2;
      }
      if (theEvent.getController().getName()=="TD4")
      {
          choixTD = 4;
      }
    }
  }