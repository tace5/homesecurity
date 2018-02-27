//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_UTILS_H
#define HOMESECURITY_UTILS_H

void timeout(int ms);

int gen_UxBRG(int processor_freq, int baud_rate);

#include "utils.c"

#endif //HOMESECURITY_UTILS_H
