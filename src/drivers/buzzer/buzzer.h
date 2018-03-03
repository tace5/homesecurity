//
// Created by Linus Bein Fahlander on 2018-02-27.
//

#ifndef HOMESECURITY_BUZZER_H
#define HOMESECURITY_BUZZER_H

#define BUZZER_BIT          0x1

void buzzer_init(void);

void buzz(int duration);

#include "buzzer.c"

#endif //HOMESECURITY_BUZZER_H
