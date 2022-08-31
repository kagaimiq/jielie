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

/*////////////////////////////////////////////////////////////////////////////*/
/* Low Speed SFR */

/*================ CLOCK ================*/
#define CLOCK_BASE		0x1E0000

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

/*================ TIMER ================*/
#define TIMER0_BASE		0x1E0400
#define TIMER1_BASE		0x1E0500
#define TIMER2_BASE		0x1E0600
#define TIMER3_BASE		0x1E0700
#define TIMER4_BASE		0x1E0800
#define TIMER5_BASE		0x1E0900

#define TIMERx_CON			0x00	// control reg
#define 	TIMERx_CON_MODE			TIMERx_CON, 0, 0x3	// timer mode [dis|count|io rising cap|io falling cap]
#define 	TIMERx_CON_SSEL			TIMERx_CON, 2, 0x3	// clock sel [bus|io|osc|rc]
#define 	TIMERx_CON_PSETa		TIMERx_CON, 4, 0x3	// prescaler (1) [1|4|16|64]
#define 	TIMERx_CON_PSETb		TIMERx_CON, 6, 0x3	// prescaler (2) [1|2|256|512]
#define 	TIMERx_CON_PWMEN		TIMERx_CON, 8, 1	// pwm enable
#define 	TIMERx_CON_PWMINV		TIMERx_CON, 9, 1	// pwm invert
#define 	TIMERx_CON_PCLR			TIMERx_CON, 14, 1	// clear pending int
#define 	TIMERx_CON_PND			TIMERx_CON, 15, 1	// int pending
#define TIMERx_CNT			0x04	// counter
#define TIMERx_PRD			0x08	// period
#define TIMERx_PWM			0x0C	// pwm duty cycle

/*================= ANA =================*/
#define ANA_BASE		0x1E1900

//blah blah blah WLA stuff

#define ANA_DAA_CON0			0xC0
#define ANA_DAA_CON1			0xC4
#define 	ANA_DAA_CON1_amux_lrmix		ANA_DAA_CON1, 17, 0x3	// mixing [L=L R=R|L=L+R R=0|L=0 R=L+R|L=R=L+R]
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
#define SPI0_BASE		0x1E1C00
#define SPI1_BASE		0x1E1D00
#define SPI2_BASE		0x1E1E00

#define SPIx_CON			0x00	// control reg
#define 	SPIx_CON_SPIE			SPIx_CON, 0, 1		// spi enable
#define 	SPIx_CON_SLAVE			SPIx_CON, 1, 1		// slave mode
#define 	SPIx_CON_CSE			SPIx_CON, 2, 1		// enable cs
#define 	SPIx_CON_BIDIR			SPIx_CON, 3, 1		// full-duplex mode
#define 	SPIx_CON_SE			SPIx_CON, 4, 1		// data sample [on ck rising edge|on ck falling edge]
#define 	SPIx_CON_UE			SPIx_CON, 5, 1		// data update [on ck rising edge|on ck falling edge]
#define 	SPIx_CON_CKID			SPIx_CON, 6, 1		// ck polarity [low when idle|high when idle]
#define 	SPIx_CON_CSID			SPIx_CON, 7, 1		// cs polarity [low when idle|high when idle]
#define 	SPIx_CON_DATW			SPIx_CON, 10, 0x3	// data width [1 bit|2 bits|4 bits]
#define 	SPIx_CON_DIR			SPIx_CON, 12, 1		// transfer direction [tx|rx]
#define 	SPIx_CON_IE			SPIx_CON, 13, 1		// int enable
#define 	SPIx_CON_PCLR			SPIx_CON, 14, 1		// pending int clear
#define 	SPIx_CON_PND			SPIx_CON, 15, 1		// pending int
#define SPIx_BAUD			0x04	// baudrate
#define SPIx_BUF			0x08	// data reg
#define SPIx_ADR			0x0C	// dma address
#define SPIx_CNT			0x10	// dma length (iirc it triggers dma)

/*================ UART =================*/
#define UART0_BASE		0x1E2000
#define UART1_BASE		0x1E2100
#define UART2_BASE		0x1E2200

