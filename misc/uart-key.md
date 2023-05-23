# UART_KEY

A MaskROM in some chips (like BR23, BR25, etc.) may contain the UART download mode
as an alternative to the USB download mode (or as an only option, like in SH55)

## Details

The key is a 16-bit number 0x68AF, which is sent over the UART line (e.g. PB5)..

It is weird so it's TODO

The chip acknowledges this by pulling the UART line high
