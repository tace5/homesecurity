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
    //If config is already set by talking to fingerprint sensor.
    char status = check_for_stored_print();
    if (status == 0x1) {
        return wait_to_arm;
    }else {
        return wait_for_api;
    }
}

void *wait_for_api(){
    state_message("Waiting for API", 15);
    //Enable config (I2C) interrupt

    //Wait for interrupt

    //Check for flag that interrupt sets

    //If set
    //Disable config (I2C) interrupt
    //return config_mode;
}

void *config_mode(){
    state_message("Configuration   Mode", 20);
    //Register fingerprint

    uint8_t enrolled = enroll_finger();

    if(enrolled){
        user_message("Success!!!", 10);
        _delay(500);
        return wait_to_arm;
    } else{
        user_message("Failed!!!       Try again", 25);
        _delay(1000);
        return config_mode;
    }
}

void *wait_to_arm(){
    state_message("Waiting to      arm device", 26);
    //Enable config (I2C) interrupt
    //Enable fingerprint (UART) interrupt
    enable_fingerprint_interrupt();

    //Check if either interrupt flag has been set
    if(FINGERPRINT_FLAG == 0x1 || CONF_FLAG == 0x1) {
        //Disable interrupts
        disable_fingerprint_interrupt();

        msg_finger_on_sensor(0x0);

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
    state_message("Arming device...", 16);
    //Authenticate user with fingerprint
    uint8_t success = authenticate();
    //If successful
    if(success == 0x1){
        user_message("Alarm will arm  in 10 sec!", 26);
        _delay(10000);
        return armed;
    } //If fingers dont match
    else if(success == 0x2){
        user_message("Prints don't    match!!!", 24);
        return wait_to_arm;
    } //If request fail
    else{
        return wait_to_arm;
    }
}

void *armed(){
    state_message("DEVICE IS       ARMED!!!", 24);
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
    state_message("Disarming...", 12);
    //Authenticate users fingerprint

    //If successful
    //Send disarmed message to users phone
    //Disarm US
    //return wait_to_arm;

    //If unsuccessful

    //If alarm has been triggered
    //Send failed try message to users phone
    //return alarm_triggered;

    //If alarm hasn't been triggered
    //return armed;
}

void *alarm_triggered(){
    display_string(0, "ALARM!!!");
    display_string(1, "ALARM!!!");
    display_string(2, "ALARM!!!");
    display_update();
    //Send alarm triggered message to users phone
    //Visual feedback
    //Enable fingerprint (UART) interrupt

    //Wait for fingerprint interrupt

    //If interrupt flag set for fingerprint (UART)
    //return disarming;
}
