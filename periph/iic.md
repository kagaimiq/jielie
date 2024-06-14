# IIC

IIC (Inter-Integrated Circuit / I<sup>2</sup>C) bus controller.

## Registers

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control register 0            |
| BUF      | 0x04   | Data buffer                   |
| BAUD     | 0x08   | Clock divider / Slave address |
| CON1     | 0x0C   | Control register 1            |

### CON0

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 31:16 | /   | /       | /            | /                                     |
| 15    | R   | 0       | PND          | Interrupt pending                     |
| 14    | W   | 0       | PCLR         | Clear pending int                     |
| 13    | R   | 0       | END_PND      | End interrupt pending                 |
| 12    | W   | 0       | END_PND_CLR  | Clear pending end interrupt           |
| 11    | R/W | 0       | /            | /                                     |
| 10    | R/W | 0       | END_PND_IE   | Enable end interrupt                  |
| 9     | R/W | 0       | IIC_ISEL     | Input select (0 = direct, 1 = filtered) |
| 8     | R/W | 0       | IE           | Interrupt enable                      |
| 7     | R   | 1       | RD_ACK       | Received ACK                          |
| 6     | R/W | 0       | WR_ACK       | ACK to send                           |
| 5     | W   | 0       | M_SET_RSTART | Send (re)start before sending byte    |
| 4     | W   | 0       | M_SET_END    | Send stop                             |
| 3     | R/W | 0       | DAT_DIR      | Direction (0 = send, 1 = receive)     |
| 2     | W   | 0       | N_CFG_DONE   | Execute the transfer                  |
| 1     | R/W | 0       | SLAVE        | Slave mode                            |
| 0     | R/W | 0       | EN           | Enable                                |

### BUF

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | R/W | /       | Data buffer                                          |

### BAUD

- Master mode:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | W   | /       | Clock divider - _Fiic = Fsys / ((BAUD + 1) * 2)_     |

- Slave mode:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:1   | W   | /       | Slave address                                        |
| 0     | W   | /       | /                                                    |

### CON1

| Bits  | R/W | Default | Name     | Description                               |
|-------|-----|---------|----------|-------------------------------------------|
| 31:16 | /   | /       | /        | /                                         |
| 15    | R   | 0       | SPND     | Start pending                             |
| 14    | W   | 0       | SPND_CLR | Clear start pending                       |
| 13    | R/W | 0       | SI_MODE  | Slave addr mode (0 = any addr, 1 = set addr in BAUD reg) |
| 12:0  | R/W | 0       | /        | /                                         |
