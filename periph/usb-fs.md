# Full-speed USB interface

The Full-speed USB interface in JL chips has a bog-standard register interface ripped off the Mentor Graphics' MUSB OTG controller,
with a slightly reordered registers and a custom DMA thing botched on top of it.

It supports a dual-role operation, which in context of these chips mean: ability to plug a USB drive full of mp3's and ability to use the chip as a sound card / a (slow) card reader / remote control. In proper speak, this means it can work as a host and a device. anyway..

## Interrupts

Two interrupts are coming out of this block: the SIE interrupt and the SOF interrupt, which are coming to separate CPU interrupt inputs.

The first one is set whenever the SIE (serial interface engine, presumeably) reports an interrupt in IntrUSB/IntrTx/IntrRx.
It is cleared by reading the USB_CON0 register.

The latter one is set whenever a SOF packet comes on the USB bus.
It is cleared by writing into the `CLR_SOFP` bit in USB_CON0.

## DMA buffers

The data transfer between the chip's memory and the USB bus is performed through
a set of buffers located in the system memory of the chip, which is then accessed
by the built-in DMA engine of the USB brigde and the corresponding FIFO's on the SIE side. (it's a guess)

| Endpoint | BR17 | BR21 | BR25 |
|----------|------|------|------|
| EP0      | 64   | 64   | 64   |
| EP1 In   | ?    | 64   | ?    |
| EP1 Out  | ?    | 64   | ?    |
| EP2 In   | ?    | 64   | ?    |
| EP2 Out  | ?    | 1024 | ?    |
| EP3 In   | ?    | 1024 | ?    |
| EP3 Out  | ?    | ?    | ?    |
| EP4 In   |      |      | ?    |
| EP4 Out  |      |      | ?    |



## Host registers

