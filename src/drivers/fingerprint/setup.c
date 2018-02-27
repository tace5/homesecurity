//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "setup.h"
#include "../../utils/utils.h"

void init(){
    timeout(1000);  // Sleep for 300ms to let sensor startup
}

void config_uart(){  // Using UART2 on PIN 39 (RX) and PIN 40 (TX)
    U2BRGSET = gen_UxBRG(80000000, 57600);
    U2STASET = 0x5400;  // Status and Control bits : 0101 0100 0000 0000
    U2MODESET = 0x80A0;  // MODE bits : 1000 0000 1010 0000
}

void handshake(){

}

void setup(){
    TRISESET = 0x1;  // Set port connected to Sout to input (PIN 26) and port connected to Vtouch to output (PIN 27)
    config_uart();
    register_interrupts();
}

void register_interrupts(){
    IECSET(1) = 0x600;  // Enable UART Receiver and Transmitter interrupts
}
