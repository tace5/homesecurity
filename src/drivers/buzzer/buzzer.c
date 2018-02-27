//
// Created by Linus Bein Fahlander on 2018-02-27.
//

#include "buzzer.h"
#include "../../utils/utils.h"
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
/*  NOT WORKING ATM, TODO
void buzz(int duration) {
    SYSTEMConfigPerformance(80000000);

    // Set OC1 to pin RB7 with peripheral pin select
    RPB7Rbits.RPB7R = 0x0005;

    // Configure standard PWM mode for output compare module 1
    OC1CON = 0x0006;

    // A write to PRy configures the PWM frequency
    // PR = [FPB / (PWM Frequency * TMR Prescale Value)] – 1
    // : note the TMR Prescaler is 1 and is thus ignored
    PR2 = (SYSCLK / PWM_FREQ) - 1;

    // A write to OCxRS configures the duty cycle
    // : OCxRS / PRy = duty cycle
    OC1RS = (PR2 + 1) * ((float) DUTY_CYCLE / 100);

    T2CONSET = 0x8000;      // Enable Timer2, prescaler 1:1
    OC1CONSET = 0x8000;     // Enable Output Compare Module 1

    int i = 0;
    while (i < 5720842){
        asm("NOP");
        i++;
    }

    return 1;
}
*/
