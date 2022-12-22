# CPU cores

## 8051

An 8051-compatible core, actually might be in some connection with
the Appotech's (Buildwin's) 8051 core...

e.g. AX225 USB Card reader chip blob has an 8051 core that has the XDATA and CODE spaces
connected together, and the 8051's internal RAM (DATA/IDATA) is actually mapped into the
offsets 580..5FF and 500..57F (yes, the first 128 bytes are put into high part, and then goes into lower part for some reason)
-- not mentioning that the B register is absent, and so the MUL/DIV instructions are essentailly a NOP...

## OpenRISC

The OpenRISC!

Seems to be present in the AC4100 SoC... so probably this is *the* first 32-bit MCU core they used.

This might explain why the generated ELF binary ends with "or32" (or32 is the old name for OpenRISC, now it's called "or1k")
What a leftover...

## Blackfin

The Analog Device's Blackfin, in its glory.

## Pi32

Their own arch, which is heavily based off (inspired by?) the Blackfin.

I thought that they based off the ARM (thumb) but actually it's not...

[More...](pi32.md)

### Pi32v2

A second version, introduced the 48-bit instructions (i.e. 3x 16-bit words), which can hold
an 32-bit constant, eliminating the need for the load low/high instructions (a leftover from Blackfin).
