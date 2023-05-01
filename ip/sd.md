# SD

SD/MMC card host controller.

## Registers

- Variant 1:

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control reg 0                 |
| CON1     | 0x04   | Control reg 1                 |
| CON2     | 0x08   | Control reg 2                 |
| CPTR     | 0x0C   | Command buffer address        |
| DPTR     | 0x10   | Data buffer address           |

- Variant 2:

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control reg 0                 |
| CON1     | 0x04   | Control reg 1                 |
| CON2     | 0x08   | Control reg 2                 |
| CPTR     | 0x0C   | Command buffer address        |
| DPTR     | 0x10   | Data buffer address           |
| CTU_CON  | 0x14   | CTU control reg               |
| CTU_CNT  | 0x18   | CTU block count               |

### CON0

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15    | r   | 0       | Data interrupt pending                               |
| 14    | w   | /       | Clear pending data interrupt                         |
| 13    | r/w | 0       | Bus width (0 = 1-bit, 1 = 4-bit)                     |
| 12    | r/w | 0       | ?? cleared on data xfer                              |
| 11    | r   | 0       | Data CRC error                                       |
| 10    | r/w | 0       | . set together with [9:8] - usually 1                |
| 9:8   | r/w | 0       | Fire data transfer (1 = send, 2 = receive)           |
| 7     | r   | 0       | Command interrupt pending                            |
| 6     | w   | /       | Clear pending command interrupt                      |
| 5     | r   | 0       | Command timed out?                                   |
| 4     | r/w | 0       | ?? set to 1, cleared after cmd was xferred           |
| 3     | r   | 0       | Command CRC error?                                   |
| 2     | r/w | 0       | . set together with [1:0], usually 1 but might be 0 for cmd3, cmd12    |
| 1:0   | r/w | 0       | Fire command transfer (1 = 48-bit resp, 2 = 136-bit resp, 3 = no resp) |

### CON1

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15:8  | r/w | 0       | Card clock divider, Fclk = Fbus / (n + 1)            |
| 7     | r/w | 0       | Enable data interrupt                                |
| 6     | r/w | 0       | Enable command interrupt                             |
| 5     | r/w | 0       | Always output card clock                             |
| 0     | r/w | 0       | Enable                                               |

### CON2

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 8:0   | r/w | 0       | Block size (n-1)                                     |

### CPTR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
|       | w   | /       | Address of the command buffer                        |

### DPTR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
|       | w   | /       | Address of the data buffer                           |

### CTU_CON

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 10    | r/w | 0       | . set together with [9:8] - usually 1                |
| 9:8   | r/w | 0       | Fire data transfer (1 = send, 2 = receive)           |
| 7     | r   | 0       | Flag 2                                               |
| 6     | w   | /       | Clear flag 2                                         |
| 5     | r   | 0       | Flag 1                                               |
| 4     | w   | /       | Clear flag 1                                         |
| 2     | r/w | 0       | Flag 2 interrupt enable                              |
| 1     | r/w | 0       | Flag 1 interrupt enable                              |
| 0     | r/w | 0       | Enable CTU                                           |

### CTU_CNT

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15:0  | r/w | /       | Block count (n-1)                                    |

Note: the data transfer via CTU is finally started when this register is written
