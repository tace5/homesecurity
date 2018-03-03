
#ifndef HOMESECURITY_ENC28J60_UTILS_H
#define HOMESECURITY_ENC28J60_UTILS_H

#include <stdint.h>

uint8_t CURRENT_BANK = 0;

void enable_autoinc(void);
void set_receive_buffer_pointer(uint16_t receive_buffer_start, uint16_t receive_buffer_end);
void enable_unicast_filter(void);
void init_mac(uint16_t max_frame_length, volatile uint8_t * mac_address);
void select_memory_bank(uint8_t bank);
uint8_t is_mac_mii_register(uint8_t addr);
void enable_reception();
void send_ethernet_frame(volatile uint8_t * dest_mac, volatile uint8_t * source_mac, int length, volatile uint8_t * data);

#include "enc28j60_utils.c"

#endif //HOMESECURITY_ENC28J60_UTILS_H
