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
}





volatile uint32_t fmtx_buf[2][1024];
volatile uint64_t lasttime;

void IRQ_HANDLER fmtx_isr(void) {
	reg32_wsmask(FM_base+FM_TX_CON1, 6, 1, 1); // clear pending
	int slice = reg32_rsmask(FM_base+FM_TX_CON0, 4, 1);

	for (int i = 0; i < 1024; i++)
		fmtx_buf[slice][i] = reg32_read(RAND_base+RAND_R64L);

	//xprintf("%08x\n", fmtx_buf[slice][0]);

	uint32_t ctime = micros() - lasttime;
	lasttime = micros();

	xprintf("!!! FMTX IRQ, slice=%d, period=%u\n", slice, 1024 * 1000000 / ctime);
}

void fmtx_on(void) {
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 1, 1);
	reg32_wsmask(FM_base+FM_TX_CON0, 7, 1, 1);
}

void fmtx_off(void) {
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 1, 0);
	reg32_wsmask(FM_base+FM_TX_CON0, 7, 1, 0);
}

void fmtx_init(void) {
	reg32_wsmask(FM_base+FM_CON, 14, 1, 0); // enable fm tx regs!

	reg32_write(FM_base+FM_TX_BASE_ADR, (uint32_t)fmtx_buf);

	// effectively fmtx_on
	reg32_wsmask(FM_base+FM_TX_CON0, 7, 1, 1);
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 1, 1);

	reg32_write(FM_base+FM_TX_MUL,      59);
	reg32_write(FM_base+FM_TX_PILOT,    166);
	reg32_write(FM_base+FM_TX_SYN_GAIN, 0x1000);
	reg32_write(FM_base+FM_TX_FREQ,     0x15400000);

	//----------------------------------------------------

	reg32_write(FM_base+FM_TX_LEN,      0);

	for (int i = 160; i >= 0; i--) {
		reg32_write(FM_base+FM_TX_ADR, i << 2);
		delay(5);
		reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
		delay(5);
	}

	//------------------

	reg32_write(FM_base+FM_TX_LEN, -13);

	reg32_write(FM_base+FM_TX_ADR, 256);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	reg32_write(FM_base+FM_TX_ADR, 296);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//------------------

	reg32_write(FM_base+FM_TX_LEN, 13);

	reg32_write(FM_base+FM_TX_ADR, 260);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	reg32_write(FM_base+FM_TX_ADR, 292);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//------------------

	reg32_write(FM_base+FM_TX_LEN, -39);

	reg32_write(FM_base+FM_TX_ADR, 264);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	reg32_write(FM_base+FM_TX_ADR, 288);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//------------------

	reg32_write(FM_base+FM_TX_LEN, 24);

	reg32_write(FM_base+FM_TX_ADR, 268);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	reg32_write(FM_base+FM_TX_ADR, 284);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//------------------

	reg32_write(FM_base+FM_TX_LEN, -451);

	reg32_write(FM_base+FM_TX_ADR, 272);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	reg32_write(FM_base+FM_TX_ADR, 280);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//------------------

	reg32_write(FM_base+FM_TX_LEN, 1945);

	reg32_write(FM_base+FM_TX_ADR, 276);
	delay(5);
	reg32_wsmask(FM_base+FM_TX_CON0, 5, 1, 1);
	delay(5);

	//----------------------------------------------------

	delay(200);

	reg32_wsmask(FM_base+FM_TX_CON0, 0, 1, 1);
	delay(10);

	reg32_wsmask(FM_base+FM_TX_CON1, 6, 1, 1);
	delay(10);

	reg32_wsmask(FM_base+FM_TX_CON0, 1, 1, 1); // <--- stereo flag

	reg32_wsmask(FM_base+FM_TX_CON1, 0, 1, 1);
	reg32_wsmask(FM_base+FM_TX_CON1, 0, 0xf, 0x0);
	reg32_wsmask(FM_base+FM_TX_CON1, 3, 1, 1);

	reg32_write(FM_base+FM_TX_FREQ, 0x15400000);

	reg32_write(FM_base+FM_TX_LEN, 1024);
	delay(500);

	reg32_wsmask(FM_base+FM_TX_CON0, 3, 1, 1);
}

#if 0
void fmtx_set_freq(int freq) {
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 31, 1, 0);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 11, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 22, 0x3, 0x1);
	reg32_wsmask(ANA_base+ANA_WLA_CON19, 21, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON2, 2, 0xf, 0x8); //<--- divider[%12 - 1]
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON2, 0, 0x3, 0x3);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 24, 0x7, 0x1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 27, 0x7, 0x3);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 10, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 19, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 31, 1, 1);

	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 0, 1, 1); // enable
	delay(150);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 1, 1, 1); // release reset

	reg32_write(FM_base+FM_TX_FREQ, (0x15<<24)|0x400000); // (%18 << 24) | %26
	delay(30);
}
#endif

void fmtx_analog_init(void) {
	reg32_wsmask(ANA_base+ANA_WLA_CON18,  1, 1, 1);
	reg32_wsmask(ANA_base+ANA_WLA_CON21, 11, 1, 0);
}

void fm_emitter_init(void) {
	irq_attach(47, fmtx_isr);

	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 24, 0x3, 0x1); // clk sel
	reg32_wsmask(FM_base+FM_TX_CON1, 3, 1, 1);
	fmtx_init();

	// for port=0
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 12, 0x3, 0x1); // clk sel
	reg32_wsmask(PORTB_base+PORTx_DIRn(1), 0); // PB1 = out
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

	irq_attach(1, ExceptionHandler_entry);

	wallclk_init();

	xputs("Start\n");

	fm_emitter_init();
	//fmtx_set_freq(9000); // 90 mhz sorta like that

	xputs("End\n");
}
