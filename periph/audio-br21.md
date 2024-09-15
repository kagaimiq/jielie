# Audio codec (BR21)

The audio codec in BR21 family of chips has the following features:
- Stereo DAC
- Single (mono) ADC
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
| 0x14   | DAC_CON1 | DAC control register 1  |
| 0x20   | LADC_CON | ADC control register    |
| 0x2C   | LADC_ADR | ADC buffer base address |
| 0x30   | LADC_LEN | ADC buffer length       |
| 0x40   | DAA_CON0 | DAC analog control 0    |
| 0x44   | DAA_CON1 | DAC analog control 1    |
| 0x48   | DAA_CON2 | DAC analog control 2    |
| 0x4C   | DAA_CON3 | DAC analog control 3    |
| 0x80   | ADA_CON0 | ADC analog control 0    |
| 0x84   | ADA_CON1 | ADC analog control 1    |

### DAC_LEN

DAC buffer length register.

Size: 16-bit.

### DAC_CON

DAC control register.

Size: 16-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:12 | R/W  | DCCS       | b0000   | DC cancelling filter coefficient (14 is suggested) |
| 11:10 |      |            | b000    |                        |
| 9     | R/W  | CHE0       | b0      | ADC channel 0 capture enable |
| 8     | R    | BUFF       | b0      | Buffer flag            |
| 7     | R    | PND        | b0      | DAC interrupt pending  |
| 6     | W    | CPND       | b0      | Clear a pending DAC interrupt |
| 5     | R/W  | DACIE      | b0      | Enable the DAC interrupt |
| 4     | R/W  | DACEN      | b0      | Enable DAC             |
| 3:0   | R/W  | DACSR      | b0000   | DAC sampling rate (b0000 = 44100Hz, b0001 = 48000Hz, b001x = 32000Hz, b0100 = 22050Hz, b0101 = 24000Hz, b011x = 16000Hz, b1x00 = 11025Hz, b1x01 = 12000Hz, b1x1x = 8000Hz) |

### DAC_ADR

DAC buffer base address register.

Size: 32-bit.

### DAC_TRML

DAC left channel trim register.

Size: 8-bit.

### DAC_TRMR

DAC right channel trim register.

Size: 8-bit.

### DAC_CON1

DAC control register 1.

Size: 8-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 7:6   |      |            |         |                        |
| 5     | R/W  | PDMRV      | b0      |  |
| 4     | R/W  | PDMOE      | b0      |  |
| 3     | R/W  | DSCM3      | b0      |  |
| 2     | R/W  | DSMC2      | b0      |  |
| 1     | R/W  | DSMC1      | b0      |  |
| 0     | R/W  | DSMC0      | b0      |  |

### LADC_CON

LADC control register.

Size: 16-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:12 | R/W  | DCCS       | b0000   | DC cancelling filter coefficient (14 is suggested) |
| 11:10 |      |            | b000    |                        |
| 9     | R/W  | CHE0       | b0      | ADC channel 0 capture enable |
| 8     | R    | BUFF       | b0      | Buffer flag            |
| 7     | R    | PND        | b0      | ADC interrupt pending  |
| 6     | W    | CPND       | b0      | Clear a pending ADC interrupt |
| 5     | R/W  | ADCIE      | b0      | Enable the ADC interrupt |
| 4     | R/W  | ADCEN      | b0      | Enable ADC             |
| 3:0   | R/W  | ADCSR      | b0000   | ADC sampling rate (b0000 = 44100Hz, b0001 = 48000Hz, b001x = 32000Hz, b0100 = 22050Hz, b0101 = 24000Hz, b011x = 16000Hz, b1x00 = 11025Hz, b1x01 = 12000Hz, b1x1x = 8000Hz) |

### DAA_CON0

DAC analog control register 0.

