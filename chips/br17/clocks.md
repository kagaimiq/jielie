# Clocks

*ripped from the AC690N user manual*

## Clock nodes

- sources:
  - rc_clk : internal 250 kHz RC oscillator
  - rt_oscl (rtosl_clk) : RTC low-frequency oscillator (32.768 kHz typ.)
  - rt_osch (rtosh_clk) : RTC high-frequency oscillator (12-26 MHz)
  - bt_osc : Bluetooth oscillator (24 MHz typ., 12-26 MHz)
  - pat_clk : Test mode clock source (which is the ISP_CLK signal in ISP mode)
- interconnections:
  - src_clk : system clock source
  - org_clk : *src_clk* gated when in standby/sleep mode
- destination:
  - wclk : Watchdog clock source (~32 kHz) which is *rc_clk* divided by 8
  - cpu_clk : CPU clock
  - mem_clk : Memory clock
  - hsb_clk : High-speed bus clock
  - lsb_clk : Low-speed bus clock
  - pll_rclk : PLL reference clock (*btosc_clk* or *pat_clk*)
  - osc_clk : Oscillator clock (e.g. for a timer's osc clock option)
- PLL clocks:
  - pll_480m : PLL VCO output, intended to be 480 MHz
  - pll_192m : *pll_480m* divided by 2.5 (192 MHz)
  - pll_128m : *pll_192m* divided by 1.5 (128 MHz)
  - pll_96m : *pll_192m* divided by 3 (96 MHz)
  - pll_48m : *pll_96m* divided by 2 (48 MHz)
  - pll_24m : *pll_48m* divided by 2 (24 MHz)
  - pll_sys_clk : PLL clock output for the system clock
  - pll_apc_clk : PLL clock output for APC
  - pll_rfi_clk : PLL clock output for RFI
- Peripheral clocks:
  - alnk_clk : ALNK clock (12.288 MHz (*pll_192m*/17) or 11.2896 MHz (*pll_480m*/39) options)
  - apc_clk : APC clock (dunno)
  - dac_clk : DAC clock
  - lcd_clk : LCD driver clock
  - rfi_clk : RFI clock (fm radio?)
  - uart_clk : UART clock source (baud rate clock)
  - usb_clk : USB clock source (48 MHz)
  - wl_clk : Bluetooth core clock

## Registers

### SYS_DIV

System clocks divider.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:11 |      |            |         |                        |
| 10:8  | R/W  |            | b000    | *lsb_clk* divider (against *hsb_clk*) |
| 7:0   | R/W  |            | h00     | *hsb_clk* divider (against *org_clk*, feeds *cpu_clk*/*mem_clk* too) |


### CLK_CON0

Clock control register 0.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 15:13 | R/W  | PB9_SEL    | b000    | PB9 clock output (b000: disabled, b001: *fm_lo_d2*, b010: *pll_rfi_clk*, b011: *pll_192m*, b100: *bt_lo_d32*, b101: *wl_clk*, b110: *apc_clk*, b111: *rccl_clk*) |
| 12:10 | R/W  | PB0_SEL    | b000    | PB0 clock output (b000: disabled, b001: *lsb_clk*, b010: *btosc_clk*, b011: *rtosh_clk*, b100: *rc_clk*, b101: *hsb_clk*, b110: *rtosl_clk*, b111: *pll_sys_clk*) |
| 9     | R/W  | SFR_CKMD   | b0      | |
| 8:6   | R/W  | CKSEL      | b000    | System clock source selection (b0xx: *rc_clk*, b100: *btosc_clk*, b101: *rtosh_clk*, b110: *rtosl_clk*, b111: *pll_sys_clk*) |
| 5:4   | R/W  | OSC_SEL    | b00     | osc_clk selection (0: *btosc_clk*, 1: *rtosh_clk*, 2: *rtosl_clk*, 3: *pat_clk*) |
| 3:2   |      |            |         |                      |
| 1     | R/W  | TS_SEL     | b0      | Override system clock source with test clock input *pat_clk* |
| 0     | R/W  | RC_EN      | b1      | RC oscillator enable |

### CLK_CON1

Clock control register 1.

| Bits  | Type | Name       | Default | Description            |
|-------|------|------------|---------|------------------------|
| 31:30 |      |            |         |                        |
| 29:28 | R/W  | SFC_DSEL   | b00     | SFC clock delay        |
| 27:19 |      |            |         |                        |
| 19    | R/W  | WL_CLKINV  | b0      | *wl_clk* inversion     |
| 18    | R/W  | ROM_PD     | b0      | Mask ROM powerdown     |
| 17    | R/W  | TM_SEL     | b0      | |
| 16    | R/W  | MEM_SCKE   | b0      | Memory clock gating mode (0: disabled when CPU is idle and no DMA is ongoing, 1: always enabled) |
| 15:14 | R/W  | BT_CKSEL   | b00     | *wl_clk* select (0: *pll_wl_clk*, 1: disable, 2: *lsb_clk*, 3: disable) |
| 13:12 | R/W  | RFI_CKSEL  | b00     | *rfi_clk* select (0: *pll_rfi_clk*, 1: disable, 2: *lsb_clk*, 3: disable) |
| 11:10 | R/W  | UART_CKSEL | b00     | *uart_clk* select (0: *osc_clk*, 1: *pll_48m*, 2: *lsb_clk*, 3: disable) |
| 9:8   | R/W  | LCD_CKSEL  | b00     | *lcd_clk* select (0: *wclk*, 1: *rtosl_clk*, 2: *lsb_clk*, 3: disable) |
| 7:6   | R/W  | APC_CKSEL  | b00     | *apc_clk* select (0: *pll_apc_clk*, 1: disable, 2: *lsb_clk*, 3: disable) |
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
| 19:18 | R/W  | PLL_APC_SEL  | b01     | *pll_apc_clk* source (0: *pll_192m*, 1: *pll_480m*, 2/3: disable) |
| 17:16 | R/W  | PLL_FM_DIV1  | b01     | *pll_rfi_clk* postdiv 2 (0: /1, 1: /2, 2: /4, 3: /8) |
| 15:14 | R/W  | PLL_FM_DIV0  | b01     | *pll_rfi_clk* postdiv 1 (0: /1, 1: /3, 2: /5, 3: /7) |
| 13:12 | R/W  | PLL_RFI_SEL  | b01     | *pll_rfi_clk* source (0: *pll_192m*, 1: *pll_480m*, 2/3: disable) |
| 11:10 | R/W  |              | b01     |                        |
| 9:8   | R/W  |              | b01     |                        |
| 7:6   | R/W  |              | b01     |                        |
| 5:4   | R/W  | PLL_SYS_DIV1 | b01     | *pll_sys_clk* postdiv 2 (0: /1, 1: /2, 2: /4, 3: /8) |
| 3:2   | R/W  | PLL_SYS_DIV0 | b01     | *pll_sys_clk* postdiv 1 (0: /1, 1: /3, 2: /5, 3: /7) |
| 1:0   | R/W  | PLL_SYS_SEL  | b01     | *pll_sys_clk* source (0: *pll_192m*, 1: *pll_480m*, 2/3: disable) |

### PLL_CON

PLL control register 0.

| Bits  | Type | Name         | Default | Description            |
|-------|------|--------------|---------|------------------------|
| 31:21 |      |              |         |                        |
| 20    | R/W  | PLL_TEST     | b0      |                        |
| 19    |      |              |         |                        |
| 18:17 | R/W  | PLL_REF_SEL  | b00     | *pll_rclk* clock selection (0: *bt_osc*, 1: *rt_osch*, 2: disable, 3: *pat_clk*) |
| 16    | R/W  | PLL_RSEL12   | b0      | PLL reference clock frequency (0: 2 MHz, 1: 12 MHz) |
| 15:12 | R/W  | PLL_TSEL     |         |                        |
| 11    | R/W  | PLL_DSMS     |         | Delta-sigma modualtion scheme (0: CIFF, 1: MASH) |
| 10    | R/W  | PLL_DIVS     |         | Divider mode (0: integer, 1: fractional) |
| 9:8   | R/W  | PLL_RSEL     |         | PLL Main reference clock selection (0: *bt_osc*, 1: *rt_oscl*, 2: as selected with `PLL_REF_SEL`, 3: disable) |
| 7     | R/W  | PLL_REFDE    |         | Reference clock divider (0: no division, 1: as specified by `PLL_REFDS`) |
| 6:2   | R/W  | PLL_REFDS    |         | PLL reference clock divider (N = `PLL_REFDS` + 2) |
| 1     | R/W  | PLL_RST      |         | PLL reset signal (active low) |
| 0     | R/W  | PLL_EN       |         | PLL enable             |

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

