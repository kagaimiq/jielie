#ifndef __MT6580_REGS_H
#define __MT6580_REGS_H

#include <stdint.h>

//===========================================================//
//                        Some stuff                         //
//===========================================================//

// make the mess in the preprocessor!
#define reg_wmask(reg, mask, val) \
	(reg) = ((reg) & ~(mask)) | ((val) & (mask))

#define reg_wsmask(reg, shift, mask, val) \
	(reg) = ((reg) & ~((mask) << (shift))) | (((val) & (mask)) << (shift))

#define reg_rsmask(reg, shift, mask) \
	(((reg) >> (shift)) & (mask))

#define REG8(a)			(*(volatile uint8_t *)(a))
#define REG16(a)		(*(volatile uint16_t *)(a))
#define REG32(a)		(*(volatile uint32_t *)(a))

#if 0
// compatibility, moar mess!!!
#define reg32_read(reg) \
	REG32(reg)

#define reg32_write(reg, val) \
	REG32(reg) = val

#define reg32_wmask(reg, mask, val) \
	REG32(reg) = (REG32(reg) & ~(mask)) | ((val) & (mask))

#define reg32_wsmask(reg, shift, mask, val) \
	REG32(reg) = (REG32(reg) & ~((mask) << (shift))) | (((val) & (mask)) << (shift))

#define reg32_rsmask(reg, shift, mask) \
	((REG32(reg) >> (shift)) & (mask))
#endif

//===========================================================//
//                     Interrupt numbers                     //
//===========================================================//

#define EMUEXCPT_IRQNO			0
#define EXCEPTION_IRQNO			1
#define SYSCALL_IRQNO			2
#define TICK_TMR_IRQNO			3
#define TIMER0_IRQNO			4
#define TIMER1_IRQNO			5
#define TIMER2_IRQNO			6
#define TIMER3_IRQNO			7
#define USB_SOF_IRQNO			8
#define USB_CTRL_IRQNO			9
#define RTC_WDT_IRQNO			10
#define ALINK0_IRQNO			11
#define AUDIO_IRQNO			12
#define PORT_IRQNO			13
#define SPI0_IRQNO			14
#define SPI1_IRQNO			15
#define SD0_IRQNO			16
#define SD1_IRQNO			17
#define UART0_IRQNO			18
#define UART1_IRQNO			19
#define UART2_IRQNO			20
#define PAP_IRQNO			21
#define IIC_IRQNO			22
#define SARADC_IRQNO			23
#define PDM_LINK_IRQNO			24
#define RDEC0_IRQNO			25
#define LRCT_IRQNO			26
#define BREDR_IRQNO			27
#define BT_CLKN_IRQNO			28
#define BT_BDG_IRQNO			29
#define WL_LOFC_IRQNO			30
#define SRC_IRQNO			31
#define FFT_IRQNO			32
#define EQ_IRQNO			33
#define LP_TIMER0_IRQNO			34
#define LP_TIMER1_IRQNO			35
#define ALINK1_IRQNO			36
#define OSA_IRQNO			37
#define BLE_RX_IRQNO			38
#define BLE_EVENT_IRQNO			39
#define AES_IRQNO			40
#define MCTMRX_IRQNO			41
#define CHX_PWM_IRQNO			42
#define FMRX_IRQNO			43
#define SPI2_IRQNO			44
#define SBC_IRQNO			45
#define GPC_IRQNO			46
#define FMTX_IRQNO			47
#define DCP_IRQNO			48
#define RDEC1_IRQNO			49
#define RDEC2_IRQNO			50
#define SPDIF_IRQNO			51
#define PWM_LED_IRQNO			52
#define CTM_IRQNO			53
#define TIMER4_IRQNO			54
#define TIMER5_IRQNO			55

#define SOFT0_IRQNO			60
#define SOFT1_IRQNO			61
#define SOFT2_IRQNO			62
#define SOFT3_IRQNO			63

//===========================================================//
//                     Base addresses                        //
//===========================================================//

// CPU core SFR
#define CMNG_BASE			0x100000		//
#define SDTAP_BASE			0x100100		//
#define MMU_BASE			0x100300		// memory management unit
#define DSP_BASE			0x101000		//
#define DEBUG_BASE			0x101040		//
#define FFT_BASE			0x102000		// fast fourier transform
#define CORE_BASE			0x10F000		// cpu core regs

