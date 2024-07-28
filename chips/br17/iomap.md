# BR17 I/O function map

| Pin   | func       | func        | func         | func      | func  | func    | func       | func       | func    | func        |
|-------|------------|-------------|--------------|-----------|-------|---------|------------|------------|---------|-------------|
| PA0   |            |             |              |           |       |         |            | SEG0       |         |             |
| PA1   |            |             |              |           |       | PWM0    | UART1_TX.C | SEG1       | Touch8  | AMUX0L      |
| PA2   |            |             |              |           |       | CAP3    | UART1_RX.C | SEG2       | Touch9  | AMUX0R      |
| PA3   | ISP_CLK    |             |              |           | ADC0  |         | UART2_TX.A | SEG3       | Touch10 | AMUX1L      |
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
| USBDP | ISP_DI     |             |              | IIC_SCL.A |       |         | UART1_TX.D |            |         |             |
| USBDM | ISP_DO     |             |              | IIC_SDA.A |       |         | UART1_RX.D |            |         |             |

Note:
- Functions that are *italic* is these which were not clearly mentioned in the docs, etc...
- Most chips have an internal SPI flash attached to the Port D as follows:
  - PD0 = SCK
  - PD1 = MOSI
  - PD2 = MISO
  - PD3 = CS
- Leftover info:
  - Default pulldown: PA3, USBDP, USBDM
  - Default pullup: PB4, PB6, PD3

## By function

### Timer

| Timer |  0  |  1   |  2   |  3  |
|-------|-----|------|------|-----|
| TMR   | PA7 | PA14 | PB1  | PB7 |
| CAP   |     | PC2  | PA15 | PA2 |
| PWM   | PA1 |      | PB3  | PB4 |

TMR is the timer's external clock input, CAP is the capture input and PWM is - guess what!

### UART

| UART0 |  A  |  B  |  C  |  D   |
|-------|-----|-----|-----|------|
| TX    | PA5 | PB6 | PC2 | PA14 |
| RX    | PA6 | PB7 | PC3 | PA15 |

| UART1 |  A  |  B  |  C  |   D   |
|-------|-----|-----|-----|-------|
| TX    | PB0 | PC0 | PA1 | USBDP |
| RX    | PB1 | PC1 | PA2 | USBDM |

| UART2 |  A  |  B   |  C   |  D  |
|-------|-----|------|------|-----|
| TX    | PA3 | PA9  | PB9  | PC4 |
| RX    | PA4 | PA10 | PB10 | PC5 |

### IIC

| IIC |   A   |  B  |  C   |  D  |
|-----|-------|-----|------|-----|
| SCL | USBDP | PC4 | PA14 | PA5 |
| SDA | USBDM | PC5 | PA15 | PA6 |

### SPI

| SPI0    |  A  |  B  |
|---------|-----|-----|
| CS      | PD3 | PB6 |
| CLK     | PD0 | PB8 |
| DO(0)   | PD1 | PB7 |
| DI(1)   | PD2 | PB5 |
| DAT2(2) |     | PB4 |
| DAT3(3) |     | PB3 |

| SPI1 |  A   |  B  |
|------|------|-----|
| CLK  | PB11 | PC4 |
| DO   | PB12 | PC5 |
| DI   | PB10 | PC3 |

| SPI2 |  A  |  B  |
|------|-----|-----|
| CLK  | PB0 | PC0 |
| DO   | PB1 | PC1 |
| DI   | PB2 | PC2 |

### SFC

The SFC basically maps into the same pins as the SPI0.

Unfortuneatly, later series does not expose all (or the least required) SFC function pins outside the Port D,
thus making impossible to hook an external SPI flash like the internal one is hooked to the chip. Is this on purpose?

| SFC     |  A  |  B  |
|---------|-----|-----|
| CS      | PD3 | PB6 |
| CLK     | PD0 | PB8 |
| DI(0)   | PD2 | PB5 |
| DO(1)   | PD1 | PB7 |
| DAT2(2) |     | PB4 |
| DAT3(3) |     | PB3 |

### SD

| SD0  |  A   |  B   |
|------|------|------|
| CLK  | PA13 | PB12 |
| CMD  | PA12 | PB11 |
| DAT0 | PA11 | PB10 |
| DAT1 | PA10 | PB9  |
| DAT2 | PA9  | PB8  |
| DAT3 | PA8  | PB7  |

| SD1  |  A  |  B  |
|------|-----|-----|
| CLK  | PC5 | PB2 |
| CMD  | PC4 | PB1 |
| DAT0 | PC3 | PB0 |
| DAT1 | PC2 | PB3 |
| DAT2 | PC1 | PB4 |
| DAT3 | PC0 | PB5 |

### ALNK

| ALNK |  A   |  B  |
|------|------|-----|
| MCLK | PA15 | PB6 |
| SCLK | PA9  | PB0 |
| LRCK | PA10 | PB1 |
| DAT0 | PA11 | PB2 |
| DAT1 | PA12 | PB3 |
| DAT2 | PA13 | PB4 |
| DAT3 | PA14 | PB5 |

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
| 31:22 |      |                 |         |                        |
| 21:20 | R/W  | WLUIOS          | b00     | WL UART I/O map select |
| 19:18 | R/W  | IICIOS          | b00     | IIC I/O map select     |
| 17    |      |                 |         |                        |
| 16    | R/W  | SPI2IOS         | b0      | SPI2 I/O map select    |
| 15:14 | R/W  | UT2IOS          | b00     | UART2 I/O map select   |
| 13:11 | R/W  | OUT_CH1S        | b000    | Output Channel 1 select (0: UT0_TX, 1: UT1_RX, 2: TMR2_PWM_OUT, 3: TMR3_PWM_OUT, 4: IRTCX32K, 5: OSC_CLK, 6: WLU_TX, 7: PWM4_OUT) |
| 10:8  | R/W  | OUT_CH0S        | b000    | Output Channel 0 select (0: UT0_TX, 1: UT1_RX, 2: TMR0_PWM_OUT, 3: TMR1_PWM_OUT, 4: RTC_OSCH, 5: BTOSC_CLK, 6: PLL_12M, 7: UT2_TX) |
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
| 29:24 | R/W  | UTS             | h00     | UART RX input mux (UART_RX_MUX) selection (0-15: PA0-15, 16-31: PB0-15, 32-47: PC0-15, 48-55: PD0-7, 62: USBDP, 63: USBDM) |
| 23:22 |      |                 |         |                        |
| 21:16 | R/W  | CAPS            | h00     | Timer capture input mux (CAP_MUX) selection (see above) |
| 15:14 |      |                 |         |                        |
| 13:8  | R/W  | IRFLTS          | h00     | IRFLT input mux (IRFLT_MUX) selection (see above) |
| 7:6   |      |                 |         |                        |
| 5:0   | R/W  | WKUPS           | h00     | Wakeup input mux (WKUP_MUX) selection (see above) |

### IOMAP_CON3 / IOMC3

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 15:12 |      |                 |         |                        |
| 11    | R/W  | UT2IOEN         | b1      | UART2 I/O enable       |
| 10:8  | R/W  | UT2MXS          | b000    | UART2 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |
| 7     | R/W  | UT1IOEN         | b1      | UART1 I/O enable       |
| 6:4   | R/W  | UT1MXS          | b000    | UART1 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |
| 3     | R/W  | UT0IOEN         | b1      | UART0 I/O enable       |
| 2:0   | R/W  | UT0MXS          | b000    | UART0 input mux select (0-3: IO mux, 4: WKUP_MUX, 5: IRFLT_MUX, 6: CAP_MUX, 7: UART_RX_MUX) |

