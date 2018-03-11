//
// Created by Linus Bein Fahlander on 2018-03-03.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "../drivers/fingerprint/commands.h"
#include "fingerprint_sensor.h"
#include "../drivers/display/display_functions.h"
#include "../utils/utils.h"
#include "../state.h"
#include "us_sensor.h"


char scan_finger(uint8_t buffer_id){
    char success = 0x1;

    display_string(1, "Keep finger");
    display_string(2, "on sensor!");
    display_update();

    uint8_t res_led = change_led(1);

    if(res_led == RES_RECEIVE_FAIL){
        success = 0x0;
    }

    if(success == 0x1) {
        uint8_t res_to_buffer;
        do {
            uint8_t res_scan;
            do {
                res_scan = scan_print();

                if (res_scan == RES_NO_FINGER) {
                    display_string(1, "No finger");
                    display_update();
                } else if (res_scan == RES_ENROLLMENT_FAIL) {
                    display_string(1, "Try again");
                    display_update();
                } else if (res_scan == RES_RECEIVE_FAIL) {
                    success = 0x0;
                    break;
                }
            } while (res_scan == RES_NO_FINGER || res_scan == RES_ENROLLMENT_FAIL);

            res_to_buffer = image_to_buffer(buffer_id);

            if (res_to_buffer == RES_WEAK_PRINT_FAIL) {
                display_string(1, "Bad scan");
                display_update();
            } else if (res_to_buffer == RES_GEN_IMAGE_FAIL) {
                display_string(1, "Try again");
                display_update();
            } else if (res_to_buffer == RES_RECEIVE_FAIL || success == 0x0) {
                success = 0x0;
                break;
            }
        } while (res_to_buffer == RES_WEAK_PRINT_FAIL || res_to_buffer == RES_GEN_IMAGE_FAIL);
    }

    change_led(0);

    display_string(1, "Remove finger");
    display_string(2, "from sensor!");
    display_update();

    return success;
}

void enroll_print_1st(){
    char res_scan = scan_finger(CHAR_BUFFER_1);
    if(res_scan == 0x0){
        display_string(1, "Request error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
        _delay(2500);
    } else {
        CURRENT_STATE = SCAN_NEXT;

        while (INTSTAT & 0x800);

        display_string(1, "1st Scan Done!");
        display_string(2, "");
        display_string(3, "");
        display_update();
    }
}


void enroll_print_2nd(){
    char res_scan = scan_finger(CHAR_BUFFER_2);
    if(res_scan == 0x0){
        display_string(1, "Request error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
        _delay(2500);
    } else {
        CURRENT_STATE = DEFAULT_STATE;

        while (INTSTAT & 0x800);

        display_string(1, "Making model");
        display_string(2, "");
        display_string(3, "");
        display_update();

        uint8_t res_model = generate_print_model();
        if(res_model == RES_COMBINE_FAIL){
            display_string(1, "Not the same");
            display_string(2, "Finger, redo");
            display_update();
            _delay(1500);
        } else if(res_model == RES_RECEIVE_FAIL){
            display_string(1, "Request error");
            display_update();
            CURRENT_STATE = ERROR_STATE;
            _delay(2500);
        }else {
            uint8_t res_store = save_print_to_flash(CHAR_BUFFER_1);
            int temp = (int) res_store;
            display_debug(1, &temp);

            display_string(1, "Model created!");
            display_string(2, "Model stored!");
            display_update();

            _delay(1500);
        }
    }
}


uint8_t auth_chain(uint8_t *match_score){
    char res_scan = scan_finger(CHAR_BUFFER_1);
    uint8_t res_match;
    if(res_scan == 0x0){
        display_string(1, "Request error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
        res_match = 0x1;
        _delay(2500);
    } else {
        while (INTSTAT & 0x800);

        display_string(1, "Authenticating");
        display_string(2, "");
        display_string(3, "");
        display_update();

        uint8_t res_load = load_print_from_flash(CHAR_BUFFER_2);
        res_match = match_buffers(match_score);
    }

    return res_match;
}


void authenticate(){

    uint8_t match_score[2];
    uint8_t res_match = auth_chain(match_score);

    if(res_match == RES_MATCH_FAIL){
        display_string(1, "Fingers DONT");
        display_string(2, "match!");
        display_update();
        _delay(500);
    } else if(res_match == RES_SUCCESS){
        CURRENT_STATE = DEFAULT_STATE;
        display_string(1, "Match!");
        display_update();
        _delay(500);
    } else{
        display_string(1, "Request error");
        display_update();
        CURRENT_STATE = ERROR_STATE;
    }

}

void arm_alarm(){
    uint8_t print_check = load_print_from_flash(CHAR_BUFFER_1);

    if(print_check == RES_SUCCESS){
        uint8_t match_score[2];
        uint8_t res_match = auth_chain(match_score);

        if(res_match == RES_MATCH_FAIL){
            display_string(1, "Fingers DONT");
            display_string(2, "match!");
            display_update();
            CURRENT_STATE = DEFAULT_STATE;
            _delay(500);
        } else if(res_match == RES_SUCCESS){
            display_string(1, "Match!");
            display_string(2, "Alarm will arm");
            display_string(3, "in 10 sec");
            display_update();

            _delay(10000);
            CURRENT_STATE = ALARM_ARMED;

            display_string(0, "Alarm active!");
            display_string(1, "");
            display_string(2, "");
            display_string(3, "");
            display_update();

            IFSCLR(0) = FINGER_TOUCH_INT;

            arm_us();
        } else{
            display_string(1, "Request error");
            display_update();
            CURRENT_STATE = ERROR_STATE;
        }
    } else if(print_check == RES_TEMPLATE_ERROR){
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

    if(res_match == RES_MATCH_FAIL){
        display_string(1, "Fingers DONT");
        display_string(2, "match!");
        display_update();
        CURRENT_STATE = ALARM_TRIGGERED;
        _delay(1500);
    } else if(res_match == RES_SUCCESS){
        CURRENT_STATE = DEFAULT_STATE;
        disarm_us();
        display_string(1, "Alarm");
        display_string(2, "Deactivated!");
        display_update();
        _delay(500);
    } else{
        display_string(1, "Request error");
        display_update();
    }
}
