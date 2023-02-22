# Memory map of BR25

| Address               | Size | Usage                 |
|-----------------------|------|-----------------------|
| 0x0010000 - 0x0031FFF | 136k | RAM0                  |
| 0x0032000 - 0x00325FF | 1.5k | + extra?              |
| 0x00FC000 - 0x00FDBFF | 7k   | icache tag            |
| 0x0100000 - 0x010FFFF | 64k  | Core peripherals      |
| 0x0110000 - 0x0117FFF | 32k  | MaskROM               |
| 0x01E0000 - 0x01EFFFF | 64k  | LSB peripherals       |
| 0x01F0000 - 0x01FFFFF | 64k  | HSB peripherals       |
| 0x0200000 - 0x0xxxxxx | xxx  | MMU mapping           |
| 0x1000000 - 0x1FFFFFF | 16M  | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 32 MiB. (mask 0x1FFFFFF)

## Peripherals

### Core

| Address   | Name                  |
|-----------|-----------------------|
| 0x0100000 | <del>CMNG</del>       |
| 0x0100100 | SDTAP                 |
| 0x0100300 | MMU                   |
| 0x0101000 | DSP                   |
| 0x0101040 | DEBUG                 |
| 0x0102000 | FFT                   |
| 0x010F000 | q32DSP                |

### LSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x01E0000 | SYSCFG                |
| 0x01E0100 | MODE                  |
| 0x01E0200 | SYSTEM                |
| 0x01E0400 | TIMER0                |
| 0x01E0500 | TIMER1                |
| 0x01E0600 | TIMER2                |
| 0x01E0700 | TIMER3                |
| 0x01E0800 | TIMER4                |
| 0x01E0900 | TIMER5                |
| 0x01E1000 | PCNT                  |
| 0x01E1100 | GPCNT                 |
| 0x01E1400 | SD0                   |
| 0x01E1500 | <del>SD1</del>        |
| 0x01E1800 | USB                   |
| 0x01E1900 | ANA                   |
| 0x01E1C00 | SPI0                  |
| 0x01E1D00 | SPI1                  |
| 0x01E1E00 | SPI2                  |
| 0x01E2000 | UART0                 |
| 0x01E2100 | UART1                 |
| 0x01E2200 | UART2                 |
| 0x01E2400 | IIC                   |
| 0x01E2800 | PAP                   |
| 0x01E2B00 | SS                    |
| 0x01E2C00 | RDEC0                 |
| 0x01E2D00 | PLNK                  |
| 0x01E2E00 | ALNK0                 |
| 0x01E2F00 | AUDIO                 |
| 0x01E3000 | MCPWM                 |
| 0x01E3100 | ADC                   |
| 0x01E3200 | IRFLT                 |
| 0x01E3300 | ALNK1                 |
| 0x01E3400 | OSA                   |
| 0x01E3500 | CRC                   |
| 0x01E3600 | LRCT                  |
| 0x01E3700 | EFUSE                 |
| 0x01E3B00 | RAND64                |
| 0x01E3C00 | CTM                   |
| 0x01E3E00 | P33                   |
| 0x01E3F00 | DMA                   |
| 0x01E4100 | PERIENC               |
| 0x01E4200 | SBC                   |
| 0x01E4300 | AES                   |
| 0x01E4400 | RDEC1                 |
| 0x01E4500 | RDEC2                 |
| 0x01E5000 | PORTA                 |
| 0x01E5040 | PORTB                 |
| 0x01E5080 | PORTC                 |
| 0x01E50C0 | PORTD                 |
| 0x01E5100 | USB_IO                |
| 0x01E5108 | WAKEUP                |
| 0x01E5114 | IOMAP                 |
| 0x01E5200 | PLED                  |
| 0x01E5300 | LCD                   |

### HSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x01F0200 | SFC                   |
| 0x01F0300 | SFCENC                |
| 0x01F0500 | <del>PSRAM</del>      |
| 0x01F1300 | DCP                   |
| 0x01F1500 | EQ                    |
| 0x01F1600 | SRC                   |
| 0x01F1700 | FM                    |
| 0x01F1800 | WL                    |
