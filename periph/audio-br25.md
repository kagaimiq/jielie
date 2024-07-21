# Audio codec (BR25)

## Registers

- Digital part:

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | DAC_CON  | DAC control register    |
| 0x04   | DAC_ADR  | DAC buffer base address |
| 0x08   | DAC_LEN  | DAC buffer length       |
| 0x0C   | DAC_PNS  | |
| 0x10   | DAC_HRP  | |
| 0x14   | DAC_SWP  | |
| 0x18   | DAC_SWN  | |
| 0x20   | DAC_VL0  | |
| 0x28   | DAC_TM0  | |
| 0x34   | DAC_DTB  | |
| 0x3C   | DAC_DPD  | |
| 0x40   | DAC_COP  | |
| 0x44   | ADC_CON  | ADC control register    |
| 0x48   | ADC_ADR  | ADC buffer base address |
| 0x4C   | ADC_LEN  | ADC buffer length       |
| 0x50   | ADC_PNS  | |
| 0x54   | ADC_HWP  | |
| 0x58   | ADC_SRP  | |
| 0x5C   | ADC_SRN  | |

- Analog part (in `JL_ANA`):

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

### DAC_CON

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:12 | R/W  | DCCS       | h0      | DC cancelling filter coefficient (14 is suggested) |
| 11:9  |      |            | b000    |                        |
| 8     | R    | BUFF       | b0      | Buffer flag            |
| 7     | R    | PND        | b0      | DAC interrupt pending  |
| 6     | W    | CPND       | b0      | Clear a pending DAC interrupt |
| 5     | R/W  | DACIE      | b0      | Enable the DAC interrupt |
| 4     | R/W  | DACEN      | b0      | Enable DAC             |
| 3:0   | R/W  | DACSR      | h0      | DAC sampling rate      |

| DACSR | Rate     |
|-------|----------|
| b0000 | 44100 Hz |
| b0001 | 48000 Hz |
| b001x | 32000 Hz |
| b0100 | 22050 Hz |
| b0101 | 24000 Hz |
| b011x | 16000 Hz |
| b1x00 | 11025 Hz |
| b1x01 | 12000 Hz |
| b1x1x | 8000 Hz  |

### ADC_CON

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:12 | R/W  | DCCS       | h0      | DC cancelling filter coefficient (14 is suggested) |
| 11:9  |      |            | b000    |                        |
| 8     | R    | BUFF       | b0      | Buffer flag            |
| 7     | R    | PND        | b0      | ADC interrupt pending  |
| 6     | W    | CPND       | b0      | Clear a pending ADC interrupt |
| 5     | R/W  | ADCIE      | b0      | Enable the ADC interrupt |
| 4     | R/W  | ADCEN      | b0      | Enable ADC             |
| 3:0   | R/W  | ADCSR      | h0      | ADC sampling rate (see above) |
