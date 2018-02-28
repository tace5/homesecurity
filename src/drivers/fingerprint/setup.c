//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "setup.h"
#include "../../utils/utils.h"
#include "controller.h"

void __attribute__ ((interrupt)) handle_interrupt();

void init() {
    timeout(1000);  // Sleep for 300ms to let sensor startup
}

void config_uart() {  // Using UART2 on PIN 39 (RX) and PIN 40 (TX)
    U2BRGSET = gen_UxBRG(80000000, 57600);
    U2STASET = 0x1480;  // Status and Control bits : 0001 0100 1000 0000
    U2MODESET = 0x80A0;  // MODE bits : 1000 0000 1010 0000
}

void handshake() {
    //TODO - Set package info for handshake command
    int data[1];
    *data = 0xABCD1234;
    int len = 4;
    int pid = 0x1;

    uint8_t packet[get_total_package_length(len)];

    pack(pid, len, data, 0, packet);
}

void setup() {
    TRISESET = 0x1;  // Set port connected to Sout to input (PIN 26) and port connected to Vtouch to output (PIN 27)
    config_uart();
    register_interrupts();
    handshake();
}

void register_interrupts() {
    IECSET(1) = 0x200;  // Enable UART Receiver interrupt
}

void handle_interrupt() {
    handle_sensor_output((int *) U2RXREG);
}
