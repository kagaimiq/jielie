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
| PD4   |            |              |                |               |               |               |           |       |         |           |                   |         |
| PD5   | SEG19      |              | SPI0_DAT3AB(3) | SFC_DAT3AB(3) |               |               |           |       |         |           |                   |         |
| PR0   |            | OSCI_32K     |                |               |               |               |           |       |         |           |                   |         |
| PR1   |            | OSCO_32K     |                |               |               |               |           |       |         |           |                   |         |
| USBDP |            |              | SDTAP_CLKB     | ISP_CLK       | SPI2CLKB      | mode_det0     | IIC_SCL_A | ADC12 |         |           | UART1TXD          |         |
| USBDM |            |              | SDTAP_DATB     | ISP_DI        | SPI2DOB       | mode_det1     | IIC_SDA_A |       |         |           | UART1RXD          |         |

Notes:
- Most chips have an internal SPI flash that is connected to the chip as follows:
  * PD0 = CLK
  * PD1 = MOSI (D0)
  * PD2 = MISO (D1)
  * PD3 = CS
  * PD4 = Power supply

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

## IOMAP registers

### IOMAP_CON0

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 31:24 |      |                |         |                        |
| 23    | R/W  | SPDIF_IN_D_IOS | b0      | S/PDIF input D selection (0: Input Channel 9, 1: PB1) |
| 22    | R/W  | SPDIF_IN_C_IOS | b0      | S/PDIF input C selection (0: Input Channel 8, 1: PB0) |
| 21    | R/W  | SPDIF_IN_B_IOS | b0      | S/PDIF input B selection (0: Input Channel 10, 1: PA10) |
| 20    | R/W  | SPDIF_IN_A_IOS | b0      | S/PDIF input A selection (0: Input Channel 11, 1: PA9) |
| 19:18 |      |                |         |                        |
| 17:16 | R/W  | SPI0_IOS       | b0      | SPI0 I/O map select    |
| 15    | R/W  | SD0_IOS        | b0      | SD0 I/O map select     |
| 14    | R/W  | PAP_DEN        | b0      | PAP data lines enable  |
| 13    | R/W  | PAP_REN        | b0      | PAP read signal enable |
| 12    | R/W  | PAP_WEN        | b0      | PAP write signal enable |
| 11    | R/W  | ALNK0_IOS      | b0      | ALNK0 I/O map select   |
| 10:8  | R/W  | IRFLT_OS       | b000    | IRFLT output desination (4: timer0 cap, 5: timer1 cap, 6: timer2 cap, 7: timer3 cap) |
| 7:6   | R/W  | UT0_IOS        | b00     | UART0 I/O map select   |
| 5     |      |                |         |                        |
| 4     | R/W  | SD1_IOS        | b0      | SD1 I/O map select     |
| 3     | R/W  | SD1_DT_EN      | b1      | SD1 CMD/DAT lines enable |
| 2     | R/W  | SD1_CK_EN      | b1      | SD1 CLK line enable    |
| 1     | R/W  | SD0_DT_EN      | b1      | SD0 CMD/DAT lines enable |
| 0     | R/W  | SD0_CK_EN      | b1      | SD0 CLK line enable    |

### IOMAP_CON1

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 31    | R/W  | TMR3_CAP_IOS   | b0      | Timer3 capture input (0: PA2, 1: Input Channel 2) |
| 30    | R/W  | TMR2_CAP_IOS   | b0      | Timer2 capture input (0: PA15, 1: Input Channel 2) |
| 29    | R/W  | TMR1_CAP_IOS   | b0      | Timer1 capture input (0: PB5, 1: Input Channel 2) |
| 28    | R/W  | TMR0_CAP_IOS   | b0      | Timer0 capture input (0: PA9, 1: Input Channel 2) |
| 27    | R/W  | TMR3_CIN_IOS   | b0      | Timer3 ext clock input (0: PB6, 1: *pll_12m*) |
| 26    | R/W  | TMR2_CIN_IOS   | b0      | Timer2 ext clock input (0: PB1, 1: Input Channel 4) |
| 25    | R/W  | TMR1_CIN_IOS   | b0      | Timer1 ext clock input (0: PA10, 1: *pll_24m*) |
| 24    | R/W  | TMR0_CIN_IOS   | b0      | Timer0 ext clock input (0: PA7, 1: Input Channel 4) |
| 23    |      |                |         |                        |
| 22:21 | R/W  | SDTAP_IOS      | b00     | SDTAP I/O map select   |
| 20    | R/W  | PLNK_SCKOE     | b0      | PLNK SCK output enable |
| 19:18 | R/W  | IIC_IOS        | b00     | IIC I/O map select     |
| 17    |      |                |         |                        |
| 16    | R/W  | SPI2_IOS       | b0      | SPI2 I/O map select    |
| 15:14 | R/W  | UT2_IOS        | b00     | UART2 I/O map select   |
| 13    | R/W  | RDEC0_SIN1_IOS | b0      | RDEC0 SIN1 input select (0: Input Channel 7, 1: PA3) |
| 12    | R/W  | RDEC0_SIN0_IOS | b0      | RDEC0 SIN0 input select (0: Input Channel 6, 1: PA2) |
| 11:8  | R/W  | OUTPUT_CH0_SEL | b0000   | Output Channel 0 select (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: TMR1_PWM_OUT, 4: RTC_OSCL, 5: BTOSC_CLK, 6: PLL_12M, 7: UT2_TX, 8: CH0_PWMH, 9: CH0_PWML, 10: CH1_PWMH, 11: CH1_PWML, 12: CH2_PWMH, 13: CH2_PWML, 14: WLC_INT_FREQ, 15: TMR3_PWM_OUT) |
| 7     | R/W  | UT1_CTS_IOS    | b0      | UART1 CTS I/O select (0: Input Channel 5, 1: PA5) |
| 6     | R/W  | CAP_ES         | b0      | Invert the CAP_MUX (Input Ch2) input level |
| 5     | R/W  | SFC_IOS        | b0      | SFC I/O map select     |
| 4     | R/W  | SPI1_IOS       | b0      | SPI1 I/O map select    |
| 3:2   | R/W  | UT1_IOS        | b00     | UART1 I/O map select   |
| 1     | R/W  | SPI0_DIDO_MIX  | b0      | SPI0 DI/DO mix control (0: receives only on DI, 1: receives both on DI and DO) |
| 0     | R/W  | PSR_IOS        | b0      | PSRAM I/O map select   |

