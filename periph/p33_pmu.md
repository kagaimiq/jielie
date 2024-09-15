# P33 (PMU)

*Specific to BR25.*


The PMU contains a watchdog, a efuse block...

## Registers

| Offset | Name         | Description             |
|--------|--------------|-------------------------|
| 0x0000 | ANA_CON0     |                         |
| 0x0001 | ANA_CON1     |                         |
| 0x0002 | ANA_CON2     |                         |
| 0x0003 | ANA_CON3     |                         |
| 0x0004 | ANA_CON4     |                         |
| 0x0005 | ANA_CON5     |                         |
| 0x0006 | ANA_CON6     |                         |
| 0x0007 | ANA_CON7     |                         |
| 0x0008 | ANA_CON8     |                         |
| 0x0009 | ANA_CON9     |                         |
| 0x000C | L5V_CON0     |                         |
| 0x000D | L5V_CON1     |                         |
| 0x000E | SDPG_CON     |                         |
| 0x000F | FSPG_CON     |                         |
| 0x0010 | PLVD_CON     |                         |
| 0x0011 | VLVD_CON     |                         |
| 0x0012 | RST_SRC      |                         |
| 0x0013 | LRC_CON0     |                         |
| 0x0014 | LRC_CON1     |                         |
| 0x0015 | RST_CON0     |                         |
| 0x0016 | ANA_KEEP     |                         |
| 0x0017 | VLD_KEEP     |                         |
| 0x0018 | CHG_WKUP     |                         |
| 0x0019 | CHG_READ     |                         |
| 0x001A | CHG_CON0     |                         |
| 0x001B | CHG_CON1     |                         |
| 0x001C | CHG_CON2     |                         |
| 0x001D | CHG_CON3     |                         |
| 0x0030 | PMU_CON0     |                         |
| 0x0031 | PMU_CON1     |                         |
| 0x0032 | PMU_CON2     |                         |
| 0x0033 | PMU_CON3     |                         |
| 0x0034 | PMU_CON4     |                         |
| 0x0035 | PMU_CON5     |                         |
| 0x0036 | LP_PRP0      |                         |
| 0x0037 | LP_PRP1      |                         |
| 0x0038 | LP_STB0_STB1 |                         |
| 0x0039 | LP_STB2_STB3 |                         |
| 0x003A | LP_STB4_STB5 |                         |
| 0x003B | LP_STB6      |                         |
| 0x0040 | LP_RSC00     |                         |
| 0x0041 | LP_RSC01     |                         |
| 0x0042 | LP_RSC02     |                         |
| 0x0043 | LP_RSC03     |                         |
| 0x0044 | LP_PRD00     |                         |
| 0x0045 | LP_PRD01     |                         |
| 0x0046 | LP_PRD02     |                         |
| 0x0047 | LP_PRD03     |                         |
| 0x0048 | LP_RSC10     |                         |
| 0x0049 | LP_RSC11     |                         |
| 0x004A | LP_RSC12     |                         |
| 0x004B | LP_RSC13     |                         |
| 0x004C | LP_PRD10     |                         |
| 0x004D | LP_PRD11     |                         |
| 0x004E | LP_PRD12     |                         |
| 0x004F | LP_PRD13     |                         |
| 0x0054 | LP_TMR0_CLK  |                         |
| 0x0058 | LP_TMR0_CON  |                         |
| 0x0059 | LP_TMR1_CON  |                         |
| 0x0060 | LP_CNTRD0    |                         |
| 0x0061 | LP_CNTRD1    |                         |
| 0x0062 | LP_CNT0      |                         |
| 0x0063 | LP_CNT1      |                         |
| 0x0064 | LP_CNT2      |                         |
| 0x0065 | LP_CNT3      |                         |
| 0x0070 | MSTM_RD      |                         |
| 0x0071 | IVS_RD       |                         |
| 0x0072 | IVS_SET      |                         |
| 0x0073 | IVS_CLR      |                         |
| 0x0074 | WLDO12_AUTO  |                         |
| 0x0075 | WLDO06_AUTO  |                         |
| 0x0080 | WDT_CON      | Watchdog control register |
| 0x0090 | WKUP_EN      |                         |
| 0x0091 | WKUP_EDGE    |                         |
| 0x0092 | WKUP_CPND    |                         |
| 0x0093 | WKUP_PND     |                         |
| 0x0094 | PINR_CON     |                         |
| 0x0095 | WKUP_FLEN    |                         |
| 0x0096 | PCNT_CON     |                         |
| 0x0097 | PCNT_VLUE    |                         |
| 0x00A0 | PR_PWR       |                         |
| 0x00A1 | LDO5V_CON    |                         |
| 0x00A2 | LVCMP_CON    |                         |
| 0x00A3 | L5DEM_CON    |                         |
| 0x00A4 | L5DEM_FLT    |                         |
| 0x00A5 | OSL_CON      |                         |
| 0x00A6 | CLK_CON0     |                         |
| 0x00A8 | WKUP_SRC     |                         |
| 0x00A9 | WKUP_SUB     |                         |
| 0x00AA | PORT_FLT     |                         |
| 0x00AC | LVCMP        |                         |
| 0x00AF | ANA_LAT      |                         |
| 0x00B0 | EFUSE_CON0   | eFuse control register 0 |
| 0x00B1 | EFUSE_CON1   | eFuse control register 1 |
| 0x00B2 | EFUSE_RDAT   | eFuse read data         |
| 0x00C0 | PORT_SEL10   |                         |
| 0x00C1 | PORT_SEL11   |                         |
| 0x00C2 | PORT_SEL12   |                         |
| 0x00C3 | PORT_SEL13   |                         |
| 0x00C4 | PORT_SEL14   |                         |
| 0x00C5 | PORT_SEL15   |                         |
| 0x00C6 | PORT_SEL16   |                         |
| 0x00C7 | PORT_SEL17   |                         |

