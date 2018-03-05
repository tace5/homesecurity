
#ifndef UDP_H
#define UDP_H

void construct_udp_header(uint32_t source_port, uint32_t dest_port, uint32_t source_ip, uint32_t dest_ip, uint32_t protocol, uint32_t data_length, uint8_t * data);
uint16_t calculate_udp_checksum(uint32_t source_ip, uint32_t dest_ip, uint32_t protocol, uint32_t data_length, uint8_t * data);

#include "udp.c"

#endif
