# Memory mapping of BR17

|  Address   | Size   | Usage                 |
|------------|--------|-----------------------|
| 0x00000000 | 104k   | SRAM0                 |
| 0x0001a000 | 16.5k  | extra SRAM??          |
| 0x00020000 | 128k   | alias 0x00000~0x1ffff |
| 0x00040000 | 24k    | SRAM1                 |
| 0x00046000 | 8k     | reserved              |
| 0x00048000 | 2k     | ? cache related ??    |
| 0x00048800 | 2k     | reserved              |
| 0x00049000 | 2k     | ? cache related ??    |
| 0x00049800 | 256    | MMU tag0              |
| 0x00049900 | 25.75k | reserved              |
| 0x00050000 | 64k    | MaskROM maybe ?!      |
| 0x00060000 | 64k    | LSB peripherals       |
| 0x00070000 | 64k    | HSB peripherals       |
| 0x00080000 | 128k   | MMU mapping           |
| 0x000e0000 | 64k    | BT SFR?               |
| 0x000f0000 | 64k    | Zebra                 |
| 0x00100000 | 2M     | UNKNOWN               |
| 0x00300000 | xxx    | alias 0x000000??      |
| 0x01000000 | 16M    | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 2 MiB.
