# Peripheral blocks

## IIC

I<sup>2</sup>C bus controller

[More info](iic.md)

## SPI

SPI bus controller

[More info](spi.md)

## UART

UART interface controller

[More info](uart.md)

## ENC

A very basic encryption/obfuscation engine for SD0, SPI0 and SFC.

Also called "PERIENC" and "SFCENC" (which are dedicated to SD0/SPI0 and SFC respectively).

[More info](enc.md)

## SFC

Serial/SPI Flash Controller

[More info](sfc.md)

## SD

SD/MMC host controller

| Family | Variant |
|--------|---------|
| BC51   | 1       |
| BR17   | 1       |
| BR21   | 1       |
| BR23   | 2       |
| BR25   | 2       |
| ...    | tbd     |

[More info](sd.md)

---------------------------------------------------------

## CRC

CRC16 calculator

| Name | Offset | Description     |
|------|--------|-----------------|
| FIFO | 0x00   | Input byte data |
| REG  | 0x04   | CRC register    |

- If the REG is set to 0x6EA5, then you can modify the WDT_CON register in SYSCFG.
- Polynomial it uses is 0x1021 (x16 + x12 + x5 + 1).

## RAND64

64-bit (pseudo-?) random number generator

| Name | Offset | Description                |
|------|--------|----------------------------|
| R64L | 0x00   | Random number low 32 bits  |
| R64H | 0x04   | Random number high 32 bits |

---------------------------------------------------------

## PORT

GPIO port controller

## TIMER

Timer!!

## PAP

Parralel Active Port

## LCD

LCD controller

## AUDIO

Audio codec (DAC+LADC)

## ALNK

I<sup>2</sup>S interface

## NFC

NFC interface

## USB

USB interface

## ADC

General purpose SAR ADC

## PLCNT

Pulse counter

## PCNT

Pulse counter 2

## GPCNT

gated pulse counter

## PD

Power down thing

## CTM

Charge Time Measurement Unit

## SS

S/PDIF slave

## RDEC

Rotation (quadrature) decoder

## PLNK

PDM link

## SPDET

Motor Speed Detection

## AES

AES engine

## FFT

Fast Fourier Transform algorithm

## EQ

Equalizer

## SRC

Sample Rate Converter

## FM

FM radio receiver (and sometimes transmitter too)

## MCPWM

Motor Control PWM

## IRFLT

IR receiver/decoder/etc

## P33

P33 PMU interface

## DMA

DMA controller

## SBC

SBC codec

## PLED

PWM LED

## PSRAM

PSRAM controller
