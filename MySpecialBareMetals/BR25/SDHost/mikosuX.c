#include <stdint.h>
#include <xprintf.h>
#include <jl_regs.h>
#include <jl_irq.h>
#include <wallclk.h>
#include <maskrom_stuff.h>
#include <ff.h>


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



void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	reg32_wsmask(CLOCK_base+CLOCK_CLK_CON1, 10, 0x3, 0x0); // uart_clk <- pll_48m?

	// init UART0 on PB5
	reg32_write(UART0_base+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART0_base+UARTx_BAUD, (48000000 / 4 / 921600) - 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0_ut0ios, 0x2); // UART0 to PB5
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0mxs, 0x0); // UART0 muxsel -> iomux
	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0ioen, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_base+PORTx_PUn(5), 1); // PB5 pullup
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\e[H\e[2J\e[3J"); // clear screen
	xputs("\e[1;37;41m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	/*==================================================================*/

	wallclk_init();

	static FATFS ftfs;
	xprintf("mount---%d\n", f_mount(&ftfs, "0:", 1));

	

	/*==================================================================*/

	#if 1
	#define P3_EFUSE_CON0		0xb0
	#define P3_EFUSE_CON1		0xb1
	#define P3_EFUSE_RDAT		0xb2

	/*for (int i = 0; i < 8; i++) {
		int sel1 = i >> 2, sel2 = i & 3;

		p33_tx_1byte(P3_EFUSE_CON0, (sel1<<6));
		p33_tx_1byte(P3_EFUSE_CON1, (sel2<<2)|(1<<7)|(1<<1));
		xprintf("%d.%d: %02x\n", sel1, sel2, p33_rx_1byte(P3_EFUSE_RDAT));
		p33_tx_1byte(P3_EFUSE_CON1, 0);
	}*/

	for (int i = 0; i < 256; i++) {
		xprintf("%02x: ", i);
		p33_tx_1byte(P3_EFUSE_CON0, i);

		for (int j = 0; j < 4; j++) {
			p33_tx_1byte(P3_EFUSE_CON1, (j<<2)|(1<<7)|(1<<1));
			xprintf("%02x ", p33_rx_1byte(P3_EFUSE_RDAT));
			p33_tx_1byte(P3_EFUSE_CON1, 0);
		}

		xputc('\n');
	}
	#endif

	#if 0
	p33_tx_1byte(0x80, 0); // disable wdt!

	/*for (int i = 0; i < 0x100; i++) {
		xprintf("%04x: %02x\n", i, p33_rx_1byte(i));
	}*/

	reg32_write(ADC_base+ADC_CON, 0);
	reg32_wsmask(ADC_base+ADC_CON_adcae, 1); // analog enable
	reg32_wsmask(ADC_base+ADC_CON_adcbaud, 0x3); // adc clk div128
	reg32_wsmask(ADC_base+ADC_CON_chsel, 15); // ch15 <- P33

	for (;;) {
		for (int i = 0; i < 8; i++) {
			p33_tx_1byte(0x04, (1<<0)|(i<<1));

			reg32_wsmask(ADC_base+ADC_CON_adcen, 1);

			for (int t = 0; t < 10; t++) { // wait for it to settle
				while (!reg32_rsmask(ADC_base+ADC_CON_pnd));
				reg32_wsmask(ADC_base+ADC_CON_cpnd, 1);
			}

			xprintf("%-4d ", reg32_read(ADC_base+ADC_RES));

			reg32_wsmask(ADC_base+ADC_CON_adcen, 0);
		}

		xputc('\n');
	}

	p33_tx_1byte(0x80, 0x1c); // enable wdt back! (5 sec)
	#endif

	wallclk_deinit();
}
