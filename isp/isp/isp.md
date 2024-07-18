# ISP

The ISP (In-System Programmer) protocol was used to burn the OTP PROM in early JieLi chips, like AC209N, AC309N, AC109N, etc.

But in the current flash-based chips, this protocol is merely used to upload a special UART bootloader that is used for the rest of the work. Another use of this protocol in such chips is the [ISP_KEY](isp-key.md) bootloader enter method.

## Signals

The ISP formely consisted of three signals: ISP_CLK (clock), ISP_DIN (data to chip) and ISP_DOUT (data from chip).

On chips since maybe BR20 or BR21 (v2/v3 ISP protocols) the DIN and DOUT signals share the same physical pin, allowing it to be fully mapped onto the pins on the USB port (USB_DP being clock and USB_DM being data).

The data is sampled by the chip on the falling edge of the clock, and is updated by the chip on the rising edge of the clock.
The data is transferred in the MSB-first bit order.

## MODE_DET

The "MODE_DET" is reponsible of determining the mode the chip will run in.
By default the chip runs in the normal mode, i.e. ISP interface inactive, clocking works as normal and the CPU reset vector is located at the location of the Mask ROM.

But if it senses a special signal being sent on the signals of the ISP interface, it will instead transfer the chip into the "test mode", which has ISP interface enabled, chip is clocked from the ISP clock signal and the CPU is kept halted, until a "start CPU" command is received over ISP which will start the CPU at the specific address where the code would've been loaded via the ISP interface prior to that.

The `MODE_CON` register contains the current run mode of the chip, where '0' is "normal" and '1' is "test mode".

This register can be written to override the run mode, which is typically used by the ISP blobs to get out of the test mode so that the chip clocking can work normally, instead of requiring ISP clock signal to be present all the time, as well as having the related ISP pins being free of the ISP function to be used for other purposes (e.g. an UART interface or USB).
This is why also you need to send a bunch of clock signals after sending the "start CPU" command.

This register is usually locked of any changes until a special magic value (usually 0x6EA5) is written to the `CRC_REG` register.

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
- If above succeed, you can now work with ISP, otherwise go to Step 2 and do it again. You can add a timeout and e.g. try all over again from step 1 or just fail immediatly.

### Running code

- For each word of data send a "RAM write" command with the data word itself ('word' means a frame word, not a CPU word), followed by an "RAM advance" command.
- After the data has been loaded, send the "start CPU" command to let CPU go.
- Send a bunch of clocks on the ISP clock line to let CPU run until the code does something like resetting `MODE_CON` in order to let it run without an external "test" clock.

## ISP frames

The frames are always sized as a multiple of 8 bits, which is accomplished by putting padding bits between the opcode and data (in chip-to-host packets) or at the end of a frame (in host-to-chip and basic command packets).

Depending on the ISP variant, the size of a data word transferred in a frame is given below:

- v1 protocol: 8-bit data words (1 byte)
- v2 protocol: 64-bit data words (8 bytes)
- v3 protocol: 32-bit data words (4 bytes)

### No-data command packet

A simple command packet (carrying no data) carries only a 5-bit opcode together with 11 padding bits, making it 16 bits long in total.

```
DIN  __oooooooooo________________________
CLK  __-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-___
       \________/\____________________/
         opcode           pad
```

This can be thought as a 8-bit host-to-chip data packet where the data is ignored. (or in reverse)

### Host-to-chip data packet

For a host to chip packet, the frame begins with 5 bits of the opcode, immediatly followed by the data bits and finally terminated with 3 padding bits.

```
DIN  __ooooooooooDDDDDDDD....DDDD________
CLK  __-_-_-_-_-_-_-_-_-_....-_-_-_-_-___
       \________/\______________/\____/
         opcode      data in      pad
```

### Chip-to-host data packet

For a chip to host packet, the frame begins with 5 bits of the opcode, followed by 3 padding bits and finally followed by data bits coming out of the chip.

```
DIN  __oooooooooo______________________________
DOUT __________________DDDDDDDD....DDDD__
CLK  __-_-_-_-_-_-_-_-_-_-_-_-_....-_-___
       \________/\____/\______________/
         opcode   pad      data out
```

## ISP commands

### Read data buffer

- Opcode: 0x07
- Type: chip-to-host

This command reads the data from a data buffer, which can be populated with commands
such as "read chip ID", and "echo", and some others.

### RAM address advance

- Opcode: 0x12
- Type: no data

This command advances to a next word in the RAM to which data has been written with a "RAM write" command.

### Echo

- Opcode: 0x14
- Type: host-to-chip

This command writes data into the data buffer, which can be accessed with the "read data buffer" command.

This command seem to have disappeared in the variant 3 protocol.
It usually has been used to check if the chip has entered the ISP mode successfully by writing some data into it and then reading it back.

### RAM write

- Opcode: 0x18
- Type: host-to-chip

This command writes a word (meaning a word size used in the data portion of the frame) into RAM portion that is also where the "start CPU" command will start execution at.

This command does not advance the write pointer, instead this is done with a separate "RAM advance" command.

### Start CPU

- Opcode: 0x19
- Type: no data

This command starts the CPU.

### Read another chip ID

- Opcode: 0x1E
- Type: no data

This command loads some other chip ID value (no clue what it is) into a data buffer,
which can be read out with an "read data buffer" command.

### Read chip ID

- Opcode: 0x1F
- Type: no data

This command loads the chip ID value into a data buffer, which can be read out with an "read data buffer" command.

The list of chip ID's can be found below, or in [this page](../../misc/chipid.md).

## Per-chip specifics

| Family | Variant | Load/Exec address  | Chip ID |
|--------|---------|--------------------|---------|
| CD02   | v1      | XRAM/0xc000        | 0x20    |
| BR17   | v1      | 0x0008000          | 0x53    |
| BR18   |         | 0x0100000          |         |
| BR20   | v2      | 0x0001000          |         |
| BR21   | v3      | 0x0001000          | 0x5A    |
| BR23   | v3      | 0x0010000          | 0x5E    |
| BR25   | v3      | 0x0010000          | 0x5F    |
| BD19   | v3      | 0x0000000          |         |
