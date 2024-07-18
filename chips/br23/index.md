# BR23

- Series: **AC695N** and **AC635N**
- CPU Core: [pi32v2](../../cpu/index.md#pi32)
- SRAM: 208k in total:
  * 176k of RAM0
  * 16k of "non-volatile" RAM1
  * 16k of icache RAM
  * a portion of it is used for interrupt vector table
  * first 16k of RAM0 are occupied by a data cache when e.g. using PSRAM.
- MaskROM: 10k
- Memory can be expanded with the QSPI PSRAM, up to 8 MiB.
- Additional info:
  * [I/O function map](iomap.md)
  * [Memory map](memmap.md)

--------------------------------------------------------------------------------

# AC695N

## Chip feature table

| Chip    | Package     | Flash     | DAC    |
|---------|-------------|-----------|--------|
| AC6951C | LQFP48      | 8 Mbit    | stereo |
| AC6951F | LQFP48      | 8 Mbit    |        |
| AC6951G | LQFP48      | 4 Mbit    |        |
| AC6951T | LQFP48      | 8 Mbit    |        |
| AC6952D | SSOP28      | 4 Mbit    |        |
| AC6955F | QSOP24      | 4, 8 Mbit | stereo |
| AC6955H | QSOP24      | 4, 8 Mbit |        |
| AC6956C | QFN32 4x4mm |           | stereo |
| AC6956F | QFN32 4x4mm |           | quadro |

## Chips

### AC6951C

- Package: LQFP48
- [Datasheet](http://www.lenzetech.com/public/store/pdf/jsggs/AC6951C%C2%A0Datasheet%C2%A0V1.3.pdf)
- Stereo DAC

### AC6951F

- Package: LQFP48

### AC6951G

- Package: LQFP48

### AC6951T

- Package: LQFP48

### AC6925D

- Package: SSOP28

### AC6955F

- Package: QSOP24
- [Datasheet](http://www.lenzetech.com/public/store/pdf/jsggs/AC6955F%C2%A0Datasheet%C2%A0V1.1.pdf)
- Stereo DAC

### AC6955H

- Package: QSOP24

### AC6956C

- Package: QFN32 4x4mm
- [Datasheet](http://www.lenzetech.com/public/store/pdf/jsggs/AC6956C%20Datasheet%20V1.1.pdf)
- Stereo DAC

### AC6956F

- Package: QFN32 4x4mm
- [Datasheet](https://www.lenzetech.com/public/store/pdf/jsggs/AC6956F%20Datasheet%20V1.2.pdf)
- Quadro (4 channel) DAC

# AC635N

Audio-less versions of AC695N chips, which have additional GPIOs exposed in place of audio-related pins. Otherwise they're nearly identical to their audio-enabled counterparts.
