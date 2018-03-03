//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_UTILS_H
#define HOMESECURITY_UTILS_H

char* itoa(int i, char b[]);

int gen_UxBRG(int processor_freq, int baud_rate);

extern void _enable_interrupt();

extern void _delay();

#include "utils.c"

#endif //HOMESECURITY_UTILS_H
