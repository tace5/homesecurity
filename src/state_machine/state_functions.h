//
// Created by Linus on 2018-03-31.
//

#ifndef HOMESECURITY_STATE_FUNCTIONS_H
#define HOMESECURITY_STATE_FUNCTIONS_H

typedef void *(*StateFunc)();

void *led1_on();
void *led1_off();

void *led2_on();
void *led2_off();

#include "state_functions.c"

#endif //HOMESECURITY_STATE_FUNCTIONS_H
