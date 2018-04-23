//
// Created by Linus on 2018-03-31.
//
// State machine inspired by http://codeandlife.com/2013/10/06/tutorial-state-machines-with-c-callbacks/
// But modified to handle device states.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "../drivers/display/display_functions.h"
#include "state_main.h"
#include "state_functions.h"
#include "../utils/utils.h"
#include "../globals.h"
#include "../controllers/us_sensor.h"

volatile static uint8_t FINGERPRINT_FLAG = 0x0;
volatile static uint8_t CONF_FLAG = 0x0;
volatile static uint8_t US_ACTIVE = 0x0;
volatile static uint8_t US_FLAG = 0x0;
volatile static uint8_t ALARM_FLAG = 0x0;

void start_state_machine(){
    volatile StateFunc current_state = boot;
    while (1){
        if(PORTD & 0x80){
            set_conf_flag(1);
        }
        if(get_us_active_flag()){
            if((int) check_trigger()){
                set_us_flag(1);
            }
        }
        current_state = (StateFunc)(*current_state)();
        _delay(100);
    }
}


void set_finger_flag(uint8_t status){
    FINGERPRINT_FLAG = status;
}

void set_us_flag(uint8_t status){
    US_FLAG = status;
}

void set_us_active_flag(uint8_t status){
    US_ACTIVE = status;
}

void set_conf_flag(uint8_t status){
    CONF_FLAG = status;
}

void set_alarm_flag(uint8_t status){
    ALARM_FLAG = status;
}

uint8_t get_finger_flag(){
    return FINGERPRINT_FLAG;
}

uint8_t  get_us_flag(){
    return US_FLAG;
}

uint8_t  get_us_active_flag(){
    return US_ACTIVE;
}

uint8_t  get_conf_flag(){
    return CONF_FLAG;
}

uint8_t  get_alarm_flag(){
    return ALARM_FLAG;
}
