
void construct_udp_header(uint32_t source_port, uint32_t dest_port, uint32_t data_length, uint8_t * data) {

}

// Inspired by https://gist.github.com/fxlv/81209bbd150abfeaceb1f85ff076c9f3
uint16_t calculate_checksum(uint32_t source_ip, uint32_t dest_ip, uint32_t protocol, uint32_t total_length, uint8_t * data) {
  uint8_t i = 0;

  if (total_length & 1) {
    i = 1;
  }

  uint8_t padded_data[total_length + i];

  if (total_length & 1) {

  } else {
    padded_data = data;
  }

  uint32_t source_ip_high = (source_ip & ~(0xffff)) >> 16;
  uint32_t source_ip_low = source_ip & 0xffff;
  uint32_t dest_ip_high = (dest_ip & ~(0xffff)) >> 16;
  uint32_t dest_ip_low = dest_ip & 0xffff;

  uint32_t sum = source_ip_high + source_ip_low + dest_ip_high + dest_ip_low + protocol + data_length;

  for (i = 0; i < total_length; i++) {
    // A 16-bit int is the same as the first byte shifted 8 bits left + the second byte
    // Sum of 0xABCD = 0xAB00 + 0xCD
    if (i & 1)
        sum += (uint32_t) padded_data[i];
    else
        sum += (uint32_t) padded_data[i] << 8;
    }
  }

  while (sum>>16) {
    sum = (sum & 0xFFFF)+(sum >> 16);
  }
  return ~sum;

}
