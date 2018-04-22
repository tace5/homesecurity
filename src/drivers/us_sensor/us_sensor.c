#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../../utils/utils.h"
#include "us_sensor.h"

void sensor_init(void) {
    TRISECLR = TRIG;
    TRISESET = ECHO;

    T1CON = 0x0;
    T1CONSET = 0x30;
}

void send_pulse(void) {
    PORTESET = TRIG;

    // Hold pulse for 10 us
    TMR1 = 0x0;
    T1CONSET = 0x8000; // Start timer
    while (TMR1 < 800);
    T1CONCLR = 0x8000;

    PORTECLR = TRIG;
}

//Returns the distance in cm
int measure_dist(void) {
    send_pulse();
    TMR1 = 0x0; // Reset timer
    while (!(PORTE & ECHO)); // Wait for Response from sensor

    T1CONSET = 0x8000; // Start timer
    while (PORTE & ECHO);  // Measure hold time of response pulse
    T1CONCLR = 0x8000; // Stop timer

    //display_debug(1, &TMR1);

    return ((TMR1 * 256) / (80 * 58));
}
