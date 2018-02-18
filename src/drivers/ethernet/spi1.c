#include <pic32mx.h>
#include "spi1.h"

void enable_spi(void) {
  IECCLR(0) = SPI1RXIF;
  IECCLR(0) = SPI1EIF;

  IFSCLR(0) = SPI1RXIF;
  IFSCLR(0) = SPI1EIF;

  IPCCLR(5) = 0x1f000000;
  IPCSET(5) = 0xd000000;

  IECSET(0) = SPI1RXIF;
  IECSET(0) = SPI1EIF;

  TRISDCLR = SS1;

  SPI1CON = 0;
  SPI1BRG = 0x2;
  SPI1STATCLR = PIC32_SPISTAT_SPIROV;
  SPI1CONSET = PIC32_SPICON_MSTEN | PIC32_SPICON_ON;
}

void spi_transfer(int data) {
  SPI1BUF = bits;
  while (!(SPI1STAT & PIC32_SPISTAT_SPITBE)); // Make sure transmit buffer is empty
}

void spi_receive(volatile int* data) {
  while (SPI1STAT & PIC32_SPISTAT_SPITBE);
  *data = SPI1BUF;
}
