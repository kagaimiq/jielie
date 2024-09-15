# CD02 I/O function map

**Scraped from some "port.bmp" image in the AC109N code dump under the "Page" directory, not checked with the AC109N docs yet..**

| Pin | func   | func    | func    | func        | func         | func    |
|-----|--------|---------|---------|-------------|--------------|---------|
| P00 | ADC0   | SPICLKB | SDCMDB  | ISD_2W_CLK1 | ISP_CLK_IN   | IIC_CLK |
| P01 | ADC1   | SPIDOB  | SDDATB  | ISD_2W_DAT1 | ISP_DATA_IN  | IIC_DAT |
| P02 | ADC2   | CAP0    | Wakeup  |             | ISP_DATA_OUT | DAC_L   |
| P03 | ADC3   | Timer0  |         | PWM1        |              | DAC_R   |
| P04 | ADC4   | CAP1    |         |             |              | DAC_CLK |
| P05 | ADC5   | Timer1  | Wakeup  | PWM2        | CLK_OUT      |         |
| P06 | ADC6   | UARTTX  |         |             |              |         |
| P07 | ADC7   | UARTRX  | Wakeup  |             |              |         |
| P10 | EMID0  |         |         |             |              |         |
| P11 | EMID1  |         |         |             |              |         |
| P12 | EMID2  |         |         |             |              |         |
| P13 | EMID3  | Timer2  |         |             |              |         |
| P14 | EMID4  |         |         |             |              |         |
| P15 | EMID5  | SPIDIA  |         |             |              |         |
| P16 | EMID6  | SPICLKA |         |             |              |         |
| P17 | EMID7  | SPIDOA  |         |             |              |         |
| P20 | SDCLKA | ADC8    |         |             |              |         |
| P21 | SDCMDA | ADC9    |         |             |              |         |
| P22 | SDDATA | ADC10   | Timer3  |             |              |         |
| P23 | MIC    | CAP2    |         |             |              |         |
| P24 | AMUX0L | UARTTX  | FM_IN   | ISD_2W_CLK0 |              |         |
| P25 | AMUX0R | UARTRX  |         | ISD_2W_DAT0 |              |         |
| P26 | AMUX1L | IIC_CLK |         |             |              |         |
| P27 | AMUX1R | IIC_DAT |         |             |              |         |
| P30 |        |         | SDCLKB  | PWM0        |              |         |
| P31 |        |         |         |             |              |         |
| P32 | LVD    | UARTTX  | IIC_CLK |             |              |         |
| P33 | EMIWR  | UARTRX  | IIC_DAT |             |              |         |
| P34 |        |         |         | PWM3        |              |         |
| P35 | ADC11  |         | SDCLKC  |             |              |         |
| P36 | USBDP  | UARTTX  | IIC_CLK |             |              |         |
| P37 | USBDM  | UARTRX  | IIC_DAT |             |              |         |
| P40 |        |         |         | ISD_DAT0    |              |         |
| P41 |        |         |         | ISD_DAT1    |              |         |
| P42 |        |         |         | ISD_DAT2    |              |         |
| P43 |        |         |         | ISD_DAT3    |              |         |
| P44 |        | SPIDIB  |         | ISD_CLK     |              |         |
| P45 |        |         |         | ISD_CMD     |              |         |
| P46 | Vpp    | CAP3    | Wakeup  |             |              |         |

Leftover ADC inputs:
 - ADC12: AMUX left channel
 - ADC13: AMUX right channel
 - ADC14: LDOIN (divided by something, I presume?)
 - ADC15: bandgap reference

## IO map registers

### IO_MC0

| Bits | Description        |
|------|--------------------|
| 7:6  | UART I/O mapping, TX/RX: 0 = P06/P07, 1 = P24/P25, 2 = P32/P33, 3 = P36/P37 |
| 5:4  | IIC I/O mapping, SCL/SDA: 0 = P00/P01, 1 = P26/P27, 2 = P32/P33, 3 = P36/P37 |
| 3    | SD I/O enable      |
| 2    | SD CMD/DAT mapping: 0 = P21/P22, 1 = P00/P01 |
| 1:0  | SD CLK mapping: 0 = P20, 1 = P30, 2 = P35, 3 = n/a? |

### IO_MC1

| Bits | Description       |
|------|-------------------|
| 7    | PWM4 wa           |
| 6    | ISD2W IO mapping, CLK/DAT: 0 = P00/P01, 1 = P24/P25  |
| 5    | SPI I/O enable    |
| 4    | SPI I/O mapping, CLK/DO/DI: 0 = P16/P17/P15, 1 = P00/P01/P44 |
| 3:2  | IRFLT source      |
| 1:0  | IRFLT destination |
