#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "utils/utils.h"
#include "state.h"
#include "drivers/display/display_functions.h"
#include "drivers/fingerprint/fingerprint.h"
#include "controllers/fingerprint_sensor.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/us_sensor/us_sensor.h"
#include "controllers/flow_control.h"

void user_isr() {
    display_string(1, "Inside ISR");
    display_update();
    _delay(1500);
    if ((IFS(0) & FINGER_TOUCH_INT) >> 11) {
        handle_interrupt();
    }
}

int main(void) {
  display_setup();

  return 0;
}
