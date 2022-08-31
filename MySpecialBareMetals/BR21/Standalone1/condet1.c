#include <stdint.h>
#include <string.h>
#include <xprintf.h>
#include <jl_regs.h>
#include <jl_irtc.h>

void uputc(int c) {
	reg32_write(UART2_BASE+UART2_BUF, c);
	while (!reg32_rsmask(UART2_BASE+UARTx_CON0_TPND));
	reg32_wsmask(UART2_BASE+UARTx_CON0_CLRTPND, 1);
}

void hexdump(void *ptr, int len) {
	for (int i = 0; i < len; i += 16) {
		xprintf("%08x: ", ptr + i);

		for (int j = 0; j < 16; j++) {
			if (i+j < len)
				xprintf("%02x ", *(uint8_t*)(ptr+i+j));
			else
				xputs("-- ");
		}

		xputs(" |");
		
		for (int j = 0; j < 16; j++) {
			uint8_t c = ' ';

			if (i+j < len) {
				c = *(uint8_t*)(ptr+i+j);
				if (c < 0x20 || c >= 0x7f) c = '.';
			}

			xputc(c);
		}

		xputs("|\n");
	}

	xputc('\n');
}



struct jl_regdump {
	uint32_t psr, pc;
	uint32_t reti, rets;
	uint32_t ie1, ie0, icfg;
	uint32_t maccl, macch;
	uint32_t ssp, usp;
	uint32_t gpr[15];
};

void jl_exc_handler(struct jl_regdump *dump) {
	xputs("=========== JieLi Crashed!! ===========\n");
	xprintf("Dump: %08x\n", dump);

	/* ============ GPR Dump ============ */
	xputs("\nGPR DUMP:\n");

	xprintf("  r0: <%08x>   r1: <%08x>   r2: <%08x>   r3: <%08x>\n",
		dump->gpr[0], dump->gpr[1], dump->gpr[2], dump->gpr[3]);

	xprintf("  r4: <%08x>   r5: <%08x>   r6: <%08x>   r7: <%08x>\n",
		dump->gpr[4], dump->gpr[5], dump->gpr[6], dump->gpr[7]);

	xprintf("  r8: <%08x>   r9: <%08x>  r10: <%08x>  r11: <%08x>\n",
		dump->gpr[8], dump->gpr[9], dump->gpr[10], dump->gpr[11]);

	xprintf(" r12: <%08x>  r13: <%08x>  r14: <%08x>\n",
		dump->gpr[12], dump->gpr[13], dump->gpr[14]);

	/* ============ SFR Dump ============ */
	xputs("\nSFR DUMP:\n");

	xprintf("   psr: <%08x>     pc: <%08x>  reti: <%08x>  rets: <%08x>\n",
		dump->psr, dump->pc, dump->reti, dump->rets);

	xprintf("   ie1: <%08x>    ie0: <%08x>  icfg: <%08x>\n",
		dump->ie1, dump->ie0);

	xprintf(" maccl: <%08x>  macch: <%08x>\n",
		dump->maccl, dump->macch);

	xprintf("   ssp: <%08x>    usp: <%08x>\n",
		dump->ssp, dump->usp);
}



static void JL_clk_config(void) {
	/* switch to safe clock */
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON0_CKSEL, 4); // sw to btosc

	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON0_OSCSEL, 0); // osc is btosc

	/* Init PLL */
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLRST, 0); // reset
	for (volatile int i = 1000; i; i--);
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLRST, 1); // release reset

	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLREFSEL2, 0); // pll ref <- btosc 24 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLREFDS, 0); // pll rev div2   ==> 12 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLREFDE, 2); // pll rev div enable -> {PLLREFDS}
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLREFSEL2, 0);

	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_PLLFBDS, (480/12)-2); // feedback clk div=> 480 MHz out of 12 MHz

	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON_PLLEN, 1); // enable
	for (volatile int i = 1000; i; i--);

	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_CK480MOE, 1); // en 480 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_CK320MOE, 1); // en 320 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_CK192MOE, 1); // en 192 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_CK137MOE, 1); // en 137 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_PLLCON1_CK107MOE, 1); // en 107 MHz

	/* Config clock routes */
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON2_PLLSYSSEL, 2); // pll_sys <- pll_480m
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON2_PLLSYSDIV0, 0); //  div1
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON2_PLLSYSDIV1, 1); //    div2  ==>240 MHz!!!

	reg32_wsmask(CLOCK_BASE+CLOCK_SYSDIV_1214, 0); // div1     => sfc    240 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_SYSDIV_0007, 0); //   div1   => main   240 MHz
	reg32_wsmask(CLOCK_BASE+CLOCK_SYSDIV_0810, 2); //     div3 => lsb     80 MHz

	/* switch to PLL */
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON0_CKSEL, 7); // sw to pll_sys

	/* peripheral clks */
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON1_UARTCKSEL, 1); // UART <- pll_48m
}

