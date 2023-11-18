# DV15 I/O function map

**Currently scaped from the AC5213B datasheet**

| Pin   | func        | func           | func           | func      | func       | func      |
|-------|-------------|----------------|----------------|-----------|------------|-----------|
| PA0   |             |                | SPI0_CSA       |           |            |           |
| PA1   |             | IIC_SDA_C      | SPI0_DIA(1)    | SD0_CMDA  |            |           |
| PA2   | ADC0        | IIC_SCL_C      | SPI0_DAT2A(2)  | SD0_CLKA  |            |           |
| PA3   |             |                | SPI0_DOA(0)    | SD0_DAT2A |            |           |
| PA4   |             |                | SPI0_CLKA      | SD0_DAT0A |            |           |
| PA6   | UART3_TXA   | LINE_0L        | IIC_SCL_B      | PWMCH0_A  |            |           |
| PA7   | PWMCH1_A    | Wakeup8        | AVOUT          | UART3_RXA |            |           |
| PA8   | UART3_TXB   | LINE_0R        | IIC_SDA_B      | Wakeup9   | PWMCH2_A   |           |
| PA9   | UART3_RXB   | MIC            | PWM0           |           |            |           |
| PD0   | SPI1_CLKB   | ADC12          | UART2_TXC      | CAP2      |            |           |
| PD3   |             | SENSOR1_CLK_A  | SENSOR0_CLK_A  |           |            |           |
| PD4   | UART0_TXD   | SENSOR1_HSYN_A | SENSOR0_HSYN_A |           |            |           |
| PD5   | UART0_RXD   | SENSOR1_VSYN_A | SENSOR0_VSYN_A |           |            |           |
| PD6   |             | SENSOR1_D9_A   | SENSOR0_D9_A   | SD1_DAT2C |            |           |
| PD7   |             | SENSOR1_D8_A   | SENSOR0_D8_A   | SD1_DAT3C |            |           |
| PD8   |             | SENSOR1_D7_A   | SENSOR0_D7_A   | SD1_CMDC  |            |           |
| PD9   |             | SENSOR1_D6_A   | SENSOR0_D6_A   | SD1_CLKC  |            |           |
| PD10  |             | SENSOR1_D5_A   | SENSOR0_D5_A   | SD1_DAT0C |            |           |
| PD11  |             | SENSOR1_D4_A   | SENSOR0_D4_A   | SD1_DAT1C |            |           |
| PD12  |             | SENSOR1_D3_A   | SENSOR0_D3_A   |           |            |           |
| PD13  |             | SENSOR1_D2_A   | SENSOR0_D2_A   |           |            |           |
| PF0   | UART2_TXB   |                |                |           |            |           |
| PF1   | UART2_RXB   | ALNK_MCKB      |                |           |            |           |
| PF2   | SD2_DAT2A   | UART1_TXD      | PWMCH0_B       | SD1_DAT2A | ALNK_SCLKB |           |
| PF3   | SD2_DAT3A   | UART1_RXD      | PWMCH1_B       | SD1_DAT3A | ALNK_LRCKB |           |
| PF4   | SD2_CMDA    | SPI1_DID(1)    | PWMCH2_B       | SD1_CMDA  | ALNK_D0B   |           |
| PF5   | SD2_CLKA    | SPI1_CLKD      | PWMCH3_B       | SD1_CLKA  | ALNK_D1B   |           |
| PF6   | SD2_DAT0A   | SPI1_DOD(0)    | PWMCH4_B       | SD1_DAT0A | ALNK_D2B   |           |
| PF7   | SD2_DAT1A   |                | PWMCH5_B       | SD1_DAT1A | ALNK_D3B   |           |
| PG8   | LCD_DAT8    | EMI_D8         | SD0_DAT2D      |           |            |           |
| PG9   | LCD_DAT9    | EMI_D9         | SD0_DAT3B      |           |            |           |
| PG10  | LCD_DAT10   | EMI_D10        | SD0_CMDD       |           |            |           |
| PG11  | LCD_DAT11   | EMI_D11        | SD0_CLKD       |           |            |           |
| PG12  | LCD_DAT12   | EMI_D12        | SD0_DAT0D      |           |            |           |
| PG13  | LCD_DAT13   | EMI_D13        | SD0_DAT1D      |           |            |           |
| PG14  | LCD_DAT14   | EMI_D14        | UART3_TXC      |           |            |           |
| PG15  | LCD_DAT15   | EMI_D15        | UART3_RXC      |           |            |           |
| PH0   | LCD_DAT16   | UART2_TXD      | ADC4           | IIC_SCL_D | CAP0       | Wakeup10  |
| PH1   | LCD_DAT17   | UART2_RXD      | ADC5           | IIC_SDA_D | TMR2       | Wakeup11  |
| PH2   | LCD_DCLK    | UART1_TXB      |                |           |            |           |
| PH3   | LCD_SYNC0   | EMI_WR         | SPI1_CLKA      | UART2_RXA |            |           |
| PH4   | LCD_SYNC1   | EMI_RD         | SPI1_DOA(0)    | UART2_TXA |            |           |
| PH5   | LCD_SYNC2   | UART1_RXB      | SPI1_DIA(1)    | CAP3      | ADC6       |           |
| PH12  |             | UART0_TXC      | CLKOUT0        | TMR3      | Wakeup16   | ADC10     |
| PH13  | PWM2        | CLKOUT1        | SPI0_DAT3A(3)  | Wakeup17  | ADC11      | SD0_DAT1A |
| PR0   |             |                |                |           |            |           |
| PR1   | ADC14       |                |                |           |            |           |
| PR2   | ADC14       |                |                |           |            |           |
| PR3   | RTC_OSC_OUT |                |                |           |            |           |
| XOSCI | RTC_OSC_IN  |                |                |           |            |           |

