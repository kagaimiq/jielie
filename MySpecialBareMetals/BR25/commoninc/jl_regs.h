#ifndef _JL_REGS_H
#define _JL_REGS_H

#include <stdint.h>

static inline uint32_t reg32_read(uint32_t addr) {
	return *(volatile uint32_t*)addr;
}
static inline void reg32_write(uint32_t addr, uint32_t val) {
	*(volatile uint32_t*)addr = val;
}
static inline void reg32_wsmask(uint32_t addr, int shift, uint32_t mask, uint32_t val) {
	*(volatile uint32_t*)addr =
		(*(volatile uint32_t*)addr & ~(mask << shift)) | ((val & mask) << shift);
}
static inline uint32_t reg32_rsmask(uint32_t addr, int shift, uint32_t mask) {
	return (*(volatile uint32_t*)addr >> shift) & mask;
}

#define _REG_MKVAL(addr, shift, mask, val)	(((val) & (mask)) << (shift))
#define REG_MKVAL(regdef, val)			_REG_MKVAL(regdef, val)

#define _REG_GETVAL(addr, shift, mask, val)	(((val) >> (shift)) & (mask))
#define REG_GETVAL(regdef, val)			_REG_GETVAL(regdef, val)

#define _REG_SMASK(addr, shift, mask)	((mask) << (shift))
#define REG_SMASK(regdef)			_REG_SMASK(regdef)

/*////////////////////////////////////////////////////////////////////////////*/
/* CPU Core SFR */
/*================= CMNG ================*/
#define CMNG_base		0x100000

#define CMNG_SOFT_INT			0x00
#define CMNG_SOFT_SET			0x04
#define CMNG_SOFT_CLR			0x08
#define CMNG_CON			0x0C

/*================ SDTAP ================*/
#define SDTAP_base		0x100100

#define SDTAP_CON			0x00
#define SDTAP_KEY			0x04

/*================= MMU =================*/
// memory management unit
#define MMU_base		0x100300

#define MMU_CON				0x00	// control
#define 	MMU_CON_enable			MMU_CON, 0, 1		// mmu enable
#define MMU_TLB1_BEG			0x04	// TLB1 begin
#define MMU_TLB1_END			0x08	// TLB1 end

// mmu mapping @ 0x200000
// page size = 128 bytes
// tlb format:
//   entry = 16 bit
//     0..12  = physical page
//     13     = valid
//     14..15 = reserved

/*================= DSP =================*/
#define DSP_base		0x101000

#define DSP_CON				0x00
#define DSP_RING_OSC			0x04
#define DSP_CPASS_CON			0x08
#define DSP_CPASS_ADRH			0x0C
#define DSP_CPASS_ADRL			0x10
#define DSP_CPASS_BUF_LAST		0x14
#define DSP_CPREFETCH_ADRH		0x18
#define DSP_CPREFETCH_ADRL		0x1C
#define DSP_CACHE_MSG_CH		0x20
#define DSP_MEM_CON			0x24

/*================ DEBUG ================*/
#define DEBUG_base		0x101040

#define DEBUG_DSP_BF_CON		0x00
#define DEBUG_WR_EN			0x04
#define DEBUG_MSG			0x08
#define DEBUG_MSG_CLR			0x0C
#define DEBUG_CPU_WR_LIMH		0x10
#define DEBUG_CPU_WR_LIML		0x14
#define DEBUG_PRP_WR_LIMH		0x18
#define DEBUG_PRP_WR_LIML		0x1C
#define DEBUG_PRP_MMU_MSG		0x20
#define DEBUG_LSB_MMU_MSG_CH		0x24
#define DEBUG_PRP_WR_LIMIT_MSG		0x28
#define DEBUG_LSB_WR_LIMIT_CH		0x2C
#define DEBUG_CPU_PC_LIMH0		0x30
#define DEBUG_CPU_PC_LIML0		0x34
#define DEBUG_CPU_PC_LIMH1		0x38
#define DEBUG_CPU_PC_LIML1		0x3C
#define DEBUG_PRP_SRM_INV_MSG		0x40
#define DEBUG_LSB_SRM_INV_CH		0x44

/*================= FFT =================*/
// fast fourier transform
#define FFT_base		0x102000

#define FFT_CON				0x00	// control
#define FFT_CADR			0x04
#define FFT_TEST0			0x08
#define FFT_TEST1			0x0C

/*================= CORE ================*/
// cpu core regs
#define CORE_base		0x10F000
#define COREn_base(n)		(CORE_base + 0x10000 * (n))

