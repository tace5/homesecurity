#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include "drivers/ethernet/enc28j60_instructions.h"
//#include "drivers/ethernet/enc28j60_control_registers.h"
#include "utils/utils.h"
#include "state.h"
#include "drivers/display/display_functions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/spi1.h"
#include "drivers/ethernet/enc28j60_instructions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/enc28j60_utils.h"
#include "drivers/ethernet/ethernet.h"
#include "drivers/us_sensor/us_sensor.h"
#include "protocols/ip.h"

void user_isr() {

}

int main(void) {
  display_setup();
  sensor_init();
  spi1_init();
  uint16_t max_frame_length = 0x5ee;
  uint8_t mac_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};
  enable_autoinc();
  uint16_t receive_buffer_start = 0x1000;
  uint16_t receive_buffer_end = 0x1fff;
  init_mac(max_frame_length, mac_address);
  set_receive_buffer_pointers(receive_buffer_start, receive_buffer_end);
  enable_reception();
  /*uint8_t dest_address[6] = {0x44, 0x8a, 0x5b, 0x9f, 0x9d, 0x7b};
  uint8_t source_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};
  uint8_t data[11] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};*/

  int header[5] = {0x4500003c, 0x1c464000, 0x40060000, 0xac100a63, 0xac100a0c};
  int tot_length = ((header[0] & 0xf0000000) >> 28) * ((header[0] & 0xf000000) >> 24);

  int checksum = (int) calculate_checksum(header);

  display_debug(1, &checksum);

  while(1) {
    int distance = measure_dist();

    display_debug(1, &distance);
  }

  return 0;
}
