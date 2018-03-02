
#ifndef HOMESECURITY_SPI1_H
#define HOMESECURITY_SPI1_H

#include <stdint.h>

#define SS1 0x80
#define SPI1TXIF 0x1000000
#define SPI1RXIF 0x2000000
#define SPI1EIF 0x800000

void spi1_init(void);
void spi_transfer(const void * buf, void * retbuf, uint32_t count);
uint8_t spi1_transfer(uint16_t data);
uint8_t spi1_receive();

#include "spi1.c"

#endif //HOMESECURITY_SPI1_H
