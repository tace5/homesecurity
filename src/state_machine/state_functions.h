//
// Created by Linus on 2018-03-31.
//

#ifndef HOMESECURITY_STATE_FUNCTIONS_H
#define HOMESECURITY_STATE_FUNCTIONS_H

typedef void * volatile (*StateFunc)();

void * volatile boot();

void * volatile wait_for_api();

void * volatile config_mode();

void * volatile wait_to_arm();

void * volatile arming();

void * volatile armed();

void * volatile disarming();

void * volatile alarm_triggered();


#include "state_functions.c"

#endif //HOMESECURITY_STATE_FUNCTIONS_H