// Low-speed bus
#define CLOCK_BASE			0x1E0000		// clock stuff
#define RST_BASE			0x1E00C0		// reset stuff
#define MODE_BASE			0x1E0100		// mode stuff
#define SYSTEM_BASE			0x1E0200		// system stuff
#define TIMER0_BASE			0x1E0400		// timer (0)
#define TIMER1_BASE			0x1E0500		// timer (1)
#define TIMER2_BASE			0x1E0600		// timer (2)
#define TIMER3_BASE			0x1E0700		// timer (3)
#define TIMER4_BASE			0x1E0800		// timer (4)
#define TIMER5_BASE			0x1E0900		// timer (5)
#define PCNT_BASE			0x1E1000		// pulse counter
#define GPCNT_BASE			0x1E1100		// g pulse counter
#define SD0_BASE			0x1E1400		// sd/mmc host (0)
#define SD1_BASE			0x1E1500		// sd/mmc host (1 - ABSENT!)
#define USB_BASE			0x1E1800		// usb host/device
#define ANA_BASE			0x1E1900		// analog stuff
#define SPI0_BASE			0x1E1C00		// spi interface (0)
#define SPI1_BASE			0x1E1D00		// spi interface (1)
#define SPI2_BASE			0x1E1E00		// spi interface (2)
#define UART0_BASE			0x1E2000		// uart interface (0)
#define UART1_BASE			0x1E2100		// uart interface (1)
#define UART2_BASE			0x1E2200		// uart interface (2)
#define IIC_BASE			0x1E2400		// i2c interface
#define PAP_BASE			0x1E2800		// parralel active port
#define SS_BASE				0x1E2900		// spdif slave
#define RDEC0_BASE			0x1E2C00		// r decoder (0)
#define PLNK_BASE			0x1E2D00		// pdm link
#define ALNK0_BASE			0x1E2E00		// audio link (0)
#define AUDIO_BASE			0x1E2F00		// audio controller
#define MCPWM_BASE			0x1E3000		// motor control pwm
#define ADC_BASE			0x1E3100		// analog-digital converter
#define IR_BASE				0x1E3200		// ir decoder
#define ALNK1_BASE			0x1E3300		// audio link (1)
#define OSA_BASE			0x1E3400		//
#define CRC_BASE			0x1E3500		// crc16 ccitt
#define LRCT_BASE			0x1E3600		//
#define EFUSE_BASE			0x1E3700		// efuse
#define RAND_BASE			0x1E3B00		// random number generator
#define CTM_BASE			0x1E3C00		//
#define P33_BASE			0x1E3E00		//
#define DMA_BASE			0x1E3F00		// direct memory access
#define PERIENC_BASE			0x1E4100		// peripheral encryptor
#define SBC_BASE			0x1E4200		// subband coding (sbc) codec
#define AES_BASE			0x1E4300		// advanced encryption standard (aes) engine
#define RDEC1_BASE			0x1E4400		// r decoder (1)
#define RDEC2_BASE			0x1E4500		// r decoder (2)
#define PORTA_BASE			0x1E5000		// gpio port (A)
#define PORTB_BASE			0x1E5040		// gpio port (B)
#define PORTC_BASE			0x1E5080		// gpio port (C)
#define PORTD_BASE			0x1E50C0		// gpio port (D)
#define USB_IO_BASE			0x1E5100		// usb gpio port
#define WAKEUP_BASE			0x1E5108		// gpio wakeup
#define IOMAP_BASE			0x1E5118		// port io map
#define PLED_BASE			0x1E5200		// pwm led
#define LCD_BASE			0x1E5300		// liquid crystal display (lcd) controller

// High-speed bus
#define SFC_BASE			0x1F0200		// serial/spi flash controller
#define SFCENC_BASE			0x1F0300		// sfc encryptor
#define PSRAM_BASE			0x1F0500		// spi psram controller (ABSENT!)
#define DCP_BASE			0x1F1300		//
#define EQ_BASE				0x1F1500		// equalizer
#define SRC_BASE			0x1F1600		// sample rate converter
//#define FM_BASE				0x1F1700		// fm radio
#define WL_BASE				0x1F1800		//

//===========================================================//
//                   Register Definitions                    //
//===========================================================//

struct JL_UART_regs {
	volatile uint32_t CON0;				// +00 - control 0
	volatile uint32_t CON1;				// +04 - control 1
	volatile uint32_t BAUD;				// +08 - baudrate
	volatile uint32_t BUF;				// +0C - buffer
	volatile uint32_t OTCNT;			// +10 - timeout
	volatile uint32_t TXADR;			// +14 - dma tx address
	volatile uint32_t TXCNT;			// +18 - dma tx length (triggers dma)
	volatile uint32_t RXSADR;			// +1C - dma rx start address
	volatile uint32_t RXEADR;			// +20 - dma rx end address
	volatile uint32_t RXCNT;			// +24 - dma rx length..
	volatile uint32_t HRXCNT;			// +28 - dma rx length..
};

struct JL_SD_regs {
	volatile uint32_t CON0;				// +00 - control 0
	volatile uint32_t CON1;				// +04 - control 1
	volatile uint32_t CON2;				// +08 - control 2
	volatile uint32_t CPTR;				// +0C - command pointer
	volatile uint32_t DPTR;				// +10 - data pointer
	volatile uint32_t CTU_CON;			// +14 - ctu control
	volatile uint32_t CTU_CNT;			// +18 - ctu count
};

struct JL_PORT_regs {
	volatile uint32_t OUT;				// +00 - output
	volatile uint32_t IN;				// +04 - input
	volatile uint32_t DIR;				// +08 - direction
	volatile uint32_t DIE;				// +0C - digital in enable
	volatile uint32_t PU;				// +10 - pullup
	volatile uint32_t PD;				// +14 - pulldown
	volatile uint32_t HD0;				// +18
	volatile uint32_t HD1;				// +1C
	volatile uint32_t DIEH;				// +20
};

//------------------------------------

#define UART0			((struct JL_UART_regs *)UART0_BASE)
#define UART1			((struct JL_UART_regs *)UART1_BASE)
#define UART2			((struct JL_UART_regs *)UART2_BASE)
#define SD0			((struct JL_SD_regs *)SD0_BASE)
#define SD1			((struct JL_SD_regs *)SD1_BASE)
#define PORTA			((struct JL_PORT_regs *)PORTA_BASE)
#define PORTB			((struct JL_PORT_regs *)PORTB_BASE)
#define PORTC			((struct JL_PORT_regs *)PORTC_BASE)
#define PORTD			((struct JL_PORT_regs *)PORTD_BASE)

#endif