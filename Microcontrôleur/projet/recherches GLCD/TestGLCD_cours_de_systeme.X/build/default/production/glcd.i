# 1 "glcd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "glcd.c" 2






# 1 "./glcd.h" 1


# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\ctype.h" 1 3







# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\features.h" 1 3
# 8 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\ctype.h" 2 3


int isalnum(int);
int isalpha(int);
int isblank(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);
# 3 "./glcd.h" 2
# 40 "./glcd.h"
extern void glcd_Init(unsigned char mode);
extern void glcd_WriteByte(unsigned char side, unsigned char data);
extern unsigned char glcd_ReadByte(unsigned char side);
extern void glcd_PlotPixel(unsigned char x, unsigned char y, unsigned char color);
extern void glcd_SetCursor(unsigned char xpos,unsigned char ypos);
void glcd_Rect(unsigned char xs, unsigned char ys, unsigned char xe ,unsigned char ye,unsigned char color);
extern void glcd_FillScreen(unsigned char color);
extern void glcd_WriteChar8X8( unsigned char ch, unsigned char color);
extern void glcd_WriteChar3x6( unsigned char ch, unsigned char color);
extern void glcd_WriteString(const char str[],unsigned char font,unsigned char color);
extern void glcd_Image(void);
void glcd_text_write(const char str[], unsigned char x, unsigned char y);
# 7 "glcd.c" 2



const unsigned char Font3x6[65][3]={
     0x00,0x00,0x00,
     0x00,0x5C,0x00,
     0x0C,0x00,0x0C,
     0x7C,0x28,0x7C,
     0x7C,0x44,0x7C,
     0x24,0x10,0x48,
     0x28,0x54,0x08,
     0x00,0x0C,0x00,
     0x38,0x44,0x00,
     0x44,0x38,0x00,
     0x20,0x10,0x08,
     0x10,0x38,0x10,
     0x80,0x40,0x00,
     0x10,0x10,0x10,
     0x00,0x40,0x00,
     0x20,0x10,0x08,
     0x38,0x44,0x38,
     0x00,0x7C,0x00,
     0x64,0x54,0x48,
     0x44,0x54,0x28,
     0x1C,0x10,0x7C,
     0x4C,0x54,0x24,
     0x38,0x54,0x20,
     0x04,0x74,0x0C,
     0x28,0x54,0x28,
     0x08,0x54,0x38,
     0x00,0x50,0x00,
     0x80,0x50,0x00,
     0x10,0x28,0x44,
     0x28,0x28,0x28,
     0x44,0x28,0x10,
     0x04,0x54,0x08,
     0x38,0x4C,0x5C,
     0x78,0x14,0x78,
     0x7C,0x54,0x28,
     0x38,0x44,0x44,
     0x7C,0x44,0x38,
     0x7C,0x54,0x44,
     0x7C,0x14,0x04,
     0x38,0x44,0x34,
     0x7C,0x10,0x7C,
     0x00,0x7C,0x00,
     0x20,0x40,0x3C,
     0x7C,0x10,0x6C,
     0x7C,0x40,0x40,
     0x7C,0x08,0x7C,
     0x7C,0x04,0x7C,
     0x7C,0x44,0x7C,
     0x7C,0x14,0x08,
     0x38,0x44,0x78,
     0x7C,0x14,0x68,
     0x48,0x54,0x24,
     0x04,0x7C,0x04,
     0x7C,0x40,0x7C,
     0x3C,0x40,0x3C,
     0x7C,0x20,0x7C,
     0x6C,0x10,0x6C,
     0x1C,0x60,0x1C,
     0x64,0x54,0x4C,
     0x7C,0x44,0x00,
     0x08,0x10,0x20,
     0x44,0x7C,0x00,
     0x08,0x04,0x08,
     0x80,0x80,0x80,
     0x04,0x08,0x00
};





