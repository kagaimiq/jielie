# BR25 I/O function map

**Scraped from AC636N refmanual**

| Pin   | func      | func     | func         | func           | func          | func                    | func      | func  | func      | func              |
|-------|-----------|----------|--------------|----------------|---------------|-------------------------|-----------|-------|-----------|-------------------|
| PA0   | SDPG      |          |              | SPIDIF_OUT     |               | ALNK_DAT0_AB            |           | ADC0  | CLKOUT0   | UART1TXC          |
| PA1   |           | MIC      |              |                |               | ALNK_DAT1_A             |           | ADC1  | PWM4      | UART1RXC          |
| PA2   | SD0CLK_C  | MIC_BIAS |              |                |               | ALNK_MCLK_A/ALNK_DAT1_B |           |       | CAP3      |                   |
| PA3   | SD0DAT_C  | AMUX0L   | Q-decoder0_0 | PLNK_SCLK      | BT_Active     | ALNK_SCLK_A/ALNK_DAT2_B | UART1_CTS | ADC2  | PWM5      | UART2TXA          |
| PA4   | SD0CMD_CE | AMUX0R   | Q-decoder0_1 | PLNK_DAT1      | Wlan_Active   | ALNK_LRCK_A/ALNK_DAT3_B | UART1_RTS | ADC3  | TMR4      | UART2RXA          |
| PA5   |           |          |              | SPDIF_IN_A     | BT_priority   | ALNK_DAT2_A/ALNK_SCLK_B | IIC_SCL_D |       | PWM0      | UART0TXA          |
| PA6   |           |          |              | SPDIF_IN_B     | BT_Freq       | ALNK_DAT3_A/ALNK_LRCK_B | IIC_SDA_D | ADC4  | CAP4      | UART0RXA          |
| PB0   | SD0CLK_D  |          | SDTAP_CLKC   | SPDIF_IN_C     |               | SPI1CLKA                |           |       | TMR5      | UART0TXB          |
| PB1   |           | lp-reset | SDTAP_DATC   | SPDIF_IN_D     |               | SPI1DOA                 | FM_TXA    | ADC5  | TMR2      | UART0RXB          |
| PB2   | SD0CMD_D  |          | Q-decoder1_0 |                |               | SPI1DIA                 |           |       | CAP0      | UART2TXB          |
| PB3   | SD0DAT_D  |          | Q-decoder1_1 |                |               |                         | FM_TXB    | ADC6  | PWM2      | UART2RXB          |
| PB4   | SD0DAT_F  | LVD      | Q-decoder2_0 | SPI0_DAT2A(2)  | SFC_DAT2A(2)  |                         |           | ADC7  | CLKOUT1   | UART2TXC/UART2RXC |
| PB5   | SD0DAT_B  |          | Q-decoder2_1 |                |               | SPI2DIA                 |           |       | PWM3/CAP1 | UART0TXC/UART0RXC |
| PB6   | SD0CMD_BF | AMUX1L   | SDTAP_CLKD   |                |               | SPI2CLKA                | IIC_SCL_C | ADC8  | TMR3      | UART1TXA          |
| PB7   | SD0CLK_BF | AMUX1R   | SDTAP_DATD   |                |               | SPI2DOA                 | IIC_SDA_C | ADC9  | PWM5      | UART1RXA          |
| PC1   | PA_EN     |          |              | SPI0_CSB       | SFC_CSB       | SPI2DIB                 |           |       | TMR0      | UART1TXB          |
| PC2   | LNA_EN    |          |              | SPI0_DIB(1)    | SFC_DIB(1)    | ALNK_MCLK_B             |           | ADC10 | CAP5      | UART1RXB          |
| PC3   | SD0DAT_A  |          |              | SPI0_DAT2B(2)  | SFC_DAT2B(2)  | SPI1DIB                 |           |       | CAP2      | UART0TXD/UART0RXD |
| PC4   | SD0CMD_A  |          | SDTAP_CLKA   | SPI0_DAT3AB(2) | SFC_DAT3AB(2) | SPI1CLKB                | IIC_SCL_B | ADC11 | PWM1      | UART2TXD          |
| PC5   | SD0CLK_AE |          | SDTAP_DATA   |                |               | SPI1DOB                 | IIC_SDA_B | ADC12 | TMR1      | UART2RXD          |
| PD0   |           |          |              | SPI0_CLKAB     | SFC_CLKAB     |                         |           |       |           |                   |
| PD1   |           |          |              | SPI0_DOAB(0)   | SFC_DOAB(0)   |                         |           |       |           |                   |
| PD2   |           |          |              | SPI0_DIA(1)    | SFC_DIA(1)    |                         |           |       |           |                   |
| PD3   |           |          |              | SPI0_CSA       | SFC_CSA       |                         |           |       |           |                   |
| PD4   |           |          |              |                |               |                         |           |       |           |                   |
| USBDP |           |          | SDTAP_CLKB   | ISP_CLK        | mode_det0     | SPI2_CLKB               | IIC_SCL_A | ADC13 |           | UART1TXD          |
| USBDM | SD0DAT_E  |          | SDTAP_DATB   | ISP_DI         | mode_det1     | SPI2_DOB                | IIC_SDA_A | ADC14 |           | UART1RXD          |

