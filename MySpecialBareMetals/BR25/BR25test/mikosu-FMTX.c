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

void IRQ_HANDLER fmtx_isr(void) {
	static uint32_t t = 0;

	int slice = reg32_rsmask(FM_base+FM_TX_CON0_buffslice);
	//xprintf("!! FMTX irq -> slice=%d, t=%u\n", slice, t);

	for (int i = 0; i < 1024; i++) {
		// ryg 2011-10-10 http://www.youtube.com/watch?v=tCRPUv8V22o 44.1 kHz
		uint8_t v = ((t*("36364689"[t>>13&7]&15))/12&128)+(((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127);
		t++;

		fmtx_buf[(slice + 1) % 2][i] = (v * 0x01000100) ^ 0x80008000;
	}

	//xprintf("%08x|%08x\n", fmtx_buf[0][0], fmtx_buf[1][0]);

	reg32_wsmask(FM_base+FM_TX_CON1_cpnd, 1); // clear pending
}

void fmtx_on(void) {
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 0x81, ~0);
}

void fmtx_off(void) {
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 0x81, 0);
}

void fmtx_init(void) {
	reg32_wsmask(FM_base+FM_CON, 14, 1, 0); // enable fm tx regs!

	reg32_write(FM_base+FM_TX_BASE_ADR, (uint32_t)fmtx_buf);

	// effectively fmtx_on
	reg32_wsmask(FM_base+FM_TX_CON0, 0, 0x81, ~0);

	reg32_write(FM_base+FM_TX_MUL,      59);
	reg32_write(FM_base+FM_TX_PILOT,    166);
	reg32_write(FM_base+FM_TX_SYN_GAIN, 0x1000);
	reg32_write(FM_base+FM_TX_FREQ,     0x15400000);

	//----------------------------------------------------

	reg32_write(FM_base+FM_TX_LEN, 0);

	for (int i = 160; i > 0; i--) {
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

	reg32_wsmask(FM_base+FM_TX_CON0, 1, 1, 0); // <--- stereo flag

	reg32_wsmask(FM_base+FM_TX_CON1, 0, 1, 1);
	reg32_wsmask(FM_base+FM_TX_CON1, 0, 0xf, 0x0);
	reg32_wsmask(FM_base+FM_TX_CON1, 3, 1, 1);

	reg32_write(FM_base+FM_TX_FREQ, 0x15400000);

	reg32_write(FM_base+FM_TX_LEN, 1024);
	delay(500);

	reg32_wsmask(FM_base+FM_TX_CON0, 3, 1, 1);
}

#if 1
void fmtx_set_freq(int freq) {

	uint8_t v10 = freq / 4800. + .5;
	if (v10 > 8) v10 = 8;
	xprintf("... V10 = %d\n", v10);

	uint32_t v13 = freq * 100 * v10;
	xprintf("...V13 = %d\n", v13);

	uint32_t v18 = v13 / 1000 / 24. - 2.;
	xprintf("...V18 = %d\n", v18);

	uint32_t v26 = (v13 / 24. / 1000.) - v18 + -2.; // * 0x4170000000000000ull;
	xprintf("...V26 = %d\n", v26);

	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 31, 1, 0);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 11, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 22, 0x3, 0x1);
	reg32_wsmask(ANA_base+ANA_WLA_CON19, 21, 1, 1);

	const char divider[8] = {0x0, 0x4, 0x1, 0x8, 0x2, 0x5, 0x3, 0xC};
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON2, 2, 0xf, divider[v10]);

	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON2, 0, 0x3, 0x3);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 24, 0x7, 0x1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 27, 0x7, 0x3);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 10, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 19, 1, 1);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON1, 31, 1, 1);

	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 0, 1, 1); // enable
	delay(150);
	reg32_wsmask(CLOCK_base+CLOCK_PLL_CON, 1, 1, 1); // release reset

	reg32_write(FM_base+FM_TX_FREQ, (v18<<24)|(v26&0xffffff)); // (%18 << 24) | %26
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




void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 10, 0x3, 0x0); // uart_clk <- pll_48m?

	// init UART0 on PB5
	reg32_write(UART0_base+UARTx_CON0, 0);
	reg32_write(UART0_base+UARTx_BAUD, (48000000 / 4 / 115200) - 1);
	reg32_wsmask(UART0_base+UARTx_CON0_uten, 1); // enable
	reg32_wsmask(IOMAP_base+IOMAP_CON0, 3, 3, 2); // UART0 to PB5
	reg32_wsmask(IOMAP_base+IOMAP_CON3, 2, 1, 0); // UART0 ... IO SEL -> IOMUX ?
	reg32_wsmask(IOMAP_base+IOMAP_CON3, 3, 1, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\e[H\e[2J\e[3J"); // clear screen
	xputs("\e[1;37;41m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	/*==================================================================*/

	wallclk_init();

	fm_emitter_init();
	fmtx_set_freq(8600); // 86 mhz
}
