# UART_KEY

The Mask ROM in some chips may contain a UART bootloader alongside the USB bootloader (or as an only option, like in SH55).

The signal used to enter the bootloader seems to be called "UART_KEY".

## Details

The key is a 16-bit number 0x68AF (0110 1000 1010 1111),
which is sent over the UART line (usually on the PB5 pin).

The transmission begins with a start bit, whose pulse doesn't matter as long as the chip can pick up both edges of it. The thing that matters is its period -- it should be maintained throughout the whole key transmission.

Then the 16 bits of the key above is sent MSB-first, with the '0' bit signalled by a 1/5th periods pulse, and a '1' bit is signalled with a 4/5th periods pulse.

The sequence ends with pulling the line high to complete the last sent bit (the processing is done on the rising edges),
and finally the acknowledge from the chip is sampled.
If the chip drives the line high, it means that the chip has acknowledged the key reception and it now proceeds to enter the UART bootloader.

![UART key signal example](uart_key.png)

*(yes I did just stick the UART wire into the input of a sound card to sample this signal (hence you can clearly see the Audacity's interface), by the way I've generated this key signal using the RP2040 MCU, utilizing the PIO!)*
