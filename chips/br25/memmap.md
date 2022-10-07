# Memory map of BR25

|  Address   | Size | Usage                 |
|------------|------|-----------------------|
| 0x00000000 | 64k  | reserved              |
| 0x00010000 | 136k | SRAM                  |
| 0x00032000 | 1.5k | extra SRAM??          |
| 0x00100000 | 64k  | Core peripherals      |
| 0x00110000 | 32k  | MaskROM               |
| 0x001e0000 | 64k  | LSB peripherals       |
| 0x001f0000 | 64k  | HSB peripherals       |
| 0x00200000 | xxx  | MMU mapping           |
| 0x01e00000 | 2M   | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 2 MiB.
