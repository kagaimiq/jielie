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

Main control register.

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 15    | R   | 0       | PND          | Main interrupt status                 |
| 14    | W   | 0       | PCLR         | Clear the main interrupt              |
| 13    | R   | 0       | END_PND      | Stop condition interrupt pending      |
| 12    | W   | 0       | END_PND_CLR  | Clear a stop condition interrupt      |
| 11    | R/W | 0       | /            | /                                     |
| 10    | R/W | 0       | END_PND_IE   | Enable stop condition interrupt       |
| 9     | R/W | 0       | IIC_ISEL     | Input select (0: direct, 1: filtered) |
| 8     | R/W | 0       | IE           | Interrupt enable                      |
| 7     | R   | 1       | RD_ACK       | Received ACK value (0: ACK, 1: NAK)   |
| 6     | R/W | 0       | WR_ACK       | ACK value to send (0: ACK, 1: NAK)    |
| 5     | W   | 0       | M_SET_RSTART | Send a (re-)Start condition before a transfer |
| 4     | W   | 0       | M_SET_END    | Send a Stop condition                 |
| 3     | R/W | 0       | DAT_DIR      | Data transfer direction (0: send, 1: receive) |
| 2     | W   | 0       | N_CFG_DONE   | Execute the transfer                  |
| 1     | R/W | 0       | SLAVE        | Mode (0: master, 1: slave)            |
| 0     | R/W | 0       | EN           | Enable                                |

### BUF

Data buffer.

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15:8  | /   | /       | /                                                    |
| 7:0   | R/W | /       | Data buffer                                          |

### BAUD

Clock divider or slave addres.

- Master mode:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15:8  | /   | /       | /                                                    |
| 7:0   | W   | /       | Clock divider - _Fiic = Fsys / ((BAUD + 1) * 2)_     |

- Slave mode:

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 15:8  | /   | /       | /                                                    |
| 7:1   | W   | /       | Slave address                                        |
| 0     | W   | /       | /                                                    |

### CON1

Slave role related control/status.

| Bits  | R/W | Default | Name     | Description                               |
|-------|-----|---------|----------|-------------------------------------------|
| 15    | R   | 0       | SPND     | Start condition interrupt pending         |
| 14    | W   | 0       | SPND_CLR | Clear the start condition interrupt       |
| 13    | R/W | 0       | SI_MODE  | Slave addressing mode (0: match any address, 1: match the address in BAUD register) |
| 12:0  | R/W | 0       | /        | /                                         |