#define CORE_DRn(n)			(0x00 + 0x4 * (n))	// gpr
#define CORE_SRn(n)			(0x40 + 0x4 * (n))	// sfr
#define CORE_RETI			CORE_SRn(0)	// reti
#define CORE_RETE			CORE_SRn(1)	// rete
#define CORE_RETX			CORE_SRn(2)	// retx
#define CORE_RETS			CORE_SRn(3)	// rets
#define CORE_PSR			CORE_SRn(5)	// psr
#define CORE_CNUM			CORE_SRn(6)	// cnum
#define CORE_ICFG			CORE_SRn(11)	// icfg
#define CORE_USP			CORE_SRn(12)	// usp
#define CORE_SSP			CORE_SRn(13)	// ssp
#define CORE_SP				CORE_SRn(14)	// sp
#define CORE_PCRS			CORE_SRn(15)	// pc
#define CORE_BPCON			0x80
#define CORE_BSP			0x84
#define CORE_BPn(n)			(0x88 + 0x4 * (n))
#define CORE_CMD_PAUSE			0x98
#define CORE_PMU_CON			0xC0
#define CORE_EMU_CON			0xD0
#define CORE_EMU_MSG			0xD4
#define CORE_EMU_SSP_H			0xD8
#define CORE_EMU_SSP_L			0xDC
#define CORE_EMU_USP_H			0xE0
#define CORE_EMU_USP_L			0xE4
#define CORE_TTMR_CON			0xEC	// tick timer control
#define CORE_TTMR_CON_enable			CORE_TTMR_CON, 0, 1	// enable
#define CORE_TTMR_CON_cpnd			CORE_TTMR_CON, 6, 1	// clear int pending
#define CORE_TTMR_CON_pnd			CORE_TTMR_CON, 7, 1	// int pending
#define CORE_TTMR_CNT			0xF0	// tick timer counter
#define CORE_TTMR_PRD			0xF4	// tick timer period
#define CORE_BANK_CON			0xF8
#define CORE_BANK_NUM			0xFC
#define CORE_ICFGn(n)			(0x100 + 0x4 * (n))	// interrupt config
#define 	CORE_ICFGi(i)			CORE_ICFGn((i) / 8), (((i) % 8) * 4), 0xf
#define 	CORE_ICFGi_enable(i)		CORE_ICFGn((i) / 8), (((i) % 8) * 4 + 0), 1
#define 	CORE_ICFGi_priority(i)		CORE_ICFGn((i) / 8), (((i) % 8) * 4 + 1), 0x7
#define CORE_IPNDn(n)			(0x180 + 0x4 * (n))	// interrupt pending
#define 	CORE_IPNDi(i)			CORE_IPNDn((i) / 32), ((i) % 32), 1
#define CORE_ETM_CON			0x1C0
#define CORE_ETM_PCn(n)			(0x1C4 + 0x4 * (n))
#define CORE_WP0_ADRH			0x1D4
#define CORE_WP0_ADRL			0x1D8
#define CORE_WP0_DATH			0x1DC
#define CORE_WP0_DATL			0x1E0
#define CORE_WP0_PC			0x1E4

/*////////////////////////////////////////////////////////////////////////////*/
/* Low Speed SFR */

/*================ CLOCK ================*/
// clock stuff
#define CLOCK_base		0x1E0000

#define CLOCK_PWR_CON			0x00
#define CLOCK_HTC_CON			0x04
#define CLOCK_SYS_DIV			0x08
#define CLOCK_CLK_CON0			0x0C
#define CLOCK_CLK_CON1			0x10
#define CLOCK_CLK_CON2			0x14
#define CLOCK_CLK_CON3			0x18
#define CLOCK_PLL_CON			0x40
#define CLOCK_PLL_CON1			0x44
#define CLOCK_PLL_INTF			0x48
#define CLOCK_PLL_DMAX			0x4C
#define CLOCK_PLL_DMIN			0x50
#define CLOCK_PLL_DSTP			0x54
#define CLOCK_PLL_CON2			0x58

/*================= RST =================*/
// reset stuff
#define RST_base		0x1E00C0

#define RST_SRC				0x00

/*================ MODE =================*/
// mode stuff
#define MODE_base		0x1E0100

#define MODE_CON			0x00

/*================ SYSTEM ===============*/
// system stuff
#define SYSTEM_base		0x1E0200

#define SYSTEM_CHIP_ID			0x00
#define SYSTEM_MBIST_CON		0x04

/*================ TIMER ================*/
// timer
#define TIMER0_base		0x1E0400
#define TIMER1_base		0x1E0500
#define TIMER2_base		0x1E0600
#define TIMER3_base		0x1E0700
#define TIMER4_base		0x1E0800
#define TIMER5_base		0x1E0900

#define TIMERx_CON			0x00	// control
#define 	TIMERx_CON_mode			TIMERx_CON, 0, 0x3	// timer mode [dis|count|io rising cap|io falling cap]
#define 	TIMERx_CON_ssel			TIMERx_CON, 2, 0x3	// clock sel [bus|io|osc|rc]
#define 	TIMERx_CON_pseta		TIMERx_CON, 4, 0x3	// prescaler (1) [1|4|16|64]
#define 	TIMERx_CON_psetb		TIMERx_CON, 6, 0x3	// prescaler (2) [1|2|256|512]
#define 	TIMERx_CON_pwmen		TIMERx_CON, 8, 1	// pwm enable
#define 	TIMERx_CON_pwminv		TIMERx_CON, 9, 1	// pwm invert
#define 	TIMERx_CON_pclr			TIMERx_CON, 14, 1	// clear pending int
#define 	TIMERx_CON_pnd			TIMERx_CON, 15, 1	// int pending
#define TIMERx_CNT			0x04	// counter
#define TIMERx_PRD			0x08	// period
#define TIMERx_PWM			0x0C	// pwm duty cycle

/*================ PCNT =================*/
// pulse counter
#define PCNT_base		0x1E1000

#define PCNT_CON			0x00	// control
#define PCNT_VAL			0x04	// value

/*================ GPCNT ================*/
// g pulse counter
#define GPCNT_base		0x1E1100

#define GPCNT_CON			0x00	// control
#define GPCNT_NUM			0x04	// number

/*================= SD ==================*/
// sd/mmc host
#define SD0_base		0x1E1400
#define SD1_base		0x1E1500

