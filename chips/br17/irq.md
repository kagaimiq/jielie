# IRQ map of BR17

- Vector table is at **0x1E000**

| #  | Vector  | SDK name  | Source                    |
|----|---------|-----------|---------------------------|
|  0 | 0x1E000 | EXCEPTION | CPU exception             |
|  1 | 0x1E004 |           | Tick timer                |
|  2 | 0x1E008 | TIME0     | Timer 0                   |
|  3 | 0x1E00C | TIME1     | Timer 1                   |
|  4 | 0x1E010 | TIME2     | Timer 2                   |
|  5 | 0x1E014 | TIME3     | Timer 3                   |
|  6 | 0x1E018 | USB_SOF   | USB (SOF)                 |
|  7 | 0x1E01C | USB_CTRL  | USB (control)             |
|  8 | 0x1E020 | RTC       | IRTC                      |
|  9 | 0x1E024 | ALINK     | ALNK                      |
| 10 | 0x1E028 | DAC       | AUDIO                     |
| 11 | 0x1E02C | PORT      | .                         |
| 12 | 0x1E030 | SPI0      | SPI0                      |
| 13 | 0x1E034 | SPI1      | SPI1                      |
| 14 | 0x1E038 | SD0       | SD0                       |
| 15 | 0x1E03C | SD1       | SD1                       |
| 16 | 0x1E040 | UART0     | UART0                     |
| 17 | 0x1E044 | UART1     | UART1                     |
| 18 | 0x1E048 | UART2     | UART2                     |
| 19 | 0x1E04C | PAP       | PAP                       |
| 20 | 0x1E050 | IIC       | IIC                       |
| 21 | 0x1E054 | SARADC    | SAR ADC                   |
| 22 | 0x1E058 | FM_HWFE   | FM (hwfe)                 |
| 23 | 0x1E05C | FM        | FM (main)                 |
| 24 | 0x1E060 | FM_LOFC   | FM (lofc)                 |
| 25 | 0x1E064 | BT_BREDR  | Bluetooth (BREDR)         |
| 26 | 0x1E068 | BT_CLKN   | Bluetooth (clkn)          |
| 27 | 0x1E06C | BT_BDG    | Bluetooth (bdg)           |
| 28 | 0x1E070 | BT_PCM    | Bluetooth (PCM)           |
| 29 | 0x1E074 | SRC       | SRC                       |
| 30 | 0x1E078 |           |                           |
| 31 | 0x1E07C | EQ        | EQ                        |
| 32 | 0x1E080 |           |                           |
| 33 | 0x1E084 |           |                           |
| 34 | 0x1E088 |           |                           |
| 35 | 0x1E08C |           |                           |
| 36 | 0x1E090 | BLE       | Bluetooth (BLE)           |
| 37 | 0x1E094 |           |                           |
| 38 | 0x1E098 |           |                           |
| 39 | 0x1E09C |           |                           |
| 40 | 0x1E0A0 |           |                           |
| 41 | 0x1E0A4 |           |                           |
| 42 | 0x1E0A8 |           |                           |
| 43 | 0x1E0AC | CTM       | CTMU                      |
| 44 | 0x1E0B0 |           |                           |
| 45 | 0x1E0B4 |           |                           |
| 46 | 0x1E0B8 |           |                           |
| 47 | 0x1E0BC |           |                           |
| 48 | 0x1E0C0 |           |                           |
| 49 | 0x1E0C4 |           |                           |
| 50 | 0x1E0C8 |           |                           |
| 51 | 0x1E0CC |           |                           |
| 52 | 0x1E0D0 |           |                           |
| 53 | 0x1E0D4 |           |                           |
| 54 | 0x1E0D8 |           |                           |
| 55 | 0x1E0DC |           |                           |
| 56 | 0x1E0E0 |           |                           |
| 57 | 0x1E0E4 |           |                           |
| 58 | 0x1E0E8 |           |                           |
| 59 | 0x1E0EC |           |                           |
| 60 | 0x1E0F0 |           |                           |
| 61 | 0x1E0F4 |           |                           |
| 62 | 0x1E0F8 | SOFT0     | SDK soft irq 0 (`swi 62`) |
| 63 | 0x1E0FC | SOFT      | SDK soft irq 1 (`swi 63`) |
