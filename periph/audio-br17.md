# Audio codec (BR17)

The audio codec in BR17 family of chips has the following features:
- Stereo DAC
- 3-channel ADC (hard routed to Line-in left, Line-in right and Microphone)
- DAC output with a headphone amplifier
- VCOMO buffered common voltage output
- Three Line-in (AMUX) input pairs
- Single microphone input and preamp
- Analog mixing for line-in and mic inputs.

## Registers

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | DAC_LEN  | DAC buffer length       |
| 0x04   | DAC_CON  | DAC control register    |
| 0x08   | DAC_ADR  | DAC buffer base address |
| 0x0C   | DAC_TRML | DAC left channel trim   |
| 0x10   | DAC_TRMR | DAC right channel trim  |
| 0x20   | LADC_CON | ADC control register    |
| 0x2C   | LADC_ADR | ADC buffer base address |
| 0x30   | LADC_LEN | ADC buffer length       |
| 0x40   | DAA_CON0 | DAC analog control 0    |
| 0x44   | DAA_CON1 | DAC analog control 1    |
| 0x48   | DAA_CON2 | DAC analog control 2    |
| 0x4C   | DAA_CON3 | DAC analog control 3    |
| 0x50   | DAA_CON4 | DAC analog control 4    |
| 0x54   | DAA_CON5 | DAC analog control 5    |
| 0x80   | ADA_CON0 | ADC analog control 0    |
| 0x84   | ADA_CON1 | ADC analog control 1    |
| 0x88   | ADA_CON2 | ADC analog control 2    |

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

### LADC_CON

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

### DAA_CON0

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15    | R/W  | TRIM_SW    | b0      | DAC trim switch ...    |
| 14    | R/W  | TRIM_SEL   | b0      | DAC trim channel select |
| 13    | R/W  | TRIM_EN    | b0      | DAC trim enable        |
| 12:9  |      |            |         |                        |
| 8     | R/W  | PNS10k_EN  | b0      |                        |
| 7     | R/W  | MUTE       | b0      | Output mute            |
| 6     | R/W  | PNS_EN     | b0      |                        |
| 5     | R/W  | HP_R_EN    | b0      | Right headphone amplifier enable |
| 4     | R/W  | HP_L_EN    | b0      | Left headphone amplifier enable |
| 3     | R/W  | LDO2_EN    | b0      |                        |
| 2     | R/W  | LDO1_EN    | b0      |                        |
| 1     | R/W  | DAC_DTSEL  | b0      |                        |
| 0     | R/W  | DAC_EN     | b0      | DAC analog part enable |

### DAA_CON1

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15    | R/W  | MIC_2_R    | b0      | Mix microphone signal to the right output channel |
| 14    | R/W  | MIC_2_L    | b0      | Mix microphone signal to the left output channel |
| 13    | R/W  | VCM_RSEL   | b0      |                        |
| 12:8  | R/W  | RG_SEL     | h00     | Right channel gain select |
| 7     | R/W  | LR_2_R     | b0      | Mono-mix stereo signal to the right output channel |
| 6     | R/W  | LR_2_L     | b0      | Mono-mix stereo signal to the left output channel |
| 5     |      |            | b0      |                        |
| 4:0   | R/W  | LG_SEL     | h00     | Left channel gain select |

### DAA_CON2

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 15:14 |      |              |         |                        |
| 13    | R/W  | AMUX_MUTE    | b0      | AMUX mute enable       |
| 12    | R/W  | AMUX_BIAS_EN | b0      | AMUX bias enable       |
| 11    | R/W  | VCM_OUT_PD   | b0      | VCOMO output pulldown enable |
| 10    | R/W  | VCM_OUT_EN   | b0      | VCOMO (buffered VCOM) enable |
| 9     | R/W  | VCM_EN       | b0      | Commom mode voltage (VCOM) enable |
| 8     | R/W  | VCM_DET_EN   | b0      | VCOM detect enable?    |
| 7     | R/W  | AMUX_EN      | b0      | AMUX enable            |
| 6     | R/W  | AMUX_G       | b0      | 'AMUX gain control'    |
| 5     | R/W  | LIN2R_EN     | b0      | Line-in 2 right input enable |
| 4     | R/W  | LIN2L_EN     | b0      | Line-in 2 left input enable  |
| 3     | R/W  | LIN1R_EN     | b0      | Line-in 1 right input enable |
| 2     | R/W  | LIN1L_EN     | b0      | Line-in 1 left input enable  |
| 1     | R/W  | LIN0R_EN     | b0      | Line-in 0 right input enable |
| 0     | R/W  | LIN0L_EN     | b0      | Line-in 0 left input enable  |

### DAA_CON3

| Bits  | Type | Name          | Default | Description            |
|-------|------|---------------|---------|------------------------|
| 15    | R/W  | TRIM_OUT      | b0      | DAC trim output result |
| 14    | R/W  | MIC_EN        | b0      | Microphone input enable |
| 13    | R/W  | LIN2R_BIAS_EN | b0      | Line-in 2 right channel bias enable |
| 12    | R/W  | LIN2L_BIAS_EN | b0      | Line-in 2 left channel bias enable  |
| 11    | R/W  | LIN1R_BIAS_EN | b0      | Line-in 1 right channel bias enable |
| 10    | R/W  | LIN1L_BIAS_EN | b0      | Line-in 1 left channel bias enable  |
| 9     | R/W  | LIN0R_BIAS_EN | b0      | Line-in 0 right channel bias enable |
| 8     | R/W  | LIN0L_BIAS_EN | b0      | Line-in 0 left channel bias enable  |
| 7     | R/W  | MIC_MUTE      | b0      | Microphone mute        |
| 6     | R/W  | MIC_GX2       | b0      | Microphone preamp double gain enable |
| 5:0   | R/W  | MIC_G         | b0      | Microphone preamp gain |

### DAA_CON4

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 15:4  |      |                | b0      |                        |
| 3     | R/W  | MIC_NEG12      | b0      | Microphone preamp -12dB attenuation enable |
| 2     | R/W  | DAC_ISEL_HALF  | b0      |                        |
| 1     | R/W  | DAC_ISEL_THIRD | b0      |                        |
| 0     | R/W  | DAC_ISEL5U     | b0      |                        |

### DAA_CON5

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 15:4  |      |                | b0      |                        |
| 5     | R/W  | ADC_DIT        | b0      | ADC dither enable      |
| 4     | R/W  | ADC_DOE        | b0      | ADC data output enable |
| 3     | R/W  | ADC_COE        | b0      | ADC clock output enable |
| 2     | R/W  | DAC_EXT        | b0      | Enable external data feed to DAC's output stage, see below |
| 1     | R/W  | DATEN          | b0      | DAC data output enable |
| 0     | R/W  | CKEN           | b0      | DAC clock output enable |

`CKEN` enables the DAC clock output to PA4.
`DATEN` enables the DAC data output to PA5 (left channel) and PA6 (right channel).

When `DAC_EXT` is set to `1`, these pins will receive external delta-signal modulated stream that's going to drive the DAC output directly.

`ADC_COE` enables the ADC clock output to PB8.
`ADC_DOE` enables the ADC data ouptut to PB3/PB2 (ch1), PB5/PB4 (ch2) and PB7/PB6 (ch3).
