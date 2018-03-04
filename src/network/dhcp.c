
#include <stdlib.h>
#include <stdbool.h>

void construct_dhcp_header(uint32_t * data, uint32_t op, bool isBroadcast, uint32_t client_ip, uint32_t y_ip, uint32_t server_ip, uint32_t gateway, uint32_t * mac_address, uint32_t * options, uint32_t options_length) {
  uint32_t htype = 0x1;
  uint32_t hlen = 0x6;
  uint32_t hops = 0;
  uint32_t xid = rand();
  uint32_t secs = 0x0;
  uint32_t flags = isBroadcast ? 0x8000 : 0x0;
  uint32_t magic_cookie = 0x63825363;

  data[0] = hops;
  data[0] |= (hlen << 8);
  data[0] |= (htype << 16);
  data[0] |= (op << 24);
  data[1] = xid;
  data[2] = flags;
  data[2] |= (secs << 16);
  data[3] = client_ip;
  data[4] = y_ip;
  data[5] = server_ip;
  data[6] = gateway;
  data[7] = mac_address[0];
  data[8] = mac_address[1];
  data[9] = mac_address[2];
  data[10] = mac_address[3];
  data[11] = magic_cookie;

  for (int i = 0; i < options_length; ++i) {
    data [12 + i] = options[i];
  }
}

void dhcp_discover() {
  uint8_t destination_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  uint8_t destination_ip[4] = {255, 255, 255, 255};
  uint8_t source_ip[4] = {0, 0, 0, 0};
  uint8_t op_code = 0x1;


}

void dhcp_request() {

}
