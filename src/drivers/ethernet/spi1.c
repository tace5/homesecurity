#include <pic32mx.h>
#include <stdint.h>
#include "../display/display_functions.h"

void spi1_init(void) {
  IECCLR(0) = SPI1TXIF;
  IECCLR(0) = SPI1RXIF;
  IECCLR(0) = SPI1EIF;

  SPI1CONCLR = 0x8000;

  SPI1BUF = 0x0;

  IFSCLR(0) = SPI1RXIF;
  IFSCLR(0) = SPI1EIF;

  IPCCLR(5) = 0x1f000000;
  IPCSET(5) = 0xd000000;

  IECSET(0) = SPI1TXIF;
  IECSET(0) = SPI1RXIF;
  IECSET(0) = SPI1EIF;

  TRISECLR = SS1;
  PORTESET = SS1;

  SPI1BRG = 0x2; // SCK = 13.33 MHz
  SPI1STATCLR = PIC32_SPISTAT_SPIROV;
  SPI1CONSET = PIC32_SPICON_MSTEN | PIC32_SPICON_ON;
}

uint8_t spi1_transfer(uint16_t data) {
  while (!(SPI1STAT & 0x08));
  SPI1BUF = data;
  while (!(SPI1STAT & 1));
  uint8_t buf_data = SPI1BUF;
  return SPI1BUF;
}
