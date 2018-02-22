#include <stdlib.h>
#include <stdint.h>
#include "spi1.h"
#include "enc28j60_control_registers.h"

uint8_t read_control_register(uint8_t eth_register) {
  uint8_t register_data;
  uint8_t op_code = 0x0;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTDCLR = SS1;
  spi1_transfer(instruction);
  spi1_receive(&register_data);
  PORTDSET = SS1;

  return register_data;
}

void read_buffer_memory(volatile int* data, unsigned int length) {
  uint8_t op_code = 0x1;
  uint8_t instruction = (opcode << 5) | 0x1a;

  PORTDCLR = SS1;
  spi1_transfer(instruction);
  for (int i = 0; i < length; i++) {
    spi1_receive(data + i);
  }
  PORTDSET = SS1;
}

void write_control_register(uint8_t eth_register, uint8_t data) {
  uint8_t op_code = 0x2;
  uint8_t instruction = (op_code << 5) | eth_register;

  PORTDCLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(data);
  PORTDSET = SS1;
}

void write_buffer_memory(volatile int* data, unsigned int length) {
  uint8_t op_code = 0x3;
  uint8_t instruction = (op_code << 5) | 0x1a;

  PORTDCLR = SS1;
  spi1_transfer(instruction);
  for(int i = 0; i < length; i++) {
    spi1_transfer(data + i);
  }
  PORTDSET = SS1;
}

void bit_field_set(uint8_t eth_register, uint8_t set_bits) {
  uint8_t op_code = 0x4
}
