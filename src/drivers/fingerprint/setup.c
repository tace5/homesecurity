//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "setup.h"
#include "../../utils/utils.h"
#include "controller.h"
#include "commands.h"

void __attribute__ ((interrupt)) handle_interrupt();

void init() {
    _delay(1000);  // Sleep for 1s to let sensor startup
}

void config_uart() {  // Using UART2 on PIN 39 (RX) and PIN 40 (TX)
    U2BRGSET = gen_UxBRG(80000000, 57600);
    U2STASET = 0x1480;  // Status and Control bits : 0001 0100 1000 0000
    U2MODESET = 0x80A0;  // MODE bits : 1000 0000 1010 0000
}

void setup() {
    TRISESET = 0x1;  // Set port connected to Sout to input (PIN 26) and port connected to Vtouch to output (PIN 27)
    register_interrupts();
    config_uart();
    force_handshake();
}

void register_interrupts() {
    IEC(1) |= 0x200;  // Enable UART Receiver interrupt
    IPC(8) |= 0x1C;  // Set priority
}

void handle_interrupt() {
    handle_sensor_output();
}