const unsigned char Font8x8[2048] =
{
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 6, 95, 95, 6, 0, 0, 0,
   0, 7, 7, 0, 7, 7, 0, 0,
   20, 127, 127, 20, 127, 127, 20, 0,
   36, 46, 107, 107, 58, 18, 0, 0,
   70, 102, 48, 24, 12, 102, 98, 0,
   48, 122, 79, 93, 55, 122, 72, 0,
   4, 7, 3, 0, 0, 0, 0, 0,
   0, 28, 62, 99, 65, 0, 0, 0,
   0, 65, 99, 62, 28, 0, 0, 0,
   8, 42, 62, 28, 28, 62, 42, 8,
   8, 8, 62, 62, 8, 8, 0, 0,
   0, 128, 224, 96, 0, 0, 0, 0,
   8, 8, 8, 8, 8, 8, 0, 0,
   0, 0, 96, 96, 0, 0, 0, 0,
   96, 48, 24, 12, 6, 3, 1, 0,
   62, 127, 113, 89, 77, 127, 62, 0,
   64, 66, 127, 127, 64, 64, 0, 0,
   98, 115, 89, 73, 111, 102, 0, 0,
   34, 99, 73, 73, 127, 54, 0, 0,
   24, 28, 22, 83, 127, 127, 80, 0,
   39, 103, 69, 69, 125, 57, 0, 0,
   60, 126, 75, 73, 121, 48, 0, 0,
   3, 3, 113, 121, 15, 7, 0, 0,
   54, 127, 73, 73, 127, 54, 0, 0,
   6, 79, 73, 105, 63, 30, 0, 0,
   0, 0, 102, 102, 0, 0, 0, 0,
   0, 128, 230, 102, 0, 0, 0, 0,
   8, 28, 54, 99, 65, 0, 0, 0,
   36, 36, 36, 36, 36, 36, 0, 0,
   0, 65, 99, 54, 28, 8, 0, 0,
   2, 3, 81, 89, 15, 6, 0, 0,
   62, 127, 65, 93, 93, 31, 30, 0,
   124, 126, 19, 19, 126, 124, 0, 0,
   65, 127, 127, 73, 73, 127, 54, 0,
   28, 62, 99, 65, 65, 99, 34, 0,
   65, 127, 127, 65, 99, 62, 28, 0,
   65, 127, 127, 73, 93, 65, 99, 0,
   65, 127, 127, 73, 29, 1, 3, 0,
   28, 62, 99, 65, 81, 115, 114, 0,
   127, 127, 8, 8, 127, 127, 0, 0,
   0, 65, 127, 127, 65, 0, 0, 0,
   48, 112, 64, 65, 127, 63, 1, 0,
   65, 127, 127, 8, 28, 119, 99, 0,
   65, 127, 127, 65, 64, 96, 112, 0,
   127, 127, 14, 28, 14, 127, 127, 0,
   127, 127, 6, 12, 24, 127, 127, 0,
   28, 62, 99, 65, 99, 62, 28, 0,
   65, 127, 127, 73, 9, 15, 6, 0,
   30, 63, 33, 113, 127, 94, 0, 0,
   65, 127, 127, 9, 25, 127, 102, 0,
   38, 111, 77, 89, 115, 50, 0, 0,
   3, 65, 127, 127, 65, 3, 0, 0,
   127, 127, 64, 64, 127, 127, 0, 0,
   31, 63, 96, 96, 63, 31, 0, 0,
   127, 127, 48, 24, 48, 127, 127, 0,
   67, 103, 60, 24, 60, 103, 67, 0,
   7, 79, 120, 120, 79, 7, 0, 0,
   71, 99, 113, 89, 77, 103, 115, 0,
   0, 127, 127, 65, 65, 0, 0, 0,
   1, 3, 6, 12, 24, 48, 96, 0,
   0, 65, 65, 127, 127, 0, 0, 0,
   8, 12, 6, 3, 6, 12, 8, 0,
   128, 128, 128, 128, 128, 128, 128, 128,
   0, 0, 3, 7, 4, 0, 0, 0,
   32, 116, 84, 84, 60, 120, 64, 0,
   65, 127, 63, 72, 72, 120, 48, 0,
   56, 124, 68, 68, 108, 40, 0, 0,
   48, 120, 72, 73, 63, 127, 64, 0,
   56, 124, 84, 84, 92, 24, 0, 0,
   72, 126, 127, 73, 3, 2, 0, 0,
   152, 188, 164, 164, 248, 124, 4, 0,
   65, 127, 127, 8, 4, 124, 120, 0,
   0, 68, 125, 125, 64, 0, 0, 0,
   96, 224, 128, 128, 253, 125, 0, 0,
   65, 127, 127, 16, 56, 108, 68, 0,
   0, 65, 127, 127, 64, 0, 0, 0,
   124, 124, 24, 56, 28, 124, 120, 0,
   124, 124, 4, 4, 124, 120, 0, 0,
   56, 124, 68, 68, 124, 56, 0, 0,
   132, 252, 248, 164, 36, 60, 24, 0,
   24, 60, 36, 164, 248, 252, 132, 0,
   68, 124, 120, 76, 4, 28, 24, 0,
   72, 92, 84, 84, 116, 36, 0, 0,
   0, 4, 62, 127, 68, 36, 0, 0,
   60, 124, 64, 64, 60, 124, 64, 0,
   28, 60, 96, 96, 60, 28, 0, 0,
   60, 124, 112, 56, 112, 124, 60, 0,
   68, 108, 56, 16, 56, 108, 68, 0,
   156, 188, 160, 160, 252, 124, 0, 0,
   76, 100, 116, 92, 76, 100, 0, 0,
   8, 8, 62, 119, 65, 65, 0, 0,
   0, 0, 0, 119, 119, 0, 0, 0,
   65, 65, 119, 62, 8, 8, 0, 0,
   2, 3, 1, 3, 2, 3, 1, 0,
   112, 120, 76, 70, 76, 120, 112, 0,
   14, 159, 145, 177, 251, 74, 0, 0,
   58, 122, 64, 64, 122, 122, 64, 0,
   56, 124, 84, 85, 93, 25, 0, 0,
   2, 35, 117, 85, 85, 125, 123, 66,
   33, 117, 84, 84, 125, 121, 64, 0,
   33, 117, 85, 84, 124, 120, 64, 0,
   32, 116, 87, 87, 124, 120, 64, 0,
   24, 60, 164, 164, 228, 64, 0, 0,
   2, 59, 125, 85, 85, 93, 27, 2,
   57, 125, 84, 84, 93, 25, 0, 0,
   57, 125, 85, 84, 92, 24, 0, 0,
   1, 69, 124, 124, 65, 1, 0, 0,
   2, 3, 69, 125, 125, 67, 2, 0,
   1, 69, 125, 124, 64, 0, 0, 0,
   121, 125, 22, 18, 22, 125, 121, 0,
   112, 120, 43, 43, 120, 112, 0, 0,
   68, 124, 124, 85, 85, 69, 0, 0,
   32, 116, 84, 84, 124, 124, 84, 84,
   124, 126, 11, 9, 127, 127, 73, 0,
   50, 123, 73, 73, 123, 50, 0, 0,
   50, 122, 72, 72, 122, 50, 0, 0,
   50, 122, 74, 72, 120, 48, 0, 0,
   58, 123, 65, 65, 123, 122, 64, 0,
   58, 122, 66, 64, 120, 120, 64, 0,
   154, 186, 160, 160, 250, 122, 0, 0,
   1, 25, 60, 102, 102, 60, 25, 1,
   61, 125, 64, 64, 125, 61, 0, 0,
   24, 60, 36, 231, 231, 36, 36, 0,
   104, 126, 127, 73, 67, 102, 32, 0,
   43, 47, 252, 252, 47, 43, 0, 0,
   255, 255, 9, 9, 47, 246, 248, 160,
   64, 192, 136, 254, 127, 9, 3, 2,
   32, 116, 84, 85, 125, 121, 64, 0,
   0, 68, 125, 125, 65, 0, 0, 0,
   48, 120, 72, 74, 122, 50, 0, 0,
   56, 120, 64, 66, 122, 122, 64, 0,
   122, 122, 10, 10, 122, 112, 0, 0,
   125, 125, 25, 49, 125, 125, 0, 0,
   0, 38, 47, 41, 47, 47, 40, 0,
   0, 38, 47, 41, 47, 38, 0, 0,
   48, 120, 77, 69, 96, 32, 0, 0,
   56, 56, 8, 8, 8, 8, 0, 0,
   8, 8, 8, 8, 56, 56, 0, 0,
   79, 111, 48, 24, 204, 238, 187, 145,
   79, 111, 48, 24, 108, 118, 251, 249,
   0, 0, 0, 123, 123, 0, 0, 0,
   8, 28, 54, 34, 8, 28, 54, 34,
   34, 54, 28, 8, 34, 54, 28, 8,
   170, 0, 85, 0, 170, 0, 85, 0,
   170, 85, 170, 85, 170, 85, 170, 85,
   221, 255, 170, 119, 221, 170, 255, 119,
   0, 0, 0, 255, 255, 0, 0, 0,
   16, 16, 16, 255, 255, 0, 0, 0,
   20, 20, 20, 255, 255, 0, 0, 0,
   16, 16, 255, 255, 0, 255, 255, 0,
   16, 16, 240, 240, 16, 240, 240, 0,
   20, 20, 20, 252, 252, 0, 0, 0,
   20, 20, 247, 247, 0, 255, 255, 0,
   0, 0, 255, 255, 0, 255, 255, 0,
   20, 20, 244, 244, 4, 252, 252, 0,
   20, 20, 23, 23, 16, 31, 31, 0,
   16, 16, 31, 31, 16, 31, 31, 0,
   20, 20, 20, 31, 31, 0, 0, 0,
   16, 16, 16, 240, 240, 0, 0, 0,
   0, 0, 0, 31, 31, 16, 16, 16,
   16, 16, 16, 31, 31, 16, 16, 16,
   16, 16, 16, 240, 240, 16, 16, 16,
   0, 0, 0, 255, 255, 16, 16, 16,
   16, 16, 16, 16, 16, 16, 16, 16,
   16, 16, 16, 255, 255, 16, 16, 16,
   0, 0, 0, 255, 255, 20, 20, 20,
   0, 0, 255, 255, 0, 255, 255, 16,
   0, 0, 31, 31, 16, 23, 23, 20,
   0, 0, 252, 252, 4, 244, 244, 20,
   20, 20, 23, 23, 16, 23, 23, 20,
   20, 20, 244, 244, 4, 244, 244, 20,
   0, 0, 255, 255, 0, 247, 247, 20,
   20, 20, 20, 20, 20, 20, 20, 20,
   20, 20, 247, 247, 0, 247, 247, 20,
   20, 20, 20, 23, 23, 20, 20, 20,
   16, 16, 31, 31, 16, 31, 31, 16,
   20, 20, 20, 244, 244, 20, 20, 20,
   16, 16, 240, 240, 16, 240, 240, 16,
   0, 0, 31, 31, 16, 31, 31, 16,
   0, 0, 0, 31, 31, 20, 20, 20,
   0, 0, 0, 252, 252, 20, 20, 20,
   0, 0, 240, 240, 16, 240, 240, 16,
   16, 16, 255, 255, 16, 255, 255, 16,
   20, 20, 20, 255, 255, 20, 20, 20,
   16, 16, 16, 31, 31, 0, 0, 0,
   0, 0, 0, 240, 240, 16, 16, 16,
   255, 255, 255, 255, 255, 255, 255, 255,
   240, 240, 240, 240, 240, 240, 240, 240,
   255, 255, 255, 255, 0, 0, 0, 0,
   0, 0, 0, 0, 255, 255, 255, 255,
   15, 15, 15, 15, 15, 15, 15, 15,
   56, 124, 68, 108, 56, 108, 68, 0,
   252, 254, 42, 42, 62, 20, 0, 0,
   126, 126, 2, 2, 6, 6, 0, 0,
   2, 126, 126, 2, 126, 126, 2, 0,
   99, 119, 93, 73, 99, 99, 0, 0,
   56, 124, 68, 124, 60, 4, 4, 0,
   128, 254, 126, 32, 32, 62, 30, 0,
   4, 6, 2, 126, 124, 6, 2, 0,
   153, 189, 231, 231, 189, 153, 0, 0,
   28, 62, 107, 73, 107, 62, 28, 0,
   76, 126, 115, 1, 115, 126, 76, 0,
   48, 120, 74, 79, 125, 57, 0, 0,
   24, 60, 36, 60, 60, 36, 60, 24,
   152, 252, 100, 60, 62, 39, 61, 24,

   };