#define SDx_CON0			0x00	// control 0
#define 	SDx_CON0_firecmd		SDx_CON0, 0, 0x7	// fire a command transfer (5 = 48 bit resp, 6 = 136 (128) bit resp)
#define 	SDx_CON0_cpnd_cmd		SDx_CON0, 6, 1		// clear pending int (command)
#define 	SDx_CON0_pnd_cmd		SDx_CON0, 7, 1		// pending interrupt (command)
#define 	SDx_CON0_cpnd_dat		SDx_CON0, 14, 1		// clear pending int (data)
#define 	SDx_CON0_pnd_dat		SDx_CON0, 15, 1		// pending interrupt (data)
#define SDx_CON1			0x04	// control 1
#define 	SDx_CON1_enable			SDx_CON1, 0, 1		// enable
#define 	SDx_CON1_idleclken		SDx_CON1, 5, 1		// output clock even when idle
#define 	SDx_CON1_baud			SDx_CON1, 8, 0xff	// clock divider (n-1)
#define SDx_CON2			0x08	// control 2
#define 	SDx_CON2_blksize		SDx_CON2, 0, 0x1ff	// block size (n-1)
#define SDx_CPTR			0x0C	// command buffer address
#define SDx_DPTR			0x10	// data buffer address
#define SDx_CTU_CON			0x14	// ctu control
#define 	SDx_CTU_CON_enable		SDx_CTU_CON, 0, 1	// enable
#define 	SDx_CTU_CON_clr_err		SDx_CTU_CON, 4, 1	// clear error flag
#define 	SDx_CTU_CON_err			SDx_CTU_CON, 5, 1	// error flag
#define 	SDx_CTU_CON_clr_done		SDx_CTU_CON, 6, 1	// clear done flag
#define 	SDx_CTU_CON_done		SDx_CTU_CON, 7, 1	// done flag ? wtf ?
#define 	SDx_CTU_CON_firedat		SDx_CTU_CON, 8, 0x7	// fire a data transfer (5 = tx data, 6 = rx data)
#define SDx_CTU_CNT			0x18	// ctu count (block count n-1)

/*================= USB =================*/
// usb host/device
#define USB_base		0x1E1800

////// FROM BR21, MIGHT BE INCORRECT/INCOMPLETE! //////

#define USB_CON0			0x00	// control 0
#define 	USB_CON0_phy_on			USB_CON0, 0, 1		// usb phy enable
#define 	USB_CON0_io_mode		USB_CON0, 1, 1		// usb phy gpio mode
#define 	USB_CON0_usb_nrst		USB_CON0, 2, 1		// usb reset [assert|release]
#define 	USB_CON0_tm1			USB_CON0, 3, 1		// "short connect timeout"
#define 	USB_CON0_cid			USB_CON0, 4, 1		// usb mode [host|device]
#define 	USB_CON0_vbus			USB_CON0, 5, 1		// ?? vbus control ??
#define 	USB_CON0_usb_test		USB_CON0, 6, 1		// "usb test"
#define 	USB_CON0_latsel			USB_CON0, 8, 1		// "reserved"
#define 	USB_CON0_pdchkdp		USB_CON0, 9, 1		// D+ ext pulldown check en
#define 	USB_CON0_sof_ie			USB_CON0, 10, 1		// SOF int enable
#define 	USB_CON0_sie_ie			USB_CON0, 11, 1		// int enable
#define 	USB_CON0_clr_sofp		USB_CON0, 12, 1		// clear SOF int pending
#define 	USB_CON0_sof_pnd		USB_CON0, 13, 1		// SOF int pending
#define 	USB_CON0_sie_pnd		USB_CON0, 14, 1		// int pending (cleared by accessing the USB peripheral)
#define 	USB_CON0_chk_dpo		USB_CON0, 15, 1		// D+ ext pulldown check status
#define 	USB_CON0_se_dm			USB_CON0, 16, 1		// single-end D- status
#define 	USB_CON0_se_dp			USB_CON0, 17, 1		// single-end D+ status
#define 	USB_CON0_lowp_md		USB_CON0, 18, 1		// low power mode [en|dis]
#define USB_CON1			0x04	// control 1
#define 	USB_CON1_mc_dat			USB_CON1, 0, 0xff	// musb reg data
#define 	USB_CON1_mc_adr			USB_CON1, 8, 0x3f	// musb reg address
#define 	USB_CON1_mc_rnw			USB_CON1, 14, 1		// musb reg access [write|read]
#define 	USB_CON1_mc_ack			USB_CON1, 15, 1		// musb reg access done [busy|ready]
#define EP0_CNT				0x08	// EP0 count
#define EP1_CNT				0x0C	// EP1 count
#define EP2_CNT				0x10	// EP2 count
#define EP3_CNT				0x14	// EP3 count
#define EP4_CNT				0x18	// EP4 count
#define EP0_ADR				0x1C	// EP0 data address
#define EP1_TADR			0x20	// EP1 tx data address
#define EP1_RADR			0x24	// EP1 rx data address
#define EP2_TADR			0x28	// EP2 tx data address
#define EP2_RADR			0x2C	// EP2 rx data address
#define EP3_TADR			0x30	// EP3 tx data address
#define EP3_RADR			0x34	// EP3 rx data address
#define EP4_TADR			0x38	// EP4 tx data address
#define EP4_RADR			0x3C	// EP4 rx data address

/*================= ANA =================*/
// analog stuff
#define ANA_base		0x1E1900

