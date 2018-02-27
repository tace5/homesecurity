//
// Created by Linus on 2018-02-26.
//

#ifdef _WIN32
#include <Windows.h>
#else
//#include <unistd.h>
#endif
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "utils.h"

void timeout(int ms){
#ifdef _WIN32
    Sleep(ms);
#else
    //usleep(ms*1000);  /* sleep for 100 milliSeconds */
#endif
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