Size: 32-bit.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31    | R/W  | TRIM_OUT   | b0      | DAC trim output result |
| 30    | R/W  | MIC_2_R    | b0      | Mix microphone signal to the right output channel |
| 29    | R/W  | MIC_2_L    | b0      | Mix microphone signal to the left output channel |
| 28:24 | R/W  | RG_SEL     | h00     | Right channel gain select |
| 23    | R/W  | MUTE       | b0      | Output mute            |
| 22    | R/W  | LR_2_R     | b0      | Mono-mix stereo signal to the right output channel |
| 21    | R/W  | LR_2_L     | b0      | Mono-mix stereo signal to the left output channel |
| 20:16 | R/W  | LG_SEL     | h00     | Left channel gain select |
| 15    | R/W  | TRIM_SW    | b0      | DAC trim switch ...    |
| 14    | R/W  | TRIM_SEL   | b0      | DAC trim channel select |
| 13    | R/W  | TRIM_EN    | b0      | DAC trim enable        |
| 12:11 |      |            |         |                        |
| 10:8  | R/W  | LPF_ISEL   | b000    | Low pass filter current select? (b001: 1/3 (1.2mA), b010: 1/2 (2 mA), b100: 4 mA) - needed for audio output to work properly!! |
| 7     | R/W  | PNS10k_EN  | b0      |                        |
| 6     | R/W  | PNS_EN     | b0      |                        |
| 5     | R/W  | HP_R_EN    | b0      | Right headphone amplifier enable |
| 4     | R/W  | HP_L_EN    | b0      | Left headphone amplifier enable |
| 3     | R/W  | LDO2_EN    | b0      |                        |
| 2     | R/W  | LDO1_EN    | b0      |                        |
| 1     | R/W  | VCM_EN     | b0      | Common mode voltage (VCOM) enable |
| 0     | R/W  | DAC_EN     | b0      | DAC analog part enable |

### DAA_CON1

DAC analog control register 1.

Size: 32-bit.

| Bits  | Type | Name          | Default | Description            |
|-------|------|---------------|---------|------------------------|
| 31    | R/W  | VCM_RSEL      | b0      |                        |
| 30    | R/W  | MIC_GX2       | b0      | Microphone preamp double gain enable |
| 29:24 | R/W  | MIC_G         | b0      | Microphone preamp gain |
| 23    | R/W  | AMUX_MUTE     | b0      | AMUX mute enable       |
| 22    | R/W  | AMUX_G        | b0      | AMUX gain control      |
| 21    | R/W  | AMUX_EN       | b0      | AMUX enable            |
| 20    | R/W  | AMUX_BIAS_EN  | b0      | AMUX bias enable       |
| 19    | R/W  | MIC_NEG12     | b0      | Microphone preamp -12dB attenuation enable |
| 18    | R/W  | MIC_MUTE      | b0      | Microphone mute        |
| 17    | R/W  | MIC_ISEL      | b0      | Microphone preamp current select? |
| 16    | R/W  | MIC_EN        | b0      | Microphone preamp enable |
| 15    | R/W  | VCM_OUT_PD    | b0      | VCOMO output pulldown enable |
| 14    | R/W  | VCM_OUT_EN    | b0      | VCOMO (buffered VCOM) enable |
| 13    | R/W  | LINR_2_ADC    | b0      | Feed Line-in right channel to the ADC |
| 12    | R/W  | LINL_2_ADC    | b0      | Feed Line-in left channel to the ADC |
| 11    | R/W  | LIN2R_BIAS_EN | b0      | Line-in 2 right channel bias enable |
| 10    | R/W  | LIN2L_BIAS_EN | b0      | Line-in 2 left channel bias enable  |
| 9     | R/W  | LIN2R_EN      | b0      | Line-in 2 right input enable |
| 8     | R/W  | LIN2L_EN      | b0      | Line-in 2 left input enable  |
| 7     | R/W  | LIN1R_BIAS_EN | b0      | Line-in 1 right channel bias enable |
| 6     | R/W  | LIN1L_BIAS_EN | b0      | Line-in 1 left channel bias enable  |
| 5     | R/W  | LIN1R_EN      | b0      | Line-in 1 right input enable |
| 4     | R/W  | LIN1L_EN      | b0      | Line-in 1 left input enable  |
| 3     | R/W  | LIN0R_BIAS_EN | b0      | Line-in 0 right channel bias enable |
| 2     | R/W  | LIN0L_BIAS_EN | b0      | Line-in 0 left channel bias enable  |
| 1     | R/W  | LIN0R_EN      | b0      | Line-in 0 right input enable |
| 0     | R/W  | LIN0L_EN      | b0      | Line-in 0 left input enable  |

