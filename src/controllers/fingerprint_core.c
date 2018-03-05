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


void __attribute__ ((interrupt)) handle_interrupt();

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

void handle_interrupt(){
    uint8_t state = CURRENT_STATE;

    switch(state) {
        // Case: State = Default
        case DEFAULT_STATE:
            display_string(0, "Arming alarm...");
            display_update();
            arm_alarm();
            break;

        // Case: State = Scan next finger to complete config
        case SCAN_NEXT:
            display_string(0, "Scan 2nd print");
            display_update();
            enroll_print_2nd();
            break;

        // Case: State = Config mode
        case CONFIG_MODE:
            display_string(0, "Adding new print");
            display_update();
            enroll_print_1st();
            break;

        // Case: State = Alarm is armed but not triggered
        case ALARM_ARMED:
            display_string(0, "Deactivating...");
            display_update();
            authenticate();
            break;

        // Case: State = Alarm is triggered
        case ALARM_TRIGGERED:
            display_string(0, "Deactivating...");
            display_update();
            authenticate();
            break;

        // Case: State = Something has gone wrong, restart is maybe a solution
        case ERROR_STATE:
            display_string(0, "An error has");
            display_string(1, "Occurred, please");
            display_string(2, "Restart");
            display_update();
            break;
        default:
            display_string(0, "An error has");
            display_string(1, "Occurred, please");
            display_string(2, "Restart");
            display_update();
            break;
    }

    IFSCLR(0) = FINGER_TOUCH_INT;
}