| Offset | BR17                  | BR21                  | BR25                  |
|--------|-----------------------|-----------------------|-----------------------|
| 0x00   | [IO_CON](#io_con0)    | [IO_CON0](#io_con0)   | [CON0](#usb_con0)     |
| 0x04   | [CON0](#usb_con0)     | [CON0](#usb_con0)     | [CON1](#usb_con1)     |
| 0x08   | [CON1](#usb_con1)     | [CON1](#usb_con1)     | [EP0_CNT](#epx_cnt)   |
| 0x0C   | [EP0_CNT](#epx_cnt)   | [EP0_CNT](#epx_cnt)   | [EP1_CNT](#epx_cnt)   |
| 0x10   | [EP1_CNT](#epx_cnt)   | [EP1_CNT](#epx_cnt)   | [EP2_CNT](#epx_cnt)   |
| 0x14   | [EP2_CNT](#epx_cnt)   | [EP2_CNT](#epx_cnt)   | [EP3_CNT](#epx_cnt)   |
| 0x18   | [EP3_CNT](#epx_cnt)   | [EP3_CNT](#epx_cnt)   | [EP4_CNT](#epx_cnt)   |
| 0x1C   | [EP0_ADR](#ep0_adr)   | [EP0_ADR](#ep0_adr)   | [EP0_ADR](#ep0_adr)   |
| 0x20   | [EP1_TADR](#epx_tadr) | [EP1_TADR](#epx_tadr) | [EP1_TADR](#epx_tadr) |
| 0x24   | [EP1_RADR](#epx_radr) | [EP1_RADR](#epx_radr) | [EP1_RADR](#epx_radr) |
| 0x28   | [EP2_TADR](#epx_tadr) | [EP2_TADR](#epx_tadr) | [EP2_TADR](#epx_tadr) |
| 0x2C   | [EP2_RADR](#epx_radr) | [EP2_RADR](#epx_radr) | [EP2_RADR](#epx_radr) |
| 0x30   | [EP3_TADR](#epx_tadr) | [EP3_TADR](#epx_tadr) | [EP3_TADR](#epx_tadr) |
| 0x34   | [EP3_RADR](#epx_radr) | [EP3_RADR](#epx_radr) | [EP3_RADR](#epx_radr) |
| 0x38   |                       | [IO_CON1](#io_con1)   | [EP4_TADR](#epx_tadr) |
| 0x3C   |                       |                       | [EP4_RADR](#epx_radr) |

Note: in 'BR25' variant the IO_CON registers have been moved into the GPIO register section.

### USB_CON0

USB control register 0.
_Width: 32-bit_

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:19 |      |            |         |                        |
| 18    | R/W  | LOWP_MD    | b0      | Low power mode (0: enable, 1: disable). When disabled, the system clock should be at 48 MHz or more. |
| 17    | R    | SE_DP      | b0      | Single-ended D+ status (0: low, 1: high) |
| 16    | R    | SE_DM      | b0      | Single-ended D- status (0: low, 1: high) |
| 15    | R    | CHKDPO     | b0      | Result of an D+ pulldown check |
| 14    | R    | SIE_PND    | b0      | SIE interrupt pending  |
| 13    | R    | SOF_PND    | b0      | SOF interrupt pending  |
| 12    | W    | CLR_SOFP   | b0      | Clear a pending SOF interrupt |
| 11    | R/W  | SIEIE      | b1      | SIE interrupt enable   |
| 10    | R/W  | SOFIE      | b0      | SOF interrupt enable   |
| 9     | R/W  | PDCHKDP    | b0      | Enable check for an externally attached pulldown on D+ |
| 8     | R/W  | LATSEL     | b0      | latency select ?       |
| 7     | R/W  |            | b0      |                        |
| 6     | R/W  | USB_TEST   | b0      |                        |
| 5     | R/W  | VBUS       | b0      | VBUS status ?          |
| 4     | R/W  | CID        | b1      | USB role (0: host, 1: device) |
| 3     | R/W  | TM1        | b0      | short connect timeout enable? |
| 2     | R/W  | USB_NRST   | b0      | USB core reset signal (active low) |
| 1     | R/W  |            | b0      |                        |
| 0     | R/W  | PHY_ON     | b0      | USB PHY enable         |

### USB_CON1

USB control register 1.
_Width: 16-bit_

| Bits | Type | Name       | Default | Description |
|------|------|------------|---------|-------------|
| 15   | R    | MC_ACK     | b0      | Access done flag |
| 14   | W    | MC_RNW     | b0      | Access type (0: Write, 1: Read) |
| 13:8 | W    | MC_ADR     | h00     | Register address |
| 7:0  | R/W  | MC_DAT     | h00     | Register data    |

After a write to this register, an access to a specified MC register is performed.
After it has completed, the `MC_ACK` bit will be set to '1', and if it was a read access, the `MC_DAT` is going to be populated with the read data.

### IO_CON0

USB I/O control register 0.
_Width: 16-bit_

| Bits  | Type | Name        | Default | Description                 |
|-------|------|-------------|---------|-----------------------------|
| 15:13 |      |             |         |                             |
| 12    | R/W  | USB_SR      | b0      | Slew rate enable thing      |
| 11    | R/W  | USB_IO_MODE | b1      | Enable USB pins as GPIOs?   |
| 10    | R/W  | DMDIE       | b1      | USB_DM digital input enable |
| 9     | R/W  | DPDIE       | b1      | USB_DP digital input enable |
| 8     | R    | PM          | b0      |                             |
| 7     | R/W  | DMPU        | b1      | USB_DM pullup enable        |
| 6     | R/W  | DPPU        | b0      | USB_DP pullup enable        |
| 5     | R/W  | DMPD        | b0      | USB_DM pulldown enable      |
| 4     | R/W  | DPPD        | b0      | USB_DP pulldown enable      |
| 3     | R/W  | DMIE        | b1      | USB_DM direction (0: output, 1: input) |
| 2     | R/W  | DPIE        | b1      | USB_DP direction (0: output, 1: input) |
| 1     | R/W  | DMOUT       | b0      | USB_DM output state         |
| 0     | R/W  | DPOUT       | b0      | USB_DP output state         |

Note: the pulldown resistance on both D+ and D- is 15 kOhm.
The D+ pullup resistance is 1.5 kOhm, and the D- pullup resistance is around 180 kOhm.

### IO_CON1

USB I/O control register 1.
_Width: 16-bit_

| Bits | Type | Name        | Default | Description                 |
|------|------|-------------|---------|-----------------------------|
| 15:2 |      |             |         |                             |
| 1    | R    | DMIN        |         | USB_DM input state          |
| 0    | R    | DPIN        |         | USB_DP input state          |

### EPx_CNT

Endpoint x write count.
_Width: 16-bit_

When this register is written, the corresponding endpoint's TX FIFO
is going to be fed with the data coming from a buffer pointed by
the EPx_TADR (or EP0_ADR in case of EP0).

### EP0_ADR

Endpoint 0 buffer address.
_Width: 32-bit_

There is only a single address register for endpoint 0 that is used both for TX and RX,
but otherwise the behavior is the same as in the TADR/RADR registers for other endpoints.

### EPx_TADR

Endpoint x TX buffer address.
_Width: 32-bit_

This register holds the address to a buffer from which the data is going to be transferred by the DMA into a corresponding endpoint's TX FIFO upon writing the EPx_CNT register that specifies how much data is going to be transmitted.

### EPx_RADR

Endpoint x RX buffer address.
_Width: 32-bit_

Whenever data comes into a specified endpoint's RX FIFO the data is going to be written into the buffer pointed by this register.

The write pointer seems to be reset whenever the RX FIFO is flushed by setting the `FlushFIFO` bit in the `RxCSRL` SIE register.

## SIE registers

The register set accessed indirectly through `USB_CON1` register:

| Address | (MUSB) | Name              |
|---------|--------|-------------------|
| 0x00    | 0x00   | FAddr             |
| 0x01    | 0x01   | Power             |
| 0x02    | 0x02   | IntrTx1           |
| 0x03    | 0x03   | IntrTx2           |
| 0x04    | 0x04   | IntrRx1           |
| 0x05    | 0x05   | IntrRx2           |
| 0x06    | 0x0A   | IntrUSB           |
| 0x07    | 0x06   | IntrTxE1          |
| 0x08    | 0x07   | IntrTxE2          |
| 0x09    | 0x08   | IntrRxE1          |
| 0x0A    | 0x09   | IntrRxE2          |
| 0x0B    | 0x0B   | IntrUSBE          |
| 0x0C    | 0x0C   | Frame1            |
| 0x0D    | 0x0D   | Frame2            |
| 0x0E    | 0x0E   | Index             |
| 0x0F    | 0x60   | DevCtl            |
| 0x10    | 0x10   | TxMaxP            |
| 0x11    | 0x12   | CSR0 / TxCSRL     |
| 0x12    | 0x13   | TxCSRH            |
| 0x13    | 0x14   | RxMaxP            |
| 0x14    | 0x16   | RxCSRL            |
| 0x15    | 0x17   | RxCSRH            |
| 0x16    | 0x18   | Count0 / RxCount1 |
| 0x17    | 0x19   | RxCount2          |
| 0x18    | 0x1A   | TxType            |
| 0x19    | 0x1B   | TxInterval        |
| 0x1A    | 0x1C   | RxType            |
| 0x1B    | 0x1D   | RxInverval        |

The function of these registers is what you'd expect from a MUSB-style interface.
For more information refer to the MUSBMHDRC documentation...
