
void construct_ipv4_header(int * header, uint16_t data_length, uint8_t ttl, uint8_t protocol, int source_ip, int dest_ip) {
  uint8_t ihl = 0x5;
  uint16_t total_length = ihl * 4 + data_length;
  uint8_t ecn = 0x0;
  uint8_t dscp = 0x0;
  uint8_t version = 0x4;

  uint8_t flag_offset = 0x0;
  uint8_t flags = 0x2;
  uint16_t identification = 0x0;

  header[0] = total_length;
  header[0] |= (ecn << 16);
  header[0] |= (dscp << 18);
  header[0] |= (ihl << 24);
  header[0] |= (version << 28);

  header[1] = flag_offset;
  header[1] |= (flags << 13);
  header[1] |= (identification << 16);

  header[2] = (protocol << 16);
  header[2] |= (ttl << 24);

  header[3] = source_ip;
  header[4] = dest_ip;

  uint16_t checksum = calculate_checksum(header);
  header[2] |= checksum;
}

uint16_t calculate_checksum(int * header) {
  int tot_length = ((header[0] & 0xf0000000) >> 28) * ((header[0] & 0xf000000) >> 24);

  uint16_t sum = 0;
  uint8_t mask = 0xffff << (tot_length * 4 - 16);
  while (tot_length--) {
    sum += *header & mask;
    mask = mask >> 16;
  }

  return ~sum;
}
