# Memory mapping of BR21

|  Address   | Size   | Usage                 |
|------------|--------|-----------------------|
| 0x00000000 | 64k    | SRAM0                 |
| 0x00010000 | 64k    | SRAM1                 |
| 0x00020000 | 10k    | MaskROM               |
| 0x00022800 | 150k   | reserved              |
| 0x00048000 | 6k     | SFC cache tag         |
| 0x00049800 | 256    | MMU tag0 ...?!        |
| 0x00049900 | 89.75k | reserved              |
| 0x00060000 | 64k    | LSB peripherals       |
| 0x00070000 | 64k    | HSB peripherals       |
| 0x00080000 | 384k   | alias 0x00000-0x7ffff |
| 0x000e0000 | 64k    | BT SFR                |
| 0x000f0000 | 64k    | reserved              |
| 0x00100000 | 7M     | alias 0x00000-0xfffff |
| 0x00800000 | 8M     | reserved              |
| 0x01000000 | 16M    | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 2 MiB.
