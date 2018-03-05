//
// Created by Linus Bein Fahlander on 2018-03-05.
//

#ifndef HOMESECURITY_FLOW_CONTROL_H
#define HOMESECURITY_FLOW_CONTROL_H

void main_flow();

void check_switches();

void default_flow();

void config_flow();

void armed_flow();

void triggered_flow();

void scan_next_flow();

void error_flow();

#include "flow_control.c"

#endif //HOMESECURITY_FLOW_CONTROL_H
