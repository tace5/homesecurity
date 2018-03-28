
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

  header[3] = source_ip;
  header[4] = dest_ip;

  header[2] |= calculate_ip_checksum(header);
  write_buffer_memory((uint8_t *) header, (ihl * 4));
}

uint16_t calculate_ip_checksum(uint32_t * header) {
  uint32_t sum = 0;
  int i;
  for (i = 0; i < 5; ++i)
  {
    uint16_t temp1 = (header[i] & 0xFFFF0000) >> 16;
    uint16_t temp2 = (header[i] & 0xFFFF);

    sum += temp1;
    sum += temp2;
  }

  while(sum & 0xFFFF0000){
    uint16_t carry = (sum & 0xFFFF0000) >> 16;
    sum = sum & 0xFFFF;
    sum += carry;
  }

  uint16_t checksum = (uint16_t) sum & 0xFFFF;

  return ~checksum;
}
