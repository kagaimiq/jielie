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

/*================ SYSCFG ===============*/
#define SYSCFG_BASE		0x60000

#define SYSCFG_CHIPID			0x00
#define SYSCFG_MODECON			0x04
#define SYSCFG_RSTSRC			0x7C
#define SYSCFG_LDOCON0			0x84
#define SYSCFG_LVDCON			0x88
#define SYSCFG_WDTCON			0x8C
#define SYSCFG_OSACON			0x90
#define SYSCFG_EFUSECON			0x94
#define SYSCFG_LDOCON1			0x9C

/*================ WAKEUP ===============*/
#define WAKEUP_BASE		0x60008

#define WAKEUP_CON0			0x00
#define WAKEUP_CON1			0x04
#define WAKEUP_CON2			0x08
#define WAKEUP_CON3			0x0C

/*================ IOMAP ================*/
#define IOMAP_BASE		0x60018

#define IOMAP_CON0			0x00
#define IOMAP_CON1			0x04
#define IOMAP_CON2			0x08
#define IOMAP_CON3			0x0C

/*================ POWER ================*/
#define POWER_BASE		0x60040

#define POWER_CON			0x00

/*================ CLOCK ================*/
#define CLOCK_BASE		0x60044

#define CLOCK_SYSDIV			0x00	// clock system divider
#define 	CLOCK_SYSDIV_0007		CLOCK_SYSDIV, 0, 0xff	// main (hsb/cpu/mem) <- sfc div
#define 	CLOCK_SYSDIV_0810		CLOCK_SYSDIV, 8, 0x7	// lsb <- main div
#define 	CLOCK_SYSDIV_1214		CLOCK_SYSDIV, 12, 0x7	// sfc <- org div
#define CLOCK_CLKCON0			0x04	// clock control reg 0
#define 	CLOCK_CLKCON0_RCEN		CLOCK_CLKCON0, 0, 1	// 
#define 	CLOCK_CLKCON0_RCHEN		CLOCK_CLKCON0, 1, 1	// *1* sel [rc_clk 250k|rc_clk 16M]
#define 	CLOCK_CLKCON0_TSSEL		CLOCK_CLKCON0, 2, 0x3	// 
#define 	CLOCK_CLKCON0_OSCSEL		CLOCK_CLKCON0, 4, 0x3	// osc sel [btosc|rtosh|rtosl|pat]
#define 	CLOCK_CLKCON0_CKSEL		CLOCK_CLKCON0, 6, 0x7	// *2* sel [*1*|*1*|*1*|*1*|btosc||rtosl|pll_sys]
#define 	CLOCK_CLKCON0_SFRCKMD		CLOCK_CLKCON0, 9, 1	// 
#define 	CLOCK_CLKCON0_PB0SEL		CLOCK_CLKCON0, 10, 0x7	// PB0 out sel [none|btosc|rtosh|ctm_in|lsb|hsb|sfc|pll_sys]
#define 	CLOCK_CLKCON0_PA2SEL		CLOCK_CLKCON0, 13, 0x7	// PA2 out sel [none|rc|lrc|rccl|bt_lo_d32|apc|pll_320m|pll_107m]
#define CLOCK_CLKCON1			0x08	// clock control reg 1
#define 	CLOCK_CLKCON1_USBCKSEL		CLOCK_CLKCON1, 0, 0x3	// usb clk sel [pll_48m|none|lsb|none]
#define 	CLOCK_CLKCON1_DACCKSEL		CLOCK_CLKCON1, 2, 0x3	// dac clk sel [pll_24m|none|lsb|none]
#define 	CLOCK_CLKCON1_APCCKSEL		CLOCK_CLKCON1, 6, 0x3 	// apc clk sel [pll_64m|pll_apc|lsb|none]
#define 	CLOCK_CLKCON1_LCDCKSEL		CLOCK_CLKCON1, 8, 0x3	// lcd clk sel [wclk|rtosl|lsb|none]
#define 	CLOCK_CLKCON1_UARTCKSEL		CLOCK_CLKCON1, 10, 0x3	// uart clk sel [osc|pll_48m|hsb|none]
#define 	CLOCK_CLKCON1_FMCKSEL		CLOCK_CLKCON1, 12, 0x3	// fm clk sel [none|pll_fm|hsb|none]
#define 	CLOCK_CLKCON1_BTCKSEL		CLOCK_CLKCON1, 14, 0x3	// bt(wl) clk sel [pll_64m|none|lsb|none]
#define 	CLOCK_CLKCON1_MEMSCKE		CLOCK_CLKCON1, 16, 1	// mem clk mode [dynamic|always on]
#define 	CLOCK_CLKCON1_SFCDSEL		CLOCK_CLKCON1, 28, 0x3	// 
#define CLOCK_CLKCON2			0x0C	// clock control reg 2
#define 	CLOCK_CLKCON2_PLLSYSSEL		CLOCK_CLKCON2, 0, 0x3	// pll_sys sel [pll_192m|pll_137m|pll_480m|none]
#define 	CLOCK_CLKCON2_PLLSYSDIV0	CLOCK_CLKCON2, 2, 0x3	// pll_sys div 0 [/1|/3|/5|/7]
#define 	CLOCK_CLKCON2_PLLSYSDIV1	CLOCK_CLKCON2, 4, 0x3	// pll_sys div 1 [/1|/2|/4|/8]
#define 	CLOCK_CLKCON2_PLLFMSEL		CLOCK_CLKCON2, 12, 0x3	// pll_fm sel [pll_192m|pll_137m|pll_480m|none]
#define 	CLOCK_CLKCON2_PLLFMDIV0		CLOCK_CLKCON2, 14, 0x3	// pll_fm div 0 [/1|/3|/5|/7]
#define 	CLOCK_CLKCON2_PLLFMDIV1		CLOCK_CLKCON2, 16, 0x3	// pll_fm div 1 [/1|/2|/4|/8]
#define 	CLOCK_CLKCON2_PLLAPCSEL		CLOCK_CLKCON2, 18, 0x3	// pll_apc sel [pll_192m|pll_137m|pll_480m|none]
#define 	CLOCK_CLKCON2_PLLAPCDIV0	CLOCK_CLKCON2, 20, 0x3	// pll_apc div 0 [/1|/3|/5|/7]
#define 	CLOCK_CLKCON2_PLLAPCDIV1	CLOCK_CLKCON2, 22, 0x3	// pll_apc div 1 [/1|/2|/4|/8]
#define 	CLOCK_CLKCON2_PLLALNKSEK	CLOCK_CLKCON2, 30, 1	// pll_alnk sel [pll_192m/17|pll_480m/39]
#define CLOCK_PLLCON			0x3C	// pll control reg
#define 	CLOCK_PLLCON_PLLEN		CLOCK_PLLCON, 0, 1	// pll enable
#define 	CLOCK_PLLCON_PLLRST		CLOCK_PLLCON, 1, 1	// pll reset
#define 	CLOCK_PLLCON_PLLREFDS		CLOCK_PLLCON, 2, 0x3f	// pll ref div n+2
#define 	CLOCK_PLLCON_PLLREFSEL		CLOCK_PLLCON, 7, 1	// pll ref sel [btosc|pll_rclk]
#define 	CLOCK_PLLCON_PLLREFDE		CLOCK_PLLCON, 8, 0x3	// pll ref div enable [x2|x1|divN|divN]
#define 	CLOCK_PLLCON_PLLTEST		CLOCK_PLLCON, 10, 1	// test enable
#define 	CLOCK_PLLCON_PLLDSMS		CLOCK_PLLCON, 11, 1	// fractional div mode
#define 	CLOCK_PLLCON_DSMTSEL		CLOCK_PLLCON, 12, 0xf	// T =14
#define 	CLOCK_PLLCON_DSMRSEL		CLOCK_PLLCON, 16, 0x3	// R =0
#define 	CLOCK_PLLCON_DSMMSEL		CLOCK_PLLCON, 18, 0x3	// M =0
#define 	CLOCK_PLLCON_PLLDIVSEL		CLOCK_PLLCON, 20, 0x3	// freq div mode [integer|x|x|fractional]
#define 	CLOCK_PLLCON_PLLPFD		CLOCK_PLLCON, 22, 0x3	// "analog control"
#define 	CLOCK_PLLCON_PLLICP		CLOCK_PLLCON, 24, 0x3	// "analog control"
#define 	CLOCK_PLLCON_PLLLPFR2		CLOCK_PLLCON, 26, 0x3	// "analog control"
#define 	CLOCK_PLLCON_PLLLPFR3		CLOCK_PLLCON, 28, 0x3	// "analog control"
#define 	CLOCK_PLLCON_PLLREFSEL2		CLOCK_PLLCON, 30, 0x3	// ref clock sel [btosc|x|x|pat]
#define CLOCK_PLLINTF			0x5C	// pll fractional div
#define CLOCK_PLLDMAX			0x60	// pll ssc max
#define CLOCK_PLLDMIN			0x64	// pll ssc min
#define CLOCK_PLLDSTP			0x68	// pll ssc step
#define CLOCK_PLLCON1			0x6C	// pll control reg 1
#define 	CLOCK_PLLCON1_PLLFBDS		CLOCK_PLLCON1, 0, 0xff	// feedback clk div (n+2)
#define 	CLOCK_PLLCON1_PLLLDO12A		CLOCK_PLLCON1, 8, 0x3	// "analog control"
#define 	CLOCK_PLLCON1_PLLLDO12D		CLOCK_PLLCON1, 10, 0x3	// "analog control"
#define 	CLOCK_PLLCON1_PLLIVCO		CLOCK_PLLCON1, 12, 0x7	// "analog control"
#define 	CLOCK_PLLCON1_PLLLDOBYPASS	CLOCK_PLLCON1, 15, 1	// "analog control"
#define 	CLOCK_PLLCON1_PLLTSSEL		CLOCK_PLLCON1, 16, 0x3	// test select
#define 	CLOCK_PLLCON1_PLLTSOE		CLOCK_PLLCON1, 18, 1	// test enable
#define 	CLOCK_PLLCON1_CK480MOE		CLOCK_PLLCON1, 24, 1	// enable 480 MHz clk
#define 	CLOCK_PLLCON1_CK320MOE		CLOCK_PLLCON1, 25, 1	// enable 320 MHz clk
#define 	CLOCK_PLLCON1_CK192MOE		CLOCK_PLLCON1, 26, 1	// enable 192 MHz clk
#define 	CLOCK_PLLCON1_CK137MOE		CLOCK_PLLCON1, 27, 1	// enable 137 MHz clk
#define 	CLOCK_PLLCON1_CK107MOE		CLOCK_PLLCON1, 28, 1	// enable 107 MHz clk