static void JL_uart_init(void) {
	// config uart
	reg32_write(UART2_BASE+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART2_BASE+UARTx_BAUD, 48000000/4/115200);

	// config uart iomux
	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 14, 3, 0); // UART2 to PA3/PA4
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3,  8, 7, 0); // UART2 I/O sel -> IOMUX
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 11, 1, 1); // UART2 I/O enable
	reg32_wsmask(PORTA_BASE+PORTx_DIRn(3), 0); //PA3: out
	reg32_wsmask(PORTA_BASE+PORTx_DIRn(4), 1); //PA4: in

	// setup the Xprintf
	xdev_out(uputc);
	for (int i = 0; i < 10; i++) xputc('\n');
	xputs("\n\e[1;40;33;7m <<  Tsukasa, Konata and Miyuki  >> \e[0m\n");
}


void sflash_spi_sel(char en) {
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(3), 0);
	reg32_wsmask(PORTD_BASE+PORTx_OUTn(3), !en);
}

void sflash_spi_send(uint8_t val) {
	reg32_wsmask(SPI0_BASE+SPIx_CON_DIR, 0);
	reg32_write(SPI0_BASE+SPIx_BUF, val);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
}

uint8_t sflash_spi_recv(void) {
	reg32_wsmask(SPI0_BASE+SPIx_CON_DIR, 1);
	reg32_write(SPI0_BASE+SPIx_BUF, 0xff);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
	return reg32_read(SPI0_BASE+SPIx_BUF);
}

void sflash_spi_wdma(void *ptr, int len) {
	reg32_wsmask(SPI0_BASE+SPIx_CON_DIR, 0);
	reg32_write(SPI0_BASE+SPIx_ADR, (uint32_t)ptr);
	reg32_write(SPI0_BASE+SPIx_CNT, len);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
}

void sflash_spi_rdma(void *ptr, int len) {
	reg32_wsmask(SPI0_BASE+SPIx_CON_DIR, 1);
	reg32_write(SPI0_BASE+SPIx_ADR, (uint32_t)ptr);
	reg32_write(SPI0_BASE+SPIx_CNT, len);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
}


void JL_uart1_init(void) {
	// config uart
	reg32_write(UART1_BASE+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART1_BASE+UARTx_BAUD, 48000000/4/115200);

	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 2, 3, 3); // UART1 to USBDP/USBDM
}

void JL_uart_putc(uint8_t val) {
	reg32_write(UART1_BASE+UARTx_BUF, val);
	while (!reg32_rsmask(UART1_BASE+UARTx_CON0_TPND));
	reg32_wsmask(UART1_BASE+UARTx_CON0_CLRTPND, 1);
}

uint8_t JL_uart_getc(void) {
	while (!reg32_rsmask(UART1_BASE+UARTx_CON0_RPND));
	uint8_t val = reg32_read(UART1_BASE+UARTx_BUF);
	reg32_wsmask(UART1_BASE+UARTx_CON0_CLRRPND, 1);
	return val;
}



/*
       A
    _______
 F | \I| / | B
   | H\|/J |
 G1 --- --- G2
 E | K/|\M | C
   | /L| \ |
    -------
       D
*/

