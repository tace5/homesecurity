//
// Created by Linus on 2018-03-31.
//

#ifndef HOMESECURITY_STATE_FUNCTIONS_H
#define HOMESECURITY_STATE_FUNCTIONS_H

typedef void *(*StateFunc)();

void *boot();

void *wait_for_api();

void *config_mode();

void *wait_to_arm();

void *arming();

void *armed();

void *disarming();

void *alarm_triggered();


#include "state_functions.c"

#endif //HOMESECURITY_STATE_FUNCTIONS_H
