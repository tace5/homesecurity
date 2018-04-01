#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include "drivers/ethernet/enc28j60_instructions.h"
//#include "drivers/ethernet/enc28j60_control_registers.h"
#include "utils/utils.h"
#include "state.h"
#include "drivers/display/display_functions.h"
#include "drivers/fingerprint/fingerprint.h"
#include "controllers/fingerprint_sensor.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/spi1.h"
#include "drivers/ethernet/enc28j60_instructions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/enc28j60_utils.h"
#include "drivers/ethernet/ethernet.h"
#include "drivers/us_sensor/us_sensor.h"
#include "network/ip.h"
#include "network/udp.h"
#include "network/http.h"
#include "state_machine/state_main.h"

void user_isr() {
    display_string(1, "Inside ISR");
    display_update();
    _delay(1500);
    if ((IFS(0) & FINGER_TOUCH_INT) >> 11) {
        handle_interrupt();
    }
}

void demo_setup() {
    //Enable switch SW2 & SW3 for demo, routed from port 7 & 8 to port 29 & 30
    //TRISESET = 0x18;
    //CURRENT_STATE = CONFIG_MODE;
}

void do_work() {
    main_flow();
}

int main(void) {
    demo_setup();
    _enable_interrupt();
    display_setup();
    sensor_init();
    fingerprint_main();

    state_main();

    return 0;
}
