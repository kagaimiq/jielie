# USB_KEY

The chips usually contain a Mask ROM memory where the initial boot code is located in,
which also contains the builtin USB download mode (UBOOT mode, download mode, update mode, etc.)

It can be invoked either by not letting it boot successfuly (by corrupting/erasing/disconnecting the flash)
or by sending a special signal on the USB lines, which seems to be called "USB_KEY".

## Details

The key is a 16-bit value 0x16EF (0001 0110 1110 1111), which is sent over USB with D+ being clock and D- being data.
The data is latched at the clock's rising edge, and is received MSB-first.

This is how it looks on the USB lines itself:

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

The USB download mode in the ROM depends on an external crystal (connected to BT_OSC, supposedly the RTC one works too, at least the high-frequency one),
whose frequency doesn't have to be exactly 24 MHz (for BT_OSC), as its frequency is auto-detected.

The system clock here usually becomes 48 MHz (the clock frequency required by the USB core to work properly)

So with these requirements in mind, sometimes the USB_KEY won't be possible to do on some chips which e.g. lack a crystal oscillator (pins), such as the AC608N series.
In this case, the [ISP_KEY](isp-key.md) is used to enter the USB download mode, which can configure the chip to run off the internal LRC oscillator instead of an crystal oscillator.
