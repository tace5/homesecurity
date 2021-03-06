//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "setup.h"
#include "../../utils/utils.h"
#include "../../controllers/fingerprint_sensor.h"
#include "commands.h"

void init() {
    _delay(1000);  // Sleep for 1s to let sensor startup
}

void config_uart() {  // Using UART1 on PIN 0 (RX) and PIN 1 (TX)
    U1BRG = gen_UxBRG(80000000, 57600);
    U1STA = 0;
    U1MODESET = 0x8000;  // MODE bits : 1000 0000 0000 0000
    U1STASET = 0x1400;  // Status and Control bits : 0001 0100 0000 0000
}

void setup() {
    TRISESET = 0x1;  // Set port connected to Sout to input (PIN 26) and port connected to Vtouch to output (PIN 27)
    config_uart();
    register_interrupts();
    force_handshake();
}

void register_interrupts() {
    INTCONSET = 0x4;
    IECSET(0) = FINGER_TOUCH_INT;      // Enable INT2 interrupt
    IPCSET(2) = 0x1F000000; // Set priority = 7 and sub = 3
}
