//
// Created by Linus Bein Fahlander on 2018-02-27.
//

#ifndef HOMESECURITY_BUZZER_H
#define HOMESECURITY_BUZZER_H

#define BUZZER_PORT_SET     PORTESET
#define BUZZER_PORT_CLR     PORTECLR
#define BUZZER_BIT          0x20

void buzz(int duration);

#include "buzzer.c"

#endif //HOMESECURITY_BUZZER_H