/*================ PORT =================*/
#define PORTA_BASE		0x60100
#define PORTB_BASE		0x60120
#define PORTC_BASE		0x60140
#define PORTD_BASE		0x60160

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
#define PORTx_HD			0x18	// port hidrive enable
#define PORTx_HD1			0x1C	// port hidrive enable

/*================ TIMER ================*/
#define TIMER0_BASE		0x60200
#define TIMER1_BASE		0x60210
#define TIMER2_BASE		0x60220
#define TIMER3_BASE		0x60230

#define TIMERx_CON			0x00	// timer control reg
#define 	TIMERx_CON_MODE			TIMERx_CON, 0, 0x3	// timer mode [dis|count|io rising cap|io falling cap]
#define 	TIMERx_CON_SSEL			TIMERx_CON, 2, 0x3	// clock sel [bus|io|osc|rc]
#define 	TIMERx_CON_PSETa		TIMERx_CON, 4, 0x3	// prescaler (1) [1|4|16|64]
#define 	TIMERx_CON_PSETb		TIMERx_CON, 6, 0x3	// prescaler (2) [1|2|256|512]
#define 	TIMERx_CON_PWMEN		TIMERx_CON, 8, 1	// pwm enable
#define 	TIMERx_CON_PWMINV		TIMERx_CON, 9, 1	// pwm invert
#define 	TIMERx_CON_PCLR			TIMERx_CON, 14, 1	// clear pending int
#define 	TIMERx_CON_PND			TIMERx_CON, 15, 1	// int pending
#define TIMERx_CNT			0x04	// timer counter
#define TIMERx_PRD			0x08	// timer period
#define TIMERx_PWM			0x0C	// timer pwm duty

