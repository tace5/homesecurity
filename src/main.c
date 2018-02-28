#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include "drivers/ethernet/enc28j60_instructions.h"
//#include "drivers/ethernet/enc28j60_control_registers.h"
#include "utils/utils.h"
#include "drivers/display/display_functions.h"
#include "drivers/fingerprint/fingerprint_main.h"
#include "drivers/fingerprint/controller.h"


void do_work() {
    int test = (IFS(1) & 0x200) >> 9;
    if(test){
        handle_interrupt();
    }
    display_debug(1, &U2TXREG);
}

int main() {
    display_setup();
    fingerprint_main();
    display_string(3, "TEST TEST TEST");
    display_update();

    while (1) {
        do_work();
    }

    return 0;
}