### IOMAP_CON2

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:30 |      |                 |         |                        |
| 29:24 | R/W  | INPUT_CHANNEL_3 | h00     | Input Channel 3 (UART RX mux) selection (0-15: PA0-15, 16-31: PB0-15, 32-47: PC0-15, 48-55: PD0-7, 59: TMR0_PWM_OUT, 60: TMR1_PWM_OUT, 61: USBDP, 62: USBDM) |
| 23:22 |      |                 |         |                        |
| 21:16 | R/W  | INPUT_CHANNEL_2 | h00     | Input Channel 2 (CAP mux) selection (see above) |
| 15    | R/W  | RDEC2_SIN1_IOS  | b0      | RDEC2 SIN1 input select (0: Input Channel 7, 1: PB6) |
| 14    | R/W  | RDEC2_SIN0_IOS  | b0      | RDEC2 SIN0 input select (0: Input Channel 6, 1: PB4) |
| 13:8  | R/W  | INPUT_CHANNEL_1 | h00     | Input Channel 1 (IRFLT mux) selection (see above) |
| 7     | R/W  | RDEC1_SIN1_IOS  | b0      | RDEC1 SIN1 input select (0: Input Channel 7, 1: PB3) |
| 6     | R/W  | RDEC1_SIN0_IOS  | b0      | RDEC1 SIN0 input select (0: Input Channel 6, 1: PB2) |
| 5:0   | R/W  | INPUT_CHANNEL_0 | h00     | Input Channel 0 (WKUP mux) selection (see above) |


### IOMAP_CON3

| Bits  | Type | Name            | Default | Description            |
|-------|------|-----------------|---------|------------------------|
| 31:28 |      |                 |         |                        |
| 27:24 | R/W  | OUTPUT_CH2_SEL  | b0000   | Output Channel 2 select (0: U1_RTS, 1: UT1_TX, 2: WLC_INT_ACTIVE, 3: TMR1_PWM_OUT, 4: PLNK_SCLK, 5: BTOSC_CLK, 6: PLL_24M, 7: UT2_TX, 8: CH0_PWMH, 9: CH0_PWML, 10: CH1_PWMH, 11: CH1_PWML, 12: CH2_PWMH, 13: CH2_PWML, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 23:20 | R/W  | OUTPUT_CH1_SEL  | b0000   | Output Channel 1 select (0: UT0_TX, 1: UT1_TX, 2: TMR0_PWM_OUT, 3: WLC_INT_STATUS, 4: RTC_OSCL, 5: BTOSC_CLK, 6: SPDIF_DO, 7: UT2_TX, 8: CH0_PWMH, 9: CH0_PWML, 10: CH1_PWMH, 11: CH1_PWML, 12: CH2_PWMH, 13: CH2_PWML, 14: TMR2_PWM_OUT, 15: TMR3_PWM_OUT) |
| 19:16 |      |                 |         |                        |
| 15    | R/W  | PLNK_D1_IOS     | b1      | PLNK D1 input select (0: PA3, 1: Input Channel 9) |
| 14    |      |                 |         |                        |
| 13    | R/W  | WLC_EXT_IOS     | b0      | WLC_EXT_ACTIVE input select (0: PA6, 1: Input Channel 10) |
| 12    | R/W  | MC_FPIN_IOS     | b0      | MCPWM FPIN input select (0: PA14, 1: Input Channel 2) |
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
