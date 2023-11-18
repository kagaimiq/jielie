# BR23 I/O function map

**Scraped from AC635N refmanual**

| Pin   | func       | func         | func           | func          | func          | func          | func      | func  | func    | func      | func              | func    |
|-------|------------|--------------|----------------|---------------|---------------|---------------|-----------|-------|---------|-----------|-------------------|---------|
| PA0   | SEG0       | AMUX0L       |                |               |               |               |           |       | Touch0  | CLKOUT0   | UART1TXC          | PWMCH0H |
| PA1   | SEG1       | AMUX0R       |                |               |               |               |           | ADC0  | Touch1  |           | UART1RXC          | PWMCH0L |
| PA2   | SEG2       | PSRAM_D3A    | PLNK_SCLK      | Q-decoder0_0  | SPI0_DAT3C(3) | ALNK0_SCLKA   |           |       | Touch2  | CAP3      | UART2TXA          | TMR0CK  |
| PA3   | SEG3       | PSRAM_CKA    | PLNK_DAT1      | Q-decoder0_1  | SPI0_CLKC     | ALNK0_LRCKA   |           |       | Touch3  |           | UART2RXA          | TMR1CK  |
| PA4   | SEG4       | PSRAM_CSA    |                |               | SPI0_CSC      | ALNK0_DAT0A   |           |       | Touch4  |           |                   |         |
| PA5   | SEG5       |              | SD0DAT0A       | BT_Active     |               | ALNK0_DAT1A   | IIC_SCL_D | ADC1  | Touch5  | PWM0      | UART0TXA          |         |
| PA6   | SEG6       | PSRAM_D1A    | SD0DAT1A       | Wlan_Active   | SPI0_DIC(1)   | ALNK0_DAT2A   | IIC_SDA_D | ADC2  | Touch6  |           | UART0RXA          |         |
| PA7   | SEG7       | PSRAM_D2A    | SD0DAT2A       | BT_priority   | SPI0_DAT2C(2) | ALNK0_DAT3A   |           |       | Touch7  | TMR0      |                   |         |
| PA8   | SEG8       | PSRAM_D0A    | SD0DAT3A       | BT_Freq       | SPI0_DOC(0)   | ALNK0_MCLKA   |           |       |         |           |                   | FPIN2   |
| PA9   | SEG9       | PA_EN        | SD0CMDA        | SPDIF_IN_A    | PAPD0         | ALNK0_SCLKB   | UART1_CTS |       | Touch8  |           | UART2TXB          | PWMCH4H |
| PA10  | SEG10      | LNA_EN       | SD0CLKA        | SPDIF_IN_B    | PAPD1         | ALNK0_LRCKB   | UART1_RTS | ADC3  | Touch9  | TMR1      | UART2RXB          | PWMCH4L |
| PA11  | SEG11      |              |                |               | PAP_RD        | ALNK0_DAT0B   |           |       |         |           | UART0TXD          |         |
| PA12  | SEG12      |              |                |               | PAP_WR        | ALNK0_DAT1B   |           | ADC4  |         | PWM1      | UART0RXD          | TMR2CK  |
| PA13  | SEG13      |              | SPI0_CSB       | SFC_CSB       | SPI2DIB       | ALNK0_DAT2B   |           |       |         |           |                   | TMR3CK  |
| PA14  | SEG14      |              | SPI0_DIB(1)    | SFC_DIB(1)    |               | ALNK0_DAT3B   |           |       |         |           |                   | FPIN0   |
| PA15  | SEG15      |              | SPI0_DAT2B(2)  | SFC_DAT2B(2)  |               | ALNK0_MCLKB   |           |       |         | CAP2      |                   | FPIN1   |
| PB0   |            |              | SDTAP_CLKC     | SPDIF_IN_C    | SPI1CLKA      | ALNK1_MCLK    |           |       |         |           | UART1TXA          | PWMCH1H |
| PB1   |            | lp-reset     | SDTAP_DATC     | SPDIF_IN_D    | SPI1DOA       |               |           | ADC5  |         | TMR2      | UART1RXA          |         |
| PB2   |            |              |                | Q-decoder1_0  | SPI1DIA       |               |           |       |         |           |                   | PWMCH1L |
| PB3   |            |              |                | Q-decoder1_1  |               |               |           | ADC6  |         | PWM2      |                   | TMR4CK  |
| PB4   |            | Q-decoder2_0 | SD1DAT0B       | PSRAM_D3B     | SD0DAT3B      | SPI0_DAT3D(3) | IIC_SCL_C | ADC7  | LVD     |           | UART0TXB          | PWMCH2H |
| PB5   |            |              | SD1CMDB        | PSRAM_CKB     | SD0DAT2B      | SPI0_CLKD     |           |       |         | PWM3/CAP1 | UART0TXC/UART0RXC |         |
| PB6   |            | Q-decoder2_1 | SD1CLKB        | PSRAM_CSB     | SD0DAT1B      | SPI0_CSD      | IIC_SDA_C |       |         | TMR3      | UART0RXB          | PWMCH2L |
| PB7   |            | AMUX1L       | SPI0_DAT2A(2)  | SFC_DAT2A(2)  |               |               |           |       |         |           |                   |         |
| PB8   |            | AMUX1R       | SD1DAT1B       | PSRAM_D1B     | SD0DAT0B      | SPI0_DID(1)   | SPI2DIA   | ADC8  |         | CLKOUT1   |                   |         |
| PB9   | SDTAP_CLKD | AMUX2L       | SD1DAT2B       | PSRAM_D2B     | SD0CLKB       | SPI0_DAT2D(2) | SPI2CLKA  |       |         | CAP0      | UART2TXC          | PWMCH3H |
| PB10  | SDTAP_DATD | AMUX2R       | SD1DAT3B       | PSRAM_D0B     | SD0CMDB       | SPI0_DOD(0)   | SPI2DOA   | ADC9  | FM_TX_A |           | UART2RXC          | PWMCH3L |
| PB11  | SDPG       |              |                | SPIDIF_OUT    |               |               |           |       | FM_TX_B |           |                   |         |
| PC0   | SEG16/COM5 | SD1DAT3A     |                | ALNK1_SCLK    | PAPD2         |               |           |       | Touch10 |           | UART1TXB          | FPIN3   |
| PC1   | SEG17/COM4 | SD1DAT2A     |                | ALNK1_LRCK    | PAPD3         |               |           |       | Touch11 |           | UART1RXB          | FPIN4   |
| PC2   | SEG18/COM3 | SD1DAT1A     |                | ALNK1_DAT0    | PAPD4         |               |           |       | Touch12 |           |                   | FPIN5   |
| PC3   | COM2       | SD1DAT0A     |                | ALNK1_DAT1    | PAPD5         | SPI1DIB       |           |       | Touch13 |           |                   | TMR5CK  |
| PC4   | COM1       | SD1CMDA      | SDTAP_CLKA     | ALNK1_DAT2    | PAPD6         | SPI1CLKB      | IIC_SCL_B | ADC10 | Touch14 |           | UART2TXD          | PWMCH5H |
| PC5   | COM0       | SD1CLKA      | SDTAP_DATA     | ALNK1_DAT3    | PAPD7         | SPI1DOB       | IIC_SDA_B | ADC13 | Touch15 |           | UART2RXD          | PWMCH5L |
| PC6   | SEG20      | MIC          |                | ISP_DO        |               |               |           | ADC11 |         |           |                   |         |
| PC7   | SEG21      | MIC_BIAS     |                |               |               |               |           |       |         |           |                   |         |
| PD0   |            |              | SPI0_CLKAB     | SFC_CLKAB     |               |               |           |       |         |           |                   |         |
| PD1   |            |              | SPI0_DOAB(0)   | SFC_DOAB(0)   |               |               |           |       |         |           |                   |         |
| PD2   |            |              | SPI0_DIA(1)    | SFC_DIA(1)    |               |               |           |       |         |           |                   |         |
| PD3   |            |              | SPI0_CSA       | SFC_CSA       |               |               |           |       |         |           |                   |         |
| PD4   |            | flash POWAA! |                |               |               |               |           |       |         |           |                   |         |
| PD5   | SEG19      |              | SPI0_DAT3AB(3) | SFC_DAT3AB(3) |               |               |           |       |         |           |                   |         |
| PR0   |            | OSCI_32K     |                |               |               |               |           |       |         |           |                   |         |
| PR1   |            | OSCO_32K     |                |               |               |               |           |       |         |           |                   |         |
| USBDP |            |              | SDTAP_CLKB     | ISP_CLK       | SPI2CLKB      | mode_det0     | IIC_SCL_A | ADC12 |         |           | UART1TXD          |         |
| USBDM |            |              | SDTAP_DATB     | ISP_DI        | SPI2DOB       | mode_det1     | IIC_SDA_A |       |         |           | UART1RXD          |         |