#define GRD14S__A	0x0002
#define GRD14S__B	0x0004
#define GRD14S__F	0x0008
#define GRD14S__H	0x0010
#define GRD14S__I	0x0020
#define GRD14S__J	0x0040
#define GRD14S__G1	0x0080
#define GRD14S__G2	0x0100
#define GRD14S__C	0x0200
#define GRD14S__E	0x0400
#define GRD14S__K	0x0800
#define GRD14S__L	0x1000
#define GRD14S__M	0x2000
#define GRD14S__D	0x4000
#define GRD14S__DP	0x8000

#define GRD14S_0		(GRD14S__A|GRD14S__B|GRD14S__C|GRD14S__D|GRD14S__E|GRD14S__F|GRD14S__J|GRD14S__K)
#define GRD14S_1		(GRD14S__B|GRD14S__C|GRD14S__J)
#define GRD14S_2		(GRD14S__A|GRD14S__B|GRD14S__D|GRD14S__G2|GRD14S__K)
#define GRD14S_3		(GRD14S__A|GRD14S__C|GRD14S__D|GRD14S__G2|GRD14S__J)
#define GRD14S_4		(GRD14S__B|GRD14S__C|GRD14S__F|GRD14S__G1|GRD14S__G2)
#define GRD14S_5		(GRD14S__A|GRD14S__C|GRD14S__D|GRD14S__H|GRD14S__G2)
#define GRD14S_6		(GRD14S__A|GRD14S__D|GRD14S__E|GRD14S__F|GRD14S__M|GRD14S__G1)
#define GRD14S_7		(GRD14S__A|GRD14S__J|GRD14S__K)
#define GRD14S_8		(GRD14S__A|GRD14S__B|GRD14S__C|GRD14S__D|GRD14S__E|GRD14S__F|GRD14S__G1|GRD14S__G2)
#define GRD14S_9		(GRD14S__A|GRD14S__B|GRD14S__C|GRD14S__D|GRD14S__H|GRD14S__G2)

#define GRD14S_A		(GRD14S__B|GRD14S__C|GRD14S__G2|GRD14S__J|GRD14S__K)
#define GRD14S_C		(GRD14S__A|GRD14S__D|GRD14S__E|GRD14S__F)
#define GRD14S_E		(GRD14S__A|GRD14S__D|GRD14S__E|GRD14S__F|GRD14S__G1)
#define GRD14S_G		(GRD14S__A|GRD14S__C|GRD14S__D|GRD14S__E|GRD14S__F|GRD14S__G2)
#define GRD14S_I		(GRD14S__A|GRD14S__D|GRD14S__I|GRD14S__L)
#define GRD14S_J		(GRD14S__D|GRD14S__C|GRD14S__B)
#define GRD14S_K		(GRD14S__F|GRD14S__E|GRD14S__G1|GRD14S__J|GRD14S__G2|GRD14S__C)
#define GRD14S_L		(GRD14S__F|GRD14S__E|GRD14S__D)
#define GRD14S_M		(GRD14S__B|GRD14S__C|GRD14S__F|GRD14S__E|GRD14S__H|GRD14S__J)
#define GRD14S_N		(GRD14S__B|GRD14S__C|GRD14S__F|GRD14S__E|GRD14S__H|GRD14S__M)
#define GRD14S_O		(GRD14S__A|GRD14S__B|GRD14S__C|GRD14S__D|GRD14S__E|GRD14S__F)
#define GRD14S_T		(GRD14S__A|GRD14S__I|GRD14S__L)
#define GRD14S_Z		(GRD14S__A|GRD14S__J|GRD14S__K|GRD14S__D)

#define GRD1_VCR	0x0001
#define GRD1_MP3	0x0002
#define GRD1_MIC	0x0004
#define GRD1_DVD	0x0008
#define GRD1_RPT	0x0010
#define GRD1_ALL	0x0020
#define GRD1_A		0x0040
#define GRD1_B		0x0080
#define GRD1_VCD	0x0100
#define GRD1_PHOTO	0x0200
#define GRD1_WMA	0x0400
#define GRD1_TV		0x0800
#define GRD1_RW		0x1000
#define GRD1_PSCAN	0x2000
#define GRD1_TIMER	0x4000
#define GRD1_LOCK	0x8000
#define GRD2_PROG	0x0001
#define GRD3_TITLE	0x0001
#define GRD4_CHPTRK	0x0001
#define GRD5_DISC	0x0001
#define GRD6_BIL	0x0001
#define GRD7_SAP	0x0001
#define GRD8_STEREO	0x0001
#define GRD9_COPY	0x0001
#define GRD10_REC	0x0001
#define GRD11_HIFI	0x0001

