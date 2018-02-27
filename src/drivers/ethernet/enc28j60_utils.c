#include <stdio.h>
#include "enc28j60_instructions.h"
#include "enc28j60_control_registers.h"

void enable_autoinc() {
  bit_field_set(ECON2, AUTOINC);
}

void set_receive_buffer_pointers(uint16_t receive_buffer_start, uint16_t receive_buffer_end) {
  uint8_t receive_buffer_start_high = receive_buffer_start & 0xff00;
  uint8_t receive_buffer_start_low = receive_buffer_start & 0xff;
  uint8_t receive_buffer_end_high = receive_buffer_end & 0xff00;
  uint8_t receive_buffer_end_low = receive_buffer_end & 0xff;

  write_control_register(ERXSTH, receive_buffer_start_high);
  write_control_register(ERXSTL, receive_buffer_start_low);
  write_control_register(ERXNDH, receive_buffer_end_high);
  write_control_register(ERXNDL, receive_buffer_end_low);
}

void enable_unicast_filter() {
  bit_field_set(ERXFCON, (UCEN | ANDOR));
}

void wait_for_ost() {
  do {
    ostIsReady = read_control_register(ESTAT) & 0x1;
  } while(!ostIsReady);
}

void init_mac(uint16_t max_frame_length, uint8_t * mac_address) { // Set MAC control registers in full duplex mode according to the IEEE specification
  select_memory_bank(2);
  uint8_t macon1_bits = MARXEN;
  macon1_bits |= TXPAUS;
  macon1_bits |= RXPAUS;
  bit_field_set(MACON1, macon1_bits);

  uint8_t macon3_bits = PADCFG0;
  macon3_bits |= PADCFG1;
  macon3_bits |= TXCRCEN;
  macon3_bits |= FULDPX;
  // Possibly must set phy-register for full duplex mode
  bit_field_set(MACON3, macon3_bits);

  bit_field_set(MACON4, DEFER);

  uint8_t max_frame_length_high = max_frame_length & 0xff00;
  uint8_t max_frame_length_low = max_frame_length & 0xff;
  write_control_register(MAMXFLH, max_frame_length_high);
  write_control_register(MAMXFLL, max_frame_length_low);
  write_control_register(MABBIPG, 0x15);
  write_control_register(MAIPGL, 0x12);

  select_memory_bank(3);
  write_control_register(MAADR1, mac_address[0]);
  write_control_register(MAADR2, mac_address[1]);
  write_control_register(MAADR3, mac_address[2]);
  write_control_register(MAADR4, mac_address[3]);
  write_control_register(MAADR5, mac_address[4]);
  write_control_register(MAADR6, mac_address[5]);
}

void select_memory_bank(int bank) {
  bit_field_set(ECON1, bank);
}

void enable_reception() {
  bit_field_set(EIE, (PKTIE | INTIE));
  bit_field_clr(EIE, RXERIF);
  bit_field_set(EIE, (RXERIE | INTIE));
  bit_field_set(ECON1, RXEN);
}

void send_ethernet_frame(uint8_t * dest_mac, uint8_t * source_mac, int length, int * data) { // May needs to be reworked
  int * protocol;
  *protocol = 0x4;

  write_buffer_memory(dest_mac, 6);
  write_buffer_memory(source_mac, 6);
  write_buffer_memory(protocol, 2);
  write_buffer_memory(data, length);

  if (length <= 46) {
    write_control_register(ETXNDL, 64);
  } else if (length > 46) {
    uint16_t end_pointer = 18 + length;
    write_control_register(ETXNDL, (end_pointer & 0xff));
    write_control_register(ETXNDH, (end_pointer & 0x1f));
  }

  bit_field_clr(EIR, TXIF);
  bit_field_set(EIE, (TXIE | INTIE));

  bit_field_set(ECON1, TXRTS);
}
