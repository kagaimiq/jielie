# Memory map of DV15

| Address               | Size   | Usage                 |
|-----------------------|--------|-----------------------|
| 0x0000000 - 0x0FFFFFF | 16M    | SFC mapping           |
| 0x0F00000 - 0x0F0FFFF | 64k    | RAM0                  |
| 0x0F60000 - 0x0F6FFFF | 64k    | LSB peripherals       |
| 0x0F70000 - 0x0F77FFF | 32k    | HSB peripherals       |
| 0x0F78000 - 0x0F7FFFF | 32k    | EVA peripherals       |
| 0x1000000 - 0x17FFFFF | 8M     | SDRAM                 |

## Peripherals

### LSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x0F60000 | IO - PORTA            |
| 0x0F60040 | IO - PORTB            |
| 0x0F60080 | IO - PORTC            |
| 0x0F600C0 | IO - PORTD            |
| 0x0F60100 | IO - PORTE            |
| 0x0F60140 | IO - PORTF            |
| 0x0F60180 | IO - PORTG            |
| 0x0F601C0 | IO - PORTH            |
| 0x0F60200 | IO - IOMC             |
| 0x0F60214 | IO - WKUP             |
| 0x0F60400 | UART0                 |
| 0x0F60440 | UART1                 |
| 0x0F60480 | UART2                 |
| 0x0F604C0 | UART3                 |
| 0x0F60800 | SPI0                  |
| 0x0F60840 | SPI1                  |
| 0x0F60C00 | SD0                   |
| 0x0F60C40 | SD1                   |
| 0x0F60C80 | SD2                   |
| 0x0F61000 | TIMER0                |
| 0x0F61040 | TIMER1                |
| 0x0F61080 | TIMER2                |
| 0x0F610C0 | TIMER3                |
| 0x0F61100 | PWM                   |
| 0x0F61400 | FUSB                  |
| 0x0F61800 | HUSB                  |
| 0x0F61C00 | ADDA                  |
| 0x0F62000 | CLK                   |
| 0x0F62400 | LS_OTH - HTC          |
| 0x0F62404 | LS_OTH - LDO          |
| 0x0F62408 | LS_OTH - LVD          |
| 0x0F6240C | LS_OTH - IRTC         |
| 0x0F62414 | LS_OTH - MODE         |
| 0x0F62418 | LS_OTH - CRC0         |
| 0x0F62420 | LS_OTH - WDT          |
| 0x0F62424 | LS_OTH - CHIP_ID      |
| 0x0F62428 | LS_OTH - IRFLT        |
| 0x0F6242C | LS_OTH - IIC          |
| 0x0F62444 | LS_OTH - PWM8         |
| 0x0F62448 | LS_OTH - PAP          |
| 0x0F62460 | LS_OTH - CRC1         |
| 0x0F6246C | LS_OTH - EFUSE        |
| 0x0F62470 | LS_OTH - MPU          |
| 0x0F62484 | LS_OTH - PLCNT        |
| 0x0F6248C | LS_OTH - CS           |
| 0x0F624A0 | LS_OTH - RAND64       |
| 0x0F624A8 | LS_OTH - GPADC        |
| 0x0F62800 | ALNK                  |
| 0x0F68000 | HUSB0                 |

### HSB

| Address   | Name                  |
|-----------|-----------------------|
| 0x0F70000 | CPU                   |
| 0x0F70400 | DBG                   |
| 0x0F70800 | SDR                   |
| 0x0F70C00 | EVA                   |
| 0x0F71000 | SFC                   |
| 0x0F71400 | <del>JPG</del>        |
| 0x0F71800 | HS_OTH - ENC          |
| 0x0F71814 | HS_OTH - DMA          |
| 0x0F71840 | HS_OTH - AES          |
| 0x0F71880 | HS_OTH - GPDMA_RD     |
| 0x0F718C0 | HS_OTH - GPDMA_WR     |
| 0x0F74000 | JPG0                  |
| 0x0F75000 | JPG1                  |
| 0x0F77000 | DMACOPY               |

### EVA

| Address   | Name                  |
|-----------|-----------------------|
| 0x0F78000 | XBUS                  |
| 0x0F78800 | ISC                   |
| 0x0F79000 | ISP0                  |
| 0x0F79800 | ISP1                  |
| 0x0F7A000 | IMC                   |
| 0x0F7A800 | IMB                   |
| 0x0F7B000 | IMD                   |
| 0x0F7B200 | IMD_DPI               |
| 0x0F7B800 | CVBS                  |
| 0x0F7BC00 | TVE                   |
| 0x0F7BE00 | CVE                   |
| 0x0F7C000 | MIPI - CSI            |
| 0x0F7C200 | MIPI - DSI_S          |
| 0x0F7C300 | MIPI - DSI_D          |
| 0x0F7C400 | MIPI - MP_PHY         |
| 0x0F7C800 | IMR                   |
