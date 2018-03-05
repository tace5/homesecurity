
void construct_ipv4_header(uint32_t ttl, uint32_t protocol, uint32_t source_ip, uint32_t dest_ip, uint32_t data_length) {
  uint32_t header[5];

  uint32_t version = 0x4;
  uint32_t ihl = 0x5;
  uint32_t dscp = 0x0;
  uint32_t ecn = 0x0;
  uint32_t total_length = ihl * 4 + data_length;

  uint32_t identification = 0x0;
  uint32_t flags = 0x2;
  uint32_t fragment_offset = 0x0;

  uint32_t checksum = 0x0;

  header[0] = (version << 28);
  header[0] |= (ihl << 24);
  header[0] |= (dscp << 18);
  header[0] |= (ecn << 16);
  header[0] |= total_length;

  header[1] = (identification << 16);
  header[1] |= (flags << 13);
  header[1] |= fragment_offset;

  header[2] = (ttl << 24);
  header[2] |= (protocol << 16);
  header[2] |= checksum;

  header[3] = source_ip;
  header[4] = dest_ip;

  write_buffer_memory((uint8_t *) header, (ihl * 4));
}

// Unused
uint16_t calculate_ip_checksum(int * header) {
  int tot_length = ((header[0] & 0xf0000000) >> 28) * ((header[0] & 0xf000000) >> 24);

  uint16_t sum = 0;
  uint8_t mask = 0xffff << (tot_length * 4 - 16);
  while (tot_length--) {
    sum += *header & mask;
    mask = mask >> 16;
  }

  return ~sum;
}