unsigned char x,y;

void wait_for_release(void) {
while(PORTEbits.RE0){};
}





void glcd_Init(unsigned char mode)
{
   TRISA = 0xFF;
   PORTA = 0x00;
   ADCON1 = 0x0F;

   TRISB = 0x00;
   PORTB = 0x00;

   TRISD = 0x00;
   PORTD = 0x00;

   unsigned char i, j, k;


   PORTD = 0x00;
   LATBbits.LATB5 = 0;

   __delay_ms(1500);
   LATBbits.LATB5 = 1;

   LATBbits.LATB4=0;
   LATBbits.LATB0=0;
   LATBbits.LATB1=0;
   LATBbits.LATB2=0;


   __delay_ms(10);
   glcd_WriteByte(0, 0xC0);
   glcd_WriteByte(1, 0xC0);
   glcd_WriteByte(0, 0x40);
   glcd_WriteByte(1, 0x40);
   glcd_WriteByte(0, 0xB8);
   glcd_WriteByte(1, 0xB8);

   if(mode == 1)
     {
       TRISA = 0x00;
       PORTA = 0xFF;
        glcd_WriteByte(0, 0x3F);
        glcd_WriteByte(1, 0x3F);
     }
   else
     {
        glcd_WriteByte(0, 0x3E);
        glcd_WriteByte(1, 0x3E);
     }

   glcd_FillScreen(0);
}




