#include <stdio.h>
#include <stdint.h>
#include "drivers/ethernet/spi1.h"
#include "drivers/ethernet/enc28j60_instructions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/enc28j60_utils.h"
#include "drivers/ethernet/ethernet.h"

int main(void) {
  display_setup();
  display_string(3, "TEST TEST TEST");
  display_update();

  spi1_init();
  initialize_ethernet();
  uint8_t dest_address[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  uint8_t source_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};
  uint8_t data[11] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
  send_ethernet_frame(dest_address, source_address, 11, data);
  send_ethernet_frame(dest_address, source_address, 11, data);
  send_ethernet_frame(dest_address, source_address, 11, data);

  while (1) {
    
  }

  return 0;
}
