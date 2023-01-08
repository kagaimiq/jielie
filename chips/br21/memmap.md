# Memory mapping of BR21

|  Address              | Size   | Usage                 |
|-----------------------|--------|-----------------------|
| 0x0000000 - 0x000FFFF | 64k    | SRAM0                 |
| 0x0010000 - 0x001FFFF | 64k    | SRAM1                 |
| 0x0020000 - 0x00227FF | 10k    | MaskROM               |
| 0x0048000 - 0x00497FF | 6k     | SFC cache tag         |
| 0x0049800 - 0x00498FF | 256    | MMU tag0 ...?!        |
| 0x0060000 - 0x006FFFF | 64k    | LSB peripherals       |
| 0x0070000 - 0x007FFFF | 64k    | HSB peripherals       |
| 0x0080000 - 0x00DFFFF | 384k   | alias 0x00000-0x7ffff |
| 0x00E0000 - 0x00EFFFF | 64k    | BT SFR                |
| 0x0100000 - 0x07FFFFF | 7M     | alias 0x00000-0xfffff |
| 0x1000000 - 0x1FFFFFF | 16M    | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 32 MiB. (mask 0x1FFFFFF)
