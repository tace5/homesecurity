//
// Created by Linus on 2018-02-26.
//

#ifndef HOMESECURITY_FINGERPRINT_H
#define HOMESECURITY_FINGERPRINT_H

void fingerprint_main(void);

uint8_t listen_for_acknowledgement(uint8_t *data_storage);

void transmit_package(uint8_t *package, int package_len);

void pack(uint8_t pid, int data_length, uint8_t *data, int adder, uint8_t *storage);


#include "fingerprint.c"

#endif //HOMESECURITY_FINGERPRINT_H