#define ANA_WLA_CON0			0x00
#define ANA_WLA_CON1			0x04
#define ANA_WLA_CON2			0x08
#define ANA_WLA_CON3			0x0C
#define ANA_WLA_CON4			0x10
#define ANA_WLA_CON5			0x14
#define ANA_WLA_CON6			0x18
#define ANA_WLA_CON7			0x1C
#define ANA_WLA_CON8			0x20
#define ANA_WLA_CON9			0x24
#define ANA_WLA_CON10			0x28
#define ANA_WLA_CON11			0x2C
#define ANA_WLA_CON12			0x30
#define ANA_WLA_CON13			0x34
#define ANA_WLA_CON14			0x38
#define ANA_WLA_CON15			0x3C
#define ANA_WLA_CON16			0x40
#define ANA_WLA_CON17			0x44
#define ANA_WLA_CON18			0x48
#define ANA_WLA_CON19			0x4C
#define ANA_WLA_CON20			0x50
#define ANA_WLA_CON21			0x54
#define ANA_WLA_CON22			0x58
#define ANA_WLA_CON23			0x5C
#define ANA_WLA_CON24			0x60
#define ANA_WLA_CON25			0x64
#define ANA_WLA_CON26			0x68
#define ANA_WLA_CON27			0x6C
#define ANA_WLA_CON28			0x70
#define ANA_WLA_CON29			0x74
#define ANA_WLA_CON30			0x78
#define ANA_WLA_CON31			0x7C
#define ANA_WLA_CON32			0x80
#define ANA_WLA_CON33			0x84
#define ANA_WLA_CON34			0x88
#define ANA_WLA_CON35			0x8C
#define ANA_WLA_CON36			0x90
#define ANA_WLA_CON37			0x94
#define ANA_WLA_CON38			0x98
#define ANA_WLA_CON39			0x9C
#define ANA_DAA_CON0			0xC0
#define ANA_DAA_CON1			0xC4
#define 	ANA_DAA_CON1_amux_lr2lmix	ANA_DAA_CON1, 17, 1
#define 	ANA_DAA_CON1_amux_lr2rmix	ANA_DAA_CON1, 18, 1
#define 	ANA_DAA_CON1_amux0l_biasen	ANA_DAA_CON1, 19, 1
#define 	ANA_DAA_CON1_amux0l_en		ANA_DAA_CON1, 20, 1
#define 	ANA_DAA_CON1_amux0r_biasen	ANA_DAA_CON1, 21, 1
#define 	ANA_DAA_CON1_amux0r_en		ANA_DAA_CON1, 22, 1
#define 	ANA_DAA_CON1_amux1l_biasen	ANA_DAA_CON1, 23, 1
#define 	ANA_DAA_CON1_amux1l_en		ANA_DAA_CON1, 24, 1
#define 	ANA_DAA_CON1_amux1r_biasen	ANA_DAA_CON1, 25, 1
#define 	ANA_DAA_CON1_amux1r_en		ANA_DAA_CON1, 26, 1
#define 	ANA_DAA_CON1_amux_biasen	ANA_DAA_CON1, 27, 1
#define 	ANA_DAA_CON1_amux_en		ANA_DAA_CON1, 28, 1
#define 	ANA_DAA_CON1_amux_gain		ANA_DAA_CON1, 29, 1	// 2x gain
#define 	ANA_DAA_CON1_amux_mute		ANA_DAA_CON1, 30, 1
#define ANA_DAA_CON2			0xC8
#define ANA_DAA_CON3			0xCC
#define ANA_DAA_CON4			0xD0
#define ANA_DAA_CON7			0xDC
#define ANA_ADA_CON0			0xE0
#define ANA_ADA_CON1			0xE4
#define ANA_ADA_CON2			0xE8
#define ANA_ADA_CON3			0xEC
#define ANA_ADA_CON4			0xF0

/*================= SPI =================*/
// spi interface
#define SPI0_base		0x1E1C00
#define SPI1_base		0x1E1D00
#define SPI2_base		0x1E1E00

#define SPIx_CON			0x00	// control
#define 	SPIx_CON_spie			SPIx_CON, 0, 1		// spi enable
#define 	SPIx_CON_slave			SPIx_CON, 1, 1		// slave mode
#define 	SPIx_CON_cse			SPIx_CON, 2, 1		// enable cs
#define 	SPIx_CON_bidir			SPIx_CON, 3, 1		// full-duplex mode
#define 	SPIx_CON_se			SPIx_CON, 4, 1		// data sample [on ck rising edge|on ck falling edge]
#define 	SPIx_CON_ue			SPIx_CON, 5, 1		// data update [on ck rising edge|on ck falling edge]
#define 	SPIx_CON_ckid			SPIx_CON, 6, 1		// ck polarity [low when idle|high when idle]
#define 	SPIx_CON_csid			SPIx_CON, 7, 1		// cs polarity [low when idle|high when idle]
#define 	SPIx_CON_datw			SPIx_CON, 10, 0x3	// data width [1 bit|2 bits|4 bits]
#define 	SPIx_CON_dir			SPIx_CON, 12, 1		// transfer direction [tx|rx]
#define 	SPIx_CON_ie			SPIx_CON, 13, 1		// int enable
#define 	SPIx_CON_pclr			SPIx_CON, 14, 1		// pending int clear
#define 	SPIx_CON_pnd			SPIx_CON, 15, 1		// pending int
#define SPIx_BAUD			0x04	// baudrate
#define SPIx_BUF			0x08	// data reg
#define SPIx_ADR			0x0C	// dma address
#define SPIx_CNT			0x10	// dma length (triggers dma)

/*================ UART =================*/
// uart interface
#define UART0_base		0x1E2000
#define UART1_base		0x1E2100
#define UART2_base		0x1E2200

////// FROM BR21, MIGHT BE INCORRECT/INCOMPLETE! //////

#define UARTx_CON0			0x00	// control 0
#define 	UARTx_CON0_uten			UARTx_CON0, 0, 1	// uart enable
#define 	UARTx_CON0_m9en			UARTx_CON0, 1, 1	// frame size [8 bit|9 bit]
#define 	UARTx_CON0_txie			UARTx_CON0, 2, 1	// tx int enable
#define 	UARTx_CON0_rxie			UARTx_CON0, 3, 1	// rx int enable
#define 	UARTx_CON0_divs			UARTx_CON0, 4, 1	// baudrate predivide [/4|/3]
#define 	UARTx_CON0_ot_ie		UARTx_CON0, 5, 1	// timeout interrupt enable
#define 	UARTx_CON0_rx_mode		UARTx_CON0, 6, 1	// rx mode [pio|dma]
#define 	UARTx_CON0_rdc			UARTx_CON0, 7, 1	// received amount clear
#define 	UARTx_CON0_rb8			UARTx_CON0, 8, 1	// rx frame bit8
#define 	UARTx_CON0_tb8			UARTx_CON0, 9, 1	// tx frame bit8
#define 	UARTx_CON0_clr_otpnd		UARTx_CON0, 10, 1	// clear timeout pending
#define 	UARTx_CON0_otpnd		UARTx_CON0, 11, 1	// timeout pending
#define 	UARTx_CON0_clrrpnd		UARTx_CON0, 12, 1	// clear rx pending
#define 	UARTx_CON0_clrtpnd		UARTx_CON0, 13, 1	// clear tx pending
#define 	UARTx_CON0_rpnd			UARTx_CON0, 14, 1	// rx pending
#define 	UARTx_CON0_tpnd			UARTx_CON0, 15, 1	// tx pending
#define UARTx_CON1			0x04	// control 1
#define 	UARTx_CON1_rtse			UARTx_CON1, 0, 1	// enable rts
#define 	UARTx_CON1_rts_dmaen		UARTx_CON1, 1, 1	// rts dma enable ??
#define 	UARTx_CON1_ctse			UARTx_CON1, 2, 1	// enable cts
#define 	UARTx_CON1_ctsie		UARTx_CON1, 3, 1	// cts int enable
#define 	UARTx_CON1_baud_frac		UARTx_CON1, 4, 0x3	// baudrate fraction
#define 	UARTx_CON1_clrrts		UARTx_CON1, 13, 1	// clear rts
#define UARTx_BAUD			0x08	// baudrate
#define UARTx_BUF			0x0C	// data reg
#define UARTx_OTCNT			0x10	// timeout
#define UARTx_TXADR			0x14	// tx dma address
#define UARTx_TXCNT			0x18	// tx dma length (triggers dma)
#define UARTx_RXSADR			0x1C	// rx dma start address
#define UARTx_RXEADR			0x20	// rx dma end address
#define UARTx_RXCNT			0x24	// rx dma length
#define UARTx_HRXCNT			0x28	// rx dma received length

