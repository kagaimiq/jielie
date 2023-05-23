# BANKCB

BANKCB (probably: BANKed Code Block) is a format for storing banked code, which was used in chips which couldn't run off the SPI flash
directly, and thus the code ran from small on-chip SRAMs, which meant that to store large amounts of code it needed to be banked.

Nowadays, though, the chips now contain the [SFC](/ip/sfc.md) block that allows to map the SPI flash into memory,
but the BANKCB still lives to this day to store the `uboot.boot` bootloader, which then bootstraps the SFC and finally jumps into the main code.

## Format

### Header

- u16: Bank count
- u16: Bank size
- u32: Bank address
- u32: Data offset
- u16: Data CRC16
- u16: Header CRC16
