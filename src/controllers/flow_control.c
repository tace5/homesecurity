//
// Created by Linus Bein Fahlander on 2018-03-05.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flow_control.h"
#include "../drivers/display/display_functions.h"
#include "../controllers/fingerprint_sensor.h"
#include "../state.h"

uint8_t last_state = 0xFF;

void main_flow(){
    check_switches();

    char change_flag = 0x0;
    if (last_state != CURRENT_STATE){
        change_flag = 0x1;
        last_state = CURRENT_STATE;
    }
    switch (CURRENT_STATE){
        case DEFAULT_STATE:
            if(change_flag){
                default_flow();
            }
            break;
        case CONFIG_MODE:
            if(change_flag){
                config_flow();
            }
            break;
        case ALARM_ARMED:
            if(change_flag){
                armed_flow();
            }
            break;
        case ALARM_TRIGGERED:
            if(change_flag){
                triggered_flow();
            }
            break;
        case SCAN_NEXT:
            if(change_flag){
                scan_next_flow();
            }
            break;
        case ERROR_STATE:
            if(change_flag){
                error_flow();
            }
            break;
    }
}


void check_switches(){
    if(PORTE & 0x10){
        drop_prints_in_flash();
        CURRENT_STATE = DEFAULT_STATE;
    }else if(PORTE & 0x8){
        CURRENT_STATE = CONFIG_MODE;
    }
}


void default_flow(){
    if(check_for_stored_print()) {
        display_string(0, "Ready to");
        display_string(1, "be armed!");
        display_string(2, "");
        display_string(3, "");
        display_update();
    } else{
        display_string(0, "Device needs to");
        display_string(1, "be configured!");
        display_string(2, "");
        display_string(3, "");
        display_update();
    }

    main_flow();
}


void config_flow(){
    display_string(0, "Configure");
    display_string(1, "Mode");
    display_string(2, "");
    display_string(3, "");
    display_update();

    main_flow();
}


void armed_flow(){
    display_string(0, "Alarm is");
    display_string(1, "Active!");
    display_string(2, "");
    display_string(3, "");
    display_update();

    main_flow();
}


void triggered_flow(){
    display_string(0, "ALARM ALARM");
    display_string(1, "ALARM ALARM");
    display_string(2, "ALARM ALARM");
    display_string(3, "PRESS FINGER!");
    display_update();

    main_flow();
}


void scan_next_flow(){
    display_string(0, "Please scan");
    display_string(1, "Your finger");
    display_string(2, "Again");
    display_string(3, "");
    display_update();

    main_flow();
}


void error_flow(){
    display_string(0, "AN ERROR");
    display_string(1, "HAS OCCURRED");
    display_string(2, "PLEASE");
    display_string(3, "RESTART");
    display_update();

    main_flow();
}


