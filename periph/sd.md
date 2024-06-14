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
for a 48 or 136-bit response.

Only first 128 bits of response is stored in the buffer, which means that we are loosing the CRC7 field, which is more useful than the first 8 bits which
usually doesn't contain any useful data, so the conventional hosts usually store the last 128 bits to be able to still fit into four 32-bit wide registers.

Here's an example of the buffer contents on a SEND_CSD (CMD9) command with a 136-bit response:
```
49 00 01 00 00 00
3f 8c 0e 01 2a 0f f9 81 e9 f6 d9 01 e1 8a 40 00
```

The first byte is the data sent out to the card, where the first byte contains the start bit (alwasys 0), the transmission bit (1 for host-to-card), and the command opcode (CMD9).
The next four bytes is the argument, which is 0x00010000 in this case (the top 16 bits contain the card address to read the CSD from).
Then the last byte is the dummy byte where the valid CRC7 is inserted by the hardware.

Next goes 16 bytes (128 bits) of the 136-bit response, with the first byte being useless as it doesn't contain any useful information - just a start bit (0),
a transmission bit (0 for card-to-host), and reserved bits.. And the next 15 bytes is the CSD itself. (yes, that's an 16 MB MMC card)

Here's another example, this time on a READ_SINGLE_BLOCK (CMD17) command with a 48-bit response:
```
51 00 00 72 00 00
11 00 00 09 00 67
```

The first 6 bytes means the same as before - CMD17, argument 0x00007200, dummy CRC..

Next goes 6 bytes of the 48-bit response, where the first byte now carries the command code (per protocol),
4 bytes of response (0x00000900) and a CRC7 of the response (this time we're not loosing it!)

### Data transfers

Again, contrary to any usual host, which handle the data transfers right after you write into a command register,
this is not the same.

The command and data transfer parts are more-or-less independent, and so they're setup independently too.

So, to send data to card you need to send a command first, and then setup the data transfer block to send data.

But to receive data from card you need to setup the data transfer block *first*, then send the command, and finally wait for data to arrive.
This is because card may transmit data well before (or right when) sending a (successful) response to command.

### CTU

The CTU (Continuous Transfer Unit?) is used to do multiple-block transfers at once.

While chip series like AC410N, AC460N, AC690N, etc. didnt't require that much bandwidth to simply play an MP3,
their SD hosts were without the CTU, and thus to do multiblock transfers needed to be made separately. (or they're not made at all)
However starting with AC695N (or even AC693N?) the SD hosts now include the CTU.

Presumeably this was first available in SoC series like AC520N, AC521N, etc.
which by nature of their intended application required high bandwidth transfers with lowest overhead
to store a bunch of upscaled JPEGs at 30 FPS with an 16-bit LPCM mono track at 8000 Hz, something like this.

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
| 9:8   | r/w | 0       | Fire data transfer (0 = nop, 1 = send, 2 = receive)  |
| 7     | r   | 0       | Command interrupt pending                            |
| 6     | w   | /       | Clear pending command interrupt                      |
| 5     | r   | 0       | Command timed out?                                   |
| 4     | r/w | 0       | ?? set to 1, cleared after cmd was xferred           |
| 3     | r   | 0       | Command CRC error?                                   |
| 2     | r/w | 0       | ? set together with [1:0], usually 1 but on CMD7 or CMD12 it's set to 0 |
| 1:0   | r/w | 0       | Fire command transfer (0 = nop, 1 = 48-bit resp, 2 = 136-bit resp, 3 = no resp) |

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
| x:2   | w   | /       | Address of the command buffer                        |

### DPTR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| x:2   | w   | /       | Address of the data buffer                           |

### CTU_CON

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 10    | r/w | 0       | ? set together with [9:8] - always 1                 |
| 9:8   | r/w | 0       | Fire data transfer (0 = nop, 1 = send, 2 = receive)  |
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
