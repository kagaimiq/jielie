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

## IOMAP registers

### IOMAP_CON0

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 31:28 |      |                |         |                        |
| 27    | R/W  | TMR5_CAP_IOS   | b0      | Timer5 capture input (0: PC2, 1: Input Channel 2) |
| 26    | R/W  | TMR4_CAP_IOS   | b0      | Timer4 capture input (0: PA6, 1: Input Channel 2) |
| 25    | R/W  | TMR3_CAP_IOS   | b0      | Timer3 capture input (0: PA2, 1: Input Channel 2) |
| 24    | R/W  | TMR2_CAP_IOS   | b0      | Timer2 capture input (0: PC3, 1: Input Channel 2) |
| 23    | R/W  | TMR1_CAP_IOS   | b0      | Timer1 capture input (0: PB5, 1: Input Channel 2) |
| 22    | R/W  | TMR0_CAP_IOS   | b0      | Timer0 capture input (0: PB2, 1: Input Channel 2) |
| 21    | R/W  | TMR5_CIN_IOS   | b0      | Timer5 ext clock input (0: PB0, 1: *pll_12m*) |
| 20    | R/W  | TMR4_CIN_IOS   | b0      | Timer4 ext clock input (0: PA4, 1: Input Channel 4) |
| 19    | R/W  | TMR3_CIN_IOS   | b0      | Timer3 ext clock input (0: PB6, 1: *pll_12m*) |
| 18    | R/W  | TMR2_CIN_IOS   | b0      | Timer2 ext clock input (0: PB1, 1: Input Channel 4) |
| 17    | R/W  | TMR1_CIN_IOS   | b0      | Timer1 ext clock input (0: PC5, 1: *pll_24m*) |
| 16    | R/W  | TMR0_CIN_IOS   | b0      | Timer0 ext clock input (0: PC1, 1: Input Channel 4) |
| 15    |      |                |         |                        |
| 14    | R/W  | SPDIF_IN_D_IOS | b0      | S/PDIF input D selection (0: Input Channel 9, 1: PB1) |
| 13    | R/W  | SPDIF_IN_C_IOS | b0      | S/PDIF input C selection (0: Input Channel 8, 1: PB0) |
| 12    | R/W  | SPDIF_IN_B_IOS | b0      | S/PDIF input B selection (0: Input Channel 10, 1: PA6) |
| 11    | R/W  | SPDIF_IN_A_IOS | b0      | S/PDIF input A selection (0: Input Channel 11, 1: PA5) |
| 10:8  | R/W  | SD0_IOS        | b000    | SD0 I/O map select     |
| 7:5   | R/W  | IRFLT_OS       | b000    | IRFLT output desination (2: timer0 cap, 3: timer1 cap ... 6: timer4 cap, 7: timer5 cap) |
| 4:3   | R/W  | UT0_IOS        | b00     | UART0 I/O map select   |
| 2     | R/W  | SPI0_IOS       | b0      | SPI0 I/O map select    |
| 1     | R/W  | SD0_DT_EN      | b1      | SD0 CMD/DAT lines enable |
| 0     | R/W  | SD0_CK_EN      | b1      | SD0 CLK line enable    |

### IOMAP_CON1

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 31:24 |      |                |         |                        |
| 23    | R/W  | ALNK0_IOS      | b0      | ALNK0 I/O map select   |
| 22:21 | R/W  | SDTAP_IOS      | b00     | SDTAP I/O map select   |
| 20    | R/W  | PLNK_SCKOE     | b0      | PLNK SCK output enable |
| 19:18 | R/W  | IIC_IOS        | b00     | IIC I/O map select     |
| 17    |      |                |         |                        |
| 16    | R/W  | SPI2_IOS       | b0      | SPI2 I/O map select    |
| 15:14 | R/W  | UT2_IOS        | b00     | UART2 I/O map select   |
| 13    | R/W  | RDEC0_SIN1_IOS | b0      | RDEC0 SIN1 input select (0: Input Channel 7, 1: IO mux) |
| 12    | R/W  | RDEC0_SIN0_IOS | b0      | RDEC0 SIN0 input select (0: Input Channel 6, 1: IO mux) |
| 11:8  | R/W  | OUTPUT_CH0_SEL | b0000   | Output Channel 0 select (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: TMR1_PWM_OUT, 4: RTC_OSCL, 5: BTOSC_CLK, 6: PLL_12M, 7: UT2_TX, 12: TMR4_PWM_OUT, 13: TMR5_PWM_OUT, 14: WLC_INT_FREQ, 15: TMR3_PWM_OUT) |
| 7     | R/W  | UT1_CTS_IOS    | b0      | UART1 CTS I/O select (0: Input Channel 5, 1: IO mux) |
| 6     | R/W  | CAP_ES         | b0      | Invert the CAP_MUX (Input Ch2) input level |
| 5     | R/W  | SFC_IOS        | b0      | SFC I/O map select     |
| 4     | R/W  | SPI1_IOS       | b0      | SPI1 I/O map select    |
| 3:2   | R/W  | UT1_IOS        | b00     | UART1 I/O map select   |
| 1     | R/W  | SPI0_DIDO_MIX  | b0      | SPI0 DI/DO mix control (0: receives only on DI, 1: receives both on DI and DO) |
| 0     |      |                |         |                        |

