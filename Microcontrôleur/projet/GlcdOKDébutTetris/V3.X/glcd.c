// INCLUDES
#include "glcd.h"

//************************************************************************
//Variables positionnement
//*************************************************************************
unsigned char x,y;		// x et y serviront � la sauvegarde des coordonn�es absolues de l'�cran


//************************************************************************
// void InitDisplay(void)
//************************************************************************
void glcd_Init(unsigned char mode)
{

	// Reset the display
	PORTD = 0x00;					
	GLCD_RST = 0;					
	__delay_us(50); //Delay10TCYx(15);				
	GLCD_RST = 1;				

	GLCD_E=0;
	GLCD_CS1=0;
	GLCD_CS2=0;
	GLCD_RS=0;
	__delay_us(1); //Delay1TCY();        			//d�lai pour initialisation

 	glcd_WriteByte(GLCD_LEFT,  0xC0);    // Specifie la premi�re ligne RAM line en haut
  	glcd_WriteByte(GLCD_RIGHT, 0xC0);    //   de l'�cran
   	glcd_WriteByte(GLCD_LEFT,  0x40);    // Place l'adresse de colonne � 0
   	glcd_WriteByte(GLCD_RIGHT, 0x40);
   	glcd_WriteByte(GLCD_LEFT,  0xB8);    // Place l'adresse de la page � 0
   	glcd_WriteByte(GLCD_RIGHT, 0xB8);	

	if(mode == GLCD_ON)
  {
      glcd_WriteByte(GLCD_LEFT,  0x3F); // Allume le GLCD
      glcd_WriteByte(GLCD_RIGHT, 0x3F);
  }
   else
  {
      glcd_WriteByte(GLCD_LEFT,  0x3E); // Eteint le GLCD
      glcd_WriteByte(GLCD_RIGHT, 0x3E);
   }
	
	glcd_FillScreen(0);                // CLearScreen !

}

//************************************************************************
// void WriteByte(unsigned char byt)
//************************************************************************
void glcd_WriteByte(unsigned char side, unsigned char data)
{
	if(side)
	{                   // S�lection du cot� pour l'�criture
     	GLCD_CS1 = 1;
		GLCD_CS2 = 0;
	}
   	else
	{
		GLCD_CS2 = 0;
      	GLCD_CS2 = 1;
	}	

	GLCD_DATA_TRIS=0;			//Port D en sortie
	GLCD_RW=0;					// Positionnement du bit pour �criture

	WR_DATA = data;				// Placement des donn�es sur le registre du GLCD

	// Delay10TCYx (10); 			//d�lai 8,33ms

	GLCD_E = 1;					//Passage de E de 0 � 1
	__delay_us(1); //Delay1TCY(); 				//d�lai 833ns revu a 500ns
	GLCD_E = 0;					//Passage de E de 1 � 0
	__delay_us(1); //Delay1TCY(); 				//d�lai 833ns revu a 500ns							
								// Le GLCD r�cup�re les donn�es !
								
	GLCD_CS1 = 0;
	GLCD_CS2 = 0;				// relachement des ChipSelect
}


//************************************************************************
// void WriteChar(unsigned char ch)
//************************************************************************
void glcd_FillScreen(unsigned char color)
{
unsigned char i, j;
								
	for(i = 0; i < 8; i ++)							// Boucle sur les pages verticales
	{
		GLCD_RS=0; 									// Positionnement du bit pour instruction (adressage)
      	glcd_WriteByte(GLCD_LEFT, 0b01000000);      // Envoi la position horizontale � 0
      	glcd_WriteByte(GLCD_RIGHT, 0b01000000);
      	glcd_WriteByte(GLCD_LEFT, i | 0b10111000);  // Envoi la position verticale (page 0)
      	glcd_WriteByte(GLCD_RIGHT, i | 0b10111000);
      	GLCD_RS=1;                                  // Positionnement du bit pour transfert de donn�es
		
			for(j = 0; j < 64; j++)					// Boucle sur les colonnes
			{
			 glcd_WriteByte(GLCD_LEFT, 0xFF*color);  // Allume ou �teint les pixels
         	 glcd_WriteByte(GLCD_RIGHT, 0xFF*color); 
			}
		
	}
}

//************************************************************************
// void WriteByte(unsigned char byt)
//************************************************************************
unsigned char glcd_ReadByte(unsigned char side)
{
unsigned char data;
	
	if(side)
	{                   // S�lection du cot� pour l'�criture
     	GLCD_CS1 = 1;
		GLCD_CS2 = 0;
	}
   	else
	{
		GLCD_CS2 = 0;
      	GLCD_CS2 = 1;
	}	

	GLCD_DATA_TRIS = 0xFF;	//Port D en entr�e
	GLCD_RW = 1;			// Positionnement du bit pour lecture
	
	// Delay10TCYx (10); 		//d�lai 8,33ms
	
	GLCD_E = 1;				//Passage de E de 0 � 1
	__delay_us(1); //Delay1TCY(); 				//d�lai 833ns revu a 500ns
	
	data = RD_DATA;			// R�cup�ration des donn�es
	GLCD_E = 0;				//Passage de E de 1 � 0
	__delay_us(1); //Delay1TCY(); 				//d�lai 833ns revu a 500ns
	
	GLCD_CS1 = 0;
	GLCD_CS2 = 0;				// relachement des ChipSelect

	return data;	
}

