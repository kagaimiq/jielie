# DV16 I/O function map

**Scraped from a AC5401 datasheet**

| Pin  | func           | func        | func          | func           | func          | func         | func       |
|------|----------------|-------------|---------------|----------------|---------------|--------------|------------|
| PA0  | SPI0_CSA       | SFC_CS      |               |                |               |              |            |
| PA1  | SD0_CMDA       | SFC_DI(1)   | SPI0_DIA(1)   | IIC_SDA1_B     |               |              |            |
| PA3  | SPI0_DOA(0)    | SFC_DO(0)   | SD0_DAT2A     |                |               |              |            |
| PA4  | SPI0_CLKA      | SFC_CLK     | SD0_DAT0A     |                |               |              |            |
| PA5  | SENSOR0_D0_B   | SD2_CMDA    | LCDS_HSYNC    |                |               |              |            |
| PA6  | SENSOR0_D1_B   | SD2_CLKA    | LCDS_VSYNC    |                |               |              |            |
| PA7  | SENSOR0_D2_B   | SD2_DAT0A   | LCDS_DCLK     |                |               |              |            |
| PA8  | SENSOR0_D3_B   | SD2_DAT1A   | LCDS_DAT16    |                |               |              |            |
| PA9  | SENSOR0_D4_B   | ALNK_D0B    | SD2_DAT2A     | LCDS_DAT17     |               |              |            |
| PA10 | SENSOR0_D5_B   | ALNK_D1B    | SD2_DAT3A     | LCDS_DAT18     |               |              |            |
| PA11 | SENSOR0_D6_B   | ALNK_D2B    | SD0_DAT3D     | LCDS_DAT19     |               |              |            |
| PA12 | SENSOR0_D7_B   | ALNK_D3B    | SD0_DAT2D     | LCDS_DAT20     |               |              |            |
| PA13 | SENSOR0_D8_B   | ALNK_CKB    | SD0_CMDD      | LCDS_DAT21     |               |              |            |
| PA14 | SENSOR0_D9_B   | ALNK_WSB    | SD0_CLKD      | LCDS_DAT22     |               |              |            |
| PA15 | SENSOR0_CLK_B  | ALNK_MCKB   | LCDS_DAT23    |                |               |              |            |
| PB0  | MII_RXCK       | IIC_SCL1_A  |               |                |               |              |            |
| PB1  | MII_RXDV       | IIC_SDA1_A  |               |                |               |              |            |
| PB3  | ADC2           | IIC_SDA0_C  | Wakeup8       | UART3_RXB      |               |              |            |
| PB4  | IIC_SCL0_C     | UART3_TXB   |               |                |               |              |            |
| PB5  | MII_TX3        | SPI2_CSB    | SD1_DAT2C     |                |               |              |            |
| PB6  | MII_TX0        | RMII_TX0    | SPI2_DIB(1)   | SD1_DAT3C      |               |              |            |
| PB7  | MII_TX1        | RMII_TX1    | SPI2_DAT2B(2) | SD1_CMDC       |               |              |            |
| PB8  | MII_TXEN       | RMII_TXEN   | SPI2_DOB(0)   | SD1_CLKC       |               |              |            |
| PB9  | MII_RXERR      | RMII_RXERR  | SPI2_CLKB     | SD1_DAT0C      |               |              |            |
| PB10 | MII_TXCK       | RMII_REFCLK | SPI2_DAT3B(3) | SD1_DAT1C      |               |              |            |
| PB11 | MII_CRS        | RMII_CRSDV  | TMR1          | SPI1_CLKD      |               |              |            |
| PB12 | MII_RX0        | RMII_RX0    | CAP3          | ADC3           | SPI1_DOD(0)   |              |            |
| PB13 | MII_RX1        | RMII_RX1    | PWM1          | SPI1_DID(1)    |               |              |            |
| PB14 | UART0_TXD      | MII_RX2     | OSCI2         | TMR0           | ADC4          |              |            |
| PB15 | UART0_RXD      | MII_RX3     | OSCO2         |                |               |              |            |
| PD12 | OSCI1          |             |               |                |               |              |            |
| PD13 | OSCO1          |             |               |                |               |              |            |
| PE0  | SENSOR0_HSYN_B | MII_TXERR_A | SD0_DAT0D     | UART3_TXA      |               |              |            |
| PE1  | SENSOR0_VSYN_B | MII_COL_A   | SD0_DAT1D     | UART3_RXA      | LCDSS_DEN     |              |            |
| PE2  | VPP            | CLKOUT0     | IIC_SCL1_C    |                |               |              |            |
| PE3  | LVD            | ADC5        | IIC_SDA1_C    |                |               |              |            |
| PE4  | IIC_SCL1_D     | SPI1_CLKA   | Wakeup10      | SENSOR1_HSYN_A |               |              |            |
| PE5  | IIC_SDA1_D     | SPI1_DOA(0) | Wakeup11      | SENSOR1_VSYN_A |               |              |            |
| PG0  | LCD_DAT0A      | EMI_D0A     | SD0_DAT3C     |                |               |              |            |
| PG1  | LCD_DAT1A      | EMI_D1A     | SD0_DAT2C     |                |               |              |            |
| PG2  | LCD_DAT2A      | EMI_D2A     | LCD_DENAB     | EMI_WRAB       | SD0_CMDC      |              |            |
| PG3  | LCD_DAT3A      | EMI_D3A     | LCD_DCLKAB    | SD0_CLKC       |               |              |            |
| PG4  | LCD_DAT4A      | EMI_D4A     | LCD_HSYNCAB   | EMI_RDAB       | SD0_DAT0C     |              |            |
| PG5  | LCD_DAT5A      | EMI_D5A     | LCD_VSYNCAB   | SD0_DAT1C      |               |              |            |
| PG6  | LCD_DAT6A      | EMI_D6A     | UART0_TXB     | IIC_SCL0_A     |               |              |            |
| PG7  | LCD_DAT7A      | EMI_D7A     | UART0_RXB     | IIC_SDA0_A     |               |              |            |
| PG8  | LCD_DAT8A      | EMI_D8A     | SD2_DAT2B     |                |               |              |            |
| PG9  | LCD_DAT9A      | EMI_D9A     | SD2_DAT3B     |                |               |              |            |
| PG10 | LCD_DAT10A     | EMI_D10A    | SD2_CMDA      |                |               |              |            |
| PG11 | LCD_DAT11A     | EMI_D11A    | SD2_CLKB      |                |               |              |            |
| PG12 | LCD_DAT12A     | EMI_D12A    | SD2_DAT0B     |                |               |              |            |
| PG13 | LCD_DAT13A     | EMI_D13A    | SD2_DAT1B     |                |               |              |            |
| PG14 | LCD_DAT14A     | EMI_D14A    |               |                |               |              |            |
| PG15 | LCD_DAT15A     | EMI_D15A    |               |                |               |              |            |
| PH0  | LCD_DAT16A     | UART2_TXD   | SPI1_DIA(1)   | CAP2           | SENSOR1_CLK_A | LCDS_DAT0    |            |
| PH1  | LCD_DAT17A     | UART2_RXD   | TMR2          | SENSOR1_D9_A   | LCDS_DAT1     |              |            |
| PH2  | LCD_DCLKAA     | UART1_TXB   | SENSOR1_D8_A  | LCDS_DAT2      |               |              |            |
| PH3  | LCD_DENAA      | EMI_WRAA    | SENSOR1_D7_A  | LCDS_DAT3      |               |              |            |
| PH4  | LCD_HSYNCAA    | EMI_RDAA    | SENSOR1_D6_A  | LCDS_DAT4      |               |              |            |
| PH5  | LCD_VSYNCAA    | UART1_RXB   | SD1_DAT1A     | SENSOR1_D5_A   | LCDS_DAT5     |              |            |
| PH6  | LCD_DAT18A     | MICL        | SENSOR1_D4_A  | LCDS_DAT6      |               |              |            |
| PH7  | LCD_DAT19A     | AMUX0L      | SD1_DAT2A     | Wakeup12       | SENSOR1_D3_A  | LCDS_DAT7    |            |
| PH8  | LCD_DAT20A     | AMUX0R      | SD1_DAT3A     | SENSOR1_D2_A   | LCDS_DAT8     |              |            |
| PH9  | LCD_DAT21A     | AMUX1L      | SD1_CMDA      | UART2_RXB      | SENSOR1_D1_A  | LCDS_DAT9    |            |
| PH10 | LCD_DAT22A     | AMUX1R      | SD1_CLKA      | Wakeup13       | UART2_TXB     | SENSOR1_D0_A | LCDS_DAT10 |
| PH11 | LCD_DAT23A     | MICR        | SD1_DAT0A     | LCDS_DAT11     |               |              |            |
| PH12 | UART0_TXC      | ADC9        | PWM2          | IIC_SCL0_B     | SPI1_CLKC     | LCDS_DAT12   |            |
| PH13 | UART0_RXC      | AVOUT       | TMR3          | SD0_DAT3A      | SPI1_DIC(1)   | LCDS_DAT13   |            |
| PH14 | UART1_TXC      | ADC10       | CLKOUT1       | IIC_SDA0_B     | Wakeup14      | SPI1_DOC(0)  | LCDS_DAT14 |
| PR0  | reset          |             |               |                |               |              |            |
| PR1  | reset          | ADC13       |               |                |               |              |            |
| PR2  | reset          | ADC12       |               |                |               |              |            |
| PR3  | reset          |             |               |                |               |              |            |