/*================ UART =================*/
#define UART0_BASE		0x60300
#define UART1_BASE		0x60328
#define UART2_BASE		0x60350

#define UARTx_CON0			0x00	// uart control reg 0
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
#define UARTx_CON1			0x04	// uart control reg 1
#define 	UARTx_CON1_RTSE			UARTx_CON1, 0, 1	// enable rts
#define 	UARTx_CON1_RTSDMAEN		UARTx_CON1, 1, 1	// rts dma enable ??
#define 	UARTx_CON1_CTSE			UARTx_CON1, 2, 1	// enable cts
#define 	UARTx_CON1_CTSIE		UARTx_CON1, 3, 1	// cts int enable
#define 	UARTx_CON1_BAUDFRAC		UARTx_CON1, 4, 0x3	// fractional baudrate
#define 	UARTx_CON1_CLRRTS		UARTx_CON1, 13, 1	// clear rts
#define UART2_BUF			0x04	// uart data reg (for uart2)
#define UARTx_BAUD			0x08	// uart baudrate reg
#define UARTx_BUF			0x0C	// uart data reg
#define UARTx_OTCNT			0x10	// uart timeout value reg
#define UARTx_TXADR			0x14	// uart tx dma address
#define UARTx_TXCNT			0x18	// uart tx dma length
#define UARTx_RXSADR			0x1C	// uart rx dma start address
#define UARTx_RXEADR			0x20	// uart rx dma end address
#define UARTx_RXCNT			0x24	// uart rx dma length

/*================= SPI =================*/
#define SPI0_BASE		0x60400
#define SPI1_BASE		0x60414
#define SPI2_BASE		0x60428

#define SPIx_CON			0x00	// spi control reg
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
#define SPIx_BAUD			0x04	// spi baudrate reg
#define SPIx_BUF			0x08	// spi data reg
#define SPIx_ADR			0x0C	// spi dma address
#define SPIx_CNT			0x10	// spi dma length

/*================= PAP =================*/
#define PAP_BASE		0x60500

