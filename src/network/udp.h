
#ifndef UDP_H
#define UDP_H

void construct_udp_header(uint32_t source_port, uint32_t dest_port, uint32_t data_length);

#include "udp.c"

#endif
