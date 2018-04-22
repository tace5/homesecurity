//
// Created by Linus on 2018-03-31.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../drivers/display/display_functions.h"
#include "../controllers/fingerprint_sensor.h"
#include "state_functions.h"
#include "state_main.h"
#include "../globals.h"
#include "../drivers/summer/summer.h"
#include "../controllers/us_sensor.h"

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
    return config_mode;
}

void *config_mode(){
    state_message("Configuration   Mode", 20);
    _delay(1500);

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
    clr_user_message();
    _delay(1000);
    //Enable config (I2C) interrupt
    //Enable fingerprint (UART) interrupt
    enable_fingerprint_interrupt();

    //Check if either interrupt flag has been set
    if(get_finger_flag() || get_conf_flag()) {
        //Disable interrupts
        disable_fingerprint_interrupt();

        msg_finger_on_sensor(0x0);

        //If interrupt flag set for fingerprint (UART)
        if(get_finger_flag()){
            set_finger_flag(0);
            int test = get_finger_flag();
            display_debug(1, &test);
            _delay(5000);
            return arming;
        }//If interrupt flag set for config (I2C)
        else if(get_conf_flag()){
            set_conf_flag(0);
            return config_mode;
        }
    }

    return wait_to_arm;
}

void *arming(){
    state_message("Arming device...", 16);
    _delay(1000);
    /*
    //Enable interrupts (maybe not needed)
    enable_fingerprint_interrupt();
    //Authenticate user with fingerprint*/
    uint8_t success = authenticate();

    //Reset interrupt flag and disable interrupt
    set_finger_flag(0);
    //disable_fingerprint_interrupt();

    //If successful
    if(success == 0x1){
        user_message("Alarm will arm  in 10 sec!", 26);
        _delay(10000);
        return armed;
    } //If fingers dont match
    else if(success == 0x2){
        user_message("Prints don't    match!!!", 24);
        _delay(1500);
        return wait_to_arm;
    } //If request fail
    else{
        _delay(1500);
        return wait_to_arm;
    }

    user_message("Unreachable", 11);
    _delay(5000);
}

void *armed(){
    state_message("DEVICE IS       ARMED!!!", 24);
    clr_user_message();
    _delay(2000);
    //Enable fingerprint (UART) interrupt
    //Enable US sensor interrupt
    if(ALARM_DISTANCE == 0){
        arm_us();
    }
    enable_fingerprint_interrupt();
    //If interrupt flag set for US sensor
    //return alarm_triggered
    if (get_us_flag()){
        disable_fingerprint_interrupt();
        set_us_flag(0);
        set_us_active_flag(0);
        disarm_us();
        return alarm_triggered;
    }

    //If interrupt flag set for fingerprint (UART)
    //return disarming
    if (get_finger_flag()){
        disable_fingerprint_interrupt();
        set_finger_flag(0);
        return disarming;
    }

    return armed;
}

void *disarming(){
    state_message("Disarming...", 12);
    _delay(1000);
    //Authenticate users fingerprint
    uint8_t success = authenticate();

    //If successful
    //Send disarmed message to users phone
    //Disarm US
    //return wait_to_arm;
    if(success == 0x1){
        summer_stop();
        set_alarm_flag(0);
        set_us_flag(0);
        set_us_active_flag(0);
        disarm_us();
        disable_fingerprint_interrupt();
        set_finger_flag(0);
        clr_state_message();
        user_message("DISARMED!!!", 11);
        _delay(2000);
        return wait_to_arm;
    }

    //If unsuccessful
    //  If alarm has been triggered
    //      Send failed try message to users phone
    //      return alarm_triggered;
    //  If alarm hasn't been triggered
    //      return armed;
    if (success == 0x2){
        user_message("Disarming failed", 16);
        if(get_alarm_flag()){
            return alarm_triggered;
        } else{
            return armed;
        }
    }

    return disarming;
}

void *alarm_triggered(){
    display_string(0, "ALARM!!!");
    display_string(1, "ALARM!!!");
    display_string(2, "ALARM!!!");
    display_update();

    set_alarm_flag(1);
    summer_trig();

    //Enable fingerprint (UART) interrupt
    enable_fingerprint_interrupt();
    //Wait for fingerprint interrupt

    if (get_finger_flag()){
        disable_fingerprint_interrupt();
        set_finger_flag(0);
        return disarming;
    }

    return alarm_triggered;
}
