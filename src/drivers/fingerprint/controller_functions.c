//
// Created by Linus Bein Fahlander on 2018-03-03.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "controller.h"
#include "commands.h"
#include "../display/display_functions.h"
#include "../../utils/utils.h"
#include "../../state.h"


void enroll_print_1st(){
    display_string(1, "Keep finger");
    display_string(2, "on sensor!");
    display_update();

    uint8_t res_led = change_led(1);
    uint8_t res_scan = scan_print();
    uint8_t res_to_buffer = image_to_buffer(CHAR_BUFFER_1);
    change_led(0);

    display_string(1, "Remove finger");
    display_string(2, "from sensor!");
    display_update();

    CURRENT_STATE = SCAN_NEXT;

    while(INTSTAT & 0x800);

    display_string(1, "Put finger on");
    display_string(2, "sensor for");
    display_string(3, "2nd scan");
    display_update();
}


void enroll_print_2nd(){
    display_string(1, "Keep finger");
    display_string(2, "on sensor!");
    display_update();

    uint8_t res_led = change_led(1);
    uint8_t res_scan = scan_print();
    uint8_t res_to_buffer = image_to_buffer(CHAR_BUFFER_2);
    change_led(0);

    display_string(1, "Remove finger");
    display_string(2, "from sensor!");
    display_update();

    CURRENT_STATE = DEFAULT_STATE;

    while(INTSTAT & 0x800);

    display_string(1, "Making model...");
    display_string(2, "");
    display_string(3, "");
    display_update();

    uint8_t res_model = generate_print_model();
    uint8_t res_store = save_print_to_flash(CHAR_BUFFER_1);

    display_string(1, "Model created!");
    display_string(2, "Model stored!");
    display_update();
}


uint8_t auth_chain(uint8_t *match_score){
    display_string(1, "Keep finger");
    display_string(2, "on sensor!");

    uint8_t res_led = change_led(1);
    uint8_t res_scan = scan_print();
    change_led(0);

    display_string(1, "Remove finger");
    display_string(2, "from sensor!");
    display_update();

    while(INTSTAT & 0x800);

    display_string(1, "Authenticating...");
    display_string(2, "");
    display_string(3, "");
    display_update();

    uint8_t res_to_buffer = image_to_buffer(CHAR_BUFFER_1);
    uint8_t res_load = load_print_from_flash(CHAR_BUFFER_2);
    uint8_t res_match = match_buffers(match_score);

    return res_match;
}


void authenticate(){

    uint8_t match_score[2];
    uint8_t res_match = auth_chain(match_score);

    if(res_match == 0x08){
        display_string(1, "Fingers DO NOT");
        display_string(2, "match!");
        display_update();
    } else if(res_match == 0x0){
        CURRENT_STATE = DEFAULT_STATE;
        display_string(1, "Match! Score:");
        display_update();
        int match = (int) (match_score[0] << 8) | match_score[1];
        display_debug(1, &match);
    } else{
        display_string(1, "Request error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
    }

}

void arm_alarm(){
    uint8_t print_check = load_print_from_flash(CHAR_BUFFER_1);

    if(print_check == 0x00){
        uint8_t match_score[2];
        uint8_t res_match = auth_chain(match_score);

        if(res_match == 0x08){
            display_string(1, "Fingers DO NOT");
            display_string(2, "match!");
            display_update();
            CURRENT_STATE = DEFAULT_STATE;
        } else if(res_match == 0x0){
            display_string(1, "Match!");
            display_string(2, "Alarm will arm");
            display_string(3, "in 20 sec");
            display_update();

            _delay(20000);
            CURRENT_STATE = ALARM_ARMED;
            // TODO - Call US sensor "arm" function

            display_string(1, "Alarm active!");
            display_string(2, "");
            display_string(3, "");
            display_update();
        } else{
            display_string(1, "Request error");
            display_update();
            CURRENT_STATE = ERROR_STATE;
        }
    } else if(print_check == 0x0C){
        display_string(1, "No print avail");
        display_update();
        CURRENT_STATE = DEFAULT_STATE;
    } else{
        display_string(1, "Data error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
    }
}

void disarm(){
    uint8_t match_score[2];
    uint8_t res_match = auth_chain(match_score);

    if(res_match == 0x08){
        display_string(1, "Fingers DO NOT");
        display_string(2, "match!");
        display_update();
        CURRENT_STATE = ALARM_TRIGGERED;
    } else if(res_match == 0x0){
        CURRENT_STATE = DEFAULT_STATE;
        // TODO - Call US "unarm" and shut buzzer off
        display_string(1, "Alarm");
        display_string(2, "Deactivated!");
        display_update();
    } else{
        display_string(1, "Request error");
        display_update();
    }
}
