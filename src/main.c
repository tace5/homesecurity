#include <stdio.h>
#include <stdint.h>
#include "drivers/display/display_functions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/spi1.h"
#include "drivers/ethernet/enc28j60_instructions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/enc28j60_utils.h"
#include "drivers/ethernet/ethernet.h"

int main(void) {
  display_setup();

  spi1_init();
  uint16_t max_frame_length = 0x5ee;
  uint8_t mac_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};
  enable_autoinc();
  uint16_t receive_buffer_start = 0x1000;
  uint16_t receive_buffer_end = 0x1fff;
  init_mac(max_frame_length, mac_address);
  set_receive_buffer_pointers(receive_buffer_start, receive_buffer_end);
  enable_reception();
  /*uint8_t dest_address[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  uint8_t source_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};
  uint8_t data[11] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};

  send_ethernet_frame(dest_address, source_address, 11, data);
  send_ethernet_frame(dest_address, source_address, 11, data);
  send_ethernet_frame(dest_address, source_address, 11, data);*/

  struct Books {
     char  title[50];
     char  author[50];
     char  subject[100];
     int   book_id;
  } book;

  /*uint8_t pktif;
  uint8_t data[4];
  int i = 0;
  do {
    pktif = read_control_register(EIR) & PKTIF;
    if (pktif) {
      read_buffer_memory((data + i++), 4);
      display_debug(1, (int *) data);
    }
  } while (!pktif);*/

  return 0;
}