void glcd_WriteByte(unsigned char side, unsigned char data)
{
   if(side)
     {
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 0;
     }
   else
     {
        LATBbits.LATB1 = 0;
        LATBbits.LATB1 = 1;
     }

   TRISD=0;
   LATBbits.LATB3=0;

   LATD = data;



   LATBbits.LATB4 = 1;

   __delay_ms(1);
   LATBbits.LATB4 = 0;

   __delay_ms(1);


   LATBbits.LATB0 = 0;
   LATBbits.LATB1 = 0;
}





unsigned char glcd_ReadByte(unsigned char side)
{
   unsigned char data;

   if(side)
     {
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 0;
     }
   else
     {
        LATBbits.LATB1 = 0;
        LATBbits.LATB1 = 1;
     }

   TRISD = 0xFF;
   LATBbits.LATB3 = 1;



   LATBbits.LATB4 = 1;

   __delay_ms(1);

   data = PORTD;
   LATBbits.LATB4 = 0;

   __delay_ms(1);
   LATBbits.LATB0 = 0;
   LATBbits.LATB1 = 0;

   return data;
}




void glcd_PlotPixel(unsigned char xpos, unsigned char ypos, unsigned char color)
{
   unsigned char data;
   unsigned char side = 0;

   if(xpos > 63)
     {
        xpos -= 64;
        side = 1;
     }
   LATBbits.LATB2=0;

   xpos &=0b01111111;
   xpos |=0b01000000;
   glcd_WriteByte(side, (xpos));
   glcd_WriteByte(side, (((ypos/8)) & 0xBF) | 0xB8);

   LATBbits.LATB2=1;

   glcd_ReadByte(side);
   data = glcd_ReadByte(side);

   LATBbits.LATB2=0;

   glcd_WriteByte(side, xpos);

   if(color)
     data=(data)|(1<<(ypos%8));
   else
     data =(data)&(~(1<<(ypos%8)));

   LATBbits.LATB2=1;

   glcd_WriteByte(side, data);
}





