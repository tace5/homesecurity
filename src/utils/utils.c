//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "utils.h"


char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

// /**
// * Generate the UxBRG value for the peripheral bus
// * from the current processor frequency and the desired baud rate.
// **/
int gen_UxBRG(int processor_freq, int baud_rate){
    int exp = (*(&DEVCFG1) & DEVCFG1_FPBDIV_MASK) >> 12;
    int fr = processor_freq / (0x1 << exp);
    int baud = PIC32_BRG_BAUD(fr, baud_rate);

    return baud;
}
