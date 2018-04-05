//
// Created by Linus on 2018-03-31.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../drivers/display/display_functions.h"
#include "../controllers/fingerprint_sensor.h"
#include "state_functions.h"
#include "../globals.h"

void *boot(){
    display_string(2, "Boot state");
    display_update();
    //If config is already set by talking to fingerprint sensor.
    char status = check_for_stored_print();
    if (status == 0x1) {
        return wait_to_arm;
    }else {
        return wait_for_api;
    }
}

void *wait_for_api(){
    display_string(2, "Waiting API");
    display_update();
    //Enable config (I2C) interrupt

    //Wait for interrupt

    //Check for flag that interrupt sets

    //If set
    //Disable config (I2C) interrupt
    //return config_mode;
}

void *config_mode(){
    display_string(2, "Conf mode");
    display_update();
    //Register fingerprint

    //return wait_to_arm;
}

void *wait_to_arm(){
    display_string(2, "Waiting arm");
    display_update();
    //Enable config (I2C) interrupt
    //Enable fingerprint (UART) interrupt
    enable_fingerprint_interrupt();

    //Check if either interrupt flag has been set
    if(FINGERPRINT_FLAG == 0x1 || CONF_FLAG == 0x1) {
        //Disable interrupts
        disable_fingerprint_interrupt();

        //If interrupt flag set for fingerprint (UART)
        if(FINGERPRINT_FLAG){
            FINGERPRINT_FLAG = 0x0;
            return arming;
        }//If interrupt flag set for config (I2C)
        else if(CONF_FLAG){
            CONF_FLAG = 0x0;
            return config_mode;
        }
    }

    return wait_to_arm;
}

void *arming(){
    display_string(2, "Arming");
    display_update();
    //Authenticate user with fingerprint

    //If successful
    //return armed;

    //If unsuccessful
    //return wait_to_arm;
}

void *armed(){
    display_string(2, "Armed!");
    display_update();
    //Enable fingerprint (UART) interrupt
    //Enable US sensor interrupt

    //Wait for interrupt

    //Disable interrupts

    //If interrupt flag set for US sensor
    //return alarm_triggered;

    //If interrupt flag set for fingerprint (UART)
    //return disarming;
}

void *disarming(){
    display_string(2, "Disarming");
    display_update();
    //Authenticate users fingerprint

    //If successful
    //Send disarmed message to users phone
    //return wait_to_arm;

    //If unsuccessful

    //If alarm has been triggered
    //Send failed try message to users phone
    //return alarm_triggered;

    //If alarm hasn't been triggered
    //return armed;
}

void *alarm_triggered(){
    display_string(2, "ALARM!!!");
    display_update();
    //Send alarm triggered message to users phone
    //Visual feedback
    //Enable fingerprint (UART) interrupt

    //Wait for fingerprint interrupt

    //If interrupt flag set for fingerprint (UART)
    //return disarming;
}
