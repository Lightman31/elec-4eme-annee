
#include "main.h"
#include "data.h"



unsigned char partition[30][2] = {
    {185,0}, //185
    {69,1}, //69 -1
    {74,2}, //74 +1
    {165,3}, //165
    {74,2}, // 74 +1
    {69,1}, // 69 -1
    {125,4}, // 125
    {62,4}, // 62 -2
    {74,2}, // 74 +1
    {185,0}, // 185
    {82,3}, // 82 -2
    {74,2}, // 74 +1
    {207,1}, // 207 +1
    {74,2}, // 74 +1
    {165,3}, // 165
    {185,0}, // 185
    {147,2}, // 147 -2
    {125,4}, // 125
    {125,4}, // 125
    {165,3}, // 165
    {99,5}, // 99 +1
    {125,7}, // 125
    {111,6}, // 111 -1
    {99,5}, // 99 +1
    {255,0}, // 255 -beaucoup
    {74,2}, // 74 +1
    {185,0}, // 185
    {82,3}, // 82 -2
    {74,2}, //74 +1
    {139,1}, //139 +1
};

/*
unsigned char partitionperte[12][2] = {
    {990,6}, // 247 -2
    {760,3}, // 190
    {654,1}, // 163 -2 
    {987,0}, // 247 +1
    {1120,9}, //255 -beaucoup
    {987,0}, // 247 +1
    {1083,8}, // 255 -beaucoup
    {1203,5}, // 255 -beaucoup
    {1083,8}, // 255 -beaucoup
    {1120,3}, // 255 -beaucoup
    {980,2}, // 245
    {1220,3}, // 255 -beaucoup
	};
*/

void delay_notes(unsigned int var){
    while(var !=1){
        var--;    
    }   
}

void la(){
    PORTCbits.RC2 = 1;
    delay_notes(356);
    PORTCbits.RC2 = 0;
    delay_notes(356);
}

void sib(){
    PORTCbits.RC2 = 1;
    delay_notes(338);
    PORTCbits.RC2 = 0;
    delay_notes(338);
}

void si(){
    PORTCbits.RC2 = 1;
    delay_notes(318);
    PORTCbits.RC2 = 0;
    delay_notes(318);
}

void don(){
    PORTCbits.RC2 = 1;
    delay_notes(300);
    PORTCbits.RC2 = 0;
    delay_notes(300);
}
/*
void red(){
    PORTCbits.RC2 = 1;
    Delay(284);
    PORTCbits.RC2 = 0;
    Delay(284);
}
*/
void re(){
    PORTCbits.RC2 = 1;
    delay_notes(268);
    PORTCbits.RC2 = 0;
    delay_notes(268);
}

void mib(){
    PORTCbits.RC2 = 1;
    delay_notes(253);
    PORTCbits.RC2 = 0;
    delay_notes(253);
}

void mi(){
    PORTCbits.RC2 = 1;
    delay_notes(239);
    PORTCbits.RC2 = 0;
    delay_notes(239);
}

void fa(){
    PORTCbits.RC2 = 1;
    delay_notes(225);
    PORTCbits.RC2 = 0;
    delay_notes(225);
}

void factest(){
    PORTCbits.RC2 = 1;
    delay_notes(225);
    PORTCbits.RC2 = 0;
    delay_notes(225);
}

void solb(){
    PORTCbits.RC2 = 1;
    delay_notes(213);
    PORTCbits.RC2 = 0;
    delay_notes(213);
}

void sol(){
    PORTCbits.RC2 = 1;
    delay_notes(200);
    PORTCbits.RC2 = 0;
    delay_notes(200);
}

void lab(){
    PORTCbits.RC2 = 1;
    delay_notes(190);
    PORTCbits.RC2 = 0;
    delay_notes(190);
}

void lao(){
    PORTCbits.RC2 = 1;
    delay_notes(178);
    PORTCbits.RC2 = 0;
    delay_notes(178);
    
    
}

void pause(){
    PORTCbits.RC2 =0;
}



void musique(){
    TRISCbits.RC2 = 0;
    
    int i, z ;
    for (i = 0 ; i < 37 ; i++)
    {
       for( z=0 ; z <( ((int) partition[i][0]*4)/tempo); z++ ){
            if (partition[i][1] == MI ) mi(); 
            if (partition[i][1] == SI ) si(); 
            if (partition[i][1] == DO ) don(); 
            if (partition[i][1] == RE ) re(); 
            if (partition[i][1] == LA ) la();
            if (partition[i][1] == FA ) fa();
            if (partition[i][1] == SOL ) sol();
            if (partition[i][1] == LAO ) lao();
        }
    }
    
}

 

/*
void musiqueperdu(){
    TRISCbits.RC2 = 0;
    
    int i, z ;
    for (i = 0 ; i < 12 ; i++)
    {
       for( z=0 ; z <( partitionperte[i][0]*4/tempo2); z++ ){
            if (partitionperte[i][1] == MI ) mi(); 
            if (partitionperte[i][1] == SI ) si();  
            if (partitionperte[i][1] == RE ) re(); 
            if (partitionperte[i][1] == LA ) la();
            if (partitionperte[i][1] == FA ) fa();
            if (partitionperte[i][1] == DO ) don();
            if (partitionperte[i][1] == SOL ) sol();
            if (partitionperte[i][1] == LAO ) lao();
            if (partitionperte[i][1] == SOLB ) solb();
            if (partitionperte[i][1] == MIB ) mib();
        }
    }
    
}

*/