### ANA_CON0

| Bits | Name | Description |
|------|------|-------------|
| 7    | RC_250K_EN       | |
| 5    | PW_GATE_EN       | |
| 3    | DCDC13_EN        | |
| 2    | LDO13_EN         | |
| 0    | VDD13TO12_SYS_EN | |

### ANA_CON1

| Bits | Name | Description |
|------|------|-------------|
| 7    | SYSVDD_BYPASS_EN    | |
| 6    | SYSVDD_RES_SHORT_EN | |
| 4    | VDC13_LOAD_EN       | |
| 3    | WLDO06_EN           | |
| 2    | BTDCDC_PFM_MODE     | |
| 1    | BTDCDC_RAMP_EN      | |
| 0    | BTDCDC_V17_PDEN     | |

### ANA_CON2

| Bits | Name | Description |
|------|------|-------------|
| 7    | SWVLD_AUTO_EN | |
| 6    | VDDOK_DIS     | |
| 4    | D2SH_EN_SW    | |
| 3    | VCM_DET_EN    | |

### ANA_CON3

| Bits | Name | Description |
|------|------|-------------|
| 1    | IVBATL_EN      | |
| 0    | FORE_BYPASS_EN | |

### ANA_CON4

| Bits | Name | Description |
|------|------|-------------|
| 3:1  | ADC_CHANNEL_SEL | P33 analog output to the GPADC selection (0: VBG, 1: VDC13, 2: SYSVDD, 3: VTEMP, 4: PROGF, 5: VBAT/4, 6: LDO5V/4, 7: WVDD) |
| 0    | PMU_DET_EN | |

### ANA_CON5

| Bits | Name | Description |
|------|------|-------------|
| 7:6  | VDDIO_HD_SEL   | |
| 4:5  | VDDIOW_VOL_SEL | |
| 3:0  | VDDIOM_VOL_SEL | |

### ANA_CON6

| Bits | Name | Description |
|------|------|-------------|
| 2:0  | VDC13_VOL_SEL | (1.05-1.4 V, 50 mV/step) |

### ANA_CON7

| Bits | Name | Description |
|------|------|-------------|
| 6:4  | BTDCDC_OSC_SEL     | BT DC-DC freqency selection (0: 537 kHz, 1: 789 kHz, 2: 1.03 MHz, 3: 1.27 MHz, 4: 1.72 MHz, 5: 1.94 MHz, 6: 2.15 MHz, 7: 2.36 MHz) |
| 3:2  | BTDCDC_DUTY_SEL    | BT DC-DC duty cycle |
| 1:0  | BTDCDC_BIAS_HD_SEL | (1-2.5 uA, 0.5 uA/step) |

### ANA_CON9

| Bits | Name | Description |
|------|------|-------------|
| 5:4  | SYSVDD_VOL_HD_SEL | |
| 3:0  | SYSVDD_VOL_SEL | SYSVDD voltage selection (0.84-1.29 V, 30 mV/step) |

### VLVD_CON

| Bits | Name | Description |
|------|------|-------------|
| 7    | VLVD_PND     |  |
| 6    | VLVD_PND_CLR |  |
| 5:3  | VLVD_SEL | (1.9-2.6 V, 100 mV/step) |
| 2    | VLVD_OE | |
| 1    | VLVD_PS | |
| 0    | VLVD_EN | |

### RST_CON0

| Bits | Name | Description |
|------|------|-------------|
| 3    | VLVD_WKUP_EN | |
| 2    | VLVD_RST_EN  | |

### LRC_CON0

| Bits | Name | Description |
|------|------|-------------|
| 7    | RC32K_RNPS_SEL[0] | |
| 5:4  | RC32K_RPPS_SEL    | |
| 3:2  |                   | |
| 1    | RC32K_RN_TRIM     | |
| 0    | RC32K_EN          | |

### LRC_CON1

