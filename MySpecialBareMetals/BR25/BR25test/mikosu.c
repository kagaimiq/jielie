#include <stdint.h>
#include <xprintf.h>
#include <jl_regs.h>


void uputc(int c) {
	reg32_write(UART0_base+UARTx_BUF, c);
	while (!reg32_rsmask(UART0_base+UARTx_CON0_TPND));
	reg32_wsmask(UART0_base+UARTx_CON0_CLRTPND, 1);
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
}


void delay(uint32_t ms) {
	while (ms--) // TODO!
		for (volatile int i = 1000; i; i--);
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


volatile int msecs;

__attribute__((interrupt)) void Konatachan2(void) {
	static int ctr;

	if (++ctr >= 1000) {
		ctr = 0;
		xprintf("hai, %d\n", msecs);
	}

	msecs++;
	reg32_wsmask(TIMER0_base+TIMERx_CON_PCLR, 1);
}

__attribute__((interrupt)) void Hakase(void) {
	static int ctr2;

	if (++ctr2 >= 1000) {
		ctr2 = 0;
		xprintf("wai, %d\n", msecs);
	}

	reg32_wsmask(TIMER1_base+TIMERx_CON_PCLR, 1);
}



void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	// init UART0 on PB5
	reg32_write(UART0_base+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART0_base+UARTx_BAUD, (48000000 / 4 / 921600) - 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0, 3, 3, 2); // UART0 to PB5
	reg32_wsmask(IOMAP_base+IOMAP_CON3, 2, 1, 0); // UART0 ... IO SEL -> IOMUX ?
	reg32_wsmask(IOMAP_base+IOMAP_CON3, 3, 1, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\e[H\e[2J\e[3J"); // clear screen
	xputs("\e[1;37;41m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	/*==================================================================*/


	extern void *irqvectors[];
	void ExceptionHandler_entry(void);

	/*for (int i = 0; i < 0x1000; i += 16) {
		xprintf("%3x: %08x %08x %08x %08x\n", i,
			reg32_read(0x100000+0xf000+i+0x0),
			reg32_read(0x100000+0xf000+i+0x4),
			reg32_read(0x100000+0xf000+i+0x8),
			reg32_read(0x100000+0xf000+i+0xc)
		);
	}*/

	irqvectors[1] = ExceptionHandler_entry;

	irqvectors[4] = Konatachan2;
	irqvectors[5] = Hakase;

	//asm volatile ("[--sp] = {r1-r0}\nr0 = 0xdead\nr1 = 0x1638\n[r0] = r1;\n{r1-r0} = [sp++]\n");

	reg32_write(TIMER0_base+TIMERx_CON, 0);
	reg32_write(TIMER0_base+TIMERx_PRD, 48000);
	reg32_wsmask(TIMER0_base+TIMERx_CON_MODE, 1);

	reg32_write(TIMER1_base+TIMERx_CON, 0);
	reg32_write(TIMER1_base+TIMERx_PRD, 24000);
	reg32_wsmask(TIMER1_base+TIMERx_CON_MODE, 1);
	reg32_wsmask(TIMER1_base+TIMERx_CON_MODE, 1);

	//reg32_wsmask(0x100000+0xf000+0x100+0x8, 8, 0xf, 0x1); // en irq18
	reg32_wsmask(0x100000+0xf000+0x100+0x0, 16, 0xf, 0x1); // en irq4
	reg32_wsmask(0x100000+0xf000+0x100+0x0, 20, 0xf, 0x1); // en irq5

	xputs("Nothing ?!");

	#if 0
	///----------- dac init
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 30, 1, 1);

	reg32_wsmask(ANA_base+ANA_DAA_CON0, 19, 0x3, 0x3);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 18, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 17, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 16, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 15, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 14, 1, 1);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 8, 1, 0);
	reg32_wsmask(ANA_base+ANA_DAA_CON0, 6, 1, 0);

	///----------- dac vdd power on
	//reg32_wsmask(ANA_base+ANA_DAA_CON2, 11, 0x7, 0x0);

	//reg32_wsmask(ANA_base+ANA_DAA_CON0, 25, 0x7, 0x0); // vdd voltage

	//reg32_wsmask(ANA_base+ANA_DAA_CON0, 22, 1, 1);
	//reg32_wsmask(ANA_base+ANA_DAA_CON0, 24, 1, 1);
	#endif

	/*==================================================================*/

	#if 0
	///----------- open linein
	reg32_wsmask(PORTA_base+PORTx_DIRn(3), 1); // PA3 in
	reg32_wsmask(PORTA_base+PORTx_DIEn(3), 0); // PA3 digital in disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0l_en, 1); // AMUX0L enable

	reg32_wsmask(PORTA_base+PORTx_DIRn(4), 1); // PA4 in
	reg32_wsmask(PORTA_base+PORTx_DIEn(4), 0); // PA4 digital in disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0r_en, 1); // AMUX0R enable

	reg32_wsmask(PORTB_base+PORTx_DIRn(6), 1); // PB6 in
	reg32_wsmask(PORTB_base+PORTx_DIEn(6), 0); // PB6 digital in disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1l_en, 1); // AMUX1L enable

	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 1); // PB7 in
	reg32_wsmask(PORTB_base+PORTx_DIEn(7), 0); // PB7 digital in disable
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1r_en, 1); // AMUX1R enable

	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_en, 1); // AMUX enable

	///----------- gain
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_gain, 0); // 2x gain

	///----------- mute
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_mute, 0); // mute

	///----------- combine
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_lrmix, 0x0);

	///----------- linein bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0l_biasen, 0); // AMUX0L bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux0r_biasen, 0); // AMUX0R bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1l_biasen, 0); // AMUX1L bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux1r_biasen, 0); // AMUX1R bias

	///----------- amux bias
	reg32_wsmask(ANA_base+ANA_DAA_CON1_amux_biasen, 0); // amux bias
	#endif
}