#define PAP_CON				0x00	// pap control reg
#define 	PAP_CON_PAPE			PAP_CON, 0, 1		// pap enable
#define 	PAP_CON_DIR			PAP_CON, 1, 1		// data direction [write|read]
#define 	PAP_CON_PWE			PAP_CON, 2, 1		// wr polarity [low when idle|high when idle]
#define 	PAP_CON_PRE			PAP_CON, 3, 1		// rd polarity [low when idle|high when idle]
#define 	PAP_CON_DW16EN			PAP_CON, 4, 1		// data width [8 bit|16 bits]
#define 	PAP_CON_DW16ED			PAP_CON, 5, 1		// data endian [little|big]
#define 	PAP_CON_PCLR			PAP_CON, 6, 1		// pending int clear
#define 	PAP_CON_PND			PAP_CON, 7, 1		// pending int
#define 	PAP_CON_TW			PAP_CON, 8, 0xf		// rd/wr assert time
#define 	PAP_CON_TH			PAP_CON, 12, 0x3	// data hold time
#define 	PAP_CON_TS			PAP_CON, 14, 0x3	// data setup time
#define 	PAP_CON_EXTE			PAP_CON, 16, 1		// ?data extend enable
#define 	PAP_CON_EXTMSB			PAP_CON, 17, 1		// ?data extend mode [LSB->MSB|MSB->LSB]
#define 	PAP_CON_PAPIE			PAP_CON, 18, 1		// int enable
#define PAP_DAT0			0x04	// pap data reg 0 (for data extend)
#define PAP_DAT1			0x08	// pap data reg 1 (for data extend)
#define PAP_ADR				0x10	// pap dma address
#define PAP_CNT				0x14	// pap dma length

/*================= SD ==================*/
#define SD0_BASE		0x60600
#define SD1_BASE		0x60618

#define SDx_CON0			0x00	// sd control reg 0
#define SDx_CON1			0x04	// sd control reg 1
#define SDx_CON2			0x08	// sd control reg 2
#define SDx_CPTR			0x0C	// sd command ptr
#define SDx_DPTR			0x10	// sd data ptr

/*================= IIC =================*/
#define IIC_BASE		0x60700

#define IIC_CON0			0x00	// iic control reg 0
#define IIC_BUF				0x04	// iic data buffer
#define IIC_BAUD			0x08	// iic baudrate
#define IIC_CON1			0x0C	// iic control reg 1

/*================= IRTC ================*/
#define IRTC_BASE		0x60908

#define IRTC_CON			0x00	// irtc control reg
#define 	IRTC_CON_X2EN			IRTC_CON, 1, 1		// 2 Hz int enable
#define 	IRTC_CON_X512EN			IRTC_CON, 2, 1		// 512 Hz int enable
#define 	IRTC_CON_WKUPEN			IRTC_CON, 3, 1		// wakeup enable
#define 	IRTC_CON_X2PND			IRTC_CON, 5, 1		// 2Hz pending int
#define 	IRTC_CON_X512PND		IRTC_CON, 6, 1		// 512 Hz pending int
#define 	IRTC_CON_WKUPPND		IRTC_CON, 7, 1		// wakeup pending
#define 	IRTC_CON_RTCCS			IRTC_CON, 8, 1		// rtc bus enable
#define 	IRTC_CON_BUSY			IRTC_CON, 9, 1		// rtc bus busy
#define 	IRTC_CON_BAUD			IRTC_CON, 10, 0x3	// rtc bus baudrate (<= 24 MHz)
#define 	IRTC_CON_STRAN			IRTC_CON, 12, 1		// rtc bus start transfer
#define 	IRTC_CON_X2CPND			IRTC_CON, 13, 1		// clear 2 Hz pending int
#define 	IRTC_CON_X512CPND		IRTC_CON, 14, 1		// clear 512 Hz pending int
#define 	IRTC_CON_WKUPCPND		IRTC_CON, 15, 1		// clear wakeup pending
#define IRTC_DAT			0x04	// irtc data reg
#define IRTC_LCON			0x10	// irtc lcon
#define IRTC_LNUM			0x14	// irtc lnum

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

/*================ AUDIO ================*/
#define AUDIO_BASE		0x60A00