Note:
- Most chips have an internal SPI flash attached to the Port D as follows:
  - PD0 = SCK
  - PD1 = MOSI
  - PD2 = MISO
  - PD3 = CS
  - PD4 = Power (yes! it's on a GPIO)

## Per function

### UART

| UART0 |  A  |  B  |  C  |  D  |
|-------|-----|-----|-----|-----|
| TX    | PA5 | PB0 | PB5 | PC3 |
| RX    | PA6 | PB1 | PB5 | PC3 |

| UART1 |  A  |  B  |  C  |  D    |
|-------|-----|-----|-----|-------|
| TX    | PB6 | PC1 | PA0 | USBDP |
| RX    | PB7 | PC2 | PA1 | USBDM |
| CTS   | PA3 | PA3 | PA3 | PA3   |
| RTS   | PA4 | PA4 | PA4 | PA4   |

| UART2 |  A  |  B  |  C  |  D  |
|-------|-----|-----|-----|-----|
| TX    | PA3 | PB2 | PB4 | PC4 |
| RX    | PA4 | PB3 | PB4 | PC5 |

### IIC

| IIC |  A    |  B  |  C  |  D  |
|-----|-------|-----|-----|-----|
| SCL | USBDP | PC4 | PB6 | PA5 |
| SDA | USBDM | PC5 | PB7 | PA6 |

### SPI

| SPI0    |  A  |  B  |
|---------|-----|-----|
| CS      | PD3 | PC1 |
| CLK     | PD0 | PD0 |
| DO(0)   | PD1 | PD1 |
| DI(1)   | PD2 | PC2 |
| DAT2(2) | PB4 | PC3 |
| DAT3(3) | PC4 | PC4 |

| SPI1 |  A  |  B  |
|------|-----|-----|
| CLK  | PB0 | PC4 |
| DO   | PB1 | PC5 |
| DI   | PB2 | PC3 |

| SPI2 |  A  |  B    |
|------|-----|-------|
| CLK  | PB6 | USBDP |
| DO   | PB7 | USBDM |
| DI   | PB5 | PC1   |

### SFC

Again, maps on the same pins as SPI0 and on the second map there are still some signals that reside on Port D... yikes!

| SFC     |  A  |  B  |
|---------|-----|-----|
| CS      | PD3 | PC1 |
| CLK     | PD0 | PD0 |
| DO(0)   | PD1 | PD1 |
| DI(1)   | PD2 | PC2 |
| DAT2(2) | PB4 | PC3 |
| DAT3(3) | PC4 | PC4 |

### SD

They stripped down the data lines...

| SD0 |  A  |  B  |  C  |  D  |  E    |  F  | G | H |
|-----|-----|-----|-----|-----|-------|-----|---|---|
| CLK | PC5 | PB7 | PA2 | PB0 | PC5   | PB7 |   |   |
| CMD | PC4 | PB6 | PA4 | PB2 | PA4   | PB6 |   |   |
| DAT | PC3 | PB5 | PA3 | PB3 | USBDM | PB4 |   |   |

### SDTAP

| SDTAP |  A  |  B    |  C  |  D  |
|-------|-----|-------|-----|-----|
| CLK   | PC4 | USBDP | PB0 | PB6 |
| DAT   | PC5 | USBDM | PB1 | PB7 |

### ALNK

| ALNK |  A  |  B  |
|------|-----|-----|
| MCLK | PA2 | PC2 |
| SCLK | PA3 | PA5 |
| LRCK | PA4 | PA6 |
| DAT0 | PA0 | PA0 |
| DAT1 | PA1 | PA2 |
| DAT2 | PA5 | PA3 |
| DAT3 | PA6 | PA4 |
