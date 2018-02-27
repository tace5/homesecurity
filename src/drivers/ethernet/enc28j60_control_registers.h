
// Common registers
#define EIE       0x1b
#define EIR       0x1c
#define ESTAT     0x1d
#define ECON2     0x1e
#define ECON1     0x1f

// Bank 0
#define ERDPTL    0x0
#define ERDPTH    0x1
#define EWRPTL    0x2
#define EWRPTH    0x3
#define ETXSTL    0x4
#define ETXSTH    0x5
#define ETXNDL    0x6
#define ETXNDH    0x7
#define ERXSTL    0x8
#define ERXSTH    0x9
#define ERXNDL    0xa
#define ERXNDH    0xb
#define ERXRDPTL  0xc
#define ERXRDPTH  0xd
#define ERXWRPTL  0xe
#define ERXWRPTH  0xf
#define EDMASTL   0x10
#define EDMASTH   0x11
#define EDMANDL   0x12
#define EDMANDH   0x13
#define EDMADSTL  0x14
#define EDMADSTH  0x15
#define EDMACSL   0x16
#define EDMACSH   0x17

// Bank 1
#define EHT0      0x0
#define EHT1      0x1
#define EHT2      0x2
#define EHT3      0x3
#define EHT4      0x4
#define EHT5      0x5
#define EHT6      0x6
#define EHT7      0x7
#define EPMM0     0x8
#define EPMM1     0x9
#define EPMM2     0xa
#define EPMM3     0xb
#define EPMM4     0xc
#define EPMM5     0xd
#define EPMM6     0xe
#define EPMM7     0xf
#define EPMCSL    0x10
#define EPMCSH    0x11
#define EPMOL     0x14
#define EPMOH     0x15
#define ERXFCON   0x18
#define EPKTCNT   0x19

// Bank 2
#define MACON1    0x0
#define MACON3    0x2
#define MACON4    0x3
#define MABBIPG   0x4
#define MAIPGL    0x6
#define MAIPGH    0x7
#define MACLCON1  0x8
#define MACLCON2  0x9
#define MAMXFLL   0xa
#define MAMXFLH   0xb
#define MICMD     0x12
#define MIREGADR  0x14
#define MIWRL     0x16
#define MIWRH     0x17
#define MIRDL     0x18
#define MIRDH     0x19

// Bank 3
#define MAADR5    0x0
#define MAADR6    0x1
#define MAADR3    0x2
#define MAADR4    0x3
#define MAADR1    0x4
#define MAADR2    0x5
#define EBSTSD    0x6
#define EBSTCON   0x7
#define EBSTCSL   0x8
#define EBSTCSH   0x9
#define MISTAT    0xa
#define EREVID    0x12
#define ECOCON    0x15
#define EFLOCON   0x17
#define EPAUSL    0x18
#define EPAUSH    0x19

/*
  Register fields
*/

// EIE
#define INTIE   0x80;
#define PKTIE   0x40;
#define DMAIE   0x20;
#define LINKIE  0x10;
#define TXIE    0x8;
#define TXERIE  0x2;
#define RXERIE  0x1;

// EIR
#define PKTIF   0x40;
#define DMAIF   0x20;
#define LINKIF  0x10;
#define TXIF    0x80;
#define TXERIF  0x20;
#define RXERIF  0x10;

// ESTAT
#define INT     0x80;
#define BUFER   0x40;
#define LATECOL 0x10;
#define RXBUSY  0x4;
#define TXABRT  0x2;
#define CLKRDY  0x1;

// ECON2
#define AUTOINC 0x80;
#define PKTDEC  0x40;
#define PWRSV   0x20;
#define VRPS    0x8;

// ECON1
#define TXRST   0x80;
#define RXRST   0x40;
#define DMAST   0x20;
#define CSUMEN  0x10;
#define TXRTS   0x8;
#define RXEN    0x4;
#define BSEL    0x3;

// ERXFCON
#define UCEN    0x80;
#define ANDOR   0x40;

// MACON1
#define TXPAUS  0x8;
#define RXPAUS  0x4;
#define PASSALL 0x2;
#define MARXEN  0x1;

// MACON3
#define PADCFG2 0x80;
#define PADCFG1 0x40;
#define PADCFG0 0x20;
#define TXCRCEN 0x10;
#define PHDREN  0x8;
#define HFRMEN  0x4;
#define FRMLNEN 0x2;
#define FULDPX  0x1;

// MACON4
#define DEFER   0x40;
#define BPEN    0x20;
#define NOPKOFF 0x10;
