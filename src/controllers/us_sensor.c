//
// Created by Linus Bein Fahlander on 2018-03-05.
//

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "us_sensor.h"
#include "../drivers/us_sensor/us_sensor.h"
#include "flow_control.h"
#include "../state.h"
#include "fingerprint_sensor.h"

void arm_us(){
    ALARM_DISTANCE = measure_dist();
}

void disarm_us(){
    ALARM_DISTANCE = 0;
}

char check_trigger(void){
    int dist = measure_dist();

    if(dist + 15 < ALARM_DISTANCE && ALARM_DISTANCE != 0){
        return 0x1;
    }

    return 0x0;
}

