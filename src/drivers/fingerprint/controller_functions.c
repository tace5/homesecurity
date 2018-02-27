//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "controller.h"
#include "../display/display_functions.h"

void handle_sensor_output(int *read_port) {
    // Template - Display sensor output on screen
    //int data = *read_port & 0xFF;
    //display_debug(read_port);
    display_string(3, "Interrupt from fingerprint");
    display_update();
}

int pack(int pid, int len, int data, int adder) {
    //TODO - Package data on correct format to send to sensor
    int package_len = (2 + 4 + 1 + 2 + len + 2) *
                      8;  // Calculate the total package length (HEADER + ADDER + PID + LENGTH + DATA(len) + SUM) bytes
    return 0;
}

int unpack(int package) {
    //TODO - Logic for unpacking the package contents depending on package type
    return 0;
}

