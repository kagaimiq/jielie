# Memory map of BR23

| Address               | Size | Usage                 |
|-----------------------|------|-----------------------|
| 0x0000000 - 0x002BFFF | 176k | RAM0                  |
| 0x002C000 - 0x002FFFF | 16k  | RAM1                  |
| 0x00FC000 - 0x00FDBFF | 7k   | icache tag            |
| 0x0100000 - 0x010FFFF | 64k  | Core peripherals      |
| 0x0110000 - 0x0107FFF | 32k  | MaskROM               |
| 0x01E0000 - 0x01EFFFF | 64k  | LSB peripherals       |
| 0x01F0000 - 0x01FFFFF | 64k  | HSB peripherals       |
| 0x0200000 - 0x0xxxxxx | xxx  | MMU mapping           |
| 0x0800000 - 0x0FFFFFF | 8M   | PSRAM mapping         |
| 0x1000000 - 0x1FFFFFF | 16M  | SFC mapping           |

- The main bus has 25-bit wide addressing, i.e. it wraps each 32 MiB. (mask 0x1FFFFFF)

## Peripherals

### LSB

| Address   | Name                  |
|-----------|-----------------------|

### HSB

| Address   | Name                  |
|-----------|-----------------------|