void glcd_Rect(unsigned char xs, unsigned char ys, unsigned char xe ,unsigned char ye,unsigned char color)
{
   unsigned char i,j;
   if (ys>ye) return;
   if (xs>xe) return;

   for(i=xs;i<=xe;i++)
     {
        for(j=ys;j<=ye;j++)
          {
             if( i == xs || i ==xe || j == ye || j == ys )
               glcd_PlotPixel(i,j,color);
          }
     }
}




void glcd_FillScreen(unsigned char color)
{
   unsigned char i, j;

   for(i = 0; i < 8; i ++)
     {
        LATBbits.LATB2=0;
        glcd_WriteByte(0, 0b01000000);
        glcd_WriteByte(1, 0b01000000);
        glcd_WriteByte(0, i | 0b10111000);
        glcd_WriteByte(1, i | 0b10111000);
        LATBbits.LATB2=1;

        for(j = 0; j < 64; j++)
          {
             glcd_WriteByte(0, 0xFF*color);
             glcd_WriteByte(1, 0xFF*color);
          }
     }
}




void glcd_SetCursor(unsigned char xpos,unsigned char ypos)
{
   unsigned char side = 0;

   if(xpos > 127 | ypos > 7)
     return;

   x = xpos;
   y = ypos;

   if(xpos > 63)
     {
        xpos -= 64;
        side = 1;
     }

   LATBbits.LATB2=0;
   glcd_WriteByte(side, 0x40 | xpos);
   glcd_WriteByte(side, 0xB8 | ypos);
   LATBbits.LATB2=1;
}




