#include "enc28j60_instructions.h"
#include "enc28j60_control_registers.h"

void init_mac() {
  select_memory_bank(2);
  uint8_t macon1_bits = MARXEN;
  macon1_bits |= TXPAUS;
  macon1_bits |= RXPAUS;
  bit_field_set(MACON1, macon1_bits);

  uint8_t macon3_bits = PADCFG0;
  macon3_bits |= PADCFG1;
  macon3_bits |= TXCRCEN;
  macon3_bits |= FULDPX;
  bit_field_set(MACON3, macon3_bits);

  bit_field_set(MACON4, DEFER);

  uint8_t max_frame_length = 0x5ee;
  write_control_register(MAMXFLL, max_frame_length);
  write_control_register(MABBIPG, 0x15);
  write_control_register(MAIPGL, 0x12);

  select_memory_bank(3);
  write_control_register(MAADR1, 0x22);
  write_control_register(MAADR2, 0xf1);
  write_control_register(MAADR3, 0x5f);
  write_control_register(MAADR4, 0x63);
  write_control_register(MAADR5, 0x4b);
  write_control_register(MAADR6, 0xe3);
}

void select_memory_bank(int bank) {
  bit_field_set(ECON1, bank);
}

void create_ethernet_frame() {

}