#define AUDIO_DAC_LEN			0x00	// audio dac dma length
#define AUDIO_DAC_CON			0x04	// audio dac control reg
#define 	AUDIO_DAC_CON_DACSR		AUDIO_DAC_CON, 0, 0xf		// dac sample rate [44100|48000|32000|32000|22050|24000|16000|16000|11025|12000|8000|8000|11025|12000|8000|8000]
#define 	AUDIO_DAC_CON_DACEN		AUDIO_DAC_CON, 4, 1		// dac enable
#define 	AUDIO_DAC_CON_DACIE		AUDIO_DAC_CON, 5, 1		// int enable
#define 	AUDIO_DAC_CON_CPND		AUDIO_DAC_CON, 6, 1		// clear pending int
#define 	AUDIO_DAC_CON_PND		AUDIO_DAC_CON, 7, 1		// pending int
#define 	AUDIO_DAC_CON_BUFF		AUDIO_DAC_CON, 8, 1		// current buffer slice
#define 	AUDIO_DAC_CON_ADCUDE		AUDIO_DAC_CON, 9, 1		// adc gain apply [on int|immediatly]
#define 	AUDIO_DAC_CON_DCCS		AUDIO_DAC_CON, 12, 0xf		// dc cancelling filter setting [dis|...]
#define AUDIO_DAC_ADR			0x08	// audio dac dma address
#define AUDIO_DAC_TRML			0x0C	// audio dac trim left
#define AUDIO_DAC_TRMR			0x10	// audio dac trim right
#define AUDIO_DAC_CON1			0x14	// audio dac control reg 1
#define 	AUDIO_DAC_CON1_DSMC		AUDIO_DAC_CON1, 0, 0xf		// dsm config
#define 	AUDIO_DAC_CON1_PDMOE		AUDIO_DAC_CON1, 4, 1		// dac pdm out enable
#define 	AUDIO_DAC_CON1_PDMRV		AUDIO_DAC_CON1, 5, 1		// dac pdm rv
#define AUDIO_ADC_CON			0x20	// audio adc control reg
#define 	AUDIO_ADC_CON_ADCSR		AUDIO_ADC_CON, 0, 0xf		// adc sample rate [44100|48000|32000|32000|22050|24000|16000|16000|11025|12000|8000|8000|11025|12000|8000|8000]
#define 	AUDIO_ADC_CON_ADCEN		AUDIO_ADC_CON, 4, 1		// adc enable
#define 	AUDIO_ADC_CON_ADCIE		AUDIO_ADC_CON, 5, 1		// int enable
#define 	AUDIO_ADC_CON_CPND		AUDIO_ADC_CON, 6, 1		// clear pending int
#define 	AUDIO_ADC_CON_PND		AUDIO_ADC_CON, 7, 1		// pending int
#define 	AUDIO_ADC_CON_BUFF		AUDIO_ADC_CON, 8, 1		// current buffer slice
#define 	AUDIO_ADC_CON_CHE0		AUDIO_ADC_CON, 9, 1		// adc channel en
#define 	AUDIO_ADC_CON_DCCS		AUDIO_ADC_CON, 12, 0xf		// dc cancelling filter setting [dis|...]
#define AUDIO_ADC_ADR			0x2c	// audio adc dma address
#define AUDIO_ADC_LEN			0x30	// audio adc dma length
#define AUDIO_DAA_CON0			0x40	// audio daa control reg 0
#define 	AUDIO_DAA_CON0_DACEN		AUDIO_DAA_CON0, 0, 1		// enable DAC analog part
#define 	AUDIO_DAA_CON0_VCMEN		AUDIO_DAA_CON0, 1, 1		// enable VCM
#define 	AUDIO_DAA_CON0_LDO1EN		AUDIO_DAA_CON0, 2, 1		// enable LDO1
#define 	AUDIO_DAA_CON0_LDO2EN		AUDIO_DAA_CON0, 3, 1		// enable LDO2 (when enabled, DACVDD doesn't need an external cap)
#define 	AUDIO_DAA_CON0_HPLEN		AUDIO_DAA_CON0, 4, 1		// enable DAC left channel
#define 	AUDIO_DAA_CON0_HPREN		AUDIO_DAA_CON0, 5, 1		// enable DAC right channel
#define 	AUDIO_DAA_CON0_PNSEN		AUDIO_DAA_CON0, 6, 1		// enable DAC 50k pulldown
#define 	AUDIO_DAA_CON0_PNS10KEN		AUDIO_DAA_CON0, 7, 1		// enable DAC 10k pulldown
#define 	AUDIO_DAA_CON0_LPFISEL		AUDIO_DAA_CON0, 8, 0x7		// ?? low pass filter current select ??
#define 	AUDIO_DAA_CON0_TRIMEN		AUDIO_DAA_CON0, 13, 1		// "trim enable"
#define 	AUDIO_DAA_CON0_TRIMSEL		AUDIO_DAA_CON0, 14, 1		// "trim channel output"
#define 	AUDIO_DAA_CON0_TRIMSW		AUDIO_DAA_CON0, 15, 1		// "trim switch"
#define 	AUDIO_DAA_CON0_LGSEL		AUDIO_DAA_CON0, 16, 0x1f	// left channel volume
#define 	AUDIO_DAA_CON0_LR2L		AUDIO_DAA_CON0, 21, 1		// route line-in L+R to DAC left channel
#define 	AUDIO_DAA_CON0_LR2R		AUDIO_DAA_CON0, 22, 1		// route line-in L+R to DAC right channel
#define 	AUDIO_DAA_CON0_MUTE		AUDIO_DAA_CON0, 23, 1		// DAC mute
#define 	AUDIO_DAA_CON0_RGSEL		AUDIO_DAA_CON0, 24, 0x1f	// right channel volume
#define 	AUDIO_DAA_CON0_MIC2L		AUDIO_DAA_CON0, 29, 1		// route MIC to DAC right channel
#define 	AUDIO_DAA_CON0_MIC2R		AUDIO_DAA_CON0, 30, 1		// route MIC to DAC left channel
#define 	AUDIO_DAA_CON0_TRIMO		AUDIO_DAA_CON0, 31, 1		// ?? trim out ??
#define AUDIO_DAA_CON1			0x44	// audio daa control reg 1
#define 	AUDIO_DAA_CON1_LIN0LEN		AUDIO_DAA_CON1, 0, 1		// Line-in 0 left channel en
#define 	AUDIO_DAA_CON1_LIN0REN		AUDIO_DAA_CON1, 1, 1		// Line-in 0 right channel en
#define 	AUDIO_DAA_CON1_LIN0LBIASEN	AUDIO_DAA_CON1, 2, 1		// Line-in 0 left channel bias en
#define 	AUDIO_DAA_CON1_LIN0RBIASEN	AUDIO_DAA_CON1, 3, 1		// Line-in 0 right channel bias en
#define 	AUDIO_DAA_CON1_LIN1LEN		AUDIO_DAA_CON1, 4, 1		// Line-in 1 left channel en
#define 	AUDIO_DAA_CON1_LIN1REN		AUDIO_DAA_CON1, 5, 1		// Line-in 1 right channel en
#define 	AUDIO_DAA_CON1_LIN1LBIASEN	AUDIO_DAA_CON1, 6, 1		// Line-in 1 left channel bias en
#define 	AUDIO_DAA_CON1_LIN1RBIASEN	AUDIO_DAA_CON1, 7, 1		// Line-in 1 right channel bias en
#define 	AUDIO_DAA_CON1_LIN2LEN		AUDIO_DAA_CON1, 8, 1		// Line-in 2 left channel en
#define 	AUDIO_DAA_CON1_LIN2REN		AUDIO_DAA_CON1, 9, 1		// Line-in 2 right channel en
#define 	AUDIO_DAA_CON1_LIN2LBIASEN	AUDIO_DAA_CON1, 10, 1		// Line-in 2 left channel bias en
#define 	AUDIO_DAA_CON1_LIN2RBIASEN	AUDIO_DAA_CON1, 11, 1		// Line-in 2 right channel bias en
#define 	AUDIO_DAA_CON1_LINL2ADC		AUDIO_DAA_CON1, 12, 1		// ?? ??
#define 	AUDIO_DAA_CON1_LINR2ADC		AUDIO_DAA_CON1, 13, 1		// ?? ??
#define 	AUDIO_DAA_CON1_VCMOUTEN		AUDIO_DAA_CON1, 14, 1		// enable VCMO
#define 	AUDIO_DAA_CON1_VCMOUTPD		AUDIO_DAA_CON1, 15, 1		// enable VCMO 1k pulldown
#define 	AUDIO_DAA_CON1_MICEN		AUDIO_DAA_CON1, 16, 1		// mic enable
#define 	AUDIO_DAA_CON1_MICISEL		AUDIO_DAA_CON1, 17, 1		// ?? mic current sel ??
#define 	AUDIO_DAA_CON1_MICMUTE		AUDIO_DAA_CON1, 18, 1		// mic mute
#define 	AUDIO_DAA_CON1_MICNEG12		AUDIO_DAA_CON1, 19, 1		// mic -12dB gain
#define 	AUDIO_DAA_CON1_AMUXBIASEN	AUDIO_DAA_CON1, 20, 1		// AMUX bias enable
#define 	AUDIO_DAA_CON1_AMUXEN		AUDIO_DAA_CON1, 21, 1		// AMUX "bypass"
#define 	AUDIO_DAA_CON1_AMUXG		AUDIO_DAA_CON1, 22, 1		// AMUX gain
#define 	AUDIO_DAA_CON1_AMUXMUTE		AUDIO_DAA_CON1, 23, 1		// AMUX mute
#define 	AUDIO_DAA_CON1_MICG		AUDIO_DAA_CON1, 24, 0x3f	// mic gain
#define 	AUDIO_DAA_CON1_MICGX2		AUDIO_DAA_CON1, 30, 1		// mic gain multiply x2
#define 	AUDIO_DAA_CON1_VCMRSEL		AUDIO_DAA_CON1, 31, 1		// VCM bias voltage resistor sel
#define AUDIO_DAA_CON2			0x48	// audio daa control reg 2
#define 	AUDIO_DAA_CON2_DACCLKSEL	AUDIO_DAA_CON2, 0, 1		// ?? ??
#define 	AUDIO_DAA_CON2_DACOSCEGDESEL	AUDIO_DAA_CON2, 1, 1		// ?? ??
#define 	AUDIO_DAA_CON2_DACOSCFSEL	AUDIO_DAA_CON2, 2, 0x3		// ?? ??
#define 	AUDIO_DAA_CON2_DACDTSEL		AUDIO_DAA_CON2, 4, 0x7		// ?? ??
#define AUDIO_DAA_CON3			0x4C	// audio daa control reg 3
#define 	AUDIO_DAA_CON3_CKEN		AUDIO_DAA_CON3, 0, 1		// dac clock out enable (PA4->clk)
#define 	AUDIO_DAA_CON3_DATEN		AUDIO_DAA_CON3, 1, 1		// dac data out enable (PA5->left, PA6->right)
#define 	AUDIO_DAA_CON3_DACEXT		AUDIO_DAA_CON3, 2, 1		// dac external in enable (PA4<-clk, PA5<-left, PA6<-right)
#define 	AUDIO_DAA_CON3_ADCCOE		AUDIO_DAA_CON3, 3, 1		// adc clk out enable (PB1->clk)
#define 	AUDIO_DAA_CON3_ADCDOE		AUDIO_DAA_CON3, 4, 1		// 
#define 	AUDIO_DAA_CON3_ADCDIT		AUDIO_DAA_CON3, 5, 1		// adc dither enable
#define AUDIO_ADA_CON0			0x80	// audio ada control reg 0
#define AUDIO_ADA_CON1			0x84	// audio ada control reg 1

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

