# Memory map of DV16

| Address               | Size   | Usage                 |
|-----------------------|--------|-----------------------|
| 0x2000000 - 0x23FFFFF | 4M     | XROM (SFC mapping?)   |
| 0x3F00000 - 0x3F0FFFF | 64k    | RAM0                  |
| 0x3F80000 - 0x3F8FFFF | 64k    | LSB peripherals       |
| 0x3F90000 - 0x3F97FFF | 32k    | HSB peripherals       |
| 0x3F98000 - 0x3F9FFFF | 32k    | EVA peripherals       |
| 0x3FA0000 - 0x3FC87FF | 162k   | VRAM                  |
| 0x4000000 - 0x5FFFFFF | 32M    | SDRAM                 |

## Peripherals

### LSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x3F801C0 | IO - IOMC             |
| 0x3F801D0 | IO - WKUP             |
| 0x3F80400 | UART0                 |
| 0x3F80440 | UART1                 |
| 0x3F80480 | UART2                 |
| 0x3F804C0 | UART3                 |
| 0x3F80800 | SPI0                  |
| 0x3F80840 | SPI1                  |
| 0x3F80880 | SPI2                  |
| 0x3F80C00 | SD0                   |
| 0x3F80C40 | SD1                   |
| 0x3F80C80 | SD2                   |
| 0x3F81000 | TIMER0                |
| 0x3F81040 | TIMER1                |
| 0x3F81080 | TIMER2                |
| 0x3F810C0 | TIMER3                |
| 0x3F81400 | FUSB                  |
| 0x3F81800 | LS_HUSB               |
| 0x3F81C00 | ADDA                  |
| 0x3F82000 | CLK                   |
| 0x3F82400 | LS_OTH - HTC          |
| 0x3F82404 | LS_OTH - LDO          |
| 0x3F82408 | LS_OTH - LVD          |
| 0x3F8240C | LS_OTH - IRTC         |
| 0x3F82414 | LS_OTH - MODE         |
| 0x3F82418 | LS_OTH - CRC0         |
| 0x3F82420 | LS_OTH - WDT          |
| 0x3F82424 | LS_OTH - CHIP_ID      |
| 0x3F82428 | LS_OTH - IRFLT        |
| 0x3F8242C | LS_OTH - IIC0         |
| 0x3F82444 | LS_OTH - IIC1         |
| 0x3F8245C | LS_OTH - PWM8         |
| 0x3F82460 | LS_OTH - PAP          |
| 0x3F8247C | LS_OTH - EFUSE_MPW    |
| 0x3F82480 | LS_OTH - EFUSE        |
| 0x3F82484 | LS_OTH - MPU          |
| 0x3F82498 | LS_OTH - PLCNT        |
| 0x3F824A0 | LS_OTH - CS           |
| 0x3F824B4 | LS_OTH - RAND64       |
| 0x3F824BC | LS_OTH - ETH          |
| 0x3F824C0 | LS_OTH - SHA1         |
| 0x3F82500 | LS_OTH - CRC1         |
| 0x3F82508 | LS_OTH - RINGOSC      |
| 0x3F8250C | LS_OTH - MBIST        |
| 0x3F82800 | ALNK                  |
| 0x3F82C00 | PWM                   |
| 0x3F84000 | HUSB0                 |
| 0x3F86000 | HUSB1                 |
| 0x3F88000 | OETH ??               |

### HSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x3F90000 | SDR                   |
| 0x3F90400 | EVA                   |
| 0x3F90800 | CPU                   |
| 0x3F90C00 | SFC                   |
| 0x3F91000 | <del>JPG</del>        |
| 0x3F91400 | HS_OTH - ENC          |
| 0x3F91440 | HS_OTH - AES          |
| 0x3F91480 | HS_OTH - GPDMA_RD     |
| 0x3F914C0 | HS_OTH - GPDMA_WR     |
| 0x3F91800 | DBG                   |
| 0x3F92000 | JIVE                  |
| 0x3F92400 | JLMD                  |
| 0x3F94000 | AVC                   |
| 0x3F94800 | JPG0                  |
| 0x3F94900 | <del>JPG1</del>       |
| 0x3F94E00 | VRAM / VIDEO          |
| 0x3F94F00 | DMACOPY               |
| 0x3F9D000 | <del>AVC</del>        |

### EVA

| Address   | Name                  |
|-----------|-----------------------|
| 0x3F98000 | XBUS                  |
| 0x3F98800 | ISC                   |
| 0x3F99000 | ISP0                  |
| 0x3F99800 | ISP1                  |
| 0x3F9A000 | IMC                   |
| 0x3F9A800 | IMB                   |
| 0x3F9B000 | IMD                   |
| 0x3F9B800 | AVO.0                 |
| 0x3F9BA00 | AVO.1                 |
| 0x3F9C000 | MIPI - CSI            |
| 0x3F9C200 | MIPI - DSI_S          |
| 0x3F9C300 | MIPI - DSI_D          |
| 0x3F9C400 | MIPI - MP_PHY         |