void glcd_WriteChar8X8(unsigned char ch, unsigned char color)
{
   unsigned char i,xpos;
   unsigned char side = 0;
   unsigned int chr;

   if (ch=='\n')
     {
        x=0;
        y++;
        return;
     }

   if(x > 63)
     {
        side = 1;
        xpos=x-64;
     }
   else
     xpos=x;

   chr = (int)ch*8;

   for(i = 0; i < 8; i++)
     {

        if(xpos > 63)
          {
             xpos -= 64;
             side = 1;
             LATBbits.LATB2=0;
             glcd_WriteByte(side, 0x40 | xpos);
             glcd_WriteByte(side, 0xB8 | y);
             LATBbits.LATB2=1;
          }
        if(color)
          glcd_WriteByte(side,Font8x8[chr+i]);
        else
          glcd_WriteByte(side,~(Font8x8[chr+i]));
        xpos++;
     }
   x+=8;
}





void glcd_WriteChar3x6(unsigned char ch, unsigned char color)
{
   unsigned char i,xpos;
   unsigned char side = 0;

   if (ch=='\n')
     {
        x=0;
        y++;
        return;
     }

   if(x > 63)
     {
        side = 1;
        xpos=x-64;
     }
   else
     xpos=x;

   ch -= 32;

   for(i = 0; i < 3; i++)
     {
        if(xpos > 63)
          {
             xpos -= 64;
             side = 1;
             LATBbits.LATB2=0;
             glcd_WriteByte(side, 0x40 | xpos);
             glcd_WriteByte(side, 0xB8 | y);
             LATBbits.LATB2=1;
          }
        if(color)
          glcd_WriteByte(side,Font3x6[ch][i]);
        else
          glcd_WriteByte(side,~(Font3x6[ch][i]));
        xpos++;
     }
   x+=5;
}





void glcd_WriteString(const char str[],unsigned char font,unsigned char color)
{
   while(*str)
     {
        if(font)
          glcd_WriteChar8X8(*str, color);
        else
          glcd_WriteChar3x6(*str, color);
        str++;
     }
}

void glcd_text_write(const char str[], unsigned char x, unsigned char y)
{

   glcd_SetCursor(x, y);
   glcd_WriteString(str, 1, 1);
}
