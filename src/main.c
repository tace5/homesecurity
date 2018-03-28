#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include "drivers/ethernet/enc28j60_instructions.h"
//#include "drivers/ethernet/enc28j60_control_registers.h"
#include "utils/utils.h"
#include "state.h"
#include "drivers/display/display_functions.h"
#include "drivers/fingerprint/fingerprint.h"
#include "controllers/fingerprint_sensor.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/spi1.h"
#include "drivers/ethernet/enc28j60_instructions.h"
#include "drivers/ethernet/enc28j60_control_registers.h"
#include "drivers/ethernet/enc28j60_utils.h"
#include "drivers/ethernet/ethernet.h"
#include "drivers/us_sensor/us_sensor.h"
#include "network/ip.h"
#include "network/udp.h"
#include "network/http.h"
#include "controllers/flow_control.h"

void user_isr() {
    display_string(1, "Inside ISR");
    display_update();
    _delay(1500);
    if ((IFS(0) & FINGER_TOUCH_INT) >> 11) {
        handle_interrupt();
    }
}

void demo_setup() {
    //Enable switch SW2 & SW3 for demo, routed from port 7 & 8 to port 29 & 30
    //TRISESET = 0x18;
    //CURRENT_STATE = CONFIG_MODE;
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
  enable_unicast_filter();
  enable_reception();

  uint8_t dest_mac[6] = {0xb8, 0x27, 0xeb, 0x56, 0x34, 0xec};
  //uint8_t dest_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  char store[200];
  char * res = "GET";
  char * path = "/index.html";
  char body[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'};
  uint32_t request_len = construct_http_request_header(store, res, 3, path, 11, body, 0);
  construct_ethernet_frame(dest_mac, mac_address);
  construct_ipv4_header(1, 0x11, 0xc0a81435, 0xc0a81434, (request_len + 8));
  construct_udp_header(80, 80, 0xc0a81435, 0xc0a81434, 0x11, request_len, store);
  write_buffer_memory(store, request_len);
  send_packet(request_len + 20 + 8 + 14);

  select_memory_bank(0);
  uint8_t endpointer_low = read_control_register(ETXNDL);
  uint8_t endpointer_high = read_control_register(ETXNDH);
  uint16_t endpointer = ((uint16_t) endpointer_high << 8) | (uint16_t) endpointer_low;
  endpointer += 2;
  //display_debug(0, &endpointer);
  write_control_register(ERDPTL, (uint8_t) (endpointer & 0xff));
  write_control_register(ERDPTH, (uint8_t) ((endpointer & 0xff00)) >> 8);
  int erdptl = (int) read_control_register(ERDPTL);
  int erdpth = (int) read_control_register(ERDPTH);
  display_debug(0, &erdptl);
  //display_debug(1, &erdpth);
  uint8_t transmit_vectors[4];
  read_buffer_memory(transmit_vectors, 4);

  display_debug(1, (int*) transmit_vectors);
  return 0;
}
