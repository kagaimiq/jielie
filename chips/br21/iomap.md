# BR21 I/O function map

| Pin      | func       | func       | func       | func         | func          | func       | func  | func     | func  | func       | func        | func       | func    | func   | func       | func      |
|----------|------------|------------|------------|--------------|---------------|------------|-------|----------|-------|------------|-------------|------------|---------|--------|------------|-----------|
| PA0      |            | PLNK_DAT0  |            |              |               |            |       | PWM_CH0H |       | UART0_RX.B |             | SEG0       |         | MIC    |            |           |
| PA1      |            | PLNK_SCLK  |            |              |               | Qdecoder0  |       |          | PWM0  | UART1_TX.C |             | SEG1       | Touch8  |        |            | Wakeup 13 |
| PA2      |            | PLNK_DAT1  |            |              | CLKOUT1       | Qdecoder1  |       | TMR0_CK  | CAP3  | UART1_RX.C |             | SEG2       | Touch9  |        |            |           |
| PA3      |            |            |            |              |               |            | ADC0  | PWM_CH0L |       | UART2_TX.A |             | SEG3       | Touch10 | AMUX1L |            | Wakeup 8  |
| PA4      |            |            |            |              |               |            | ADC1  |          | PWM1  | UART2_RX.A |             | SEG4       | Touch11 | AMUX1R | *dac_clk*  |           |
| PA5      | SD0_DAT0.A |            |            |              |               | IIC_SCL.D  | ADC2  |          |       | UART0_TX.A | UART1_CTS   | SEG5       | Touch12 | SPIDIF | *dac_datl* | Wakeup 9  |
| PA6      | SD0_CMD.A  |            |            |              |               | IIC_SDA.D  | ADC3  |          | CAP0  | UART0_RX.A | UART1_RTS   | SEG6       | Touch13 |        | *dac_datr* |           |
| PA7      | SD0_CLK.A  |            |            |              | PAP_D0        |            |       |          | TMR0  | UART0_TX.D | ALNK_MCLK.A | SEG7       | Touch14 |        |            |           |
| PA8      | SD0_DAT3.A |            |            |              | PAP_D1        |            |       |          |       | UART0_RX.D | ALNK_DAT3.A | SEG8       | Touch15 |        |            | Wakeup 2  |
| PA9      | SD0_DAT2.A |            |            |              | PAP_D2        |            |       |          |       | UART2_TX.B | ALNK_SCLK.A | SEG9       |         |        |            |           |
| PA10     | SD0_DAT1.A |            |            |              | PAP_D3        |            | ADC5  |          |       | UART2_RX.B | ALNK_LRCK.A | SEG10      |         |        |            | Wakeup 3  |
| PA11     |            |            | SPI2_DI.B  |              |               |            |       |          | TMR1  |            | ALNK_DAT0.A | SEG11      | Touch7  |        |            |           |
| PA12     |            |            |            |              | LNA_EN        |            |       |          | CAP2  |            | ALNK_DAT1.A | SEG12      |         |        |            | Wakeup 4  |
| PA13     |            |            |            |              | PA_EN         |            |       |          |       |            | ALNK_DAT2.A |            |         |        |            |           |
| PB0      | SD1_DAT0.B | SD0_DAT3.B | SPI2_CLK.A |              | CLKOUT0       |            | ADC6  | PWM_CH2L |       | UART1_TX.A | ALNK_SCLK.B |            | Touch0  |        |            | Wakeup 10 |
| PB1      | SD1_CMD.B  | SD0_DAT2.B | SPI2_DO.A  |              |               |            | ADC7  |          | TMR2  | UART1_RX.A | ALNK_LRCK.B |            | Touch1  |        | *adc_clk*  |           |
| PB2      | SD1_CLK.B  | SD0_DAT1.B | SPI2_DI.A  | SPI0_CLK.B   | *sfc_clk.b*   |            |       |          |       | UART2_TX.C | ALNK_DAT0.B |            | Touch2  |        | *adc_dat1* | Wakeup 11 |
| PB3      | SD1_DAT1.B | SD0_DAT0.B | SPI1_DI.A  | SPI0_DAT3.AB | *sfc_dat3.ab* |            |       |          | PWM2  | UART2_RX.C | ALNK_DAT1.B |            | Touch3  | AMUX2R | *adc_dat2* |           |
| PB4      | SD1_DAT2.B | SD0_CMD.B  | SPI1_CLK.A | SPI0_DAT2.AB | *sfc_dat2.ab* |            | ADC8  |          | PWM3  |            | ALNK_DAT2.B |            | Touch4  | AMUX0L |            | Wakeup 12 |
| PB5      | SD1_DAT3.B | SD0_CLK.B  | SPI1_DO.A  |              |               |            | ADC9  | PWM_CH2H |       | UART0_TX.B | ALNK_DAT3.B |            | Touch5  | AMUX0R |            |           |
| PB6      |            |            |            | SPI0_DI.B    | *sfc_di.b*    |            |       |          |       |            | ALNK_MCLK.B |            | Touch6  | AMUX2L |            |           |
| PC0      | SD1_DAT3.A |            |            |              | PAP_D4        |            |       |          |       | UART1_TX.B |             | SEG16/COM5 |         |        |            |           |
| PC1      | SD1_DAT2.A |            |            |              | PAP_D5        | IIC_SCL.C  |       | PWM_CH1H |       | UART1_RX.B |             | SEG17/COM4 |         |        |            |           |
| PC2      | SD1_DAT1.A |            |            |              | PAP_D6        | IIC_SDA.C  |       |          | CAP1  | UART0_TX.C |             | SEG18/COM3 |         |        |            |           |
| PC3      | SD1_DAT0.A |            | SPI1_DI.B  |              | PAP_D7        |            | ADC10 | PWM_CH1L | TMR3  | UART0_RX.C |             | SEG19/COM2 |         |        |            |           |
| PC4      | SD1_CMD.A  |            | SPI1_CLK.B |              | PAP_RD        | IIC_SCL.B  | ADC4  |          |       | UART2_TX.D |             | SEG20/COM1 |         |        |            |           |
| PC5      | SD1_CLK.A  |            | SPI1_DO.B  |              | PAP_WR        | IIC_SDA.B  |       |          | FPIN0 | UART2_RX.D |             | SEG21/COM0 |         |        |            |           |
| PD0      |            |            |            | SPI0_CLK.A   | *sfc_clk.a*   |            |       |          |       |            |             |            |         |        |            |           |
| PD1      |            |            |            | SPI0_DO.A    | *sfc_do.a*    |            |       |          |       |            |             |            |         |        |            |           |
| PD2      |            |            | SPI0_DO.B  | SPI0_DI.A    | *sfc_di.a*    | *sfc_do.b* |       |          |       |            |             |            |         |        |            |           |
| PD3      |            |            |            | SPI0_CS.AB   | *sfc_cs.ab*   |            |       |          |       |            |             |            |         |        |            |           |
| PR0      | LP Reset   | OSCO_32K   |            |              |               |            |       |          |       |            |             |            |         |        |            |           |
| PR1      | LP Reset   |            |            |              |               |            | ADC12 |          |       |            |             |            |         |        |            |           |
| PR2      | LP Reset   |            |            |              |               |            | ADC12 |          |       |            |             |            |         |        |            |           |
| PR3      | LP Reset   |            |            |              |               |            |       |          |       |            |             |            |         |        |            |           |
| RTC_OSCI |            | OSCI_32K   |            |              |               |            |       |          |       |            |             |            |         |        |            |           |
| USBDP    |            |            | SPI2_CLK.B |              |               | IIC_SCL.A  |       |          |       | UART1_TX.D |             |            |         |        |            |           |
| USBDM    |            |            | SPI2_DO.B  |              |               | IIC_SDA.A  | ADC11 |          |       | UART1_RX.D |             |            |         |        |            |           |

Note:
- Functions that are *italic* is these which were not clearly mentioned in the docs, etc...
- Most chips have an internal SPI flash attached to the Port D as follows:
  - PD0 = SCK
  - PD1 = MOSI
  - PD2 = MISO
  - PD3 = CS
