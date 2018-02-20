#include <pic32mx.h>
#include <stdint.h>
#include "spi1.h"

void spi1_init(void) {
  IECCLR(0) = SPI1RXIF;
  IECCLR(0) = SPI1EIF;

  IFSCLR(0) = SPI1RXIF;
  IFSCLR(0) = SPI1EIF;

  IPCCLR(5) = 0x1f000000;
  IPCSET(5) = 0xd000000;

  IECSET(0) = SPI1RXIF;
  IECSET(0) = SPI1EIF;

  TRISDCLR = SS1;
  PORTDSET = SS1;

  SPI1CON = 0;
  SPI1BRG = 0x2; // SCK = 13.33 MHz
  SPI1STATCLR = PIC32_SPISTAT_SPIROV;
  SPI1CONSET = PIC32_SPICON_MSTEN | PIC32_SPICON_ON;
}

void spi1_transfer(uint8_t data) {
  SPI1BUF = data;
  while (!(SPI1STAT & PIC32_SPISTAT_SPITBE)); // Make sure transmit buffer is empty
}

void spi1_receive(volatile int* data) {
  while (SPI1STAT & PIC32_SPISTAT_SPITBE); // Wait for transmit buffer to fill up
  *data = SPI1BUF;
}
