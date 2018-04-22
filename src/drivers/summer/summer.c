//
// Created by Ruben Hume on 2018-04-22.
//

#include "summer.h"

void summer_trig() {
    OC1CON = 0x0000; // Turn off the OC1 when performing the setup
    OC1R = 2048; // Initialize primary Compare register
    OC1RS = 2048; // Initialize secondary Compare register
    OC1CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    T2CONSET = 0x30;
    PR2 = 0x270f; // Set period

    // Configure Timer2 interrupt. Note that in PWM mode, the
    // corresponding source timer interrupt flag is asserted.
    // OC interrupt is not generated in PWM mode.
    IFSCLR(0) = 0x00000100; // Clear the T2 interrupt flag
    IECSET(0) = 0x00000100; // Enable T2 interrupt
    IPCSET(2) = 0x0000001C; // Set T2 interrupt priority to 7
    T2CONSET = 0x8000; // Enable Timer2
    OC1CONSET = 0x8000; // Enable OC1
}

void summer_stop() {
    T2CONCLR = 0x8000; // Enable Timer2
    OC1CON = 0x0000; // Enable OC1
}

void summer_isr() {
    if(OC1R == 1024){
        OC1RS = 2048;
    } else {
        OC1RS = 1024;
    }

    IFSCLR(0) = 0x100;
}