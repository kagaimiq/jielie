# UART

UART (Universal Asynchronous Receiver-Transmitter) interface

## Registers

- Most UARTs:

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control register 0            |
| CON1     | 0x04   | Control register 1            |
| BAUD     | 0x08   | Clock divider                 |
| BUF      | 0x0C   | Data buffer                   |
| OTCNT    | 0x10   | Timeout                       |
| TXADR    | 0x14   | TX DMA address                |
| TXCNT    | 0x18   | TX DMA length                 |
| RXSADR   | 0x1C   | RX DMA start address          |
| RXEADR   | 0x20   | RX DMA end address            |
| RXCNT    | 0x24   | RX DMA length                 |
| HRXCNT   | 0x28   | RX DMA received length        |

- UART2 in some chips (e.g. BT15 ... BR21):

| Name     | Offset | Description                   |
|----------|--------|-------------------------------|
| CON0     | 0x00   | Control register 0            |
| BUF      | 0x04   | Data buffer                   |
| BAUD     | 0x08   | Clock divider                 |

### CON0

- Most UARTs:

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 31:16 | /   | /       | /            | /                                     |
| 15    | R   | 0       | TPND         | TX interrupt pending                  |
| 14    | R   | 0       | RPND         | RX interrupt pending                  |
| 13    | W   | /       | CLRTPND      | Clear pending TX interrupt            |
| 12    | W   | /       | CLRRPND      | Clear pending RX interrupt            |
| 11    | R   | 0       | OTPND        | Timeout interrupt pending             |
| 10    | W   | /       | CLR_OTPND    | Clear pending timeout interrupt       |
| 9     | R/W | 0       | TB8          | 9th bit to transmit in 9-bit mode     |
| 8     | R   | 0       | RB8          | 9th bit received in 9-bit mode        |
| 7     | W   | /       | RDC          | Received amount counter clear         |
| 6     | R/W | 0       | RX_MODE      | RX mode (0 = PIO, 1 = via DMA)        |
| 5     | R/W | 0       | OT_IE        | Timeout interrupt enable              |
| 4     | R/W | 0       | DIVS         | Clock predivider (0 = /4, 1 = /3)     |
| 3     | R/W | 0       | RXIE         | RX interrupt enable                   |
| 2     | R/W | 0       | TXIE         | TX interrupt enable                   |
| 1     | R/W | 0       | M9EN         | Frame size (0 = 8-bit, 1 = 9-bit)     |
| 0     | R/W | 0       | UTEN         | Enable                                |

- Some UART2's:

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 31:16 | /   | /       | /            | /                                     |
| 15    | R   | 0       | TPND         | TX interrupt pending                  |
| 14    | R   | 0       | RPND         | RX interrupt pending                  |
| 13    | W   | /       | CLRTPND      | Clear pending TX interrupt            |
| 12    | W   | /       | CLRRPND      | Clear pending RX interrupt            |
| 11:10 | /   | /       | /            | /                                     |
| 9     | R/W | 0       | TB8          | 9th bit to transmit in 9-bit mode     |
| 8     | R   | 0       | RB8          | 9th bit received in 9-bit mode        |
| 7:5   | /   | /       | /            | /                                     |
| 4     | R/W | 0       | DIVS         | Clock predivider (0 = /4, 1 = /3)     |
| 3     | R/W | 0       | RXIE         | RX interrupt enable                   |
| 2     | R/W | 0       | TXIE         | TX interrupt enable                   |
| 1     | R/W | 0       | M9EN         | Frame size (0 = 8-bit, 1 = 9-bit)     |
| 0     | R/W | 0       | UTEN         | Enable                                |

### CON1

| Bits  | R/W | Default | Name         | Description                           |
|-------|-----|---------|--------------|---------------------------------------|
| 31:14 | /   | /       | /            | /                                     |
| 13    | R/W | 0       | CLRRTS       | Enable RTS                            |
| 12:6  | /   | /       | /            | /                                     |
| 5:4   | R/W | 0       | BAUD_FRAC    | Baudrate fraction                     |
| 3     | R/W | 0       | CTSIE        | Enable CTS interrupt                  |
| 2     | R/W | 0       | CTSE         | Enable CTS                            |
| 1     | R/W | 0       | RTS_DMAEN    | Enable RTS DMA...                     |
| 0     | R/W | 0       | RTSE         | Enable RTS                            |

### BAUD

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:x  | /   | /       | /                                                    |
| x:0   | W   | /       | Clock divider - _Fuart = Fsys / <4 or 3> / (BAUD + 1)_ |

### BUF

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | R/W | /       | Data buffer                                          |
