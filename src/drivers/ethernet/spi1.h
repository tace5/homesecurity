
#define SS1 0x40
#define SPI1TXIF 0x1000000
#define SPI1RXIF 0x2000000
#define SPI1EIF 0x800000

void enable_spi(void);
void spi_transfer(int data);
void spi_receive(volatile int* data);
