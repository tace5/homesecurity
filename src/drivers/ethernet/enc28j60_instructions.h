
#ifndef HOMESECURITY_ENC28J60_INSTRUCTIONS_H

#include <stdint.h>

uint8_t read_control_register(uint8_t eth_register);
void read_buffer_memory(volatile int * data, unsigned int length);
void write_control_register(uint8_t eth_register, uint8_t data);
void write_buffer_memory(volatile uint8_t * data, unsigned int length);
void bit_field_set(uint8_t eth_register, uint8_t set_bits);
void bit_field_clr(uint8_t eth_register, uint8_t clr_bits);

#include "enc28j60_instructions.c"

#endif //HOMESECURITY_ENC28J60_INSTRUCTIONS_H
