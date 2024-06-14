# BR25

- Series: **AC696N** and **AC636N**, likely **AC608N** too
- CPU Core: [pi32v2](../../cpu/index.md#pi32)
- SRAM: 153.5k in total:
  * 128k of RAM0
  * 16k of RAM1
  * some more extra 1.5k following RAM1
  * 16k of icache RAM
- MaskROM: 32k
  * System boot code
  * USB bootloader, UART bootloader
  * FreeRTOS bits
  * LZ4 decompression lib
  * some other stuff
  * see the [rom listing](https://github.com/jiang20082233/AC6966B-JBD/blob/696X/SDK/cpu/br25/tools/rom.lst)
  * here's the [dump](br25_110000.bin), too (likely redundant due to existence of a listing above, though)
- Additional info:
  * [I/O function map](iomap.md)
  * [IRQ map](irq.md)
  * [Memory map](memmap.md)

--------------------------------------------------------------------------------

# AC696N

## Chip feature table

| Chip    | Package     | Flash    | DAC    |
|---------|-------------|----------|--------|
| AC6965A | QSOP24      | 4 Mbit   | stereo |
| AC6965E | QSOP24      | 4 Mbit   | mono   |
| AC6966A | QFN32 4x4mm |          | stereo |
| AC6966B | QFN32 4x4mm |          | stereo |
| AC6968A | SOP8        |          | none   |
| AC6969A | SOP16       | 2 Mbit   | stereo |
| AC6969D | SOP16       | 4 Mbit   | mono   |
| AC6969E | SOP16       | 2 Mbit   | mono   |
| AC6969H | SOP16       | 4 Mbit   |        |

## Chips

### AC6965A

- Package: QSOP24
- [Pinout diagram](../pinout-diagrams/AC6965A.svg)
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6965A%C2%A0Datasheet%C2%A0V1.0.pdf)
- Stereo DAC

### AC6965E

- Package: QSOP24
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6965E%C2%A0Datasheet%C2%A0V1.0.pdf)
- Mono DAC

### AC6966A

- Package: QFN32 4x4mm
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6966A%C2%A0Datasheet%C2%A0V1.0.pdf)
- Stereo DAC

### AC6966B

- Package: QFN32 4x4mm
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6966B%C2%A0Datasheet%C2%A0V1.0.pdf)
- Stereo DAC

### AC6968A

- Package: SOP8
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6968A%C2%A0Datasheet%C2%A0V1.0.pdf)

### AC6969A

- Package: SOP16
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6969A%C2%A0Datasheet%C2%A0V1.0.pdf)
- Stereo DAC

### AC6969D

- Package: SOP16
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6969D%C2%A0Datasheet%C2%A0V1.0.pdf)
- Mono DAC

### AC6969E

- Package: SOP16
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6969E%C2%A0Datasheet%C2%A0V1.0.pdf)
- Mono DAC

### AC6969H

- Package: SOP16

# AC636N

Audio-less versions of AC696N chips.
