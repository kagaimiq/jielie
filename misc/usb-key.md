# USB_KEY

The chips usually contain a Mask ROM memory where the initial boot code is located in,
which also contains the builtin USB download mode (UBOOT mode, download mode, update mode, etc.)

It can be invoked either by not letting it boot successfuly (by corrupting/erasing/disconnecting the flash)
or by sending a special signal on the USB lines, which seems to be called "USB_KEY".

## Details

The key is a 16-bit number 0x16EF (0001 0110 1110 1111), which is sent over USB with D+ being clock and D- being data.
The data is latched at the clock's rising edge, and is received MSB-first.

This is how it looks:

```
D+ _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-...
D- ______--__----__------__--------...
```

This sequence is sent repeadetly until the chip acknowledges it by pulling both lines low for at least 2ms:

```
D+ ..._-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-___________________________-_-_-
D- ...______--__----__------__--------___________________________-----

      \______________________________/\_________________________/
            valid 0x16EF                  chip's acknowledge
                            (not to scale)
```

Basically in this time the chip inhibits any furhter reception of the key
before it stops reception of the key and initializes the USB interface.

The dongle that sends this key should also stop sending this key and proceed to switch the USB to the PC side.

The clock frequency is usually around 50 kHz, but there isn't really any strict requirements other than
it should be not too fast as the reception is done in software (either in the timer interrupt or in a loop).

### Response considerations

The chip's response to the key is pulling both lines to ground, which may cause problems
when you detect it by using your MCU's builtin pullups, and you chose not to switch power to the chip.
(so you send the key to the powered off chip and then apply power to it)

Basically the issue is that when you apply this to the chip that is not powered, it will suck the power
from the pullups through an internal diode to VDDIO and so the voltage may fall below the threshold
where the pin will report that it is in LOW state.

So either consider using more strong pullups or apply power to the chip before sending the key (by using a power switch).

## Enviroment

To be able to use the USB download mode this way, you should have an XTAL connected to the chip,
whose frequency is autodetected so it doesn't have to be an 24 MHz crystal.

The system clock becomes 48 MHz (the minimum required for the USB core to work)

So with these requirements, in some cases (e.g. crystal-less chips like AC608N) you should use some other
method like [ISP_KEY](isp-key.md)
