# IO map of BR17

| Pin   | func       | func        | func         | func      | func  | func    | func       | func       | func    | func        |
|-------|------------|-------------|--------------|-----------|-------|---------|------------|------------|---------|-------------|
| PA0   |            |             |              |           |       |         |            | SEG0       |         |             |
| PA1   |            |             |              |           |       | PWM0    | UART1_TX.C | SEG1       | Touch8  | AMUX0L      |
| PA2   |            |             |              |           |       | CAP3    | UART1_RX.C | SEG2       | Touch9  | AMUX0R      |
| PA3   |            |             |              |           | ADC0  |         | UART2_TX.A | SEG3       | Touch10 | AMUX1L      |
| PA4   |            |             |              |           | ADC1  |         | UART2_RX.A | SEG4       | Touch11 | AMUX1R      |
| PA5   |            |             |              | IIC_SCL.D | ADC2  |         | UART0_TX.A | SEG5       | Touch12 |             |
| PA6   |            |             |              | IIC_SDA.D | ADC3  |         | UART0_RX.A | SEG6       | Touch13 |             |
| PA7   |            |             | PAP_D0       |           |       | TMR0    |            | SEG7       | Touch14 |             |
| PA8   | SD0_DAT3.A |             | PAP_D1       |           |       |         |            | SEG8       | Touch15 |             |
| PA9   | SD0_DAT2.A |             | PAP_D2       |           | ADC4  |         | UART2_TX.B | SEG9       |         | ALNK_SCLK.A |
| PA10  | SD0_DAT1.A |             | PAP_D3       |           | ADC5  |         | UART2_RX.B | SEG10      |         | ALNK_LRCK.A |
| PA11  | SD0_DAT0.A |             |              |           |       |         |            | SEG11      |         | ALNK_DAT0.A |
| PA12  | SD0_CMD.A  |             |              |           |       |         |            | SEG12      |         | ALNK_DAT1.A |
| PA13  | SD0_CLK.A  |             |              |           |       |         |            | SEG13      |         | ALNK_DAT2.A |
| PA14  |            |             | PA_EN        | IIC_SCL.C |       | TMR1    | UART0_TX.D | SEG14      |         | ALNK_DAT3.A |
| PA15  |            |             | LNA_EN       | IIC_SDA.C |       | CAP2    | UART0_RX.D | SEG15      |         | ALNK_MCLK.A |
| PB0   | SD1_DAT0.B | SPI2_CLK.A  |              |           |       | CLKOUT0 | UART1_TX.A |            | Touch0  | ALNK_SCLK.A |
| PB1   | SD1_CMD.B  | SPI2_DO.A   |              |           |       | TMR2    | UART1_RX.A |            | Touch1  | ALNK_LRCK.B |
| PB2   | SD1_CLK.B  | SPI2_DI.A   |              |           |       |         |            |            | Touch2  | ALNK_DAT0.B |
| PB3   | SD1_DAT1.B | SPI0_DAT3.B | SFC_DAT3.B   |           |       | PWM2    |            |            | Touch3  | ALNK_DAT1.B |
| PB4   | SD1_DAT2.B | SPI0_DAT2.B | SFC_DAT2.B   |           |       | PWM3    |            |            | Touch4  | ALNK_DAT2.B |
| PB5   | SD1_DAT3.B | SPI0_DI.B   | SFC_DI.B     |           |       |         |            |            |         | ALNK_DAT3.B |
| PB6   |            | SPI0_CS.B   | SFC_CS.B     |           |       |         | UART0_TX.B |            |         | ALNK_MCLK.B |
| PB7   | SD0_DAT3.B | SPI0_DO.B   | SFC_DO.B     |           | ADC6  | TMR3    | UART0_RX.B |            |         |             |
| PB8   | SD0_DAT2.B | SPI0_CLK.B  | SFC_CLK.B    |           | ADC7  |         |            |            |         |             |
| PB9   | SD0_DAT1.B |             | NFC_CRR_TEST |           | ADC8  | CLKOUT1 | UART2_TX.C |            |         |             |
| PB10  | SD0_DAT0.B | SPI1_DI.A   | NFC_AMP_TEST |           | ADC9  |         | UART2_RX.C |            | Touch5  |             |
| PB11  | SD0_CMD.B  | SPI1_CLK.A  | NFC_TX       |           | ADC10 |         |            |            | Touch6  | AMUX2L      |
| PB12  | SD0_CLK.B  | SPI1_DO.A   | NFC_RX       |           | ADC11 |         |            |            | Touch7  | AMUX2R      |
| PB13  |            |             |              |           |       |         |            |            |         | MIC         |
| PC0   | SD1_DAT3.A | SPI2_CLK.B  | PAP_D4       |           |       |         | UART1_TX.B | SEG16/COM5 |         |             |
| PC1   | SD1_DAT2.A | SPI2_DO.B   | PAP_D5       |           |       |         | UART1_RX.B | SEG17/COM4 |         |             |
| PC2   | SD1_DAT1.A | SPI2_DI.B   | PAP_D6       |           |       | CAP1    | UART0_TX.C | SEG18/COM3 |         |             |
| PC3   | SD1_DAT0.A | SPI1_DI.B   | PAP_D7       |           |       |         | UART0_RX.C | SEG19/COM2 |         |             |
| PC4   | SD1_CMD.A  | SPI1_CLK.B  | PAP_RD       | IIC_SCL.B |       |         | UART2_TX.D | SEG20/COM1 |         |             |
| PC5   | SD1_CLK.A  | SPI1_DO.B   | PAP_WR       | IIC_SDA.B |       |         | UART2_RX.D | SEG21/COM0 |         |             |
| PD0   |            | SPI0_CLK.A  | SFC_CLK.A    |           |       |         |            |            |         |             |
| PD1   |            | SPI0_DO.A   | SFC_DO.A     |           |       |         |            |            |         |             |
| PD2   |            | SPI0_DI.A   | SFC_DI.A     |           |       |         |            |            |         |             |
| PD3   |            | SPI0_CS.A   | SFC_CS.A     |           |       |         |            |            |         |             |
| PR0   | LP Reset   | OSCO_32K    |              |           |       |         |            |            |         |             |
| PR1   | LP Reset   |             |              |           | ADC12 |         |            |            |         |             |
| PR2   | LP Reset   |             |              |           | ADC13 |         |            |            |         |             |
| PR3   | LP Reset   | OSCO_12     |              |           |       |         |            |            |         |             |
| OSCI  |            | OSCI_32K    |              |           |       |         |            |            |         |             |
| HOSCI |            | OSCI_12     |              |           |       |         |            |            |         |             |
| USBDP |            |             |              | IIC_SCL.A |       |         | UART1_TX.D |            |         |             |
| USBDM |            |             |              | IIC_SDA.A |       |         | UART1_RX.D |            |         |             |

Note:
- Functions that are *italic* is these which were not clearly mentioned in the docs, etc...
- Most chips have an internal SPI flash attached to the Port D as follows:
  - PD0 = SCK
  - PD1 = MOSI
  - PD2 = MISO
  - PD3 = CS