//************************************************************************
// void glcd_PlotPixel(unsigned char xpos, unsigned char ypos, unsigned char color)
//************************************************************************
void glcd_PlotPixel(unsigned char xpos, unsigned char ypos, unsigned char color)
{
   	unsigned char data;
   	unsigned char side = GLCD_LEFT;  			// On initialise sur le cot� gauche

   	if(xpos > 63)             						// Si ce n'est pas le c�t� gauche, c'est le droit
   	{
      	xpos -= 64;
      	side = GLCD_RIGHT;
   	}
   	GLCD_RS=0;                        			 // Positionnement du bit pour instruction (adressage)
	
	xpos &=0b01111111;								// force � 0 le MSB
	xpos |=0b01000000;								// Positionne � 1 le bit 6.
	glcd_WriteByte(side, (xpos));                  	// Envoi la position horizontale
	glcd_WriteByte(side, (((ypos/8)) & 0xBF) | 0xB8);   // Envoi la position verticale (page)
	
	GLCD_RS=1;                        				// Positionnement du bit pour r�cup�ration de donn�es
	
	glcd_ReadByte(side);                         	// On doit lire 2 fois pour obtenir les donn�es
	data = glcd_ReadByte(side);                  	//  � l'adresse intialis�e 
	
	GLCD_RS=0;                        			 	// Positionnement du bit pour instruction (adressage)
	
	glcd_WriteByte(side, xpos);                 	// reinitialise la position horizontale, incrementer lors de la lecture	

	if(color)    
		data=(data)|(1<<(ypos%8));					//Allume le pixel sans modifier les autres
	else                           
		data =(data)&(~(1<<(ypos%8)));				//Eteint le pixel sans modifier les autres
		
	GLCD_RS=1;  			       					// Positionnement du bit pour envoi de donn�es
	
	glcd_WriteByte(side, data);   					// On �crit les donn�es
}

//************************************************************************
// void glcd_SetCursor(unsigned char xpos,unsigned char ypos)
//************************************************************************
void glcd_SetCursor(unsigned char xpos,unsigned char ypos)
{
	unsigned char side = GLCD_LEFT;  			// On initialise sur le cot� gauche

	if(xpos > 127 | ypos > 7)					// Si les coordonn�es sont Hors limite, on ne traite pas
		return;

	x = xpos;									// Sauvegarde des donn�es position absolue
	y = ypos;

   	if(xpos > 63)             					// Si ce n'est pas le c�t� gauche, c'est le droit
   	{
      xpos -= 64;								// xpos est la position relative au controleur G ou D
      side = GLCD_RIGHT;
   	}	

	GLCD_RS=0; 									//Placement du bit pour envoi instruction (adressage)
		glcd_WriteByte(side, 0x40 | xpos);		//Envoi de l'adresse horizontale
		glcd_WriteByte(side, 0xB8 | ypos);		//Envoi de l'adresse verticale
	GLCD_RS=1; 									//Placement du bit pour transfert de donn�e
}

//************************************************************************
// void glcd_Rect(unsigned char xs, unsigned char ys, unsigned char ye ,unsigned char ye,unsigned char color)
//************************************************************************

void glcd_Rect(unsigned char xs, unsigned char ys, unsigned char xe ,unsigned char ye,unsigned char color)
{
   unsigned char i,j;
   if (ys>ye)	return;
   if (xs>xe)	return;

   for(i=xs;i<=xe;i++)
     {
        for(j=ys;j<=ye;j++)
          {
             if( i == xs || i ==xe || j == ye || j == ys )
               glcd_PlotPixel(i,j,color);
          }
     }
}


void glcd_print_tab(unsigned char tabAffichage[HEIGHT_TAB][WIDTH_TAB])
{
    glcd_Rect(1,21,90,62,1);
    unsigned char i,j;
    // glcd_Rect(0,20,90,62,1);
    for(i=0;i<=9;i++)
      {
         for(j=0;j<=21;j++)
           {
              if( tabAffichage[j][i] == TRUE)
              {
                 glcd_draw_cube(i,j,1);
              }
              if( tabAffichage[j][i] == FALSE)
              {
                 glcd_draw_cube(i,j,0);
              }
           }
      }
    }


void glcd_draw_cube(unsigned char y, unsigned char x, unsigned char color)
{

    glcd_Rect(4*(x+1) - 2, 61 - 4*y - 3 , 4*(x+1) + 1 , 61 - 4*y ,color);
    glcd_Rect(4*(x+1) - 1, 61 - 4*y - 2 , 4*(x+1)  , 61 - 4*y - 1 ,color);

}

void glcd_draw_shape(unsigned char forme[4][2], unsigned char color)
{

    unsigned char j;



    for(j=0;j<=3;j++)
      {
        glcd_draw_cube(forme[j][1],forme[j][0],color);
      }
}






