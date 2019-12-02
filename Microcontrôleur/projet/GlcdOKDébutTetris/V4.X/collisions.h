#include "data.h"

unsigned short checkCollision(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned char forme[4][2]);

void putPiece(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned char forme[4][2]);

unsigned short checkLine(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned short line);

void eraseLine(unsigned char tab[HEIGHT_TAB][WIDTH_TAB], unsigned short line);