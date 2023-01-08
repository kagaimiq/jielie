# Memory mapping of BR17

|  Address              | Size   | Usage                 |
|-----------------------|--------|-----------------------|
| 0x0000000 - 0x0019000 | 104k   | SRAM0                 |
| 0x001A000 - 0x001E1FF | 16.5k  | extra SRAM??          |
| 0x0020000 - 0x003FFFF | 128k   | alias 0x00000~0x1ffff |
| 0x0040000 - 0x0045FFF | 24k    | SRAM1                 |
| 0x0048000 - 0x00497FF | 6k     | SFC cache tag         |
| 0x0049800 - 0x00498FF | 256    | MMU tag0              |
| 0x0050000 - 0x00527FF | 10k    | MaskROM               |
| 0x0060000 - 0x006FFFF | 64k    | LSB peripherals       |
| 0x0070000 - 0x007FFFF | 64k    | HSB peripherals       |
| 0x0080000 - 0x009FFFF | 128k   | MMU mapping           |
| 0x00E0000 - 0x00EFFFF | 64k    | BT SFR?               |
| 0x00F0000 - 0x00FFFFF | 64k    | "Zebra"               |
| 0x0100000 - 0x07FFFFF | 7M     | alias 0x00000~0xfffff |
| 0x1000000 - 0x1FFFFFF | 16M    | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 32 MiB. (mask 0x1FFFFFF)
