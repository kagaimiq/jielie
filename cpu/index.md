# CPU cores

## 8051

An 8051-compatible core, which also has a 16-bit DSP-like extension mapped to the opcode 0xA5 (reserved in plain 8051)

Might be in some connection with the Appotech's 8051-compatible core.

[More info](8051.md)

## OpenRISC

The OpenRISC 1000 (or1k), all in its glory.

It might be the first 32-bit CPU core that JieLi has ever used (and deployed).

This architecture can be seen used e.g. in the AC4100 (CD003) chip.

## Blackfin

Analog Devices' Blackfin, all in its glory.

The vendor's toolchain package provides two separate compilers: dv10 and dv12.
So either there are some custom additions and changes to this architecture, or idk.

At least, they both produce an ELF file which tells that this is the "Analog Devices Blackfin" machine,
and the flags are zero in both cases.

## pi32

The JieLi's custom architecture to be Independent and Free /as in freedom/!!

Seemingly this is heavily based off (or inspired by) the Analog Devices' Blackfin.
This can be seen in the instruction encoding scheme (although I've thought that this was like the ARM Thumb.. but no!),
the algebraic notation in the assembly language, etc!

[More info](pi32.md)

## pi32v2

Second generation of the pi32 architecture.

[More info](pi32v2.md)

## q32s

[More info](q32s.md)

## f59

[More info](f59.md)

## f95

[More info](f95.md)