/*================= USB =================*/
#define USB_BASE		0x60D00

#define USB_IO_CON0			0x00	// usb io control reg 0
#define 	USB_IO_CON0_DPOUT		USB_IO_CON0, 0, 1	// D+ output level
#define 	USB_IO_CON0_DMOUT		USB_IO_CON0, 1, 1	// D- output level
#define 	USB_IO_CON0_DPIE		USB_IO_CON0, 2, 1	// D+ direction [out|in]
#define 	USB_IO_CON0_DMIE		USB_IO_CON0, 3, 1	// D- direction [out|in]
#define 	USB_IO_CON0_DPPD		USB_IO_CON0, 4, 1	// D+ pulldown enable
#define 	USB_IO_CON0_DMPD		USB_IO_CON0, 5, 1	// D- pulldown enable
#define 	USB_IO_CON0_DPPU		USB_IO_CON0, 6, 1	// D+ pullup enable
#define 	USB_IO_CON0_DMPU		USB_IO_CON0, 7, 1	// D- pullup enable
#define 	USB_IO_CON0_PM			USB_IO_CON0, 8, 1	// "for test"
#define 	USB_IO_CON0_DPDIE		USB_IO_CON0, 9, 1	// D+ digital in enable
#define 	USB_IO_CON0_DMDIE		USB_IO_CON0, 10, 1	// D- digital in enable
#define 	USB_IO_CON0_USBIOMODE		USB_IO_CON0, 11, 1	// io mux mode
#define 	USB_IO_CON0_USBSR		USB_IO_CON0, 12, 1	// slew rate enable
#define USB_CON0			0x04	// usb control reg 0
#define 	USB_CON0_PHYON			USB_CON0, 0, 1		// usb phy enable
#define 	USB_CON0_IOMODE			USB_CON0, 1, 1		// usb phy gpio mode
#define 	USB_CON0_USBNRST		USB_CON0, 2, 1		// usb reset [assert|release]
#define 	USB_CON0_TM1			USB_CON0, 3, 1		// "short connect timeout"
#define 	USB_CON0_CID			USB_CON0, 4, 1		// usb mode [host|device]
#define 	USB_CON0_VBUS			USB_CON0, 5, 1		// ?? vbus control ??
#define 	USB_CON0_USBTEST		USB_CON0, 6, 1		// "usb test"
#define 	USB_CON0_LATSEL			USB_CON0, 8, 1		// "reserved"
#define 	USB_CON0_PDCHKDP		USB_CON0, 9, 1		// D+ ext pulldown check en
#define 	USB_CON0_SOFIE			USB_CON0, 10, 1		// SOF int enable
#define 	USB_CON0_SIEIE			USB_CON0, 11, 1		// int enable
#define 	USB_CON0_CLRSOFP		USB_CON0, 12, 1		// clear SOF int pending
#define 	USB_CON0_SOFPND			USB_CON0, 13, 1		// SOF int pending
#define 	USB_CON0_SIEPND			USB_CON0, 14, 1		// int pending (cleared by accessing USB)
#define 	USB_CON0_CHKDPO			USB_CON0, 15, 1		// D+ ext pulldown check status
#define 	USB_CON0_SEDM			USB_CON0, 16, 1		// single ended D- status
#define 	USB_CON0_SEDP			USB_CON0, 17, 1		// single ended D+ status
#define 	USB_CON0_LOWPMD			USB_CON0, 18, 1		// low power mode [en|dis]
#define USB_CON1			0x08	// usb control reg 1
#define 	USB_CON1_MCDAT			USB_CON1, 0, 0xff	// usb reg data
#define 	USB_CON1_MCADR			USB_CON1, 8, 0x3f	// usb reg addr
#define 	USB_CON1_MCRNW			USB_CON1, 14, 1		// usb reg access type [write|read]
#define 	USB_CON1_ACK			USB_CON1, 15, 1		// usb reg access done flag
#define USB_EP0_CNT			0x0C	// usb ep0 data len
#define USB_EP1_CNT			0x10	// usb ep1 data len
#define USB_EP2_CNT			0x14	// usb ep2 data len
#define USB_EP3_CNT			0x18	// usb ep3 data len
#define USB_EP0_ADR			0x1C	// usb ep0 buff addr
#define USB_EP1_TADR			0x20	// usb ep1 tx buff addr
#define USB_EP1_RADR			0x24	// usb ep1 rx buff addr
#define USB_EP2_TADR			0x28	// usb ep2 tx buff addr
#define USB_EP2_RADR			0x2C	// usb ep2 rx buff addr
#define USB_EP3_TADR			0x30	// usb ep3 tx buff addr
#define USB_EP3_RADR			0x34	// usb ep3 rx buff addr
#define USB_IO_CON1			0x38	// usb io control reg 1
#define 	USB_IO_CON1_DPIN		USB_IO_CON1, 0, 1	// usb D+ input level
#define 	USB_IO_CON1_DMIN		USB_IO_CON1, 1, 1	// usb D- input level

