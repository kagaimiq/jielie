# Clocks

*ripped from the AC692N user manual, like everything else is*

## Clock nodes

- sources:
  - rc_clk : internal 16 MHz RC oscillator (predivided to get 250 kHz)
  - rt_oscl : RTC low-frequency oscillator (32.768 kHz typ.)
  - bt_osc : Bluetooth oscillator (24 MHz typ.)
  - lrc_clk : 32 kHz RC oscillator inside PMU
  - pat_clk : Test mode clock source (which is the ISP_CLK signal in ISP mode)
- interconnections:
  - src_clk : system clock source
  - org_clk : *src_clk* gated when in standby/sleep mode
- destination:
  - wclk : Watchdog clock source (~32 kHz) which is *rc_clk* divided by 64, further divided by 8
  - cpu_clk : CPU clock
  - mem_clk : Memory clock
  - sfc_clk : [SFC](../../periph/sfc.md) clock source
  - hsb_clk : High-speed bus clock
  - lsb_clk : Low-speed bus clock
  - pll_rclk : PLL reference clock (*btosc_clk* or *pat_clk*)
  - osc_clk : Oscillator clock (e.g. for a timer's osc clock option)
- PLL clocks:
  - pll_480m : PLL VCO output, intended to be 480 MHz
  - pll_320m : *pll_480m* divided by 1.5 (320 MHz)
  - pll_192m : *pll_480m* divided by 2.5 (192 MHz)
  - pll_137m : *pll_480m* divided by 3.5 (~137.1428 MHz)
  - pll_107m : *pll_480m* divided by 4.5 (~106.(6) MHz)
  - pll_96m : *pll_192m* divided by 3 (96 MHz)
  - pll_64m : *pll_192m* divided by 3 (64 MHz)
  - pll_48m : *pll_96m* divided by 2 (48 MHz)
  - pll_24m : *pll_48m* divided by 2 (24 MHz)
  - pll_sys_clk (aka *pll_clk*) : PLL clock output for the system clock
  - pll_apc_clk : PLL clock output for APC
  - pll_fm_clk : PLL clock output for FM
- Peripheral clocks:
  - alnk_clk : ALNK clock (12.288 MHz (*pll_192m*/17) or 11.2896 MHz (*pll_480m*/39) options)
  - apc_clk : APC clock (dunno)
  - dac_clk : DAC clock
  - fm_clk : FM radio core clock
  - lcd_clk : LCD driver clock
  - uart_clk : UART clock source (baud rate clock)
  - usb_clk : USB clock source (48 MHz)
  - wl_clk : Bluetooth core clock

## Registers

### SYS_DIV

System clocks divider.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15    |      |            |         |                        |
| 14:12 | R/W  |            | b000    | *sfc_clk* divider (against *org_clk* which is a gated *src_clk*) |
| 10:8  | R/W  |            | b000    | *lsb_clk* divider (against *hsb_clk*) |
| 7:0   | R/W  |            | h00     | *hsb_clk* divider (against *sfc_clk*, feeds *cpu_clk*/*mem_clk* too) |


### CLK_CON0

Clock control register 0.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:13 | R/W  | PA2_SEL    | b000    | PA2 clock output (b000: disabled, b001: *rc_clk*, b010: *lrc_clk*, b011: *rccl_clk*, b100: *bt_lo_d32*, b101: *apc_clk*, b110: *pll_320m*, b111: *pll_107m*) |
| 12:10 | R/W  | PB0_SEL    | b000    | PB0 clock output (b000: disabled, b001: *btosc_clk*, b010: *rtosh_clk*, b011: *ctm_in*, b100: *lsb_clk*, b101: *hsb_clk*, b110: *sfc_clk*, b111: *pll_sys_clk*) |
| 9     | R/W  | SFR_CKMD   | b0      | |
| 8:6   | R/W  | CKSEL      | b000    | System clock source selection (b0xx: *rc_clk*, b100: *btosc_clk*, b110: *rtosl_clk*, b111: *pll_sys_clk*) |
| 5:4   | R/W  | OSC_SEL    | b00     | osc_clk selection (0: *btosc_clk*, 1: *rtosh_clk*, 2: *rtosl_clk*, 3: *pat_clk*) |
| 3:2   | R/W  | TS_SEL     | b00     | Test clock selection |
| 1     | R/W  | RCH_EN     | b0      | RC oscillator frequency (0: ~250 kHz (divide by 64), 1: ~16 MHz) |
| 0     | R/W  | RC_EN      | b1      | RC oscillator enable |

### CLK_CON1

Clock control register 1.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:30 |      |            |         |                        |
| 29:28 | R/W  | SFC_DSEL   | b00     | SFC clock delay        |
| 27:17 |      |            |         |                        |
| 16    | R/W  | MEM_SCKE   | b0      | Memory clock gating mode (0: disabled when CPU is idle and no DMA is ongoing, 1: always enabled) |
| 15:14 | R/W  | BT_CKSEL   | b00     | *wl_clk* select (0: *pll_64m*, 1: disable, 2: *lsb_clk*, 3: disable) |
| 13:12 | R/W  | FM_CKSEL   | b00     | *fm_clk* select (0: disable, 1: *pll_fm_clk*, 2: *hsb_clk*, 3: disable) |
| 11:10 | R/W  | UART_CKSEL | b00     | *uart_clk* select (0: *osc_clk*, 1: *pll_48m*, 2: *lsb_clk*, 3: disable) |
| 9:8   | R/W  | LCD_CKSEL  | b00     | *lcd_clk* select (0: *wclk*, 1: *rtosl_clk*, 2: *lsb_clk*, 3: disable) |
| 7:6   | R/W  | APC_CKSEL  | b00     | *apc_clk* select (0: *pll_64m*, 1: *pll_apc_clk*, 2: *lsb_clk*, 3: disable) |
| 5:4   |      |            |         |  |
| 3:2   | R/W  | DAC_CKSEL  | b00     | *dac_clk* select (0: *pll_24m*, 1: disable, 2: *lsb_clk*, 3: disable) |
| 1:0   | R/W  | USB_CKSEL  | b00     | *usb_clk* select (0: *pll_48m*, 1: disable, 2: *lsb_clk*, 3: disable) |

### CLK_CON2

Clock control register 2.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31    |      |              |         |                        |
| 30    | R/W  | PLL_ALNK_SEL | b0      | *alnk_clk* select (0: *pll_192m*/17, 1: *pll_480m*/39) |
| 29:24 |      |              |         |                        |
| 23:22 | R/W  | PLL_APC_DIV1 | b01     | *pll_apc_clk* postdiv 2 (0: /1, 1: /2, 2: /4, 3: /8) |
| 21:20 | R/W  | PLL_APC_DIV0 | b01     | *pll_apc_clk* postdiv 1 (0: /1, 1: /3, 2: /5, 3: /7) |
| 19:18 | R/W  | PLL_APC_SEL  | b01     | *pll_apc_clk* source (0: *pll_192m*, 1: *pll_137m*, 2: *pll_480m*, 3: disable) |
| 17:16 | R/W  | PLL_FM_DIV1  | b01     | *pll_fm_clk* postdiv 2 (0: /1, 1: /2, 2: /4, 3: /8) |
| 15:14 | R/W  | PLL_FM_DIV0  | b01     | *pll_fm_clk* postdiv 1 (0: /1, 1: /3, 2: /5, 3: /7) |
| 13:12 | R/W  | PLL_FM_SEL   | b01     | *pll_fm_clk* source (0: *pll_192m*, 1: *pll_137m*, 2: *pll_480m*, 3: disable) |
| 11:10 | R/W  |              | b01     |                        |
| 9:8   | R/W  |              | b01     |                        |
| 7:6   | R/W  |              | b01     |                        |
| 5:4   | R/W  | PLL_SYS_DIV1 | b01     | *pll_sys_clk* postdiv 2 (0: /1, 1: /2, 2: /4, 3: /8) |
| 3:2   | R/W  | PLL_SYS_DIV0 | b01     | *pll_sys_clk* postdiv 1 (0: /1, 1: /3, 2: /5, 3: /7) |
| 1:0   | R/W  | PLL_SYS_SEL  | b01     | *pll_sys_clk* source (0: *pll_192m*, 1: *pll_137m*, 2: *pll_480m*, 3: disable) |

### PLL_CON

PLL control register 0.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:30 | R/W  | PLL_REF_SEL  | b00     | *pll_rclk* clock selection (0: *bt_osc*, 1/2: disable, 3: *pat_clk*) |
| 29:28 | R/W  | PLL_LPFR3    | b00     |                        |
| 27:26 | R/W  | PLL_LPFR2    | b00     |                        |
| 25:24 | R/W  | PLL_ICP      | b00     |                        |
| 23:22 | R/W  | PLL_PFD      | b00     |                        |
| 21:20 | R/W  | PLL_DIVSEL   | b00     | (b00: integer mode, b11: fractional mode) |
| 19:18 | R/W  | DSM_MSEL     | b00     |                        |
| 17:16 | R/W  | DSM_RSEL     | b00     |                        |
| 15:12 | R/W  | DSM_TSEL     | b0000   |                        |
| 11    | R/W  | PLL_DSMS     | b0      | Delta-sigma modualtion scheme (0: CIFF, 1: MASH) |
| 10    | R/W  | PLL_TEST     | b0      |                        |
| 9:8   | R/W  | PLL_REFDE    | b00     | Reference clock divider (b00: multiply by 2, b01: no division, b1x: as specified by `PLL_REFDS`) |
| 7     | R/W  | PLL_REFSEL   | b0      | PLL reference clock selection (0: *bt_osc*, 1: *pll_rclk* as selected with `PLL_REF_SEL`) |
| 6:2   | R/W  | PLL_REFDS    | b00000  | PLL reference clock divider (N = `PLL_REFDS` + 2) |
| 1     | R/W  | PLL_RST      | b0      | PLL reset signal (active low) |
| 0     | R/W  | PLL_EN       | b0      | PLL enable             |


### PLL_CON1

PLL control register 1.

| Bits  | Type | Name          | Default | Description            |
|-------|------|---------------|---------|------------------------|
| 31:29 |      |               |         |                        |
| 28    | R/W  | CK107M_OE     | b0      | ~107 MHz (480/4.5) clock output enable |
| 27    | R/W  | CK137M_OE     | b0      | ~137 MHz (480/3.5) clock output enable |
| 26    | R/W  | CK192M_OE     | b0      | 192 MHz (480/2.5) clock output enable |
| 25    | R/W  | CK320M_OE     | b0      | 320 MHz (480/1.5) clock output enable |
| 24    | R/W  | CK480M_OE     | b0      | 480 MHz (480/1) clock output enable |
| 23:19 |      |               |         |                        |
| 18    | R/W  | PLL_TSOE      | b0      |                        |
| 17:16 | R/W  | PLL_TSSEL     | b00     |                        |
| 15    | R/W  | PLL_LDOBYPASS | b0      |                        |
| 14:12 | R/W  | PLL_IVCO      | b000    |                        |
| 11:10 | R/W  | PLL_LDO12D    | b00     |                        |
| 9:8   | R/W  | PLL_LDO12A    | b00     |                        |
| 7:0   | R/W  | PLL_FBDS      | h00     | Feedback loop divider (480 / 2 MHz = 240) |

### PLL_INTF

PLL fractional divider.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:24 | R/W  |              |         | Integer divider value  |
| 23:0  | R/W  |              |         | Fractional divider value |

### PLL_DMAX

PLL spread spectrum clock max deviation.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:24 |      |              |         |                        |
| 23:0  | R/W  |              |         |                        |

### PLL_DMIN

PLL spread spectrum clock min deviation.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:24 |      |              |         |                        |
| 23:0  | R/W  |              |         |                        |

### PLL_DSTP

PLL spread spectrum clock step.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:24 |      |              |         |                        |
| 23:0  | R/W  |              |         |                        |

