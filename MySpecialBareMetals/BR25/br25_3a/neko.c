#include <stdint.h>
#include <jl_regs.h>
#include <xprintf.h>

void uputc(int c) {
	reg32_write(UART0_base+UARTx_BUF, c);
	while (!reg32_rsmask(UART0_base+UARTx_CON0_tpnd));
	reg32_wsmask(UART0_base+UARTx_CON0_clrtpnd, 1);
}

void hexdump(void *ptr, int len) {
	for (int i = 0; i < len; i += 16) {
		xprintf("%08x: ", ptr+i);

		for (int j = 0; j < 16; j++) {
			if (i+j < len)
				xprintf("%02X ", *(uint8_t*)(ptr+i+j));
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



struct JieLi_ExceptFrame {
	// general purpose
	uint32_t gpr[16];

	// special function
	union {
		uint32_t sfr[16];
		struct {
			uint32_t reti, rete, retx, rets;
			uint32_t sr4,  psr,  cnum, sr7;
			uint32_t sr8,  sr9,  sr10, icfg;
			uint32_t usp,  ssp,  sp,   pc;
		};
	};
};

void ExceptionHandler(struct JieLi_ExceptFrame *ef) {
	xputs("\e[1;33;44m=========== JieLi Crashed! ===========\e[0m\n");

	uint32_t *p;

	xputs("\n---- General purpose regs ----\n");
	p = ef->gpr;
	xprintf(" r0: <%08x>   r1: <%08x>   r2: <%08x>   r3: <%08x>\n", p[ 0], p[ 1], p[ 2], p[ 3]);
	xprintf(" r4: <%08x>   r5: <%08x>   r6: <%08x>   r7: <%08x>\n", p[ 4], p[ 5], p[ 6], p[ 7]);
	xprintf(" r8: <%08x>   r9: <%08x>  r10: <%08x>  r11: <%08x>\n", p[ 8], p[ 9], p[10], p[11]);
	xprintf("r12: <%08x>  r13: <%08x>  r14: <%08x>  r15: <%08x>\n", p[12], p[13], p[14], p[15]);

	xputs("\n---- Special function regs ----\n");
	p = ef->sfr;
	xprintf("reti: <%08x>  rete: <%08x>  retx: <%08x>  rets: <%08x>\n", p[ 0], p[ 1], p[ 2], p[ 3]);
	xprintf(" sr4: <%08x>   psr: <%08x>  cnum: <%08x>   sr7: <%08x>\n", p[ 4], p[ 5], p[ 6], p[ 7]);
	xprintf(" sr8: <%08x>   sr9: <%08x>  sr10: <%08x>  icfg: <%08x>\n", p[ 8], p[ 9], p[10], p[11]);
	xprintf(" usp: <%08x>   ssp: <%08x>    sp: <%08x>    pc: <%08x>\n", p[12], p[13], p[14], p[15]);
}

__attribute__((naked)) void ExceptionHandler_entry(void) {
	// store all the regs - make an exception frame
	asm ("[--sp] = {pc, sp, ssp, usp, icfg, sr10, sr9, sr8, sr7, cnum, psr, sr4, rets, retx, rete, reti}");
	asm ("[--sp] = {r15-r0}");

	// pass the pointer to the exception frame
	asm ("r0 = sp");

	// call the handler
	asm ("call ExceptionHandler");

	// halt
	asm ("1: idle\ngoto 1b");
}




void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 10, 0x3, 0x1); // uart_clk <- pll_48m?

	// init UART0 on PB5
	reg32_write(UART0_base+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART0_base+UARTx_BAUD, (24000000 / 4 / 115200) - 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0_ut0ios, 0x2); // UART0 to PB5
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0mxs, 0x0); // UART0 muxsel -> iomux
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0ioen, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\e[H\e[2J\e[3J"); // clear screen
	xputs("\e[1;37;41m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	*(void **)0x31f04 = ExceptionHandler_entry;

	/*==================================================================*/

	reg32_wsmask(PORTD_base+PORTx_DIRn(0), 0); // PD0 out  -> SCK
	reg32_wsmask(PORTD_base+PORTx_DIRn(1), 0); // PD1 out  -> MOSI
	reg32_wsmask(PORTD_base+PORTx_DIRn(2), 1); // PD2 in   -> MISO
	reg32_wsmask(PORTD_base+PORTx_DIRn(3), 0); // PD3 out  -> CS
	reg32_wsmask(PORTD_base+PORTx_DIRn(4), 0); // PD4 out  -> ?? HOLD? Power?!

	reg32_wsmask(PORTD_base+PORTx_PUn(1), 1); // PD1 pullup
	reg32_wsmask(PORTD_base+PORTx_PUn(2), 1); // PD2 pullup

	reg32_wsmask(PORTD_base+PORTx_OUTn(3), 1); // PD3 high
	reg32_wsmask(PORTD_base+PORTx_OUTn(4), 1); // PD4 high

	reg32_wsmask(IOMAP_base+IOMAP_CON0_spi0ios, 0x0); // SPI0 on PD3/PD2/PD1/PD0
	reg32_wsmask(IOMAP_base+IOMAP_CON1_sfcios, 0x0); // SFC on PD3/PD2/PD1/PD0

	reg32_write(SFC_base+SFC_CON, 0xf00000);
	reg32_write(SFC_base+SFC_CON, 0);

	reg32_write(SFC_base+SFC_BAUD, 0xff);

	/*
	 * mask -> 6ff0fbd : 0110'1111'1111'0000'1111'1011'1101
	 *         0000034   0000'0000'0000'0000'0000'0011'0100
	 *
	 * write ->6ff0f89   0110'1111'1111'0000'1111'1000'1001
	 *
	 *          200088   0000'0010'0000'0000'0000'1000'1000
	 *
	 * b0 = enable
	 * b3 = combine MOSI and MISO
	 * b7 = 
	 * b8~b11 = 
	 * b16~b19 = dummy bits count
	 * b20~b23 = 
	 * b25 = if set, then the JEDEC ID is readed out (cmd 9F)
	 *
	 * 00000011 Aaaaaaaa:aaaaaaaa:aaaaaaaa          <Data>
	 * 00001011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Data>
	 * 00111011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Dual data>
	 * 01101011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Quad data>
	 * 10111011 AA.aa.aa.aa:aa.aa.aa.aa:... XX.XX.XX.XX <Dual data>
	 * 11101011 AAAA.aaaa:aaaa.aaaa:.... XXXX.XXXX.XXXX.XXXX.XXXX.XXXX <Quad data>
	 * xxxxyzzz
	 * 
	 *
	 * SINGLE IO
	 * 0x00200088 <== [r2 != 4] && [r1 != 8]  >>>> cmd 03 - read
	 * 0x00280188 <== [r2 != 4] && [r1 == 8]  >>>> cmd 0B - read fast
	 *
	 * DUAL IO
	 * 0x00200080 <== [r2 == 2] && [r1 != 8]  >>>> cmd 03 - read
	 * 0x00280280 <== [r2 == 2] && [r1 == 4]  >>>> cmd 3B - read dual out
	 * 0x00240480 <== [r2 == 2] && [r1 == 8]  >>>> cmd BB - read dual io
	 * 0x00240680 <== [r2 == 2] && [r1 == 12] >>>> 
	 *
	 * QUAD IO
	 * 0x00200080 <== [r2 == 4] && [r1 != 8]  >>>> cmd 03 - read
	 * 0x00280380 <== [r2 == 4] && [r1 == 4]  >>>> cmd 6B - read quad out
	 * 0x00260580 <== [r2 == 4] && [r1 == 8]  >>>> cmd EB - read quad io
	 * 0x00260780 <== [r2 == 4] && [r1 == 12] >>>> 
	 */

	reg32_wsmask(SFC_base+SFC_CON, 0, 0x6ff0f88, 0x0280280);

	reg32_write(SFC_base+SFC_BASE_ADR, 0x1000);

	reg32_write(SFCENC_base+SFCENC_CON, 0); //b0 = enable, b1=?
	reg32_write(SFCENC_base+SFCENC_KEY, 0x077A);
	reg32_write(SFCENC_base+SFCENC_UNENC_ADRH, 0x0000);
	reg32_write(SFCENC_base+SFCENC_UNENC_ADRL, 0x0000);
	reg32_write(SFCENC_base+SFCENC_LENC_ADRH,  0x0000);
	reg32_write(SFCENC_base+SFCENC_LENC_ADRL,  0x0000);
	reg32_wsmask(SFCENC_base+SFCENC_CON_enable, 0);

	reg32_wsmask(DSP_base+DSP_CON, 8, 1, 0); // disable sfc map
	memset((void *)0xfc000, 0x00, 0x1c00);   // clear sfc cache tags
	reg32_wsmask(DSP_base+DSP_CON, 8, 1, 1); // enable sfc map

	reg32_wsmask(SPI0_base+SPIx_CON_spie, 0); // disable spi
	reg32_wsmask(SFC_base+SFC_CON_enable, 1); // enable sfc

	hexdump((void *)0x1000000, 0x100);

	((void (*)())0x1000000)();
}
