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
#include "drivers/summer/summer.h"

void user_isr() {
    if ((IFS(0) & FINGER_TOUCH_INT) >> 11) {
        handle_finger_interrupt();
    } else if (IFS(0) & 0x100) {
        summer_isr();
    }
}

int main(void) {
    _enable_interrupt();
    display_setup();

    summer_trig();
    _delay(5000);
    summer_stop();

    while(1); // Never return
}
