# SPI

SPI (Serial Peripheral Interface) bus controller.

The SPI0 is dedicated to the main SPI flash (and to a PSRAM chip in some cases), thus it supports the DSPI/QSPI (2/4-bit wide) mode, and also it has some special properties, namely:
the DMA transfers can be (de)scrambled with the [ENC](enc.md) block (if enabled), and they also automatically feed the CRC16 calculation block.

## Registers

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON      | 0x00   | Control register              |
| BAUD     | 0x04   | Clock divider                 |
| BUF      | 0x08   | Data buffer                   |
| ADR      | 0x0C   | DMA address                   |
| CNT      | 0x10   | DMA transfer length           |

### CON

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 31:16 | /   | /       | /            | /                                     |
| 15    | R   | 0       | PND          | Interrupt pending                     |
| 14    | W   | 0       | PCLR         | Clear pending int                     |
| 13    | R/W | 0       | IE           | Interrupt enable                      |
| 12    | R/W | 0       | DIR          | Direction (0 = send, 1 = receive)     |
| 11:10 | R/W | 0       | DATW         | Bus width (0 = 1-bit, 1 = 2-bit, 2 = 4-bit)  |
| 9:8   | /   | /       | /            | /                                     |
| 7     | R/W | 0       | CSID         | CS polarity (0 = low idle, 1 = high idle)    |
| 6     | R/W | 0       | CKID         | Clock polarity (0 = low idle, 1 = high idle) |
| 5     | R/W | 0       | UE           | Data update edge (0 = rising, 1 = falling)   |
| 4     | R/W | 0       | SE           | Data sample edge (0 = rising, 1 = falling)   |
| 3     | R/W | 0       | BIDIR        | Full duplex mode                      |
| 2     | R/W | 0       | CSE          | CS enable                             |
| 1     | R/W | 0       | SLAVE        | Slave mode                            |
| 0     | R/W | 0       | SPIE         | Enable                                |

### BAUD

- Master mode:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | W   | /       | Clock divider - _Fspi = Fsys / (BAUD + 1)_           |

### BUF

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | R/W | /       | Data buffer                                          |

### ADR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:26 | /   | /       | /                                                    |
| 25:0  | W   | /       | DMA address                                          |

### CNT

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:16 | /   | /       | /                                                    |
| 15:0  | W   | /       | DMA transfer length (triggers DMA)                   |
