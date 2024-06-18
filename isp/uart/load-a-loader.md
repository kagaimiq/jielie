# Loading the loader

When the chip has entered the UART bootloader in the ROM, the only thing we can do at that point is to send a "loader" binary
that implements the rest of the functionality.

First of all, the UART interface is initialized at 9600 baud (8N1), and the following is sent to the chip:

`55 AA -- -- -- aa:aa:aa:AA ll:ll:ll:LL cc:CC rr:RR GG TT -- -- -- `

where:
- `aa:aa:aa:AA` → Load/execution address
- `ll:ll:ll:LL` → Data length
- `cc:CC` → CRC16 of data
- `rr:RR` → CRC16 of the previous 10 bytes (addr/len/crc)
- `GG` → Flags (b1 = the data is scrambled with CrcDecode, the usual form of the shipped UART loaders)
- `TT` → baudrate, in 10k baud units. If zero, it defaults to 100000 baud.

This is how the ROM parses it, three missing bytes at the start surely are some kind of opcode bytes, but they're not checked at all.

Shortly after, if everything went well, the chip will reply with the following reply:

`55 AA 01 20 22`

Next you change the speed to one you specified in the initial packet, and send the loader binary itself.

The loader binary starts executing with the pointer to the received packet data above being passed in the first parameter.

The stock loaders, for some reason, set the UART speed to the half of the one we sent the loader binary with (i.e. treat the baudrate field in the initial packet as a 5k baud units), and at that speed send a reply packet to indicate that the loader has been loaded successfully.

The rest of the process is yet to be discovered.

-----

```
on <uart_isr>
 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15
 55 AA -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

on <uart_cmd_verify>
 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15
 -- -- -- -- -- DD-DD-DD-DD-DD-DD-DD-DD-DD-DD cc-CC -- -- -- -- --

DD... = data
cc-CC = CRC16 of data

on <uart_recv_loader>
 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15
 -- -- -- -- -- aa-aa-aa-AA ll-ll-ll-LL cc-CC -- -- GG RR -- -- --

aa-aa-aa-AA = load&execute address
ll-ll-ll-LL = data length
cc-CC = CRC16 of data
GG = flags [b1 = encrypted data]
RR = uart baudrate on data reception (in 10000 baud units, if 0 defaults to 10 -> 100000 baud,
                                      and so the baudrate has to be in multiples of 10k baud)

* the called loader receives a pointer to the received command as an argument (in r0 register)
```
