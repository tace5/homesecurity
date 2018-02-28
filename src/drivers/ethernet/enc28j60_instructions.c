#include <stdlib.h>
#include "spi1.h"
#include "enc28j60_control_registers.h"

uint8_t read_control_register(uint8_t eth_register) {
  int register_data;
  uint8_t op_code = 0x0;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_receive(&register_data);
  PORTESET = SS1;

  return register_data;
}

void read_buffer_memory(volatile int * data, unsigned int length) {
  uint8_t op_code = 0x1;
  uint8_t instruction = (op_code << 5) | 0x1a;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  int i;
  for (i = 0; i < length; i++) {
    spi1_receive(data);
    data++;
  }
  PORTESET = SS1;
}

void write_control_register(uint8_t eth_register, uint8_t data) {
  uint8_t op_code = 0x2;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(data);
  PORTESET = SS1;
}

void write_buffer_memory(volatile uint8_t * data, unsigned int length) {
  uint8_t op_code = 0x3;
  uint8_t instruction = (op_code << 5) | 0x1a;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  int i;
  for(i = 0; i < length; i++) {
    spi1_transfer(*data);
    data++;
  }
  PORTESET = SS1;
}

void bit_field_set(uint8_t eth_register, uint8_t set_bits) { // Cannot be used on the MAC registers
  uint8_t op_code = 0x4;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(set_bits);
  PORTESET = SS1;
}

void bit_field_clr(uint8_t eth_register, uint8_t clr_bits) { // Cannot be used on the MAC registers
  uint8_t op_code = 0x5;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(clr_bits);
  PORTESET = SS1;
}

void system_reset(uint8_t eth_register) {
  PORTECLR = SS1;
  spi1_transfer(0xff);
  PORTESET = SS1;
}
