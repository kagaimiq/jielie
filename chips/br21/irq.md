# IRQ map of BR21

- Vector table is at **0x00000**

| #  | Vector  | SDK name  | Source                    |
|----|---------|-----------|---------------------------|
|  0 | 0x00000 | EXCEPTION | CPU exception             |
|  1 | 0x00004 | TICK_TMR  | Tick timer                |
|  2 | 0x00008 | TMR0      | Timer 0                   |
|  3 | 0x0000C | TMR1      | Timer 1                   |
|  4 | 0x00010 | TMR2      | Timer 2                   |
|  5 | 0x00014 | TMR3      | Timer 3                   |
|  6 | 0x00018 | FUSB_SOF  | USB (SOF)                 |
|  7 | 0x0001C | FUSB_CTRL | USB (control)             |
|  8 | 0x00020 | RRTC      | IRTC                      |
|  9 | 0x00024 | ALNK      | ALNK                      |
| 10 | 0x00028 | AUDIO     | AUDIO                     |
| 11 | 0x0002C | PORT      | .                         |
| 12 | 0x00030 | SPI0      | SPI0                      |
| 13 | 0x00034 | SPI1      | SPI1                      |
| 14 | 0x00038 | SDC0      | SD0                       |
| 15 | 0x0003C | SDC1      | SD1                       |
| 16 | 0x00040 | UART0     | UART0                     |
| 17 | 0x00044 | UART1     | UART1                     |
| 18 | 0x00048 | UART2     | UART2                     |
| 19 | 0x0004C | PAP       | PAP                       |
| 20 | 0x00050 | IIC       | IIC                       |
| 21 | 0x00054 | SARADC    | SAR ADC                   |
| 22 | 0x00058 | PLNK      | PLNK                      |
| 23 | 0x0005C |           |                           |
| 24 | 0x00060 |           |                           |
| 25 | 0x00064 | BT_BREDR  | Bluetooth (BREDR)         |
| 26 | 0x00068 | BT_CLKN   | Bluetooth (clkn)          |
| 27 | 0x0006C | BT_BDG    | Bluetooth (bdg)           |
| 28 | 0x00070 | BT_LOFC   | Bluetooth (lofc)          |
| 29 | 0x00074 | SRC       | SRC                       |
| 30 | 0x00078 | FFT       | FFT                       |
| 31 | 0x0007C | EQ        | EQ                        |
| 32 | 0x00080 | PD_PND    |                           |
| 33 | 0x00084 | LVD       | LVD                       |
| 34 | 0x00088 | WATCHDOG  | Watchdog                  |
| 35 | 0x0008C | OSC_SAFE  |                           |
| 36 | 0x00090 | BT_BLE    | Bluetooth (BLE)           |
| 37 | 0x00094 |           |                           |
| 38 | 0x00098 | AES       | AES                       |
| 39 | 0x0009C |           |                           |
| 40 | 0x000A0 |           |                           |
| 41 | 0x000A4 |           |                           |
| 42 | 0x000A8 |           |                           |
| 43 | 0x000AC |           |                           |
| 44 | 0x000B0 | SPI2      | SPI2                      |
| 45 | 0x000B4 |           |                           |
| 46 | 0x000B8 |           |                           |
| 47 | 0x000BC |           |                           |
| 48 | 0x000C0 |           |                           |
| 49 | 0x000C4 |           |                           |
| 50 | 0x000C8 |           |                           |
| 51 | 0x000CC |           |                           |
| 52 | 0x000D0 |           |                           |
| 53 | 0x000D4 |           |                           |
| 54 | 0x000D8 |           |                           |
| 55 | 0x000DC |           |                           |
| 56 | 0x000E0 |           |                           |
| 57 | 0x000E4 |           |                           |
| 58 | 0x000E8 |           |                           |
| 59 | 0x000EC |           |                           |
| 60 | 0x000F0 |           |                           |
| 61 | 0x000F4 |           |                           |
| 62 | 0x000F8 |           |                           |
| 63 | 0x000FF |           |                           |