### DAA_CON2

DAC analog control register 2.

Size: 16-bit.

| Bits  | Type | Name             | Default | Description            |
|-------|------|------------------|---------|------------------------|
| 15:7  | R    |                  | b0      |                        |
| 6:4   | R/W  | DAC_DTSEL        | b000    | DAC dead-time select?  |
| 3:2   | R/W  | DAC_OSC_FSEL     | b00     |                        |
| 1     | R/W  | DAC_OSC_EDGE_SEL | b0      |                        |
| 0     | R/W  | DAC_CLK_SEL      | b0      |                        |

### DAA_CON3

DAC analog control register 3.

Size: 16-bit.

| Bits  | Type | Name           | Default | Description            |
|-------|------|----------------|---------|------------------------|
| 15:4  |      |                | b0      |                        |
| 5     | R/W  | ADC_DIT        | b0      | ADC dither enable      |
| 4     | R/W  | ADC_DOE        | b0      | ADC data output enable |
| 3     | R/W  | ADC_COE        | b0      | ADC clock output enable |
| 2     | R/W  | DAC_EXT        | b0      | Enable external data feed to DAC's output stage, see below |
| 1     | R/W  | DATEN          | b0      | DAC data output enable  |
| 0     | R/W  | CKEN           | b0      | DAC clock output enable |

`CKEN` enables the DAC clock output to PA4.
`DATEN` enables the DAC data output to PA5 (left channel) and PA6 (right channel).

When `DAC_EXT` is set to `1`, these pins will receive external delta-signal modulated stream that's going to drive the DAC output directly.

`ADC_COE` enables the ADC clock output to PB8.
`ADC_DOE` enables the ADC data ouptut to PB3/PB2.

### ADA_CON0

ADC analog control register 0.

Size: 32-bit.

| Bits  | Type | Name               | Default | Description            |
|-------|------|--------------------|---------|------------------------|
| 31    |      |                    |         |                        |
| 30    | R/W  | VOUTR_TS_EN        | b0      |                        |
| 29    | R/W  | VOUTL_TS_EN        | b0      |                        |
| 28    | R/W  | VCM_TS_EN          | b0      |                        |
| 27    | R/W  | SDADC0_TS          | b0      |                        |
| 26    | R/W  | DACVDD_TS_EN       | b0      |                        |
| 25:23 | R/W  | AUDLDO_VSEL        | b000    |                        |
| 22    | R/W  | AUDLDO_EN          | b0      |                        |
| 21:20 |      |                    |         |                        |
| 19:18 | R/W  | SDADC_OSC_FSEL     | b00     | ADC clock frequency select |
| 17    | R/W  | SDADC_OSC_EDGE_SEL | b0      | ADC clock edge select  |
| 16    | R/W  | SDADC_CLK_SEL      | b0      | ADC clock select       |
| 15:13 |      |                    |         |                        |
| 12    | R/W  | SDADC_PGA_ISEL     | b0      | ADC PGA current select |
| 11:8  | R/W  | SDADC_PGA_G        | b0000   | ADC PGA gain           |
| 7     | R/W  | SDADC0_PGA_EN      | b0      | ADC PGA enable         |
| 6     | R/W  | SDADC_ISEL         | b0      |                        |
| 5:4   | R/W  | SDADC_S1_ISEL      | b00     |                        |
| 3:2   | R/W  | SDADC_DITHER_CFG   | b00     |                        |
| 1     | R/W  | SDADC_FF_EN        | b0      |                        |
| 0     | R/W  | SDADC0_EN          | b0      | Enable SDADC0          |

### ADA_CON1

ADC analog control register 1.

Size: 8-bit.

| Bits  | Type | Name               | Default | Description            |
|-------|------|--------------------|---------|------------------------|
| 7:2   |      |                    |         |                        |
| 1     | R/W  | SDADC0_MIC_CH_EN   | b0      | Enable microphone recording on ADC |
| 0     | R/W  | SDADC0_LINE_CH_EN  | b0      | Enable line-in recording on ADC (see also `LINL_2_ADC` and `LINR_2_ADC` in `DAA_CON1`) |
