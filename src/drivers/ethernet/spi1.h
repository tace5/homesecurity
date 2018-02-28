
#ifndef HOMESECURITY_SPI1_H

#include <stdint.h>

#define SS1 0x80
#define SPI1TXIF 0x1000000
#define SPI1RXIF 0x2000000
#define SPI1EIF 0x800000

void spi1_init(void);
void spi1_transfer(uint8_t data);
void spi1_receive(volatile int * data);

#include "spi1.c"

#endif //HOMESECURITY_SPI1_H
