//
// Created by Linus on 2018-03-31.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "state_functions.h"

void *led1_on(){
    //Turn on led1
    PORTESET = 0x4;
    return led1_off;
}

void *led1_off(){
    //Turn off led1
    PORTECLR = 0x4;
    return led2_on;
}


void *led2_on(){
    //Turn on led2
    PORTESET = 0x8;
    return led2_off;
}

void *led2_off(){
    //Turn off led2
    PORTECLR = 0x8;
    return led1_on;
}
