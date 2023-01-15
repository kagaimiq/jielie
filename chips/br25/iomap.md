# IO map of BR25

| Pin   | func       | func         | func        | func      | func  | func    | func       | func       | func       | func         | func        |
|-------|------------|--------------|-------------|-----------|-------|---------|------------|------------|------------|--------------|-------------|
| PA0   | SD_PG      |              |             |           | ADC0  | CLKOUT0 | UART1_TX.C |            |            | ALNK_DAT0.AB |             |
| PA1   |            |              |             |           | ADC1  | PWM4    | UART1_RX.C |            | MIC        | ALNK_DAT1.B  | ALNK_MCLK.A |
| PA2   | SD0_CLK.C  |              |             |           |       | CAP3    |            |            | MIC_BIAS   |              | ALNK_SCLK.A |
| PA3   | SD0_DAT0.C |              | PLNK_SCLK   |           | ADC2  | PWM5    | UART2_TX.A | UART1_CTS  | AMUX0L     | ALNK_DAT2.B  | ALNK_LRCK.A |
| PA4   | SD0_CMD.CE |              | PLNK_DAT1   |           | ADC3  | TMR4    | UART2_RX.A | UART1_RTS  | AMUX0R     | ALNK_DAT3.B  | ALNK_SCLK.B |
| PA5   |            |              |             | IIC_SCL.D |       | PWM0    | UART0_TX.A |            | SPDIF_IN.A | ALNK_DAT2.A  | ALNK_LRCK.B |
| PA6   |            |              |             | IIC_SDA.D | ADC4  | CAP4    | UART0_RX.A |            | SPDIF_IN.B | ALNK_DAT3.A  |             |
| PB0   | SD0_CLK.D  |              | SPI1_CLK.A  |           |       | TMR5    | UART0_TX.B |            | SPDIF_IN.C |              |             |
| PB1   |            |              | SPI1_DO.A   |           | ADC5  | TMR2    | UART0_RX.B | LP Reset   | SPDIF_IN.D |              | *fm_tx*     |
| PB2   | SD0_CMD.D  |              | SPI1_DI.A   |           |       | CAP0    | UART2_TX.B |            |            |              |             |
| PB3   | SD0_DAT0.D |              |             |           | ADC6  | PWM2    | UART2_RX.B |            |            |              |             |
| PB4   | SD0_DAT0.F | SPI0_DAT2.A  |             |           | ADC7  | CLKOUT1 | UART2_TX.C | UART2_RX.C |            |              |             |
| PB5   |            |              | SPI2_DI.A   |           | PWM3  | CAP1    | UART0_TX.C | UART0_RX.C |            |              |             |
| PB6   | SD0_CMD.F  |              | SPI2_CLK.A  | IIC_SCL.C | ADC8  | TMR3    | UART1_TX.A |            | AMUX1L     |              |             |
| PB7   | SD0_CLK.BF |              | SPI2_DO.A   | IIC_SDA.C | ADC9  | PWM5    | UART1_RX.A |            | AMUX1R     |              |             |
| PC2   |            | SPI0_DI.B    |             |           | ADC10 | CAP5    | UART1_RX.B |            |            |              | ALNK_MCLK.B |
| PC3   | SD0_DAT0.A | SPI0_DAT2.B  | SPI1_DI.B   |           |       | CAP2    | UART0_TX.D | UART0_RX.D |            |              |             |
| PC4   | SD0_CMD.A  | SPI0_DAT3.AB | SPI1_CLK.B  | IIC_SCL.B | ADC11 | PWM1    | UART2_TX.D |            |            |              |             |
| PC5   | SD0_CLK.AE |              | SPI1_DO.B   | IIC_SDA.B | ADC12 | TMR1    | UART2_RX.D |            |            |              |             |
| PD0   |            | *SPI0_CLK.A* | *SFC_CLK.A* |           |       |         |            |            |            |              |             |
| PD1   |            | *SPI0_DO.A*  | *SFC_DO.A*  |           |       |         |            |            |            |              |             |
| PD2   |            | *SPI0_DI.A*  | *SFC_DI.A*  |           |       |         |            |            |            |              |             |
| PD3   |            | *SPI0_CS.A*  | *SFC_CS.A*  |           |       |         |            |            |            |              |             |
| PD4   |            |              |             |           |       |         |            |            |            |              |             |
| USBDP |            |              | SPI2_CLK.B  | IIC_SCL.A | ADC13 |         | UART1_TX.D |            |            |              |             |
| USBDM |            |              | SPI2_DO.B   | IIC_SDA.A | ADC14 |         | UART1_RX.D |            |            |              |             |

Note:
- Functions that are *italic* is these which were not clearly mentioned in the docs, etc...
- Most chips have an internal SPI flash attached to the Port D as follows:
  - PD0 = SCK
  - PD1 = MOSI
  - PD2 = MISO
  - PD3 = CS
  - PD4 = Power?