/*================= IIC =================*/
// i2c interface
#define IIC_base		0x1E2400

#define IIC_CON0			0x00	// control 0
#define IIC_BUF				0x04	// data reg
#define IIC_BAUD			0x08	// baudrate
#define IIC_CON1			0x0C	// control 1

/*================= PAP =================*/
// parralel active port
#define PAP_base		0x1E2800

#define PAP_CON				0x00	// control
#define PAP_DAT0			0x04	// data reg 0
#define PAP_DAT1			0x08	// data reg 1
#define PAP_BUF				0x0C	// data reg ...
#define PAP_ADR				0x10	// dma address
#define PAP_CNT				0x14	// dma length

/*================= SS ==================*/
// spdif slave
#define SS_base			0x1E2B00

#define SS_CON				0x00	// control
#define SS_SR_CNT			0x04
#define SS_IO_CON			0x08
#define SS_DMA_CON			0x0C	// dma control
#define SS_DMA_LEN			0x10	// dma length
#define SS_DAT_ADR			0x14	// data addresss
#define SS_INF_ADR			0x18	// info address
#define SS_CSB0				0x1C
#define SS_CSB1				0x20
#define SS_CSB2				0x24
#define SS_CSB3				0x28
#define SS_CSB4				0x2C
#define SS_CSB5				0x30

/*================ RDEC =================*/
// r decoder
#define RDEC0_base		0x1E2C00
#define RDEC1_base		0x1E4400
#define RDEC2_base		0x1E4500

#define RDECx_CON			0x00	// control
#define RDECx_DAT			0x04
#define RDECx_SMP			0x08

/*================ PLNK =================*/
// pdm link
#define PLNK_base		0x1E2D00

#define PLNK_CON			0x00	// control
#define PLNK_SMR			0x04	// sample rate ?
#define PLNK_ADR			0x08	// data address
#define PLNK_LEN			0x0C	// data length

/*================ ALNK =================*/
// audio link
#define ALNK0_base		0x1E2E00
#define ALNK1_base		0x1E3300

#define ALNK_CON0			0x00	// control 0
#define ALNK_CON1			0x04	// control 1
#define ALNK_CON2			0x08	// control 2
#define ALNK_CON3			0x0C	// control 3
#define ALNK_ADR0			0x10	// data address 0
#define ALNK_ADR1			0x14	// data address 1
#define ALNK_ADR2			0x18	// data address 2
#define ALNK_ADR3			0x1C	// data address 3
#define ALNK_LEN			0x20	// data length

/*================ AUDIO ================*/
// audio controller
#define AUDIO_base		0x1E2F00

#define AUDIO_DAC_CON			0x00	// dac control
#define 	AUDIO_DAC_CON_dacsr		AUDIO_DAC_CON, 0, 0xf	// 96000,88200,64000,x, 48000,44100,32000,x, 24000,22050,16000,x, 12000,11025,8000,x
#define 	AUDIO_DAC_CON_dacen		AUDIO_DAC_CON, 4, 1	// dac start
#define 	AUDIO_DAC_CON_dacie		AUDIO_DAC_CON, 5, 1	// dac interrupt enable
#define 	AUDIO_DAC_CON_cpnd		AUDIO_DAC_CON, 6, 1	// clear pending int
#define 	AUDIO_DAC_CON_pnd		AUDIO_DAC_CON, 7, 1	// interrupt pending
#define AUDIO_DAC_ADR			0x04	// dac data address
#define AUDIO_DAC_LEN			0x08	// dac data length
#define AUDIO_DAC_PNS			0x0C
#define AUDIO_DAC_HRP			0x10
#define AUDIO_DAC_SWP			0x14
#define AUDIO_DAC_SWN			0x18
#define AUDIO_DAC_VL0			0x20	// dac volume?
#define AUDIO_DAC_TM0			0x28	// dac trim?
#define AUDIO_DAC_DTB			0x34
#define AUDIO_DAC_DPD			0x38
#define AUDIO_DAC_COP			0x3C
#define AUDIO_ADC_CON			0x40	// adc control
#define AUDIO_ADC_ADR			0x44	// adc data address
#define AUDIO_ADC_LEN			0x48	// adc data length
#define AUDIO_ADC_PNS			0x4C
#define AUDIO_ADC_HWP			0x50
#define AUDIO_ADC_SRP			0x54
#define AUDIO_ADC_SRN			0x58

/*================ MCPWM ================*/
// motor control pwm
#define MCPWM_base		0x1E3000

