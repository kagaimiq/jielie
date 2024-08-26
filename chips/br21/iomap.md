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
| PB4      | SD1_DAT2.B | SD0_CMD.B  | SPI1_CLK.A | SPI0_DAT2.AB | *sfc_dat2.ab* |            | ADC8  |          | PWM3  | UART0_RX.B? | ALNK_DAT2.B |            | Touch4  | AMUX0L |            | Wakeup 12 |
| PB5      | SD1_DAT3.B | SD0_CLK.B  | SPI1_DO.A  |              |               |            | ADC9  | PWM_CH2H |       | UART0_TX.B? | ALNK_DAT3.B |            | Touch5  | AMUX0R |            |           |
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

Notes:
- Functions that are *italic* is these which were not clearly mentioned in the docs, etc...
- Most chips have an internal SPI flash that is connected to the chip as follows:
  - PD0 = SCK
  - PD1 = MOSI (D0)
  - PD2 = MISO (D1)
  - PD3 = CS
- Leftover info:
  - Default pulldown: USBDP, USBDM
  - Default pullup: PD3, PR2, PR3

## IOMAP registers

### IOMAP_CON0 / IOMC0

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 15    | R/W  | SD0IOS          | b0      | SD0 I/O map select     |
| 14    | R/W  | PAPDEN          | b0      | PAP data I/O enable    |
| 13    | R/W  | PAPREN          | b0      | PAP read signal enable |
| 12    | R/W  | PAPWEN          | b0      | PAP write signal enable |
| 11    | R/W  | ALNKIOS         | b0      | ALNK I/O map select    |
| 10:8  | R/W  | IRFLTOS         | b000    | IRFLT output select (4: Timer0 capture, 5: Timer1 capture, 6: Timer2 capture, 7: Timer3 capture) |
| 7:6   | R/W  | UT0IOS          | b00     | UART0 I/O map select   |
| 5     | R/W  | SPI0IOS         | b0      | SPI0 I/O map select    |
| 4     | R/W  | SD1IOS          | b0      | SD1 I/O map select     |
| 3     | R/W  | SD1DTEN         | b0      | SD1 CMD/DAT enable     |
| 2     | R/W  | SD1CKEN         | b0      | SD1 CLK enable         |
| 1     | R/W  | SD0DTEN         | b0      | SD0 CMD/DAT enable     |
| 0     | R/W  | SD0CKEN         | b0      | SD0 CLK enable         |

### IOMAP_CON1 / IOMC1

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31    | R/W  | T3_CAP          | b0      | Timer3 capture input (0: PA2, 1: CAP_MUX_IN) |
| 30    | R/W  | T2_CAP          | b0      | Timer2 capture input (0: PA12, 1: CAP_MUX_IN) |
| 29    | R/W  | T1_CAP          | b0      | Timer1 capture input (0: PC2, 1: CAP_MUX_IN) |
| 28    | R/W  | T0_CAP          | b0      | Timer0 capture input (0: PA6, 1: CAP_MUX_IN) |
| 27    | R/W  | T3_CIN          | b0      | Timer3 ext clock input (0: PC3, 1: CLK_MUX_IN) |
| 26    | R/W  | T2_CIN          | b0      | Timer2 ext clock input (0: PB1, 1: CLK_MUX_IN) |
| 25    | R/W  | T1_CIN          | b0      | Timer1 ext clock input (0: PA11, 1: CLK_MUX_IN) |
| 24    | R/W  | T0_CIN          | b0      | Timer0 ext clock input (0: PA7, 1: CLK_MUX_IN) |
| 23:21 |      |                 |         |                        |
| 20    | R/W  | PLNK_SCKOE      | b0      | PLNK SCK output enable |
| 19:18 | R/W  | IICIOS          | b00     | IIC I/O map select     |
| 17    |      |                 |         |                        |
| 16    | R/W  | SPI2IOS         | b0      | SPI2 I/O map select    |
| 15:14 | R/W  | UT2IOS          | b00     | UART2 I/O map select   |
| 13:12 |      |                 |         |                        |
| 11:8  | R/W  | OUT_CH0S        | b0000   | Output Channel 0 select (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: TMR1_PWM_OUT, 4: RTC_OSCL, 5: BTOSC_CLK, 6: PLL_24M, 7: UT2_TX, 8: CH0_PWMH, 9: CH0_PWML, 10: CH1_PWMH, 11: CH1_PWML, 12: CH2_PWMH, 13: CH2_PWML, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 7     |      |                 |         |                        |
| 6     | R/W  | CAPEDS          | b0      | Invert the CAP_MUX input level |
| 5     | R/W  | SFCIOS          | b0      | SFC I/O map select     |
| 4     | R/W  | SPI1IOS         | b0      | SPI1 I/O map select    |
| 3:2   | R/W  | UT1IOS          | b00     | UART1 I/O map select   |
| 1     | R/W  | SPI0_DIDO_MIX   | b0      | SPI0 DI/DO mix control (0: receive on DI, 1: receive on both DI and DO) |
| 0     |      |                 |         |                        |


### IOMAP_CON2 / IOMC2

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:30 |      |                 |         |                        |
| 29:24 | R/W  | UART_RX_MUX     | h00     | UART RX input mux selection (0-15: PA0-15, 16-31: PB0-15, 32-47: PC0-15, 48-55: PD0-7, 59: TMR0_PWM_OUT, 60: TMR1_PWM_OUT, 61: USBDP, 62: USBDM) |
| 23:22 |      |                 |         |                        |
| 21:16 | R/W  | CAP_MUX         | h00     | Timer capture input mux selection (see above) |
| 15:14 |      |                 |         |                        |
| 13:8  | R/W  | IRFLT_MUX       | h00     | IRFLT input mux selection (see above) |
| 7:6   |      |                 |         |                        |
| 5:0   | R/W  | WKUP_MUX        | h00     | Wakeup input mux selection (see above) |


### IOMAP_CON3 / IOMC3

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:28 | R/W  | OUTPUT_CH3_SEL  | b0000   | Output channel 3 selection (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: TMR1_PWM_OUT, 4: RTC_OSCH, 5: BTOSC_CLK, 6: PLL_24M, 7: UT2_TX, 8: CH0_PWMH, 9: CH0_PWML, 10: CH1_PWMH, 11: CH1_PWML, 12: CH2_PWMH, 13: CH2_PWML, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 27:24 | R/W  | OUTPUT_CH2_SEL  | b1000   | Output channel 2 selection (see above) |
| 23:20 | R/W  | OUTPUT_CH1_SEL  | b0000   | Output channel 1 selection (see above) |
| 19    | R/W  |                 | b1      | |
| 18:13 | R/W  | TMR_CLK_MUX     | h00     | Timer clock input mux selection (see above of IOMAP_CON2) |
| 12    | R/W  | MC_FPIN         | b0      | MCPWM FPIN input selection (0: PD1, 1: CAP_MUX) |
| 11    | R/W  | UT2IOEN         | b1      | UART2 I/O enable       |
| 10:8  | R/W  | UT2MXS          | b000    | UART2 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |
| 7     | R/W  | UT1IOEN         | b1      | UART1 I/O enable       |
| 6:4   | R/W  | UT1MXS          | b000    | UART1 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |
| 3     | R/W  | UT0IOEN         | b1      | UART0 I/O enable       |
| 2:0   | R/W  | UT0MXS          | b000    | UART0 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |

