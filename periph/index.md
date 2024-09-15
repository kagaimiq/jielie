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

# Miscellaneous

## CRC

CRC16-CCITT calculation block.

| Name | Offset | Description     |
|------|--------|-----------------|
| FIFO | 0x00   | Input byte data |
| REG  | 0x04   | CRC register    |

- Setting the `REG` to 0x6EA5 allows to modify some registers, notably: `WDT_CON` (to modify more than just the watchdog feed bit), and `MODE_CON` (to change the chip operaion mode, see [mode_det](../isp/isp/isp.md#mode_det)).
- Polynomial: 0x1021 (x16 + x12 + x5 + 1).

## EFUSE_CON

A single register providing access to the efuse bits and allowing to burn efuse bits as well.

| Bits  | Type | Name | Default | Description            |
|-------|------|------|---------|------------------------|
| 15    | R    |      |         | Bit read value (0: 'open', 1: 'short') |
| 14:10 |      |      |         |                        |
| 9     | R/W  |      |         | Read enable            |
| 8     | R/W  |      |         | Burn enable            |
| 7:6   |      |      |         |                        |
| 5     | R/W  |      |         | Bank 2 enable          |
| 4     | R/W  |      |         | Bank 1 enable          |
| 3:0   | R/W  |      |         | Bit select             |

## POWER_CON

| Bits  | Type | Name    | Default | Description            |
|-------|------|---------|---------|------------------------|
| 7:5   | R    | RSRC    | ???     | Reset source (0: power-on reset, 1: VCM reset, 2: key reset, 3: LVD reset, 4: watchdog reset, 5: soft reset) |
| 4     | W    | SRST    | b0      | Perform a system soft reset |
| 3     | R/W  | SSMODE  | b0      | Sleep/standby recovery mode (0: wait 8ms before waking up, 1: wake up immediatly) |
| 2     | W    | SLEEP   | b0      | Enter sleep mode       |
| 1     | W    | STANDBY | b0      | Enter standby mode     |
| 0     | W    | IDLE    | b0      | Enter idle mode        |

## IRFLT_CON

This thing is used to filter out unwanted spurious noise that can, for example, come from an IR receiver (hence the name) so that the underlying software doesn't need to take care of that by itself. (there is no actual IR decoder there, you're supposed to do it all manually using a timer and its capture function, to which the IRFLT output connect to; see the corresponding IOMAP description of your chip family.)

| Bits  | Type | Name     | Default | Description            |
|-------|------|----------|---------|------------------------|
| 7:4   | R/W  | PSEL     | ???     | IRFLT prescaler (0: /1, 1: /2, 2: /4, 3: /8, 4: /16, 5: /32, 6: /64, 7: /128, 8: /256, 9: /512, 10: /1024, 11: /2048, 12: /4096, 13: /8192, 14: /16384, 15: /32768) |
| 3:2   | R/W  | TSRC     | ???     | IRFLT clock source (0: system clock, 1: osc_clk, 2/3: htc clock?) |
| 1     |      |          |         |                        |
| 0     | R/W  | IRFLT_EN | b0      | Enable IRFLT           |

## RAND64

64-bit (pseudo?) random number generator

| Name | Offset | Description                |
|------|--------|----------------------------|
| R64L | 0x00   | Random number low 32 bits  |
| R64H | 0x04   | Random number high 32 bits |

## WDT_CON

Watchdog control register.

Note: in order to change this register's value (except for writing to `WCLR`, of course) you need to unlock it by writing 0x6EA5 to `CRC_REG` as stated above.

| Bits  | Type | Name  | Default | Description            |
|-------|------|-------|---------|------------------------|
| 7     | R    | WINT  | b0      | Watchdog interrupt flag |
| 6     | W    | WCLR  | b0      | Feed watchdog           |
| 5     | R/W  | WDTMD | b0      | Watchdog trip mode (0: reset the system, 1: raise an interrupt) |
| 4     | R/W  | WDTEN | b0      | Watchdog enable         |
| 3:0   | R/W  | TSEL  | b0000   | Watchdog timeout (0: 1ms, 2: 2ms, ... 6: 16s, 7: 32s *@ 32 kHz wclk*) |

# TODO

- **AES**: Advanced Encryption Standard (AES) cipher engine.
- **ALNK**: Digital audio interface (I²S protocols)
- **CTM**: Charge Time Measurement Unit
- **DMA**: Some DMA controller
- **EQ**: A hardware equalizer
- **FFT**: Fast Fourier Transform
- **GPCNT**: Gated pulse counter
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
