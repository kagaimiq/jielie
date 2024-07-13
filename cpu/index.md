# CPU cores

## i8051

An industry-standard 8-bit MCU core, used pretty much everywhere.

The JieLi chips, however, have one outstanding addition on it: the 16-bit "DSP" extension, which adds some special features
like a 16-bit register file, a 32-bit multiply accumulator, and a 16-bit access to XDATA.

Other than that, it has pretty standard modifications to the original 8051, including dual data pointers, a separate PDATA bank register,
extended stack pointer I believe, and stuff like that.

[More info](8051.md)

## OpenRISC

Probably the first deployed 32-bit CPU architecture used in JieLi chips, as seen in, for example, the AC4100 (CD03) chip series.

In the toolchain it goes under name "mc", and apprently there is a thing called "mc001" that uses or1k.

## Blackfin

The Analog Devices Blackfin architecture derivative has been used in a number of JieLi chips such as: AC510N (DV10), AC520N (DV12), AC460N (BT15) and possibly somewhere else.

There are two variations that seem to exist: "dv10" and "dv12".
The dv10 one seems to have some custom instruction set dedicated to the 64-bit multiply-accumulation stuff, and alike.

The dv12 one adds a variant of the `LINK`/`UNLINK` instructions that formely took a numeric value representing the size of the stack allocation in bytes, but the new variants use a log2 of the size instead. Not sure why, but that's how it goes.

## pi32

A first custom-built 32-bit CPU architecture, that however takes deep inspiration from the Blackfin architecture used in the past.

This can be seen in the assembly language syntax (in old toolchains it was a traditional mnemonic syntax, but later on they switched to the "algebraic" notation similar to one that has been used by Blackfin)

On top of that, it has some features that are present for example in ARM, for example: table branches, multiple register load/store.

And as a bonus there are some stuff that seems to be exclusive to this architecture, such as: if-else blocks (imagine that!), zero-overhead loops (implemented differently than in blackfin)..

[More info](pi32.md)

## pi32v2

An evolution of the pi32 architecture, adding more DSP features like saturated arithmetics, and other SIMD-y stuff on board (don't quote me on that, not an expert on that.)

[More info](pi32v2.md)

## q32s

A severely cut-down version of pi32v2, meant to be used as a basic 32-bit CPU for simple chips.

For example it is used in the AC630N and AC632N series, which do not do any audio so they don't need such powerful and complex CPU's that do not have any real benefit for the intended application of these chips (Bluetooth Low Energy stuff)

[More info](q32s.md)

## f59

some PIC knockoff I guess

[More info](f59.md)

## f95

another PIC knockoff

[More info](f95.md)
