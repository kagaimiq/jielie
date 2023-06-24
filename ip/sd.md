# SD

SD/MMC card host controller.

## Some details

### Command buffer

Contrary to any ordinary SD/MMC host like SDHCI, MSDC, SMHC and alike, this controller does not
have a concept of a command register, argument register, response registers or such.

Instead, it has an `CPTR` register, which specifies an address of a memory region where the *raw bits*
of the command transfer is stored to.

Nevertheless, it *is* capable of generating a proper CRC7, as well as checking it.

The first 6 bytes are the 48 command bits that are shifted out of the CMD line as is,
except for the last byte, which is replaced with a valid CRC7 of this command frame.

Then the next 6 or 16 bytes hold the bits shifted in from the CMD line after it noticed a start bit,
for a 48 or 136-bit response. Out of the 136 bits only 128 bits are received (or stored?) for some reason..

Here's an example of the buffer contents on a SEND_CSD (CMD9) command with a 136-bit response:
```
49 00 01 00 00 00
3f 8c 0e 01 2a 0f f9 81 e9 f6 d9 01 e1 8a 40 00
```

Here, the first byte is the opcode with the start bit (always 0), a transmission bit (1 for host-to-card),
and opcode bits (9 is obviously CMD9). The next 4 bytes is the argument field,
which in this case contains an RCA in top 16 bits. Then comes a dummy byte, which is replaced with a proper CRC7.

Then, the next 16 bytes is the first 128 bits of a 136-bit response, where the first one again has
a start bit, a transmission bit (0 for card-to-host), and reserved bits, which are always 1.
Remaining 15 bytes is the CSD register itself. (and yes, that's a 16 MB MMC card, just so you know)
The byte that we lost there is the CRC7 of the response.

### Data transfers

Again, contrary to any host controller, it doesn't handle data transmission in one go.
Instead, the command and data transfers are handled more-or-less independently.

So this means that to send data to card, one need to send the command first, and then configure
the data transmission part to send a block of data.

While to receive data from card, one need to initialize the data transmission part *first*,
then send a command, and then wait for the data to be received.
This is because the card may transmit data well before (or right when) sending the response of the command,
so it's better to prepare to early rather than too late, as otherwise it might receive wrong data.
(and likely signal a data CRC error too)

The size of a data block is configurable well from 1 byte up to 512 bytes.

### CTU

The CTU (Continuous Transfer Unit?) is used to do multiple-block transfers at once.

Presumeably this was first available in SoC series like AC520N, AC521N, etc.
which by nature of their intended application required high-bandwidth data transfers with lowest overhead
to store a bunch of upscaled (that is, from 640x480 to 1920x1088) JPEGs at 30 FPS with an 16-bit LPCM mono track at 8000 Hz,
something like this.

While chip series like AC410N, AC460N, AC690N, etc. doesn't require all that bandwidth to simply play an MP3,
so their SD controller blocks were (left off) without CTU, but in AC695N (or even in AC693N?) and newer,
their SD controllers got the CTU too.

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
| 2     | r/w | 0       | . set together with [1:0], usually 1 but might be 0 for CMD3 or CMD12  |
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
| x:0   | w   | /       | Address of the command buffer                        |

### DPTR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| x:0   | w   | /       | Address of the data buffer                           |

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

**Note:** the data transfer via CTU is finally started when this register is written
