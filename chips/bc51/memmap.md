# Memory map of BC51

| Address               | Size   | Usage                 |
|-----------------------|--------|-----------------------|
| 0x0000000 - 0x0017FFF | 96k    | RAM0                  |
| 0x0018000 - 0x001BFFF | 16k    | + icache data?        |
| 0x001C000 - 0x001C1FF | 512b   | + interrupt vectors   |
| 0x0020000 - 0x003FFFF | 128k   | alias 0x00000~0x1FFFF |
| 0x0040000 - 0x00427FF | 10k    | RAM1                  |
| 0x0048000 - 0x00497FF | 6k     | icache tag            |
| 0x0049800 - 0x00498FF | 256    | MMU tag0              |
| 0x0050000 - 0x00527FF | 10k    | MaskROM               |
| 0x0060000 - 0x006FFFF | 64k    | LSB peripherals       |
| 0x0070000 - 0x007FFFF | 64k    | HSB peripherals       |
| 0x0080000 - 0x009FFFF | 128k   | MMU mapping           |
| 0x00E0000 - 0x00EFFFF | 64k    | BT SFR                |
| 0x0100000 - 0x07FFFFF | 7M     | alias 0x00000~0xFFFFF |
| 0x1000000 - 0x1FFFFFF | 16M    | SFC mapping           |

- This is based off the BR17 memory mapping, and so some things might be incorrect here.
- The main bus has 25-bit wide addressing, i.e. it wraps each 32 MiB. (mask 0x1FFFFFF)

## Peripherals

### LSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x0060000 | SYSCFG - CHIP_ID      |
| 0x0060004 | SYSCFG - MODE         |
| 0x0060008 | SYSCFG - WKUP         |
| 0x0060018 | SYSCFG - IOMC         |
| 0x0060040 | SYSCFG - PWR          |
| 0x0060044 | SYSCFG - CLK          |
| 0x0060080 | SYSCFG - PLL          |
| 0x0060084 | SYSCFG - LDO          |
| 0x0060088 | SYSCFG - LVD          |
| 0x006008C | SYSCFG - WDT          |
| 0x0060090 | SYSCFG - OSA          |
| 0x0060094 | SYSCFG - EFUSE        |
| 0x0060098 | <del>SYSCFG - HTC</del>|
| 0x0060100 | PORTA                 |
| 0x0060120 | PORTB                 |
| 0x0060140 | PORTC                 |
| 0x0060160 | PORTD                 |
| 0x0060200 | TIMER0                |
| 0x0060210 | TIMER1                |
| 0x0060220 | TIMER2                |
| 0x0060230 | TIMER3                |
| 0x0060300 | UART0                 |
| 0x0060324 | UART1                 |
| 0x0060348 | UART2                 |
| 0x0060400 | SPI0                  |
| 0x0060414 | SPI1                  |
| 0x0060500 | PAP                   |
| 0x0060600 | SD0                   |
| 0x0060614 | SD1                   |
| 0x0060700 | IIC                   |
| 0x0060800 | LCD                   |
| 0x0060900 | LS_OTH - PWM4         |
| 0x0060904 | LS_OTH - IRTC         |
| 0x0060908 | LS_OTH - IRFLT        |
| 0x0060A00 | AUDIO                 |
| 0x0060B00 | ALNK                  |
| 0x0060C00 | <del>NFC</del>        |
| 0x0060D00 | USB                   |
| 0x0060E00 | CRC                   |
| 0x0060F00 | RAND64                |
| 0x0061000 | ADC                   |
| 0x0061100 | PLCNT                 |

### HSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x0070000 | CPU                   |
| 0x0070100 | DEBUG                 |
| 0x0070200 | SFC                   |
| 0x0070300 | ENC                   |
| 0x0070400 | HS_OTH - RFI          |
| 0x0070404 | <del>HS_OTH - PD</del>|
| 0x0070500 | AES                   |
| 0x0070600 | FFT                   |
| 0x0070700 | EQ                    |
| 0x0070800 | SRC                   |