| Bits | Name | Description |
|------|------|-------------|
| 7    |                     | |
| 6:5  | RC32K_LDO_SEL       | |
| 4:2  | RC32K_CAP_SEL       | |
| 1:0  | RC32K_RNPS_SEL[2:1] | |

### ANA_KEEP

| Bits | Name | Description |
|------|------|-------------|
| 7    |                  | |
| 6    | PDIO_KEEP        | |
| 5:0  |                  | |

### VLD_KEEP

| Bits | Name | Description |
|------|------|-------------|
| 7    |                  | |
| 6    | WDT_EXPT_EN      | |
| 5    | SYS_VDD_KEEP     | |
| 4    | SYS_RST_KEEP     | |
| 3    | PWM_LED_KEEP     | |
| 2    | FLASH_KEEP       | |
| 1    | WKUP_KEEP        | |
| 0    | CLOCK_KEEP       | |

### CLK_CON0

| Bits | Name | Description |
|------|------|-------------|
| 7:3  |                  | |
| 2    | SYSPLL_DPLL_REF  | |
| 1:0  | PWM_LED_SEL      | |

### CHG_WKUP

| Bits | Name | Description |
|------|------|-------------|
| 7    |                        | |
| 6    | CHARGE_WKUP_PND_CLR    | |
| 5    | CHARGE_WKUP_EDGE_SEL   | |
| 4    | CHARGE_WKUP_EN         | |
| 3    |                        | |
| 2    | CHARGE_WKUP_SOURCE_SEL | |
| 1    | CHARGE_EDGE_DETECT_EN  | |
| 0    | CHARGE_LEVEL_DETECT_EN | |

### CHG_READ

| Bits | Name | Description |
|------|------|-------------|
| 7:1  |                  | |
| 0    | CHARGE_FULL_FLAG | |

### CHG_CON0

| Bits | Name | Description |
|------|------|-------------|
| 7:2  |                  | |
| 1    | CHGBG_EN         | |
| 0    | CHARGE_EN        | |

### CHG_CON1

| Bits | Name | Description |
|------|------|-------------|
| 7:4  | CHARGE_MA_SEL     | |
| 3:0  | CHARGE_FULL_V_SEL | |

### CHG_CON2

| Bits | Name | Description |
|------|------|-------------|
| 7    |                    | |
| 6:4  | CHARGE_FULL_mA_SEL | |
| 3:0  |                    | |

### LDO5V_CON

| Bits | Name | Description |
|------|------|-------------|
| 7    | LDO5V_PND ?         | |
| 6    | LDO5V_PND_CLR       | |
| 5    | LDO5V_DET           | |
| 3    | LDO5V_EDGE_WKUP_EN  | |
| 2    | LDO5V_LEVEL_WKUP_EN | |
| 1    | LDO5V_EDGE_SEL      | |
| 0    | LDO5V_EN            | |

### LVCMP_CON

| Bits | Name | Description |
|------|------|-------------|
| 7    | LVCMP_PND ?         | |
| 6    | LVCMP_PND_CLR       | |
| 5    | LVCMP_DET           | |
| 4    | LVCMP_CMP_SEL       | |
| 3    | LVCMP_EDGE_WKUP_EN  | |
| 2    | LVCMP_LEVEL_WKUP_EN | |
| 1    | LVCMP_EDGE_SEL      | |
| 0    | LVCMP_EN            | |

### L5DEM_CON

| Bits | Name | Description |
|------|------|-------------|
| 7    | L5DEM_PND ?         | |
| 6    | L5DEM_PND_CLR       | |
| 5    | L5DEM_DET           | |
| 4    |                     | |
| 3    | L5DEM_EDGE_WKUP_EN  | |
| 2    | L5DEM_LEVEL_WKUP_EN | |
| 1    | L5DEM_EDGE_SEL      | |
| 0    | L5DEM_EN            | |

### L5DEM_FLT

| Bits | Name | Description |
|------|------|-------------|
| 7:3  |                  | |
| 2:0  | L5DEM_FIT_SEL    | |

### WKUP_SUB

| Bits | Name | Description |
|------|------|-------------|
| 7:3  |                  | |
| 2    | IS_L5DEM_WKUP    | |
| 1    | IS_LDO5V_WKUP    | |
| 0    | IS_LVCMP_WKUP    | |

### L5V_CON0

| Bits | Name | Description |
|------|------|-------------|
| 7:5  |                  | |
| 4    | L5V_IM_S_SEL     | |
| 3    | L5V_IM_EN        | |
| 2    | L5V_VM_EN        | |
| 1    | L5V_RES_DET_EN   | |
| 0    | L5V_LOAD_EN      | |

### L5V_CON1

| Bits | Name | Description |
|------|------|-------------|
| 7:6  |                   | |
| 5:4  | L5V_VM_S_SEL      | |
| 3:2  |                   | |
| 1:0  | L5V_RES_DET_S_SEL | |

### WDT_CON

[Same as in the ordinary WDT_CON](index.md#wdt_cons)
