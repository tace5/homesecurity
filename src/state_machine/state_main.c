//
// Created by Linus on 2018-03-31.
//
// State machine inspired by http://codeandlife.com/2013/10/06/tutorial-state-machines-with-c-callbacks/
// But modified to handle device states.
//

#include "../drivers/display/display_functions.h"
#include "state_main.h"
#include "state_functions.h"
#include "../utils/utils.h"

void start_state_machine(){
    volatile StateFunc current_state = boot;
    while (1){
        current_state = (StateFunc)(*current_state)();
        _delay(1000);
    }

    display_string(3, "Out of loop");
    display_update();
}
