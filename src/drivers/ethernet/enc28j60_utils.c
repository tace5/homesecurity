#include <stdio.h>
#include "enc28j60_instructions.h"
#include "enc28j60_control_registers.h"
#include "../display/display_functions.h"

void enable_autoinc(void) {
  bit_field_set(ECON2, AUTOINC);
}

void set_receive_buffer_pointers(uint16_t receive_buffer_start, uint16_t receive_buffer_end) {
  uint8_t receive_buffer_start_high = (uint8_t) ((receive_buffer_start & 0xff00) >> 8);
  uint8_t receive_buffer_start_low = (uint8_t) (receive_buffer_start & 0xff);
  uint8_t receive_buffer_end_high = (uint8_t) ((receive_buffer_end & 0xff00) >> 8);
  uint8_t receive_buffer_end_low = (uint8_t) (receive_buffer_end & 0xff);

  select_memory_bank(0);
  write_control_register(ERXSTH, receive_buffer_start_high);
  write_control_register(ERXSTL, receive_buffer_start_low);
  write_control_register(ERXNDH, receive_buffer_end_high);
  write_control_register(ERXNDL, receive_buffer_end_low);
}

void enable_unicast_filter(void) {
  bit_field_set(ERXFCON, (UCEN | ANDOR));
}


void init_mac(uint16_t max_frame_length, volatile uint8_t * mac_address) { // Set MAC control registers in full duplex mode according to the IEEE specification
  system_reset();
  uint8_t ost_is_ready;
  do {
    ost_is_ready = read_control_register(ESTAT) & 0x1;
  } while(!ost_is_ready);

  select_memory_bank(2);
  bit_field_set(MACON1, MARXEN);

  bit_field_set(MACON3, PADCFG0 | PADCFG1 | TXCRCEN);

  bit_field_set(MACON4, DEFER);

  uint8_t max_frame_length_high = (uint8_t) ((max_frame_length & 0xff00) >> 8);
  uint8_t max_frame_length_low = (uint8_t) (max_frame_length & 0xff);
  write_control_register(MAMXFLH, max_frame_length_high);
  write_control_register(MAMXFLL, max_frame_length_low);
  write_control_register(MABBIPG, 0x12);
  write_control_register(MAIPGL, 0x12);
  write_control_register(MAIPGH, 0xc);
  select_memory_bank(3);
  write_control_register(MAADR1, mac_address[0]);
  write_control_register(MAADR2, mac_address[1]);
  write_control_register(MAADR3, mac_address[2]);
  write_control_register(MAADR4, mac_address[3]);
  write_control_register(MAADR5, mac_address[4]);
  write_control_register(MAADR6, mac_address[5]);
}

void select_memory_bank(uint8_t bank) {
  if (bank >= 0 && bank <= 3) {
    CURRENT_BANK = bank;
    bit_field_clr(ECON1, BSEL);
    bit_field_set(ECON1, bank);
  }
}

uint8_t is_mac_mii_register(uint8_t addr) {
  return (CURRENT_BANK == 2 && addr <= MIRDH || CURRENT_BANK == 3 && addr <= MISTAT) ? 1 : 0x0;
}

void enable_reception() {
  bit_field_set(EIE, (PKTIE | INTIE));
  bit_field_clr(EIE, RXERIF);
  bit_field_set(EIE, (RXERIE | INTIE));
  bit_field_set(ECON1, RXEN);
}

void construct_ethernet_frame(volatile uint8_t * dest_mac, volatile uint8_t * source_mac) { // May needs to be reworked
  uint8_t protocol[2] = {0x81, 0x00};

  write_buffer_memory(dest_mac, 6);
  write_buffer_memory(source_mac, 6);
  write_buffer_memory(protocol, 2);
}

void send_packet(uint32_t length) {
  if (length <= 64) {
    write_control_register(ETXNDL, 64);
  } else if (length > 64) {
    uint16_t end_pointer = length;
    write_control_register(ETXNDL, (end_pointer & 0xff));
    write_control_register(ETXNDH, ((end_pointer & 0x1f00) >> 8));
  }

  bit_field_clr(EIR, TXIF);
  bit_field_set(EIE, (TXIE | INTIE));

  bit_field_set(ECON1, TXRTS);
}
