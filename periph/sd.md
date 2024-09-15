# SD

An SD/MMC card host interface.



## Registers

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control register 0            |
| CON1     | 0x04   | Control register 1            |
| CON2     | 0x08   | Control register 2            |
| CPTR     | 0x0C   | Command buffer address        |
| DPTR     | 0x10   | Data buffer address           |

Variants with CTU add the following registers:

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CTU_CON  | 0x14   | CTU control reg               |
| CTU_CNT  | 0x18   | CTU block count               |

### CON0

| Bits  | Type | Name        | Description                 |
|-------|------|-------------|-----------------------------|
| 15    | R    | DINT        | Data interrupt pending      |
| 14    | W    | CLR_DINT    | Clear a pending data interrupt |
| 13    | R/W  | LINE4       | Data bus width (0 = 1-bit, 1 = 4-bit) |
| 12    | R/W  | DATCLK8     | Send 8 clocks after transferring a data block |
| 11    | R    | DATCRC      | Data CRC error flag         |
| 10:8  | W    | SDDMODE     | Fire a single data block transfer ([10:9] = 0: NOP, 2: send block, 3: receive block; [8] = 0: do not check for busy, 1: check for busy)  |
| 7     | R    | CINT        | Command interrupt pending   |
| 6     | W    | CLR_CINT    | Clear a pending command interrupt |
| 5     | R    | TIMEOUT     | Timed out flag              |
| 4     | R/W  | CMDCLK8     | Send 8 clocks after transferring a command |
| 3     | R    | CMDCRC      | Response CRC error flag     |
| 2:0   | W    | SDCMODE     | Fire a command transfer ([2] = 0: check for busy, 1: do not check for busy; [1:0] = 0: NOP, 1: send with a 48-bit response, 2: send with a 136-bit response, 3: send without receiving a response) |

### CON1

| Bits  | Type | Name        | Description                 |
|-------|------|-------------|-----------------------------|
| 15:8  | R/W  | SD_BAUD     | Card clock divider, Fsys / (SD_BAUD + 1) |
| 7     | R/W  | DATIE       | Data interrupt enable       |
| 6     | R/W  | CMDIE       | Command interrupt enable    |
| 5     | R/W  | CLKALL      | Always send a card clock    |
| 4     |      |             |                             |
| 3:1   | R    | CRCSTA      | CRC status flags            |
| 0     | R/W  | SDCEN       | Enable the SD host controller |

### CON2

| Bits  | Type | Name        | Description                 |
|-------|------|-------------|-----------------------------|
| 15:9  |      |             |                             |
| 8:0   | R/W  | SDDCNT      | Data block size (SDDCNT + 1) |

### CPTR

| Bits  | Type | Description                               |
|-------|------|-------------------------------------------|
| x:2   | W    | Address of the command buffer             |

### DPTR

| Bits  | Type | Description                               |
|-------|------|-------------------------------------------|
| x:2   | W    | Address of the data buffer                |

### CTU_CON

| Bits  | Type | Name         | Description                 |
|-------|------|--------------|-----------------------------|
| 15:11 |      |              |                             |
| 10:8  | R/W  | SDDMODE_KEEP | Fire a multi-block data transfer ([10:9] = 0: NOP, 2: send, 3: receive; [8] = 0: do not check for busy, 1: check for busy) |
| 7     | R    | CTU_PND      | CTU interrupt pending flag  |
| 6     | W    | CLR_CTU_PND  | Clear CTU pending flag      |
| 5     | R    | CTU_ERR      | CTU error flag              |
| 4     | W    | CLR_CTU_ERR  | Clear CTU error flag        |
| 3     | R    | CTU_BUSY     | CTU busy flag               |
| 2     | R/W  | CTU_PND_IE   | CTU general interrupt enable |
| 1     | R/W  | CTU_ERR_IE   | CTU error interrupt enable  |
| 0     | R/W  | SD_CTU_EN    | Enable the CTU block        |

### CTU_CNT

| Bits  | Type | Description                               |
|-------|------|-------------------------------------------|
| 15:0  | R/W  | Block count (CTU_CNT + 1)                 |

**Note:** the data transfer via CTU is finally started when this register is written
