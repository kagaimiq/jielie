# CPU cores

## 8051

An 8051-compatible core, which also has a 16-bit DSP extension put on the 0xA5 (reserved) opcode.

Might be in some connection with the Appotech's 8051-compatible core.

## OpenRISC

The OpenRISC 1000, all in its glory.
Probably this is the first 32-bit core that JieLi ever used...

Seems to be used in the AC410N series, as well as in the 'MC001' thing...

This might explain the '.or32' extension on the compiled ELF binary in the SDK, as "or32" is an old name for OpenRISC,
before they renamed it to "or1k", or something like that. -- that's an leftover!!

## Blackfin

Analog Devices' Blackfin, all in its glory.

Was used in chip series like AC460N, AC520N, etc.

This is what the pi32 arch seems to be heavily based off.

## pi32

A custom architecture, heavily based off (or inspired by?) the Blackfin.

First might be seen in the AC461N series, and from now on it the main arch they use in their chips.

[More...](pi32.md)

## pi32v2

A second version of pi32

## q32s

Q32s --- 