## Per function

### UART

| UART0 |  A  |  B  |  C  |  D   |
|-------|-----|-----|-----|------|
| TX    | PA5 | PB4 | PB5 | PA11 |
| RX    | PA6 | PB6 | PB5 | PA12 |

| UART1 |  A   |  B   |  C   |  D    |
|-------|------|------|------|-------|
| TX    | PB0  | PC0  | PA0  | USBDP |
| RX    | PB1  | PC1  | PA1  | USBDM |
| CTS   | PA9  | PA9  | PA9  | PA9   |
| RTS   | PA10 | PA10 | PA10 | PA10  |

| UART2 |  A  |  B   |  C   |  D  |
|-------|-----|------|------|-----|
| TX    | PA2 | PA9  | PB9  | PC4 |
| RX    | PA3 | PA10 | PB10 | PC5 |

### IIC

| IIC  |  A    |  B  |  C  |  D  |
|------|-------|-----|-----|-----|
| SCL  | USBDP | PC4 | PB4 | PA5 |
| SDA  | USBDM | PC5 | PB5 | PA6 |

### SPI

| SPI0    |  A  |  B   |  C  |  D   |
|---------|-----|------|-----|------|
| CS      | PD3 | PA13 | PA4 | PB6  |
| CLK     | PD0 | PD0  | PA3 | PB5  |
| DO(0)   | PD1 | PD1  | PA8 | PB10 |
| DI(1)   | PD2 | PA14 | PA6 | PB8  |
| DAT2(2) | PB7 | PA15 | PA7 | PB9  |
| DAT3(3) | PD5 | PD5  | PA2 | PB4  |

| SPI1 |  A  |  B  |
|------|-----|-----|
| CLK  | PB0 | PC4 |
| DO   | PB1 | PC5 |
| DI   | PB2 | PC3 |

| SPI2 |  A   |  B    |
|------|------|-------|
| CLK  | PB10 | USBDP |
| DO   | PB9  | USBDM |
| DI   | PB8  | PA13  |
