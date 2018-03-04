
#ifndef IP_H
#define IP_H

#include "../drivers/ethernet/enc28j60_instructions.h"

void construct_ipv4_header(uint16_t data_length, uint8_t ttl, uint8_t protocol, int source_ip, int dest_ip);
uint16_t calculate_checksum(int * header);

#include "ip.c"

#endif
