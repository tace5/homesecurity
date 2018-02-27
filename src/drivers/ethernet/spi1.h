
#define SS1 0x80
#define SPI1TXIF 0x1000000
#define SPI1RXIF 0x2000000
#define SPI1EIF 0x800000

void spi1_init(void);
void spi1_transfer(int data);
void spi1_receive(volatile int* data);
