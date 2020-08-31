
#ifndef IP_H
#define IP_H

#include "../drivers/ethernet/enc28j60_instructions.h"

void construct_ipv4_header(uint32_t ttl, uint32_t protocol, uint32_t source_ip, uint32_t dest_ip, uint32_t data_length);
uint16_t calculate_ip_checksum(uint32_t * header);

#include "ip.c"

#endif
