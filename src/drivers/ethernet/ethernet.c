#include "enc28j60_utils.h"

void initialize() {
  uint16_t receive_buffer_start = 0x1000;
  uint16_t receive_buffer_end = 0x1fff;
  uint16_t max_frame_length = 0x5ee;
  uint8_t mac_address[6] = {0x6e, 0x79, 0x8a, 0x9b, 0xee, 0x9d};

  enable_autoinc();
  set_receive_buffer_pointers(receive_buffer_start, receive_buffer_end);
  enable_unicast_filter();
  wait_for_ost();
  init_mac(max_frame_length, mac_address);
  enable_reception();
}
