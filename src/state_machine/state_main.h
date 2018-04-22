//
// Created by Linus on 2018-03-31.
//

#ifndef HOMESECURITY_STATE_MAIN_H
#define HOMESECURITY_STATE_MAIN_H

void start_state_machine();

void set_finger_flag(uint8_t status);

void set_us_flag(uint8_t status);

void set_us_active_flag(uint8_t status);

void set_conf_flag(uint8_t status);

void set_alarm_flag(uint8_t status);

uint8_t get_finger_flag();

uint8_t  get_us_flag();

uint8_t  get_us_active_flag();

uint8_t  get_conf_flag();

uint8_t  get_alarm_flag();

#include "state_main.c"

#endif //HOMESECURITY_STATE_MAIN_H