// TODO the MC space regs (Spoiler: this is MUSB!!!! although somewhat altered OF COURSE)

/*================= CRC =================*/
#define CRC_BASE		0x60E00

#define CRC_FIFO			0x00	// crc fifo reg
#define CRC_REG				0x04	// crc shift reg

/*================ RAND =================*/
#define RAND_BASE		0x60F00

#define RAND_R64L			0x00	// random bits 0..31
#define RAND_R64H			0x04	// random bits 32..63

/*================= ADC =================*/
#define ADC_BASE		0x61000

#define ADC_CON				0x00	// adc control reg
#define 	ADC_CON_ADCBAUD			ADC_CON, 0, 0x7		// adc clock divider [/1|/6|/12|/24|/48|/72|/96|/128] (<= 1MHz)
#define 	ADC_CON_ADCAE			ADC_CON, 3, 1		// adc analog enable
#define 	ADC_CON_ADCEN			ADC_CON, 4, 1		// adc enable
#define 	ADC_CON_ADCIE			ADC_CON, 5, 1		// adc int enable
#define 	ADC_CON_CPND			ADC_CON, 6, 1		// clear pending int
#define 	ADC_CON_PND			ADC_CON, 7, 1		// pending int
#define 	ADC_CON_CHSEL			ADC_CON, 8, 0xf		// channel select [adc0..11|12:rtc|pmu|bt|audio]
#define 	ADC_CON_WAITTIME		ADC_CON, 12, 0xf	// startup delay (in 8x clocks)
#define ADC_RES				0x04	// adc result