#define MCPWM_TMRn_CON(n)		(0x00 + (n) * 0xC)	// timer control
#define MCPWM_TMRn_CNT(n)		(0x04 + (n) * 0xC)	// timer counter
#define MCPWM_TMRn_PR(n)		(0x08 + (n) * 0xC)	// timer period
#define MCPWM_FPIN_CON			0x60			// fpin control
#define MCPWM_CHn_CON0(n)		(0x64 + (n) * 0x10)	// channel control 0
#define MCPWM_CHn_CON1(n)		(0x68 + (n) * 0x10)	// channel control 1
#define MCPWM_CHn_CMPH(n)		(0x6C + (n) * 0x10)	// channel compare hi
#define MCPWM_CHn_CMPL(n)		(0x70 + (n) * 0x10)	// channel compare low
#define MCPWM_CON0			0xE4			// control

/*================= ADC =================*/
// analog-digital converter
#define ADC_base		0x1E3100

////// FROM BR21, MIGHT BE INCORRECT/INCOMPLETE! maybe... //////

#define ADC_CON				0x00	// control
#define 	ADC_CON_adcbaud			ADC_CON, 0, 0x7		// clock divider [/1|/6|/12|/24|/48|/72|/96|/128] (<= 1MHz)
#define 	ADC_CON_adcae			ADC_CON, 3, 1		// analog enable
#define 	ADC_CON_adcen			ADC_CON, 4, 1		// enable
#define 	ADC_CON_adcie			ADC_CON, 5, 1		// interrupt enable
#define 	ADC_CON_cpnd			ADC_CON, 6, 1		// clear pending int
#define 	ADC_CON_pnd			ADC_CON, 7, 1		// interrupt pending
#define 	ADC_CON_chsel			ADC_CON, 8, 0xf		// channel select [adc0..14, 15=p33]
#define 	ADC_CON_waittime		ADC_CON, 12, 0xf	// startup delay (in 8x clocks)
#define ADC_RES				0x04	// result

/*================= IR ==================*/
// ir decoder
#define IR_base			0x1E3200

#define IR_RFLT_CON			0x00	// rflt control

/*================= OSA =================*/
#define OSA_base		0x1E3400

#define OSA_CON				0x00	// control

/*================= CRC =================*/
// crc16 ccitt
#define CRC_base		0x1E3500

#define CRC_FIFO			0x00	// fifo
#define CRC_REG				0x04	// shift reg

/*================ LRCT =================*/
#define LRCT_base		0x1E3600

#define LRCT_CON			0x00	// control
#define LRCT_NUM			0x04	// number

/*================ EFUSE ================*/
#define EFUSE_base		0x1E3700

#define EFUSE_CON			0x00	// control
#define EFUSE_ME			0x20

/*================= RAND ================*/
// random number generator
#define RAND_base		0x1E3B00

#define RAND_R64L			0x00	// low 32 bits
#define RAND_R64H			0x04	// high 32 bits

/*================= CTM =================*/
#define CTM_base		0x1E3C00

#define CTM_CON0			0x00	// control 0
#define CTM_CON1			0x04	// control 1
#define CTM_ADR				0x08

/*================= P33 =================*/
#define P33_base		0x1E3E00

#define P33_PMU_CON			0x00	// pmu control
#define P33_RTC_CON			0x04	// rtc control
#define P33_SPI_CON			0x08	// spi control
#define P33_SPI_DAT			0x0C	// spi data

/*================= DMA =================*/
// direct memory access
#define DMA_base		0x1E3F00

#define DMA_PRI0			0x00
#define DMA_PRI1			0x04
#define DMA_PRI2			0x08
#define DMA_PRI3			0x0C
#define DMA_MSG				0x20
#define DMA_MSG_CH			0x24
#define DMA_RDL				0x28
#define DMA_RDH				0x2C
#define DMA_WRL				0x30
#define DMA_WRH				0x34

/*=============== PERIENC ===============*/
// peripheral encryptor
#define PERIENC_base		0x1E4100

#define PERIENC_CON			0x00	// control
#define 	PERIENC_CON_en_spi0dma		PERIENC_CON, 0, 1	// enable for SPI0 DMA transfers
//#define 	PERIENC_CON_en_konata		PERIENC_CON, 1, 1	// enable for something
#define 	PERIENC_CON_en_sd0data		PERIENC_CON, 2, 1	// enable for SD0 data transfers
#define 	PERIENC_CON_rstkey		PERIENC_CON, 7, 1	// reset key register
#define PERIENC_KEY			0x04	// key
#define PERIENC_ADR			0x08	// "address" (key ^ (ADR >> 2)), something like that

/*================= SBC =================*/
// subband coding (sbc) codec
#define SBC_base		0x1E4200

#define SBC_CON0			0x00	// control
#define SBC_DEC_SRC_ADR			0x04	// decoder source address
#define SBC_DEC_DST_ADR			0x08	// decoder dest address
#define SBC_DEC_PCM_WCNT		0x0C	// decoder pcm write length
#define SBC_DEC_INBUF_LEN		0x10	// decoder input buffer length
#define SBC_ENC_SRC_ADR			0x14	// encoder source address
#define SBC_ENC_DST_ADR			0x18	// encoder dest address
#define SBC_DEC_DST_BASE		0x1C
#define SBC_RAM_CFG			0x20

/*================= AES =================*/
// advanced encryption standard (aes) engine
#define AES_base		0x1E4300

#define AES_CON				0x00	// control key
#define AES_DATIN			0x04	// input data
#define AES_KEY				0x08	// key
#define AES_ENCRES0			0x0C	// encryped result 0
#define AES_ENCRES1			0x10	// encryped result 1
#define AES_ENCRES2			0x14	// encryped result 2
#define AES_ENCRES3			0x18	// encryped result 3
#define AES_NONCE			0x1C	// nonce
#define AES_HEADER			0x20
#define AES_SRCADR			0x24	// source address
#define AES_DSTADR			0x28	// dest address
#define AES_CTCNT			0x2C
#define AES_TAGLEN			0x30	// tag length
#define AES_TAGRES0			0x34	// tag result 0
#define AES_TAGRES1			0x38	// tag result 1
#define AES_TAGRES2			0x3C	// tag result 2
#define AES_TAGRES3			0x40	// tag result 3

