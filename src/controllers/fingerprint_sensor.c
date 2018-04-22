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

    msg_finger_on_sensor(0x0);

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
                    user_message("No finger", 9);
                } else if (res_scan == RES_ENROLLMENT_FAIL) {
                    msg_try_again();
                } else if (res_scan == RES_RECEIVE_FAIL) {
                    success = 0x0;
                    break;
                }
            } while (res_scan == RES_NO_FINGER || res_scan == RES_ENROLLMENT_FAIL);

            res_to_buffer = image_to_buffer(buffer_id);

            if (res_to_buffer == RES_WEAK_PRINT_FAIL) {
                user_message("Bad scan", 8);
            } else if (res_to_buffer == RES_GEN_IMAGE_FAIL) {
                msg_try_again();
            } else if (res_to_buffer == RES_RECEIVE_FAIL || success == 0x0) {
                success = 0x0;
                break;
            }
        } while (res_to_buffer == RES_WEAK_PRINT_FAIL || res_to_buffer == RES_GEN_IMAGE_FAIL);
    }

    change_led(0);

    msg_remove_finger();

    return success;
}

uint8_t enroll_print_1st(){
    msg_finger_on_sensor(0x0);

    while(!(PORTD & 0x200)); // Wait for user to put finger on sensor

    char res_scan = scan_finger(CHAR_BUFFER_1);
    if(res_scan == 0x0){
        msg_request_err();
        return 0x0;
    } else {
        msg_remove_finger();

        while((PORTD & 0x200)); // Check if user has removed finger

        user_message("1st Scan Done!", 14);
    }

    return 0x1;
}


uint8_t enroll_print_2nd(){
    msg_finger_on_sensor(0x0);

    while(!(PORTD & 0x200)); // Wait for user to put finger on sensor

    char res_scan = scan_finger(CHAR_BUFFER_2);
    if(res_scan == 0x0){
        msg_request_err();
        return 0x0;
    } else {

        user_message("Making model...", 15);

        uint8_t res_model = generate_print_model();
        if(res_model == RES_COMBINE_FAIL){
            user_message("Not the same    Finger, redo", 28);
            return 0x2;
        } else if(res_model == RES_RECEIVE_FAIL){
            msg_request_err();
            return 0x0;
        }else {
            uint8_t res_store = save_print_to_flash(CHAR_BUFFER_1);

            user_message("Model created   and stored!", 27);

            _delay(500);
        }
    }

    return 0x1;
}


uint8_t enroll_finger(){
    msg_finger_on_sensor((char) ~(PORTD & 0x200));

    _delay(500);

    while(!(PORTD & 0x200)); // Wait for user to put finger on sensor

    uint8_t finger_diff = 0x0;
    while(!finger_diff) {
        uint8_t res_1st = enroll_print_1st();

        if(res_1st == 0x1) {
            msg_finger_on_sensor(0x1);

            _delay(500);

            uint8_t res_2nd = enroll_print_2nd();
            if (res_2nd != 0x2) {
                finger_diff = 0x1;
            } else if(res_2nd == 0x0){
                return 0x0;
            }
        } else{
            return 0x0;
        }
    }

    return 0x1;
}

uint8_t auth_chain(uint8_t *match_score){
    char res_scan = scan_finger(CHAR_BUFFER_1);
    uint8_t res_match;
    if(res_scan == 0x0){
        msg_request_err();
        return 0x0;
    } else {
        msg_remove_finger();

        while((PORTD & 0x200)); // Check if user has removed finger

        user_message("Authenticating", 14);

        _delay(2500);

        uint8_t res_load = load_print_from_flash(CHAR_BUFFER_2);
        res_match = match_buffers(match_score);
    }

    return res_match;
}


uint8_t authenticate(){

    uint8_t match_score[2];
    uint8_t res_match = auth_chain(match_score);

    if(res_match == RES_MATCH_FAIL){
        user_message("Fingers DONT    match!", 22);
        _delay(500);
        return 0x2;
    } else if(res_match == RES_SUCCESS){
        user_message("MATCH!", 6);
        _delay(500);
        return 0x1;
    } else{
        msg_request_err();
        return 0x0;
    }
}

uint8_t arm_alarm(){
    uint8_t print_check = load_print_from_flash(CHAR_BUFFER_1);

    if(print_check == RES_SUCCESS){
        uint8_t match_score[2];
        uint8_t res_match = auth_chain(match_score);

        if(res_match == RES_MATCH_FAIL){
            user_message("Fingers DONT    match!", 22);
            _delay(500);
            return 0x2;
        } else if(res_match == RES_SUCCESS){
            return 0x1;
        } else{
            msg_request_err();
            return 0x0;
        }
    } else if(print_check == RES_TEMPLATE_ERROR){
        user_message("No print        available!", 26);
        return 0x3;
    } else{
        user_message("Data error", 10);
        return 0x4;
    }
}

uint8_t disarm(){
    uint8_t match_score[2];
    uint8_t res_match = auth_chain(match_score);

    if(res_match == RES_MATCH_FAIL){
        user_message("Fingers DONT    match!", 22);
        _delay(500);
        return 0x2;
    } else if(res_match == RES_SUCCESS){
        return 0x1;
    } else{
        msg_request_err();
        return 0x0;
    }
}