/*////////////////////////////////////////////////////////////////////////////*/
/* High Speed SFR */

/*================= SFC =================*/
#define SFC_BASE		0x70200

#define SFC_CON				0x00	// sfc control reg
#define SFC_BAUD			0x04	// sfc baudrate
#define SFC_CODE			0x08	// sfc code
#define SFC_BASEADR			0x0C	// sfc flash base addr

/*================= ENC =================*/
#define ENC_BASE		0x70300

#define ENC_CON				0x00	// enc control reg
#define ENC_KEY				0x04	// enc key
#define ENC_ADR				0x08	// enc address
#define ENC_UNENCADRH			0x0C	// enc unenc addr h
#define ENC_UNENCADRL			0x10	// enc unenc addr l

/*================= AES =================*/
#define AES_BASE		0x70500

#define AES_CON				0x00	// aes control reg
#define AES_DATIN			0x04	// aes data in
#define AES_KEY				0x08	// aes key
#define AES_ENCRES0			0x0C	// aes encrypted res 0
#define AES_ENCRES1			0x10	// aes encrypted res 1
#define AES_ENCRES2			0x14	// aes encrypted res 2
#define AES_ENCRES3			0x18	// aes encrypted res 3
#define AES_DECRES0			0x1C	// aes decrypted res 0
#define AES_DECRES1			0x20	// aes decrypted res 1
#define AES_DECRES2			0x24	// aes decrypted res 2
#define AES_DECRES3			0x28	// aes decrypted res 3

/*================= FFT =================*/
#define FFT_BASE		0x70600

#define FFT_CON				0x00	// fft control reg
#define 	FFT_CON_b00			FFT_CON, 0, 1		// bit0
#define 	FFT_CON_b01			FFT_CON, 1, 1		// bit1
#define 	FFT_CON_b02			FFT_CON, 2, 1		// bit2 --type [xxx/forward]
#define 	FFT_CON_start			FFT_CON, 4, 1		// start
#define 	FFT_CON_busy			FFT_CON, 7, 1		// busy
#define 	FFT_CON_b0811			FFT_CON, 8, 0xf		// bit8~11
#define 	FFT_CON_b1215			FFT_CON, 12, 0xf	// bit12~15 --nshift
#define FFT_ADRI			0x04	// fft input addr
#define FFT_ADRO			0x08	// fft output addr
#define FFT_ADRW			0x0C	// fft w addr

/*================== EQ =================*/
#define EQ_BASE			0x70700

#define EQ_CON				0x00	// eq control reg
#define EQ_LEN				0x04	// eq data length
#define EQ_ADRI				0x08	// eq input addr
#define EQ_ADRO				0x0C	// eq output addr
#define EQ_CADR				0x10	// eq c addr

#endif