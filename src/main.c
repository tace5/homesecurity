#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include "drivers/ethernet/enc28j60_instructions.h"
//#include "drivers/ethernet/enc28j60_control_registers.h"
#include "utils/utils.h"
#include "state.h"
#include "drivers/display/display_functions.h"
#include "drivers/fingerprint/fingerprint_main.h"
#include "drivers/fingerprint/controller.h"
#include "drivers/fingerprint/commands.h"
#include "drivers/buzzer/buzzer.h"

void user_isr(){
    if((IFS(0) & FINGER_TOUCH_INT) >> 11){
        handle_interrupt();
    }
}

void do_work() {
    display_string(0, "Buzzing...");
    display_update();
    buzz(50);
    display_string(0, "Buzzing stopped");
    display_update();
    _delay(2000);
}

int main() {
    display_setup();
    buzzer_init();
    _enable_interrupt();

    fingerprint_main();

  return 0;
}
