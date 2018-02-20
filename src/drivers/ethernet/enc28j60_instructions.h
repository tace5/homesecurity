
uint8_t read_control_register(uint8_t eth_register);
volatile int* read_buffer_memory(void)
void write_control_register(uint8_t eth_register, int data);
void write_buffer_memory(volatile int* data, unsigned int length);
void bit_field_set(uint8_t eth_register, uint8_t set_bits);
