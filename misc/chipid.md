# Chip IDs

- Top 8 bits from the `JL_SYSTEM->CHIP_ID` which is also sent e.g. on the [ISP_KEY](isp-key.md) handshake.

|  ID  | Family |
|------|--------|
| 0x53 | BR17   |
| 0x5B | ?      |
| 0x5E | BR23   |
| 0x5F | BR25   |
| 0x67 | ?      |
| 0x68 | BR34   |
| 0x69 | ?      |
| 0x6A | ?      |
| 0x6B | ?      |
| 0x6D | ?      |
| 0x73 | ?      |

- The value from the `JL_SYSTEM->CHIP_ID` register

| CHIP_ID | Family | Exact chip tested |
|---------|--------|-------------------|
| 0x5302  | BR17   | AC6908C           |
| 0x5F04  | BR25   | AC6965A           |
