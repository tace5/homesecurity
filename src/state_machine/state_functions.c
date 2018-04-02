//
// Created by Linus on 2018-03-31.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../drivers/display/display_functions.h"
#include "state_functions.h"

void *boot(){
    //If config is already set by talking to fingerprint sensor.
    return wait_to_arm;

    //Else
    return wait_for_api;
}

void *wait_for_api(){
    //Enable raspberry (I2C) interrupt

    //Wait for interrupt

    //Check for flag that interrupt sets

    //If set
    //Disable raspberry (I2C) interrupt
    return config_mode;
}

void *config_mode(){
    //Register fingerprint
}

void *wait_to_arm(){
    //Enable raspberry (I2C) interrupt
    //Enable fingerprint (UART) interrupt

    //Wait for either interrupt flag to be set

    //Disable interrupts

    //If interrupt flag set for fingerprint (UART)
    return arming;

    //If interrupt flag set for raspberry (I2C)
    return config_mode;
}

void *arming(){
    //Authenticate user with fingerprint

    //If successful
    return armed;

    //If unsuccessful
    return wait_to_arm;
}

void *armed(){
    //Enable fingerprint (UART) interrupt
    //Enable US sensor interrupt

    //Wait for interrupt

    //Disable interrupts

    //If interrupt flag set for US sensor
    return alarm_triggered;

    //If interrupt flag set for fingerprint (UART)
    return disarming;
}

void *disarming(){
    //Authenticate users fingerprint

    //If successful
    //Send disarmed message to users phone
    return wait_to_arm;

    //If unsuccessful

    //If alarm has been triggered
    //Send failed try message to users phone
    return alarm_triggered;

    //If alarm hasn't been triggered
    return armed;
}

void *alarm_triggered(){
    //Send alarm triggered message to users phone
    //Visual feedback
    //Enable fingerprint (UART) interrupt

    //Wait for fingerprint interrupt

    //If interrupt flag set for fingerprint (UART)
    return disarming;
}
