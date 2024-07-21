# FM radio (BR23, BR25)

## FM receiver

## FM transmitter

The FM transmitter block reads audio data from memory and outputs a multiplex signal in form of a 32-bit value (usually interpreted as a 8.24 fixed point number) to the frequency synthesizer that generates the frequency-modulated carrier.

The memory buffer format is a stereo 16-bit linear PCM with 41666.(6) Hz sampling rate.

`output = TX_FREQ + ((Left + Right) / 256 + Pilot19 * TX_PILOT + (Left - Right) * Carrier36 / 256) * TX_MUL * TX_SYN_GAIN / 4096`

## Registers

- FM receiver:

| Offset | Name        | Description             |
|--------|-------------|-------------------------|
| 0x00   | CON         | Control register        |
| 0x04   | BASE        | RX DMA buffer base address |
| 0x08   | ADC_CON     |                         |
| 0x0C   | ADC_CON1    |                         |
| 0x10   | HF_CON0     |                         |
| 0x14   | HF_CON1     |                         |
| 0x18   | HF_CRAM     |                         |
| 0x1C   | HF_CRAM2    |                         |
| 0x20   | HF_DRAM     |                         |
| 0x24   | LF_CON      |                         |
| 0x28   | LF_RES      |                         |
| 0x2C   | FMRX_CON4   |                         |
| 0x30   | FMRX_CON5   |                         |

- FM transmitter:

| Offset | Name        | Description             |
|--------|-------------|-------------------------|
| 0x34   | TX_CON0     | TX control register 1   |
| 0x38   | TX_CON1     | TX control regsiter 2   |
| 0x3C   | TX_PILOT    | Pilot tone gain         |
| 0x40   | TX_SYN_GAIN | Synth gain 1            |
| 0x44   | TX_MUL      | Multiplier              |
| 0x48   | TX_ADR      | ireg address            |
| 0x4C   | TX_LEN      | buffer length / ireg value |
| 0x50   | TX_FREQ     | base frequency          |
| 0x54   | TX_BASE_ADR | DMA buffer base address |

- Analog part: (in `JL_ANA`)

| Offset | Name        | Description             |
|--------|-------------|-------------------------|

### CON

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 14    | R/W  |            |         | Setting this to '0' enables TX related registers |
| 3     | R/W  |            |         |                        |
| 0     | R/W  |            |         |                        |

### HF_CON1

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 7     | R    | PND        |         | Interrupt pending      |
| 6     | W    | CPND       |         | Clear pending interrupt |
| 4     | R    |            |         | DMA buffer slice index (buffer index that has been filled now) |

### TX_CON0

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 7     | R/W  |            |         | enable2                |
| 5     | W    |            |         | Something write strobe |
| 4     | R    |            |         | DMA buffer slice index (buffer index that can be filled now) |
| 3     | R/W  |            |         |                        |
| 1     | R/W  |            |         | Enable stereo          |
| 0     | R/W  |            |         | enable1                |

### TX_CON1

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 7     | R    | PND        |         | Interrupt pending      |
| 6     | W    | CPND       |         | Clear pending interrupt |
| 3:0   | R/W  |            |         |                        |

### TX_PILOT

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 12:0  | R/W  |            |         | Pilot tone gain        |

### TX_SYN_GAIN

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 12:0  | R/W  |            |         | Synth gain 1 (4096 = 1.0) |

### TX_MUL

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| ..:0  | R/W  |            |         | multipler              |

### TX_FREQ

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:24 | R/W  |            |         | Integer part           |
| 23:0  | R/W  |            |         | Fractional part        |