void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	/* disable WDT */
	reg32_write(CRC_BASE+CRC_REG, 0x6EA5); // CRC_REG = 0x6EA5 to unlock WDT reg
	reg32_write(SYSCFG_BASE+SYSCFG_WDTCON, 0x00);   // disable WDT altogether
	reg32_write(CRC_BASE+CRC_REG, 0x0000); // lock WDT reg back

	JL_clk_config();
	JL_uart_init();
	irtc_init();

	// disconnect usb
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPPU, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMPU, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPPD, 1);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMPD, 1);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPIE, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMIE, 1);
	reg32_wsmask(USB_BASE+USB_IO_CON0_USBIOMODE, 1);

	reg32_wsmask(PORTB_BASE+PORTx_DIRn(0), 0); // PB0 => out  (LED)
	reg32_wsmask(PORTC_BASE+PORTx_DIRn(3), 0); // PC3 => out  (ST_CP)
	reg32_wsmask(PORTC_BASE+PORTx_DIRn(4), 0); // PC4 => out  (SH_CP)
	reg32_wsmask(PORTC_BASE+PORTx_DIRn(5), 0); // PC5 => out  (DS)

	/*
	 * GRD0  GRD1  GRD2   GRD3   GRD4   GRD5   GRD6   GRD7
	 * GRD8  GRD9  GRD10  x      x      x      x      FIL
	 * AND0  AND1  AND2   AND3   AND4   AND5   AND6   AND7
	 * AND8  AND9  AND10  AND11  AND12  AND13  AND14  AND15
	 */

	/* ============================================================== */

	xputs("=== "__DATE__" - "__TIME__" ===\n");
	xprintf("r0=%08x, r1=%08x, r2=%08x, r3=%08x\n", r0,r1,r2,r3);

	const uint16_t segs[11] = {
		GRD1_MP3|GRD1_MIC|GRD1_A|GRD1_B|GRD1_LOCK,

		/*GRD14S_K,
		GRD14S_O|GRD3_TITLE,
		GRD14S_N,
		GRD14S_A|GRD5_DISC,
		GRD14S_T,
		GRD14S_A,
		GRD14S_6,
		GRD14S_9,
		GRD14S_2,
		GRD14S_5,*/

		/*GRD14S_G,
		GRD14S_E|GRD3_TITLE,
		GRD14S_M,
		GRD14S_A|GRD5_DISC,
		GRD14S_T,
		GRD14S_A,
		GRD14S_N,
		GRD14S_Z,
		GRD14S_E,
		GRD14S_N,*/

		GRD14S_0,
		GRD14S_1|GRD3_TITLE,
		GRD14S_2,
		GRD14S_3|GRD5_DISC,
		GRD14S_4,
		GRD14S_5,
		GRD14S_6,
		GRD14S_7,
		GRD14S_8,
		GRD14S_9,
	};

	for (char fil = 0;;) {
		for (int i = 0; i < 11; i++) {
			uint32_t send = (fil<<15) | (segs[i]<<16) | (1<<i);

			for (uint32_t m = 0x80000000; m; m >>= 1) {
				reg32_wsmask(PORTC_BASE+PORTx_OUTn(5), !!(m & send));
				reg32_wsmask(PORTC_BASE+PORTx_OUTn(4), 1);
				reg32_wsmask(PORTC_BASE+PORTx_OUTn(4), 0);
			}

			reg32_wsmask(PORTC_BASE+PORTx_OUTn(3), 1);
			for (volatile int i = 100; i; i--);
			reg32_wsmask(PORTC_BASE+PORTx_OUTn(3), 0);
			for (volatile int i = 100; i; i--);

			fil = !fil;
		}
	}
}
