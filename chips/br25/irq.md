# IRQ map of BR25

- Vector table is at **0x31F00** (last 256 bytes of RAM1)

| #  | Vector  | SDK name  | Source                    |
|----|---------|-----------|---------------------------|
|  0 | 0x31F00 | EMUEXCPT  | Emulation (debug) vector  |
|  1 | 0x31F04 | EXCEPTION | CPU exception vector      |
|  2 | 0x31F08 | SYSCALL   | System call vector (triggered with the `syscall` instruction) |
|  3 | 0x31F0C | TICK_TMR  | Tick timer                |
|  4 | 0x31F10 | TIMER0    | Timer 0                   |
|  5 | 0x31F14 | TIMER1    | Timer 1                   |
|  6 | 0x31F18 | TIMER2    | Timer 2                   |
|  7 | 0x31F1C | TIMER3    | Timer 3                   |
|  8 | 0x31F20 | USB_SOF   | USB SOF interrupt         |
|  9 | 0x31F24 | USB_CTRL  | USB SIE interrupt         |
| 10 | 0x31F28 | RTC_WDT   | P33 RTC and Watchdog      |
| 11 | 0x31F2C | ALINK0    | ALNK0                     |
| 12 | 0x31F30 | AUDIO     | AUDIO                     |
| 13 | 0x31F34 | PORT      | GPIO interrupts of some sort? |
| 14 | 0x31F38 | SPI0      | SPI0                      |
| 15 | 0x31F3C | SPI1      | SPI1                      |
| 16 | 0x31F40 | SD0       | SD0                       |
| 17 | 0x31F44 | SD1       | SD1                       |
| 18 | 0x31F48 | UART0     | UART0                     |
| 19 | 0x31F4C | UART1     | UART1                     |
| 20 | 0x31F50 | UART2     | UART2                     |
| 21 | 0x31F54 | PAP       | PAP                       |
| 22 | 0x31F58 | IIC       | IIC                       |
| 23 | 0x31F5C | SARADC    | SAR ADC                   |
| 24 | 0x31F60 | PDM_LINK  | PLNK                      |
| 25 | 0x31F64 | RDEC0     | RDEC0                     |
| 26 | 0x31F68 | LRCT      |                           |
| 27 | 0x31F6C | BREDR     | Bluetooth (BREDR)         |
| 28 | 0x31F70 | BT_CLKN   | Bluetooth (clkn)          |
| 29 | 0x31F74 | BT_BDG    | Bluetooth (bdg)           |
| 30 | 0x31F78 | WL_LOFC   | Bluetooth (lofc)          |
| 31 | 0x31F7C | SRC       | SRC                       |
| 32 | 0x31F80 | FFT       | FFT                       |
| 33 | 0x31F84 | EQ        | EQ                        |
| 34 | 0x31F88 | LP_TIMER0 | P33 Timer 0               |
| 35 | 0x31F8C | LP_TIMER1 | P33 Timer 1               |
| 36 | 0x31F90 | ALINK1    | ALNK1                     |
| 37 | 0x31F94 | OSA       |                           |
| 38 | 0x31F98 | BLE_RX    | Bluetooth (BLE RX)        |
| 39 | 0x31F9C | BLE_EVENT | Bluetooth (BLE event)     |
| 40 | 0x31FA0 | AES       | AES                       |
| 41 | 0x31FA4 | MCTMRX    | MCTMRx                    |
| 42 | 0x31FA8 | CHX_PWM   | CHx PWM                   |
| 43 | 0x31FAC | FMRX      | FM RX                     |
| 44 | 0x31FB0 | SPI2      | SPI2                      |
| 45 | 0x31FB4 | SBC       | SBC                       |
| 46 | 0x31FB8 | GPC       | GPCNT                     |
| 47 | 0x31FBC | FMTX      | FM TX                     |
| 48 | 0x31FC0 | DCP       |                           |
| 49 | 0x31FC4 | RDEC1     | RDEC1                     |
| 50 | 0x31FC8 | RDEC2     | RDEC2                     |
| 51 | 0x31FCC | SPDIF     | SS                        |
| 52 | 0x31FD0 | PWM_LED   | PWM LED                   |
| 53 | 0x31FD4 | CTM       | CTMU                      |
| 54 | 0x31FD8 | TIMER4    | Timer 4                   |
| 55 | 0x31FDC | TIMER5    | Timer 5                   |
| 56 | 0x31FE0 |           |                           |
| 57 | 0x31FE4 |           |                           |
| 58 | 0x31FE8 |           |                           |
| 59 | 0x31FEC |           |                           |
| 60 | 0x31FF0 | SOFT0     | Software interrupt 0 (`swi 0`) |
| 61 | 0x31FF4 | SOFT1     | Software interrupt 1 (`swi 1`) |
| 62 | 0x31FF8 | SOFT2     | Software interrupt 2 (`swi 2`) |
| 63 | 0x31FFC | SOFT3     | Software interrupt 3 (`swi 3`) |
