# ENC

ENC (ENCrypter?) is used to (de)crypt the data from the [SFC](sfc.md), SPI, SD, etc.

The algorithm is actually pretty basic, they just used the CRC16 shift register logic for that...

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

| Name       | Offset | Description        |
|------------|--------|--------------------|
| CON        | 0x00   | Control register   |
| KEY        | 0x04   | Key register       |
| ADR        | 0x08   | "Address" register |
| UNENC_ADRH | 0x0C   |                    |
| UNENC_ADRL | 0x10   |                    |

- PERIENC:

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| KEY      | 0x04   | Key register       |
| ADR      | 0x08   | "Address" register |

- SFCENC:

| Name       | Offset | Description        |
|------------|--------|--------------------|
| CON        | 0x00   | Control register   |
| KEY        | 0x04   | Key register       |
| UNENC_ADRH | 0x08   |                    |
| UNENC_ADRL | 0x0C   |                    |
| LENC_ADRH  | 0x10   |                    |
| LENC_ADRL  | 0x14   |                    |

### CON

- ENC, PERIENC:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7     | W   |         | Reset key shift register                             |
| 6:3   | /   | /       | /                                                    |
| 2     | R/W | 0       | Enable ENC for SD0 DATA transfers                    |
| 1     | R/W | 0       | Enable ENC for SFC?                                  |
| 0     | R/W | 0       | Enable ENC for SPI0 DMA transfers                    |

- SFCENC:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:1  | /   | /       | /                                                    |
| 0     | R/W | 0       | Enable ENC for SFC                                   |

### KEY

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:16 | /   | /       | /                                                    |
| 15:0  | W   |         | Key register value                                   |