### IOMAP_CON2

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:30 |      |                 |         |                        |
| 29:24 | R/W  | INPUT_CHANNEL_3 | h00     | Input Channel 3 (UART RX mux) selection (0-15: PA0-15, 16-31: PB0-15, 32-47: PC0-15, 48-55: PD0-7, 59: TMR0_PWM_OUT, 60: TMR1_PWM_OUT, 61: USBDP, 62: USBDM) |
| 23:22 |      |                 |         |                        |
| 21:16 | R/W  | INPUT_CHANNEL_2 | h00     | Input Channel 2 (CAP mux) selection (see above) |
| 15    | R/W  | RDEC2_SIN1_IOS  | b0      | RDEC2 SIN1 input select (0: Input Channel 7, 1: IO mux) |
| 14    | R/W  | RDEC2_SIN0_IOS  | b0      | RDEC2 SIN0 input select (0: Input Channel 6, 1: IO mux) |
| 13:8  | R/W  | INPUT_CHANNEL_1 | h00     | Input Channel 1 (IRFLT mux) selection (see above) |
| 7     | R/W  | RDEC1_SIN1_IOS  | b0      | RDEC1 SIN1 input select (0: Input Channel 7, 1: IO mux) |
| 6     | R/W  | RDEC1_SIN0_IOS  | b0      | RDEC1 SIN0 input select (0: Input Channel 6, 1: IO mux) |
| 5:0   | R/W  | INPUT_CHANNEL_0 | h00     | Input Channel 0 (WKUP mux) selection (see above) |


### IOMAP_CON3

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:28 |      |                 |         |                        |
| 27:24 | R/W  | OUTPUT_CH2_SEL  | b0000   | Output Channel 2 select (0: U1_RTS, 1: UT1_TX, 2: WLC_INT_ACTIVE, 3: TMR1_PWM_OUT, 4: PLNK_SCLK, 5: BTOSC_CLK, 6: PLL_24M, 7: UT2_TX, 12: TMR4_PWM_OUT, 13: TMR5_PWM_OUT, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 23:20 | R/W  | OUTPUT_CH1_SEL  | b0000   | Output Channel 1 select (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: WLC_INT_STATUS, 4: RTC_OSCL, 5: BTOSC_CLK, 6: SPDIF_DO, 7: UT2_TX, 12: TMR4_PWM_OUT, 13: TMR5_PWM_OUT, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 19:16 |      |                 |         |                        |
| 15    | R/W  | PLNK_D1_IOS     | b1      | PLNK D1 input select (0: IO mux, 1: Input Channel 9) |
| 14    |      |                 |         |                        |
| 13    | R/W  | WLC_EXT_IOS     | b0      | WLC_EXT_ACTIVE input select (0: PA6, 1: Input Channel 10) |
| 12    |      |                 |         |                        |
| 11    | R/W  | UT2_IOEN        | b1      | UART2 I/O enable       |
| 10:8  | R/W  | UT2_MXS         | b000    | UART2 input select (0-3: IO mux, 4: Input Channel 0, 5: Input Channel 1, 6: Input Channel 2, 7: Input Channel 3) |
| 7     | R/W  | UT1_IOEN        | b1      | UART1 I/O enable       |
| 6:4   | R/W  | UT1_MXS         | b000    | UART1 input select (0-3: IO mux, 4: Input Channel 0, 5: Input Channel 1, 6: Input Channel 2, 7: Input Channel 3) |
| 3     | R/W  | UT0_IOEN        | b1      | UART0 I/O enable       |
| 2:0   | R/W  | UT0_MXS         | b000    | UART0 input select (0-3: IO mux, 4: Input Channel 0, 5: Input Channel 1, 6: Input Channel 2, 7: Input Channel 3) |

### IOMAP_CON4

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:30 |      |                 |         |                        |
| 29:24 | R/W  | INPUT_CHANNEL_7 | h00     | Input Channel 7 (RDEC DI1) selection (see above) |
| 23:22 |      |                 |         |                        |
| 21:16 | R/W  | INPUT_CHANNEL_6 | h00     | Input Channel 6 (RDEC DI0) selection (see above) |
| 15:14 |      |                 |         |                        |
| 13:8  | R/W  | INPUT_CHANNEL_5 | h00     | Input Channel 5 (UART1 CTS) selection (see above) |
| 7:6   |      |                 |         |                        |
| 5:0   | R/W  | INPUT_CHANNEL_4 | h00     | Input Channel 4 (Timer clock) selection (see above) |

### IOMAP_CON5

| Bits  | Type | Name             | Default | Description            |
|-------|------|------------------|---------|------------------------|
| 31:30 |      |                  |         |                        |
| 29:24 | R/W  | INPUT_CHANNEL_11 | h00     | Input Channel 11 (S/PDIF input A) selection (see above) |
| 23:22 |      |                  |         |                        |
| 21:16 | R/W  | INPUT_CHANNEL_10 | h00     | Input Channel 10 (WLC_EXT_ACTIVE_P) selection (see above) |
| 15:14 |      |                  |         |                        |
| 13:8  | R/W  | INPUT_CHANNEL_9  | h00     | Input Channel 9 (PLNK D1) selection (see above) |
| 7:6   |      |                  |         |                        |
| 5:0   | R/W  | INPUT_CHANNEL_8  | h00     | Input Channel 8 (PLNK D0) selection (see above) |
