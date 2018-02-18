#include "spi1.h"

void read_control_register(volatile int eth_register) {
  int opcode = 0x0;
  int instruction = (opcode << 5) | eth_register;
  SS1 = 0;
  spi_transfer(instruction);
  SS1 = 1;
}

void write_control_register(volatile int eth_register, int data) {
  int opcode = 0x2;
  int instruction = (opcode << 5) | eth_register;
  SS1 = 0;
  spi_transfer(instruction);
  spi_transfer(data);
  SS1 = 1;
}
