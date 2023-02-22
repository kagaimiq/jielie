# ENC

## Overview

This peripheral implements a simple "encryption" (or rather obfuscation) algorithm,
which can be tied to SD0's DATA transfers, SPI0's DMA transfer and the SFC fetches.

### Other ENCs

It used to handle both the SPI0/SD0 and the SFC, but after some time
it was split into two separate peripherals, PERIENC and SFCENC,
which handle SPI0/SD0 and SFC separately.

And after some more time the SFCENC essentially became a part of SFC itself.

### Algorithm

The algorithm it uses is basically the CRC16-CCITT shift register logic,
which is updated on each byte, and its value is XORed onto a data byte prior to the register update.

```c
void jl_crypt(uint8_t *data, int len, uint16_t key) {
    while (len--) {
        *data++ ^= key;
        key = (key << 1) ^ ((key >> 15) ? 0x1021 : 0);
    }
}
```

## Registers

- ENC:

| Name       | Offset | Description            |
|------------|--------|------------------------|
| CON        | 0x00   | Control register       |
| KEY        | 0x04   | Key register           |
| ADR        | 0x08   | "Address" register     |
| UNENC_ADRH | 0x0C   | Unencrypted area end   |
| UNENC_ADRL | 0x10   | Unencrypted area start |

- PERIENC:

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| KEY      | 0x04   | Key register       |
| ADR      | 0x08   | "Address" register |

- SFCENC:

| Name       | Offset | Description            |
|------------|--------|------------------------|
| CON        | 0x00   | Control register       |
| KEY        | 0x04   | Key register           |
| UNENC_ADRH | 0x08   | Unencrypted area end   |
| UNENC_ADRL | 0x0C   | Unencrypted area start |
| LENC_ADRH  | 0x10   | Lenc area end          |
| LENC_ADRL  | 0x14   | Lenc area start        |

### CON

- ENC:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7     | W   |         | Reset key shift register                             |
| 6:3   | /   | /       | /                                                    |
| 4     | R/W | 0       | Enable UNENC area                                    |
| 3     | R/W | 0       | Enable ENC for SFC                                   |
| 2     | R/W | 0       | Enable ENC for SD0 DATA transfers                    |
| 1     | R/W | 0       | Enable ENC for something?                            |
| 0     | R/W | 0       | Enable ENC for SPI0 DMA transfers                    |

- PERIENC:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7     | W   |         | Reset key shift register                             |
| 6:3   | /   | /       | /                                                    |
| 2     | R/W | 0       | Enable ENC for SD0 DATA transfers                    |
| 1     | R/W | 0       | Enable ENC for something?                            |
| 0     | R/W | 0       | Enable ENC for SPI0 DMA transfers                    |

- SFCENC:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:1  | /   | /       | /                                                    |
| 1     | R/W | 0       | Enable UNENC/LENC areas                              |
| 0     | R/W | 0       | Enable ENC for SFC                                   |

### KEY

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:16 | /   | /       | /                                                    |
| 15:0  | W   |         | Key register value                                   |
