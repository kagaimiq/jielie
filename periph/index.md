# Peripheral blocks

## ADC

General purpose 10-bit successive approximation register (SAR) ADC.

[More info](adc.md)

## AUDIO

Integrated audio codec.

- [BR17](audio-br17.md)
- [BR21](audio-br21.md)
- [BR25](audio-br25.md) - incomplete

## ENC / PERIENC / SFCENC

A hardware scrambler for SPI0, SD0 and SFC.

[More info](enc.md)

## FM

FM radio receiver (and sometimes transmitter too)

- [BR23/BR25](fm-br23.md)

## IIC

A really basic I²C (inter-integrated circuit) bus interface.

[More info](iic.md)

## PORT

GPIO port controller

[More info](port.md)

## SD

SD/MMC card host controller.

[More info](sd.md)

## SFC

A memory-mapped SPI flash controller (interface part).

[More info](sfc.md)

## SPI

SPI bus interface.

[More info](spi.md)

## TIMER

Basic timers with PWM output capability.

| Family | Count | Resolution |
|--------|-------|------------|
| BR17   | 4     | 16-bit     |
| BR21   | 4     | 16-bit     |
| BR23   | 6     | 32-bit     |
| BR25   | 6     | 32-bit     |

[More info](timer.md)

## UART

UART serial interface.

[More info](uart.md)

## USB

- [Fullspeed USB](usb-fs.md)

# Brief

## CRC

CRC16-CCITT calculation block.

| Name | Offset | Description     |
|------|--------|-----------------|
| FIFO | 0x00   | Input byte data |
| REG  | 0x04   | CRC register    |

- Setting the `REG` to 0x6EA5 allows to modify some registers, notably: `WDT_CON` (to modify more than just the watchdog feed bit), and `MODE_CON` (to change the chip operaion mode, see [mode_det](../isp/isp/isp.md#mode_det)).
- Polynomial: 0x1021 (x16 + x12 + x5 + 1).

## RAND64

64-bit (pseudo?) random number generator

| Name | Offset | Description                |
|------|--------|----------------------------|
| R64L | 0x00   | Random number low 32 bits  |
| R64H | 0x04   | Random number high 32 bits |

# TODO

- **AES**: Advanced Encryption Standard (AES) cipher engine.
- **ALNK**: Digital audio interface (I²S protocols)
- **CTM**: Charge Time Measurement Unit
- **DMA**: Some DMA controller
- **EQ**: A hardware equalizer
- **FFT**: Fast Fourier Transform
- **GPCNT**: Gated pulse counter
- **IRFLT**: Infrared receiver filter (to suppress noise in order to keep software side of the process clean)
- **LCD**: Segment LCD controller/driver.
- **P33**: A "P33" PMU/RTC interface
- **PAP**: Parralel Active Port - a 16-bit parralel port with DMA capability.
- **PCNT**: Pulse counter 2
- **PD**: Power down thing / control interface
- **PLCNT**: Pulse counter
- **PLED**: Dedicated PWM timers for LEDs
- **PLNK**: PDM link
- **PSRAM**: QSPI PSRAM controller.
- **MCPWM**: Motor Control PWM. An advanced PWM timer.
- **NFC**: NFC interface
- **RDEC**: Rotary incremental encoder decoder
- **SBC**: Bluetooth SBC codec
- **SPDET**: Motor Speed Detection
- **SRC**: Sample Rate Converter
- **SS**: S/PDIF slave
- **IRTC**: Internal RTC interface.
