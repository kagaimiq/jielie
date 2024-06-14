# ENC

## Overview

This block implements a simple LFSR-based stream cipher algorithm,
which can be tied to SD0's DATA transfers, SPI0's DMA transfers and SFC reads.

### ENC variants

Initially there was a single ENC peripheral that was both responsible for "peripherals" (SPI0, SD0) and the [SFC](sfc.md).

Then, at some point the peripheral and SFC ENC's were split into independent PERIENC and SFCENC blocks,
and finally the SFCENC became a part of the SFC block itself.

### Algorithm

The LFSR logic used is basically the one of a CRC16-CCITT.
The lower 8 bits of the key is XORed with the data byte, and then the key is scrambled,
then the same is done for any subsequent bytes.

```c
void jl_crypt(uint8_t *data, int len, uint16_t key) {
    while (len--) {
        *data++ ^= key;
        key = (key << 1) ^ ((key >> 15) ? 0x1021 : 0);
    }
}
```

### UNENC area

The UNENC_ADR[H|L] registers define the area which is going to be passed as-is (i.e. no decryption is performed)
when this area is accessed in the SFC map, thus these registers only exist on the SFC ENC blocks.

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
