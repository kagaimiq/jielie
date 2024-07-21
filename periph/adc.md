# ADC

General purpose 10-bit Successive Approximation Register (SAR) ADC.

| Channel | BR17 | BR21  | BR23  | BR25  |
|---------|------|-------|-------|-------|
| b0000   | PA3  | PA3   | PA1   | PA0   |
| b0001   | PA4  | PA4   | PA5   | PA1   |
| b0010   | PA5  | PA5   | PA6   | PA3   |
| b0011   | PA6  | PA6   | PA10  | PA4   |
| b0100   | PA9  | PC4   | PA12  | PA6   |
| b0101   | PA10 | PA10  | PB1   | PB1   |
| b0110   | PB7  | PB0   | PB3   | PB3   |
| b0111   | PB8  | PB1   | PB4   | PB4   |
| b1000   | PB9  | PB4   | PB8   | PB6   |
| b1001   | PB10 | PB5   | PB10  | PB7   |
| b1010   | PB11 | PC3   | PC4   | PC2   |
| b1011   | PB12 | USBDM | PC6   | PC4   |
| b1100   | wtw  | RTC   | USBDP | PC5   |
| b1101   | wtw  | PMU   | PC5   | USBDP |
| b1110   | wtw  | BT    | RTC   | USBDM |
| b1111   | wtw  | AUDIO | wtw   | wtw   |

## Registers

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | CON      | Control regsiter        |
| 0x04   | RES      | Conversion result       |

### CON

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:12 | R/W  | WAIT_TIME  | ?       | Wait N*8 ticks before starting a conversion |
| 11:8  | R/W  | CH_SEL     | h0      | Channel selection      |
| 7     | R    | PND        | b1      | Pending interrupt flag |
| 6     | W    | CPND       | b0      | Clear a pending interrupt |
| 5     | R/W  | ADC_IE     | b0      | Interrupt enable       |
| 4     | R/W  | ADC_EN     | b0      | ADC enable             |
| 3     | R/W  | ADC_AE     | b0      | ADC analog part enable |
| 2:0   | R/W  | ADC_BAUD   | b000    | ADC clock divider (/1, /6, /12, /24, /48, /72, /96 and /128) |

Note: the ADC clock frequency should be ≤ 1 MHz.

### RES

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:10 |      |            |         |                        |
| 9:0   | R    | RES        | h000    | ADC conversion result  |
