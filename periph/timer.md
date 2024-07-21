# TIMER

Basic counter timers with ability to output PWM.

Timer signals are exposed outside as the `TMRx`, `CAPx` and `PWMx` pins.
TMR pins are the external clock inputs, CAP pins are the input capture signals and
PWM pins are the PWM output pins of the respective timers.

## Registers

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | CON      | Control regsiter        |
| 0x04   | CNT      | Counter                 |
| 0x08   | PRD      | Period                  |
| 0x0C   | PWM      | PWM duty cycle          |

### CON

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15    | R    | PND        |         | Interrupt pending flag |
| 14    | W    | PCLR       |         | Clear a pending interrupt |
| 9     | R/W  | PWM_INV    | b0      | Invert output PWM signal |
| 8     | R/W  | PWM_EN     | b0      | Enable PWM output      |
| 7:4   | R/W  | PSEL       | b0000   | Prescaler              |
| 3:2   | R/W  | SSEL       | b00     | Clock source (0: bus clock, 1: external clock, 2: osc_clk, 3: rc_clk) |
| 1:0   | R/W  | MODE       | b00     | Timer mode (0: disabled, 1: counting, 2: capture rising, 3: capture falling) |

- Prescaler:

| PSEL  | Prescaler           |
|-------|---------------------|
| b0000 | /1                  |
| b0100 | /2 (1*2)            |
| b0001 | /4                  |
| b0101 | /8 (4*2)            |
| b0010 | /16                 |
| b0110 | /32 (16*2)          |
| b0011 | /64                 |
| b0111 | /128 (64*2)         |
| b1000 | /256 (1*256)        |
| b1100 | /512 (1*2*256)      |
| b1001 | /1024 (4*256)       |
| b1101 | /2048 (4*2*256)     |
| b1010 | /4096 (16*256)      |
| b1110 | /8192 (16*2*256)    |
| b1011 | /16384 (64*256)     |
| b1111 | /32768 (64*2*256)   |

