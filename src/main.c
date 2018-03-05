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
#include "network/ip.h"
#include "network/udp.h"
#include "network/http.h"

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

  uint8_t dest_mac[6] = {0x9c, 0x5c, 0x8e, 0xbf, 0x87, 0x57};

  char store[200];
  char * res = "GET";
  char * path = "/index.html";
  uint32_t request_len = construct_http_request_header(store, res, 3, path, 11, EMPTY_BODY, 0);
  construct_ethernet_frame(dest_mac, mac_address);
  construct_ipv4_header(1, 0x11, 0xc0a81401, 0xc0a814c8, (request_len + 8));
  construct_udp_header(80, 80, 0xc0a81401, 0xc0a814c8, 0x11, request_len, store);
  write_buffer_memory(store, request_len);
  send_packet(request_len + 20 + 8 + 14);
  int temp = (int) store[request_len - 2];
  display_debug(1, &temp);
  //display_debug(0, (int *) &request_len);

  int intie = (int) read_control_register(ETXNDL);
  //display_debug(1, &intie);

  int txif;
  do {
    txif = (int) (read_control_register(EIR) & TXIF);
    if (txif) {
      //display_debug(1, &txif);
    }
  } while (!txif);

  return 0;
}
