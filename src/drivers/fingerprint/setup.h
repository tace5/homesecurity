//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_SETUP_H
#define HOMESECURITY_SETUP_H

void init(void);
void config_uart(void);
void setup(void);
void handshake(void);
void register_interrupts(void);

#include "setup.c"

#endif //HOMESECURITY_SETUP_H
