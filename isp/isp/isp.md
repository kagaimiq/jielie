# ISP

The ISP (In-System Programmer) protocol was used to burn the OTP PROM in early JieLi chips, like AC209N, AC309N, AC109N, etc.

But in the current flash-based chips, this protocol is merely used to upload a special UART bootloader that is used for the rest of the work. Another use of this protocol in such chips is the [ISP_KEY](isp-key.md) bootloader enter method.

## Signals

The ISP formely consisted of three signals: ISP_CLK (clock), ISP_DIN (data to chip) and ISP_DOUT (data from chip).

On chips since maybe BR20 or BR21 (v2/v3 ISP protocols) the DIN and DOUT signals share the same physical pin, allowing it to be fully mapped onto the pins on the USB port (USB_DP being clock and USB_DM being data).

The data is sampled by the chip on the falling edge of the clock, and is updated by the chip on the rising edge of the clock.
The data is transferred in the MSB-first bit order, the protocol itself is byte-oriented.

## Entering ISP

- Step 1: Apply power to the chip
- Step 2: Send an appropriate MODE_DET key:
  * First of all a 0xFF is sent over (8 bits); then according to the specific protocol variant:
  * For v1 protocol: 0x6A58 (16 bits)
  * For v2 protocol: 0x81F9A8 (24 bits)
  * For v3 protocol: 0x01F9A8 (24 bits)
- Step 3: Send `00 00 00 00 00 A8 00 00`
- Step 4: Try to identify the chip
  * For v1 protocol: Send a byte to an echo register and read it back. If the result matches you're good to go.
  * For v2 protocol: Send 8 bytes of data to an echo register and read it back. If the result matches you're good to go.
  * For v3 protocol: .. there seems to be no echo register anymore so the only way of doing that is to read the chip ID and check if the read value makes sense i.e. not 0x00 or 0xFF, and only low 8 bits are populated, among other measures.
- If above succeed, you can now work with ISP, otherwise go to Step 2 and do it again. You can add a timeout and e.g. go to Step 1 to power cycle the chip or just immediately report a failure.

## ISP frames

The ISP frame format carries a 5-bit opcode together with N bits of data (depending on the ISP protocol variant, see below)

- v1 protocol: 8-bit data (1 byte)
- v2 protocol: 64-bit data (8 bytes)
- v3 protocol: 32-bit data (4 bytes)

### Simple command packet

A simple command packet (carrying no data) carries only a 5-bit opcode together with 11 padding bits.

```
DIN  __oooooooooo________________________
CLK  __-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-___
       \________/\____________________/
         opcode           pad
```

This can be though as a 8-bit host-to-chip data packet where the data is ignored. (or in reverse)

### Host-to-chip data packet

For a host to chip packet, the frame begins with 5 bits of the opcode, immediatly followed by the data bits and finally terminated with 3 padding bits.

```
DIN  __ooooooooooDDDDDDDD....DDDD________
CLK  __-_-_-_-_-_-_-_-_-_....-_-_-_-_-___
       \________/\______________/\____/
         opcode      data out     pad
```

### Chip-to-host data packet

For a chip to host packet, the frame begins with 5 bits of the opcode, followed by 3 padding bits, finally followed by data bits coming out of the chip.

```
DIN  __oooooooooo______________________________
DOUT __________________DDDDDDDD....DDDD__
CLK  __-_-_-_-_-_-_-_-_-_-_-_-_....-_-___
       \________/\____/\______________/
         opcode   pad      data in
```

## ISP commands

Here is the summary of the ISP opcodes:

- 0x07: Read the data buffer
- 0x12: Advance to a next word in RAM
- 0x14: Send data into the buffer (echo)
- 0x18: Write a word into RAM
- 0x19: Start the CPU
- 0x1E: Read another chip ID
- 0x1F: Read the chip ID

