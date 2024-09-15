# Audio codec (BR25)

## Digital control registers

Base address: 0x1E2F00 (AUDIO)

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | DAC_CON  | DAC control register    |
| 0x04   | DAC_ADR  | DAC buffer base address |
| 0x08   | DAC_LEN  | DAC buffer length       |
| 0x0C   | DAC_PNS  | |
| 0x10   | DAC_HRP  | DAC buffer Hardware Read Pointer |
| 0x14   | DAC_SWP  | DAC buffer Software Write Pointer |
| 0x18   | DAC_SWN  | DAC buffer Software Write Number |
| 0x20   | DAC_VL0  | |
| 0x28   | DAC_TM0  | |
| 0x34   | DAC_DTB  | |
| 0x38   | DAC_DPD  | |
| 0x3C   | DAC_COP  | |
| 0x40   | ADC_CON  | ADC control register    |
| 0x44   | ADC_ADR  | ADC buffer base address |
| 0x48   | ADC_LEN  | ADC buffer length       |
| 0x4C   | ADC_PNS  |  |
| 0x50   | ADC_HWP  | ADC buffer Hardware Write Pointer |
| 0x54   | ADC_SRP  | ADC buffer Software Read Pointer |
| 0x58   | ADC_SRN  | ADC buffer Software Read Number |

### DAC_CON

DAC control register.

Size: 32-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:8  |      |            |         |                        |
| 7     | R    |            | b0      | DAC interrupt pending flag |
| 6     | W    |            |         | Clear the interrupt flag   |
| 5     | R/W  |            | b0      | Enable DAC interrupt   |
| 4     | R/W  |            | b0      | Enable DAC             |
| 3:0   | R/W  |            | b0000   | DAC sample rate (0: 96000 Hz, 1: 88200 Hz, 2: 64000 Hz, 4: 48000 Hz, 5: 44100 Hz, 6: 32000 Hz, 8: 24000 Hz, 9: 22050 Hz, 10: 16000 Hz, 12: 12000 Hz, 13: 11025 Hz, 14: 8000 Hz) |

### DAC_ADR

DAC buffer base address register.

Size: 32-bit.

### DAC_LEN

DAC buffer length register.

Size: 16-bit.

### DAC_PNS

DAC whatever related to the ring buffer..

Size: 16-bit.

### DAC_HRP

DAC ring buffer hardware read pointer.

Size: 16-bit.

### DAC_SWP

DAC ring buffer software write pointer.

Size: 16-bit.

### DAC_SWN

DAC ring buffer software write number of data.

Size: 16-bit.

### DAC_VL0

DAC digital volume setting register.

Size: 32-bit.

### DAC_TM0

DAC trim register?

Size: 32-bit.

### DAC_DTB

Size: 16-bit.

### DAC_DPD

Size: 32-bit.

### DAC_COP

Size: 16-bit.

### ADC_CON

ADC control register.

Size: 32-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:8  |      |            |         |                        |
| 7     | R    |            | b0      | ADC interrupt pending flag |
| 6     | W    |            |         | Clear the interrupt flag   |
| 5     | R/W  |            | b0      | Enable ADC interrupt   |
| 4     | R/W  |            | b0      | Enable ADC             |
| 3:0   | R/W  |            | b0000   | ADC sample rate (0: 48000 Hz, 1: 44100 Hz, 2: 32000 Hz, 3: 24000 Hz, 5: 22050 Hz, 6: 16000 Hz, 8: 12000 Hz, 9: 11025 Hz, 10: 8000 Hz) |

### ADC_ADR

ADC buffer base address register.

Size: 32-bit.

### ADC_LEN

ADC buffer size register.

Size: 16-bit.

### ADC_PNS

ADC something related to ring buffer too register.

Size: 16-bit.

### ADC_HWP

ADC ring buffer hardware write pointer.

Size: 16-bit.

### ADC_SRP

ADC ring buffer software read pointer.

Size: 16-bit.

### ADC_SRN

ADC ring buffer software read number of data.

Size: 16-bit.

## Analog control registers

Base address: 0x1E1900 (ANA)

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0xC0   | DAA_CON0 | DAC analog control 0    |
| 0xC4   | DAA_CON1 | DAC analog control 1    |
| 0xC8   | DAA_CON2 | DAC analog control 2    |
| 0xCC   | DAA_CON3 | DAC analog control 3    |
| 0xD0   | DAA_CON4 | DAC analog control 4    |
| 0xDC   | DAA_CON7 | DAC analog control 7    |
| 0xE0   | ADA_CON0 | ADC analog control 0    |
| 0xE4   | ADA_CON1 | ADC analog control 1    |
| 0xE8   | ADA_CON2 | ADC analog control 2    |
| 0xEC   | ADA_CON3 | ADC analog control 3    |
| 0xF0   | ADA_CON4 | ADC analog control 4    |

### DAA_CON0

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |
| 27:25 | R/W  |            | b000    | dacvdd voltage selection |
| 24    | R/W  |            | b0      | dacvdd                 |
| 22    | R/W  |            | b0      | dacvdd                 |

96000, 88200, 64000, x, 
48000, 44100, 32000, x, 
24000, 22050, 16000, x, 
12000, 11025, 8000, x

### DAA_CON1

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:30 |      |            |         |                        |
| 29    | R/W  |            | b0      | AMUX mute  -?- dac as line-in 3 |
| 28    | R/W  |            | b0      | AMUX enable            |
| 27    | R/W  |            | b0      | AMUX bias enable       |
| 26    | R/W  |            | b0      | Line in 1 right channel enable |
| 25    | R/W  |            | b0      | Line in 1 right channel bias enable |
| 24    | R/W  |            | b0      | Line in 1 left channel enable |
| 23    | R/W  |            | b0      | Line in 1 left channel bias enable |
| 22    | R/W  |            | b0      | Line in 0 right channel enable |
| 21    | R/W  |            | b0      | Line in 0 right channel bias enable |
| 20    | R/W  |            | b0      | Line in 0 left channel enable |
| 19    | R/W  |            | b0      | Line in 0 left channel bias enable |
| 18    | R/W  |            | b0      | -?- dac as line-in 5 --- linein ch combine 2 |
| 17    | R/W  |            | b0      | -?- dac as line-in 4 --- linein ch combine 1 |
| 16:15 | R/W  |            | b0      | LDO feedback current select (0: 15 µA, 1: 48 µA, 2: 81 µA, 3: 114 µA) |
| 14    | R/W  |            | b0      | right channel enable 1 |
| 13    | R/W  |            | b0      | left channel enable 2  |
| 12    |      |            |         |                        |
| 11    | R/W  |            | b0      | -?- dac as line-in 2   |
| 10    | R/W  |            | b0      | -?- dac as line-in 1   |
| 9:5   | R/W  |            | b00000  | Right output gain      |
| 4:0   | R/W  |            | b00000  | Left output gain       |

### DAA_CON2

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |
| 20    | R/W  |            | b0      | VCM rise time          |
| 13:11 | R/W  |            | b000    | LDO current select (5-40 µA, in 5 µA steps) |
| 9:7   | R/W  |            | b000    |                        |
| 3:0   | R/W  |            | b0000   | LPF bias current select (0-4.6785 µA, in 0.3125 µA steps) |

### DAA_CON3

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### DAA_CON4

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### DAA_CON7

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### ADA_CON0

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### ADA_CON1

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |
| 11    | R/W  |            | b0      | mic mute               |

### ADA_CON2

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### ADA_CON3

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |

### ADA_CON4

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:0  |      |            |         |                        |
