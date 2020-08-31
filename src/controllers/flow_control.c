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
    switch (CURRENT_STATE){
        case DEFAULT_STATE:
            default_flow();
            break;
        case CONFIG_MODE:
            config_flow();
            break;
        case ALARM_ARMED:
            armed_flow();
            break;
        case ALARM_TRIGGERED:
            triggered_flow();
            break;
        case SCAN_NEXT:
            scan_next_flow();
            break;
        case ERROR_STATE:
            error_flow();
            break;
    }
}


void default_flow(){
    display_string(0, "Ready to");
    display_string(1, "be armed!");
    display_string(2, "");
    display_string(3, "");
    display_update();
}


void config_flow(){
    display_string(0, "Configure");
    display_string(1, "Mode");
    display_string(2, "");
    display_string(3, "");
    display_update();
}


void armed_flow(){
    display_string(0, "Alarm is");
    display_string(1, "Active!");
    display_string(2, "");
    display_string(3, "");
    display_update();
}


void triggered_flow(){
    display_string(0, "ALARM ALARM");
    display_string(1, "ALARM ALARM");
    display_string(2, "ALARM ALARM");
    display_string(3, "PRESS FINGER!");
    display_update();
}


void scan_next_flow(){
    display_string(0, "Please scan");
    display_string(1, "Your finger");
    display_string(2, "Again");
    display_string(3, "");
    display_update();
}


void error_flow(){
    display_string(0, "AN ERROR");
    display_string(1, "HAS OCCURRED");
    display_string(2, "PLEASE");
    display_string(3, "RESTART");
    display_update();
}