/*================ PORT =================*/
// gpio port
#define PORTA_base		0x1E5000
#define PORTB_base		0x1E5040
#define PORTC_base		0x1E5080
#define PORTD_base		0x1E50C0

#define PORTx_OUT			0x00	// port output reg
#define 	PORTx_OUTn(n)			PORTx_OUT, (n), 1	// 0=low, 1=high
#define PORTx_IN			0x04	// port input reg
#define 	PORTx_INn(n)			PORTx_IN, (n), 1	// 0=low, 1=high
#define PORTx_DIR			0x08	// port direction reg
#define 	PORTx_DIRn(n)			PORTx_DIR, (n), 1	// 0=out, 1=in [[MStar OEN]]
#define PORTx_DIE			0x0C	// port digital input enable
#define 	PORTx_DIEn(n)			PORTx_DIE, (n), 1	// 0=disable, 1=enable
#define PORTx_PU			0x10	// port pullup enable
#define 	PORTx_PUn(n)			PORTx_PU, (n), 1	// 0=disable, 1=enable
#define PORTx_PD			0x14	// port pulldown enable
#define 	PORTx_PDn(n)			PORTx_PD, (n), 1	// 0=disable, 1=enable
#define PORTx_HD0			0x18
#define PORTx_HD1			0x1C
#define PORTx_DIEH			0x20

/*================ USB_IO ===============*/
// usb gpio port
#define USBIO_base		0x1E5100

////// FROM BR21, MIGHT BE INCORRECT/INCOMPLETE! //////

#define USBIO_CON0			0x00	// control 0
#define 	USBIO_CON0_dpout		USBIO_CON0, 0, 1	// D+ output level
#define 	USBIO_CON0_dmout		USBIO_CON0, 1, 1	// D- output level
#define 	USBIO_CON0_dpie			USBIO_CON0, 2, 1	// D+ direction [out|in]
#define 	USBIO_CON0_dmie			USBIO_CON0, 3, 1	// D- direction [out|in]
#define 	USBIO_CON0_dppd			USBIO_CON0, 4, 1	// D+ pulldown enable
#define 	USBIO_CON0_dmpd			USBIO_CON0, 5, 1	// D- pulldown enable
#define 	USBIO_CON0_dppu			USBIO_CON0, 6, 1	// D+ pullup enable
#define 	USBIO_CON0_dmpu			USBIO_CON0, 7, 1	// D- pullup enable
#define 	USBIO_CON0_pm			USBIO_CON0, 8, 1	// "for test"
#define 	USBIO_CON0_dpdie		USBIO_CON0, 9, 1	// D+ digital in enable
#define 	USBIO_CON0_dmdie		USBIO_CON0, 10, 1	// D- digital in enable
#define 	USBIO_CON0_usb_io_mode		USBIO_CON0, 11, 1	// io mux mode
#define 	USBIO_CON0_usb_sr		USBIO_CON0, 12, 1	// slew rate enable
#define USBIO_CON1			0x04	// control 1
#define 	USBIO_CON1_dpin			USBIO_CON1, 0, 1	// usb D+ input level
#define 	USBIO_CON1_dmin			USBIO_CON1, 1, 1	// usb D- input level

/*================ WAKEUP ===============*/
// gpio wakeup
#define WAKEUP_base		0x1E5108

#define WAKEUP_CON0			0x00	// control 0
#define WAKEUP_CON1			0x04	// control 1
#define WAKEUP_CON2			0x08	// control 2
#define WAKEUP_CON3			0x0C	// control 3

/*================ IOMAP ================*/
// port io map
#define IOMAP_base		0x1E5118

#define IOMAP_CON0			0x00
#define 	IOMAP_CON0_sd0cken		IOMAP_CON0, 0, 1	// SD0 clock enable
#define 	IOMAP_CON0_sd0dten		IOMAP_CON0, 1, 1	// SD0 data enable
#define 	IOMAP_CON0_spi0ios		IOMAP_CON0, 2, 0x1	// SPI0 io mapping sel
#define 	IOMAP_CON0_ut0ios		IOMAP_CON0, 3, 0x3	// UART0 io mapping select
#define 	IOMAP_CON0_sd0ios		IOMAP_CON0, 8, 0x7	// SD0 io mapping sel
#define IOMAP_CON1			0x04
#define 	IOMAP_CON1_ut1ios		IOMAP_CON1, 2, 0x3	// UART1 io mapping sel
#define 	IOMAP_CON1_spi1ios		IOMAP_CON1, 4, 0x1	// SPI1 io mapping sel
#define 	IOMAP_CON1_sfcios		IOMAP_CON1, 5, 0x1	// SFC io mapping sel
#define 	IOMAP_CON1_ut2ios		IOMAP_CON1, 14, 0x3	// UART2 io mapping sel
#define 	IOMAP_CON1_spi2ios		IOMAP_CON1, 16, 0x1	// SPI2 io mapping sel
#define 	IOMAP_CON1_iicios		IOMAP_CON1, 18, 0x3	//MAYBE!! IIC io mapping sel
#define IOMAP_CON2			0x08
#define IOMAP_CON3			0x0C
#define 	IOMAP_CON3_ut0mxs		IOMAP_CON3, 0, 0x7	// UART0 mux sel [0-3=iomux]
#define 	IOMAP_CON3_ut0ioen		IOMAP_CON3, 3, 1	// UART0 io enable
#define 	IOMAP_CON3_ut1mxs		IOMAP_CON3, 4, 0x7	// UART1 mux sel
#define 	IOMAP_CON3_ut1ioen		IOMAP_CON3, 7, 1	// UART1 io enable
#define 	IOMAP_CON3_ut2mxs		IOMAP_CON3, 8, 0x7	// UART2 mux sel
#define 	IOMAP_CON3_ut2ioen		IOMAP_CON3, 11, 1	// UART2 io enable
#define IOMAP_CON4			0x10
#define IOMAP_CON5			0x14

