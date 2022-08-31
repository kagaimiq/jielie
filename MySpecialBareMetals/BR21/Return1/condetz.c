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
}

static void JL_uart_init(void) {
	/* peripheral clks */
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON1_UARTCKSEL, 1); // UART <- pll_48m

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


void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	/* disable WDT */
	//reg32_write(CRC_BASE+CRC_REG, 0x6EA5); // CRC_REG = 0x6EA5 to unlock WDT reg
	//reg32_write(SYSCFG_BASE+SYSCFG_WDTCON, 0x00);   // disable WDT altogether
	//reg32_write(CRC_BASE+CRC_REG, 0x0000); // lock WDT reg back

	//JL_clk_config();
	JL_uart_init();
	irtc_init();

	/* ============================================================== */

	xputs("=== "__DATE__" - "__TIME__" ===\n");
	xprintf("r0=%08x, r1=%08x, r2=%08x, r3=%08x\n", r0,r1,r2,r3);

	/*for (int i = 0; i < 0x20; i++) {
		reg32_write(USB_BASE+USB_CON1, (1<<14)|(i<<8));
		while (!reg32_rsmask(USB_BASE+USB_CON1_ACK));
		xprintf("%02x:>>> %02x\n", i, reg32_rsmask(USB_BASE+USB_CON1_MCDAT));
	}*/

	uint8_t tmp[128] = {};

	reg32_write(SFC_BASE+SFC_CON, 0);
	reg32_write(SPI0_BASE+SPIx_CON, 0x20);
	reg32_write(SPI0_BASE+SPIx_BAUD, 2);

	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 5, 1, 0); // SPI0 on PD3/PD2/PD1/PD0
	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 1, 1, 1); // SPI0 DI is DI+DO

	reg32_wsmask(PORTD_BASE+PORTx_PU,  0, 0x7, 0x6); // PD2/PD1=pullup, PD0=no pullup
	reg32_wsmask(PORTD_BASE+PORTx_PD,  0, 0xf, 0x0); // PD3/PD2/PD1/PD0= no pulldown
	reg32_wsmask(PORTD_BASE+PORTx_OUT, 0, 0x8, 0x8); // PD3=hi
	reg32_wsmask(PORTD_BASE+PORTx_DIR, 0, 0xf, 0x4); // PD3/PD1/PD0=out, PD2=in

	reg32_wsmask(SPI0_BASE+SPIx_CON_SPIE, 1);

	reg32_write(ENC_BASE+ENC_KEY, 0xffff);
	reg32_write(ENC_BASE+ENC_ADR, 0);
	reg32_write(ENC_BASE+ENC_CON, 0x82);

	sflash_spi_sel(0);

	/* wake up flash */
	sflash_spi_sel(1);
	sflash_spi_send(0xab);
	sflash_spi_sel(0);

	/* reset flash */
	sflash_spi_sel(1);
	sflash_spi_send(0x66);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x99);
	sflash_spi_sel(0);

	/* clear status reg */
	sflash_spi_sel(1);
	sflash_spi_send(0x06);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x01);
	sflash_spi_send(0x00);
	sflash_spi_sel(0);
	sflash_spi_sel(1);
	sflash_spi_send(0x05);
	while (sflash_spi_recv() & 1);
	sflash_spi_sel(0);

	/* erase whole flash */
	/*sflash_spi_sel(1);
	sflash_spi_send(0x06);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x60);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x05);
	while (sflash_spi_recv() & 1);
	sflash_spi_sel(0);*/

	/* write data */
	/*sflash_spi_sel(1);
	sflash_spi_send(0x06);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x02);
	sflash_spi_send(0x00);
	sflash_spi_send(0x00);
	sflash_spi_send(0x10);
	sflash_spi_wdma("Tsukasa", 8);
	sflash_spi_sel(0);

	sflash_spi_sel(1);
	sflash_spi_send(0x05);
	while (sflash_spi_recv() & 1);
	sflash_spi_sel(0);*/

	/* read */
	sflash_spi_sel(1);
	sflash_spi_send(0x9f);
	sflash_spi_send(0x00);
	sflash_spi_send(0x00);
	sflash_spi_send(0x00);

	sflash_spi_rdma(tmp, sizeof(tmp));
	hexdump(tmp, sizeof(tmp));

	sflash_spi_sel(0);
}