#define UARTx_CON0			0x00	// control reg 0
#define 	UARTx_CON0_UTEN			UARTx_CON0, 0, 1	// uart enable
#define 	UARTx_CON0_M9EN			UARTx_CON0, 1, 1	// frame size [8 bit|9 bit]
#define 	UARTx_CON0_TXIE			UARTx_CON0, 2, 1	// tx int enable
#define 	UARTx_CON0_RXIE			UARTx_CON0, 3, 1	// rx int enable
#define 	UARTx_CON0_DIVS			UARTx_CON0, 4, 1	// baudrate predivide [/4|/3]
#define 	UARTx_CON0_OTIE			UARTx_CON0, 5, 1	// timeout interrupt enable
#define 	UARTx_CON0_RXMODE		UARTx_CON0, 6, 1	// rx mode [pio|dma]
#define 	UARTx_CON0_RDC			UARTx_CON0, 7, 1	// received amount clear
#define 	UARTx_CON0_RB8			UARTx_CON0, 8, 1	// rx frame bit8
#define 	UARTx_CON0_TB8			UARTx_CON0, 9, 1	// tx frame bit8
#define 	UARTx_CON0_CLROTPND		UARTx_CON0, 10, 1	// clear timeout pending
#define 	UARTx_CON0_OTPND		UARTx_CON0, 11, 1	// timeout pending
#define 	UARTx_CON0_CLRRPND		UARTx_CON0, 12, 1	// clear rx pending
#define 	UARTx_CON0_CLRTPND		UARTx_CON0, 13, 1	// clear tx pending
#define 	UARTx_CON0_RPND			UARTx_CON0, 14, 1	// rx pending
#define 	UARTx_CON0_TPND			UARTx_CON0, 15, 1	// tx pending
#define UARTx_CON1			0x04	// control reg 1
#define 	UARTx_CON1_RTSE			UARTx_CON1, 0, 1	// enable rts
#define 	UARTx_CON1_RTSDMAEN		UARTx_CON1, 1, 1	// rts dma enable ??
#define 	UARTx_CON1_CTSE			UARTx_CON1, 2, 1	// enable cts
#define 	UARTx_CON1_CTSIE		UARTx_CON1, 3, 1	// cts int enable
#define 	UARTx_CON1_BAUDFRAC		UARTx_CON1, 4, 0x3	// fractional baudrate
#define 	UARTx_CON1_CLRRTS		UARTx_CON1, 13, 1	// clear rts
#define UARTx_BAUD			0x08	// baudrate
#define UARTx_BUF			0x0C	// data reg
#define UARTx_OTCNT			0x10	// timeout
#define UARTx_TXADR			0x14	// tx dma address
#define UARTx_TXCNT			0x18	// tx dma length (triggers dma)
#define UARTx_RXSADR			0x1C	// rx dma start address
#define UARTx_RXEADR			0x20	// rx dma end address
#define UARTx_RXCNT			0x24	// rx dma length
#define UARTx_HRXCNT			0x28	// rx dma received length

/*================ AUDIO ================*/
#define AUDIO_BASE		0x1E2F00

#define AUDIO_DAC_CON			0x00	// dac control
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

/*================= P33 =================*/
#define P33_BASE		0x1E3E00

#define P33_PMU_CON			0x00	// pmu control
#define P33_RTC_CON			0x04	// rtc control
#define P33_SPI_CON			0x08	// spi control
#define P33_SPI_DAT			0x0C	// spi data

/*================ PORT =================*/
#define PORTA_BASE		0x1E5000
#define PORTB_BASE		0x1E5040
#define PORTC_BASE		0x1E5080
#define PORTD_BASE		0x1E50C0

#define PORTx_OUT			0x00	// port output reg
#define 	PORTx_OUTn(n)			PORTx_OUT, (n), 1	// 0=low, 1=high
#define PORTx_IN			0x04	// port input reg
#define 	PORTx_INn(n)			PORTx_IN, (n), 1	// 0=low, 1=high
#define PORTx_DIR			0x08	// port direction reg
#define 	PORTx_DIRn(n)			PORTx_DIR, (n), 1	// 0=out, 1=in [[MStar OEN]]
#define PORTx_DIE			0x0C	// port input enable
#define 	PORTx_DIEn(n)			PORTx_DIE, (n), 1	// 0=disable, 1=enable
#define PORTx_PU			0x10	// port pullup enable
#define 	PORTx_PUn(n)			PORTx_PU, (n), 1	// 0=disable, 1=enable
#define PORTx_PD			0x14	// port pulldown enable
#define 	PORTx_PDn(n)			PORTx_PD, (n), 1	// 0=disable, 1=enable
#define PORTx_HD0			0x18
#define PORTx_HD1			0x1C
#define PORTx_DIEH			0x20

/*================ IOMAP ================*/
#define IOMAP_BASE		0x1E5118

#define IOMAP_CON0			0x00
#define IOMAP_CON1			0x04
#define IOMAP_CON2			0x08
#define IOMAP_CON3			0x0C
#define IOMAP_CON4			0x10
#define IOMAP_CON5			0x14

/*////////////////////////////////////////////////////////////////////////////*/
/* High Speed SFR */

/*================= FM ==================*/
#define FM_BASE			0x1F1700

#define FM_CON				0x00


#endif