/*================ PLED =================*/
// pwm led
#define PLED_base		0x1E5200

#define PLED_CON0			0x00	// control
#define PLED_CON1			0x04	// control
#define PLED_CON2			0x08	// control
#define PLED_CON3			0x0C	// control
#define PLED_BRI_PRDL			0x10	// brightness period low
#define PLED_BRI_PRDH			0x14	// brightness period hi
#define PLED_BRI_DUTY0L			0x18	// brightness duty 0 low
#define PLED_BRI_DUTY0H			0x1C	// brightness duty 0 hi
#define PLED_BRI_DUTY1L			0x20	// brightness duty 1 low
#define PLED_BRI_DUTY1H			0x24	// brightness duty 1 hi
#define PLED_PRD_DIVL			0x28	// period divider low
#define PLED_DUTY0			0x2C	// duty 0
#define PLED_DUTY1			0x30	// duty 1
#define PLED_DUTY2			0x34	// duty 2
#define PLED_DUTY3			0x38	// duty 3
#define PLED_CNT_RD			0x3C	// counter read

/*================= LCD =================*/
// liquid crystal display (lcd) controller
#define LCD_base		0x1E5300

#define LCD_CON0			0x00	// control
#define LCD_SEG_IOEN0			0x04	// segment io enable 0
#define LCD_SEG_IOEN1			0x08	// segment io enable 1

/*////////////////////////////////////////////////////////////////////////////*/
/* High Speed SFR */

/*================= SFC =================*/
// serial/spi flash controller
#define SFC_base		0x1F0200

#define SFC_CON				0x00	// control
#define 	SFC_CON_enable			SFC_CON, 0, 1		// enable

#define SFC_BAUD			0x04	// baudrate
#define SFC_CODE			0x08
#define SFC_BASE_ADR			0x0C	// map offset in flash
#define SFC_QUCNT			0x10

/*=============== SFCENC ================*/
// sfc encryptor
#define SFCENC_base		0x1F0300

#define SFCENC_CON			0x00	// control
#define 	SFCENC_CON_enable		SFCENC_CON, 0, 1	// enable
#define 	SFCENC_CON_bit1			SFCENC_CON, 1, 1	// ?? cleared
#define SFCENC_KEY			0x04	// key
#define SFCENC_UNENC_ADRH		0x08
#define SFCENC_UNENC_ADRL		0x0C
#define SFCENC_LENC_ADRH		0x10
#define SFCENC_LENC_ADRL		0x14

/*================ PSRAM ================*/
// spi psram controller (ABSENT!)
#define PSRAM_base		0x1F0500

#define PSRAM_CON			0x00	// control
#define PSRAM_BAUD			0x04	// baudrate
#define PSRAM_QUCNT			0x08

/*================= DCP =================*/
#define DCP_base		0x1F1300

#define DCP_CON				0x00	// control
#define DCP_ADR				0x04	// address

/*================= EQ ==================*/
// equalizer
#define EQ_base			0x1F1500

#define EQ_CON0				0x00	// control 0
#define EQ_CON1				0x04	// control 1
#define EQ_DATAI_ADR			0x08	// input data address
#define EQ_DATAO_ADR			0x0C	// output data address
#define EQ_DATA_LEN			0x10	// data length
#define EQ_FLT_ADR			0x14	// flt address

/*================= SRC =================*/
// sample rate converter
#define SRC_base		0x1F1600

#define SRC_CON0			0x00	// control 0
#define SRC_CON1			0x04	// control 1
#define SRC_CON2			0x08	// control 2
#define SRC_CON3			0x0C	// control 3
#define SRC_IDAT_ADR			0x10	// input data address
#define SRC_IDAT_LEN			0x14	// input data length
#define SRC_ODAT_ADR			0x18	// output data address
#define SRC_ODAT_LEN			0x1C	// output data length
#define SRC_FLTB_ADR			0x20	// fltb address

/*================= FM ==================*/
// fm radio
#define FM_base			0x1F1700

#define FM_CON				0x00	// control
#define FM_BASE				0x04
#define FM_ADC_CON			0x08	// adc control
#define FM_ADC_CON1			0x0C	// adc control 1
#define FM_HF_CON0			0x10	// hf control 0
#define FM_HF_CON1			0x14	// hf control 1
#define FM_HF_CRAM			0x18
#define FM_HF_CRAM2			0x1C
#define FM_HF_DRAM			0x20
#define FM_LF_CON			0x24	// lf control
#define FM_LF_RES			0x28
#define FM_FMRX_CON4			0x2C	// fm rx control 4
#define FM_FMRX_CON5			0x30	// fm rx control 5
#define FM_TX_CON0			0x34	// tx control 0
#define 	FM_TX_CON0_buffslice		FM_TX_CON0, 4, 1	// current buffer slice
#define FM_TX_CON1			0x38	// tx control 1
#define 	FM_TX_CON1_cpnd			FM_TX_CON1, 6, 1	// clear pending
#define 	FM_TX_CON1_pnd			FM_TX_CON1, 7, 1	// interrupt pending
#define FM_TX_PILOT			0x3C
#define FM_TX_SYN_GAIN			0x40
#define FM_TX_MUL			0x44
#define FM_TX_ADR			0x48
#define FM_TX_LEN			0x4C
#define FM_TX_FREQ			0x50
#define FM_TX_BASE_ADR			0x54

/*================= WL ==================*/
#define WL_base			0x1F1800

#define WL_CON0				0x00	// control 0
#define WL_CON3				0x04	// control 3
#define WL_LOFC_CON			0x08	// lofc control
#define WL_LOFC_RES			0x0C

#endif