## By function

### UART

| UART0 |  A  |  B  |  C   |  D  |
|-------|-----|-----|------|-----|
| TX    |     |     | PH12 | PD4 |
| RX    |     |     |      | PD5 |

| UART1 |  A  |  B  |  C  |  D  |
|-------|-----|-----|-----|-----|
| TX    |     | PH2 |     | PF2 |
| RX    |     | PH5 |     | PF3 |

| UART2 |  A  |  B  |  C  |  D  |
|-------|-----|-----|-----|-----|
| TX    | PH3 | PF0 | PD0 | PH0 |
| RX    | PH4 | PF1 |     | PH1 |

| UART3 |  A  |  B  |  C   |  D  |
|-------|-----|-----|------|-----|
| TX    | PA6 | PA8 | PG14 |     |
| RX    | PA7 | PA9 | PG15 |     |

### IIC

| IIC |  A  |  B  |  C  |  D  |
|-----|-----|-----|-----|-----|
| SDA |     | PA6 | PA1 | PH0 |
| SCL |     | PA7 | PA2 | PH1 |

### SPI

| SPI0    |  A   |  B  |  C  |  D  |
|---------|------|-----|-----|-----|
| CS      | PA0  |     |     |     |
| CLK     | PA4  |     |     |     |
| DO(0)   | PA3  |     |     |     |
| DI(1)   | PA1  |     |     |     |
| DAT2(2) | PA2  |     |     |     |
| DAT3(3) | PH13 |     |     |     |

| SPI1 |  A  |  B  |  C  |  D  |
|------|-----|-----|-----|-----|
| CLK  | PH3 | PD0 |     | PF5 |
| DO   | PH4 |     |     | PF6 |
| DI   | PH5 |     |     | PF4 |

### SD

| SD0   |  A   |  B  |  C  |  D   |
|-------|------|-----|-----|------|
| CLK   | PA2  |     |     | PG11 |
| CMD   | PA1  |     |     | PG10 |
| DAT0  | PA4  |     |     | PG12 |
| DAT1  | PH13 |     |     | PG13 |
| DAT2  | PA3  |     |     | PG8  |
| DAT3  |      |     |     | PG9  |

| SD1   |  A  |  B  |  C   |  D   |
|-------|-----|-----|------|------|
| CLK   | PF5 |     | PD9  |      |
| CMD   | PF4 |     | PD8  |      |
| DAT0  | PF6 |     | PD10 |      |
| DAT1  | PF7 |     | PD11 |      |
| DAT2  | PF2 |     | PD6  |      |
| DAT3  | PF3 |     | PD7  |      |
