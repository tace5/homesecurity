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
    int current_measure;
    do{
        current_measure = measure_dist();
    } while (current_measure + 5 >= ALARM_DISTANCE && ALARM_DISTANCE != 0);

    CURRENT_STATE = ALARM_TRIGGERED;
    //TODO - Call API controller

}

void disarm_us(){
    ALARM_DISTANCE = 0;
}

