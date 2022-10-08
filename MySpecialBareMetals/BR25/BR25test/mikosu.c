#include <stdint.h>
#include <xprintf.h>
#include <jl_regs.h>
#include <jl_irq.h>
#include <wallclk.h>

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





void dac_analog_init(void) {
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 4, 1, 0);
	delay(1000);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 14, 1, 1);
	delay(1000);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 22, 1, 1);

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 29, 1, 0); // ... %0[1] >> 23 | zero cross en

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 28, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 23, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 21, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 10, 0x7, 0x0);

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 9, 1, 0); // .... %0[1] >> 23 | zero cross en
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 8, 1, 0); // .... %0[1] >> 23 | zero cross en
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 7, 1, 0); // .... %0[1] >> 23 | zero cross en

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 4, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 3, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 2, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 1, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 0, 1, 0);

	reg32_wsmask(ANA_base+ANA_DAA_CON1, 31, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 30, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 29, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 28, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 27, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 26, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 25, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 24, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 23, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 22, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 21, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 20, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 19, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 18, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 17, 1, 0);

	reg32_wsmask(ANA_base+ANA_DAA_CON1, 5, 0x1f, 0x00);
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 0, 0x1f, 0x00);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 24, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 23, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 22, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 21, 1, 0);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 20, 1, 0); // %0[1] >> 22 | vmc rise time

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 18, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 16, 0x3, 0x0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 15, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 4, 1, 0);

	reg32_wsmask(ANA_base+ANA_DAA_CON4, 3, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON4, 2, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON4, 1, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON4, 0, 1, 0);
	delay(200);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 19, 1, 1);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 0, 0x1f, 0x00); // %0[1] >> 12 | lpf_isel
	delay(1000);

	//......
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 25, 0x7, 0x0); //...

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 22, 1, 1);
	delay(1000);

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 22, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 5, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 13, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 24, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 6, 1, 1);
	delay(1000);

	reg32_wsmask(ANA_base+ANA_DAA_CON2, 22, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON2, 14, 1, 0);
}




void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 10, 0x3, 0x0); // uart_clk <- pll_48m?

	// init UART0 on PB5
	reg32_write(UART0_base+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART0_base+UARTx_BAUD, (48000000 / 4 / 921600) - 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0_ut0ios, 0x2); // UART0 to PB5
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0mxs, 0x0); // UART0 muxsel -> iomux
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0ioen, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\e[H\e[2J\e[3J"); // clear screen
	xputs("\e[1;37;41m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	/*==================================================================*/

	wallclk_init();
	irq_attach(1, ExceptionHandler_entry);

	dac_analog_init();

	//------------------------------------------------------//

	#if 0
	///----------- open linein
	reg32_wsmask(PORTA_base+PORTx_DIRn(3), 1); // PA3 in
	reg32_wsmask(PORTA_base+PORTx_DIEn(3), 0); // PA3 analog in
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0l_en, 1); // AMUX0L enable

	reg32_wsmask(PORTA_base+PORTx_DIRn(4), 1); // PA4 in
	reg32_wsmask(PORTA_base+PORTx_DIEn(4), 0); // PA4 analog in
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0r_en, 1); // AMUX0R enable

	reg32_wsmask(PORTB_base+PORTx_DIRn(6), 1); // PB6 in
	reg32_wsmask(PORTB_base+PORTx_DIEn(6), 0); // PB6 analog in
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1l_en, 1); // AMUX1L enable

	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 1); // PB7 in
	reg32_wsmask(PORTB_base+PORTx_DIEn(7), 0); // PB7 analog in
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1r_en, 1); // AMUX1R enable

	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_en, 1); // AMUX enable

	///----------- gain
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_gain, 0); // 2x gain

	///----------- mute
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_mute, 0); // mute

	///----------- combine
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_lr2lmix, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_lr2rmix, 0);

	///----------- linein bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0l_biasen, 0); // AMUX0L bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0r_biasen, 0); // AMUX0R bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1l_biasen, 0); // AMUX1L bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1r_biasen, 0); // AMUX1R bias

	///----------- amux bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_biasen, 0); // amux bias
	#endif

	#if 0
	///----------- open linein via dac
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0l_en, 0); // AMUX0L disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0r_en, 0); // AMUX0R disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1l_en, 0); // AMUX1L disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1r_en, 0); // AMUX1R disable

	reg32_wsmask(ANA_base+ANA_DAA_CON1, 10, 1, 0); // 
	reg32_wsmask(ANA_base+ANA_DAA_CON1, 11, 1, 1); // 

	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_gain, 1); // 2x gain

	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_en, 0); // AMUX enable

	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_lr2lmix, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_lr2rmix, 1);
	#endif
}
