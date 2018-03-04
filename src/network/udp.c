
void construct_udp_header(uint32_t source_port, uint32_t dest_port, uint32_t data_length, uint8_t * data) {

}

// Inspired by https://gist.github.com/fxlv/81209bbd150abfeaceb1f85ff076c9f3
uint16_t calculate_checksum(uint32_t source_ip, uint32_t dest_ip, uint32_t protocol, uint32_t data_length, uint8_t * data) {
    uint8_t i = 0;

    if (data_length & 1) {
        i = 1;
    }

    uint8_t padded_data[data_length + i];

    if (data_length & 1) {
        int j;
        for (int j = 0; j < data_length; ++j)
        {
            padded_data[j] = data[j];
        }
        padded_data[j] = 0x0;
    } else {
        int j;
        for (int j = 0; j < data_length; ++j)
        {
            padded_data[j] = data[j];
        }
    }

    uint32_t source_ip_high = (source_ip & ~(0xffff)) >> 16;
    uint32_t source_ip_low = source_ip & 0xffff;
    uint32_t dest_ip_high = (dest_ip & ~(0xffff)) >> 16;
    uint32_t dest_ip_low = dest_ip & 0xffff;

    // Pseudo header
    uint32_t sum = source_ip_high + source_ip_low + dest_ip_high + dest_ip_low + protocol + 0xA;

    //Actual header
    uint16_t src_port = 0x14;
    uint16_t dest_port = 0xA;
    sum += src_port + dest_port + (data_length + 8); // data length + lenght of protocol + len of ports + len of UDP length

    for (i = 0; i < data_length / 2; i += 2) {
        sum += (uint16_t) ((padded_data[i] << 8) & 0xFF00) | (padded_data[i + 1] & 0xFF);
    }

    // See github link
    while (sum>>16) {
        sum = (sum & 0xFFFF)+(sum >> 16);
    }
    return ~sum;

}
