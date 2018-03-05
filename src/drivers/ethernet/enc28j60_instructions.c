#include <stdlib.h>
#include "spi1.h"
#include "../display/display_functions.h"
#include "enc28j60_control_registers.h"
#include "enc28j60_utils.h"

uint8_t read_control_register(uint8_t addr) {
  uint8_t register_data;
  uint8_t op_code = 0x0;
  uint8_t instruction = (op_code << 5) | addr;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  if (is_mac_mii_register(addr)) {
    spi1_transfer(0x0); // Read dummy byte
  }
  register_data = spi1_transfer(0x0);
  PORTESET = SS1;

  return register_data;
}

void read_buffer_memory(volatile uint8_t * data, uint32_t length) {
  uint8_t op_code = 0x1;
  uint8_t instruction = (op_code << 5) | 0x1a;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  while (length--) {
    *data++ = spi1_transfer(0x0);
  }
  PORTESET = SS1;
}

void write_control_register(uint8_t addr, uint8_t data) {
  uint8_t op_code = 0x2;
  uint8_t instruction = (op_code << 5) | addr;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(data);
  PORTESET = SS1;
}

void write_buffer_memory(volatile uint8_t * data, uint32_t length) {
  uint8_t op_code = 0x3;
  uint8_t instruction = (op_code << 5) | 0x1a;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  while (length--) {
    /*if (length != 0) {
      int temp = (int) *data;
      display_debug(1, &temp);
    }*/
    spi1_transfer(*data++);
  }
  PORTESET = SS1;
}

void bit_field_set(uint8_t addr, uint8_t set_bits) { // Cannot be used on the MAC registers
  uint8_t op_code = 0x4;
  uint8_t instruction = (op_code << 5) | addr;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(set_bits);
  PORTESET = SS1;
}

void bit_field_clr(uint8_t addr, uint8_t clr_bits) { // Cannot be used on the MAC registers
  uint8_t op_code = 0x5;
  uint8_t instruction = (op_code << 5) | addr;

  PORTECLR = SS1;
  spi1_transfer(instruction);
  spi1_transfer(clr_bits);
  PORTESET = SS1;
}

void system_reset(void) {
  PORTECLR = SS1;
  spi1_transfer(0xff);
  PORTESET = SS1;
}
