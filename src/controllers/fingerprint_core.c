//
// Created by Linus on 2018-02-26.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "../drivers/fingerprint/commands.h"
#include "../drivers/display/display_functions.h"
#include "../utils/utils.h"
#include "../state.h"
#include "../globals.h"


int check_for_errors(){
    if(U2STA & 0x8){
        display_string(1, "ERROR! Parity");
        display_update();
        _delay(1000);

        return 1;
    }

    if(U2STA & 0x4){
        display_string(1, "ERROR! Framing");
        display_update();
        _delay(1000);

        return 1;
    }

    if(U2STA & 0x2){
        display_string(1, "ERROR! Overflow");
        display_update();
        _delay(1000);

        return 1;
    }

    return 0;
}

char check_for_stored_print(){
    uint8_t print_check = load_print_from_flash(CHAR_BUFFER_1);
    char res = 0x1;
    if(print_check == RES_TEMPLATE_ERROR || print_check == RES_RECEIVE_FAIL){
        char res = 0x0;
    }

    return res;
}

int get_total_package_length(int data_length){
    return (2 + 4 + 1 + 2 + data_length + 2);
}

void enable_fingerprint_interrupt(){
    INTCONSET = 0x4;
    IECSET(0) = FINGER_TOUCH_INT;      // Enable INT2 interrupt
    IPCSET(2) = 0x1F000000; // Set priority = 7 and sub = 3
}

void disable_fingerprint_interrupt(){
    INTCONCLR = 0x4;
    IECCLR(0) = FINGER_TOUCH_INT;      // Disable INT2 interrupt
}

void handle_finger_interrupt(){
    //TODO - Set flag to signal state machine to move on.
    FINGERPRINT_FLAG = 0x1;
}
