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







void sflash_init(void) {
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

	reg32_wsmask(SFC_base+SFC_CON, 0, 1, 0); // disable sfc

	reg32_write(SPI0_base+SPIx_CON, 0x20);
	reg32_write(SPI0_base+SPIx_BAUD, 1); // some clock speed
	reg32_wsmask(SPI0_base+SPIx_CON_bidir, 1); // full duplex
	reg32_wsmask(SPI0_base+SPIx_CON_spie, 1); // enable spi

	for (volatile int i = 100000; i; i--); // stutter
}

void sflash_sel(char sel) {
	reg32_wsmask(PORTD_base+PORTx_OUTn(3), !sel); // CS
}

uint8_t sflash_bytexfer(uint8_t val) {
	reg32_write(SPI0_base+SPIx_BUF, val);
	while (!reg32_rsmask(SPI0_base+SPIx_CON_pnd));
	reg32_wsmask(SPI0_base+SPIx_CON_pclr, 1);
	return reg32_read(SPI0_base+SPIx_BUF);
}

void sflash_dmaxfer(void *ptr, int len, int dir) {
	reg32_wsmask(SPI0_base+SPIx_CON_dir, !!dir); //1=recv, 0=send
	reg32_write(SPI0_base+SPIx_ADR, (uint32_t)ptr);
	reg32_write(SPI0_base+SPIx_CNT, len);
	while (!reg32_rsmask(SPI0_base+SPIx_CON_pnd));
	reg32_wsmask(SPI0_base+SPIx_CON_pclr, 1);
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

	xprintf("sys div   :%08x\n", reg32_read(CLOCK_base+CLOCK_SYS_DIV));
	xprintf("clk con0  :%08x\n", reg32_read(CLOCK_base+CLOCK_CLK_CON0));
	xprintf("clk con1  :%08x\n", reg32_read(CLOCK_base+CLOCK_CLK_CON1));
	xprintf("clk con2  :%08x\n", reg32_read(CLOCK_base+CLOCK_CLK_CON2));
	xprintf("clk con3  :%08x\n", reg32_read(CLOCK_base+CLOCK_CLK_CON3));

	//wallclk_init();
	//irq_attach(1, ExceptionHandler_entry);

	xprintf("iomap_con0 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON0));
	xprintf("iomap_con1 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON1));
	xprintf("iomap_con2 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON2));
	xprintf("iomap_con3 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON3));
	xprintf("iomap_con4 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON4));
	xprintf("iomap_con5 = %08x\n", reg32_read(IOMAP_base+IOMAP_CON5));

	xprintf("dsp_con            = %08x\n", reg32_read(DSP_base+DSP_CON));
	xprintf("dsp_ring_osc       = %08x\n", reg32_read(DSP_base+DSP_RING_OSC));
	xprintf("dsp_cpass_con      = %08x\n", reg32_read(DSP_base+DSP_CPASS_CON));
	xprintf("dsp_cpass_adrh     = %08x\n", reg32_read(DSP_base+DSP_CPASS_ADRH));
	xprintf("dsp_cpass_adrl     = %08x\n", reg32_read(DSP_base+DSP_CPASS_ADRL));
	xprintf("dsp_cpass_buf_last = %08x\n", reg32_read(DSP_base+DSP_CPASS_BUF_LAST));
	xprintf("dsp_cprefetch_adrh = %08x\n", reg32_read(DSP_base+DSP_CPREFETCH_ADRH));
	xprintf("dsp_cprefetch_adrl = %08x\n", reg32_read(DSP_base+DSP_CPREFETCH_ADRL));
	xprintf("dsp_cache_msg_ch   = %08x\n", reg32_read(DSP_base+DSP_CACHE_MSG_CH));
	xprintf("dsp_mem_con        = %08x\n", reg32_read(DSP_base+DSP_MEM_CON));

	sflash_init();

	#if 0
	xprintf("sfc_con      = %08x\n", reg32_read(SFC_base+SFC_CON));
	xprintf("sfc_baud     = %08x\n", reg32_read(SFC_base+SFC_BAUD));
	xprintf("sfc_code     = %08x\n", reg32_read(SFC_base+SFC_CODE));
	xprintf("sfc_base_adr = %08x\n", reg32_read(SFC_base+SFC_BASE_ADR));
	xprintf("sfc_qucnt    = %08x\n", reg32_read(SFC_base+SFC_QUCNT));

	/*
		sfc_con      = 01580034
		sfc_baud     = 00000001
		sfc_code     = 00006f9f
		sfc_base_adr = 00201000
		sfc_qucnt    = 0000001f
	*/

	reg32_write(SFC_base+SFC_CON,      0);
	reg32_write(SFC_base+SFC_CODE,     0);
	reg32_write(SFC_base+SFC_BASE_ADR, 0);
	reg32_write(SFC_base+SFC_BAUD,     0xff);

	reg32_write(SFCENC_base+SFCENC_CON, 2); //b0 = enable?, b1=?
	reg32_write(SFCENC_base+SFCENC_KEY, 0x077A);
	reg32_write(SFCENC_base+SFCENC_UNENC_ADRH, 0x020);
	reg32_write(SFCENC_base+SFCENC_UNENC_ADRL, 0x060);
	reg32_write(SFCENC_base+SFCENC_LENC_ADRH,  0x080);
	reg32_write(SFCENC_base+SFCENC_LENC_ADRL,  0x0e0);
	//reg32_write(SFCENC_base+SFCENC_CON, 0);

	reg32_wsmask(SPI0_base+SPIx_CON_spie, 0); // disable
	reg32_wsmask(SFC_base+SFC_CON, 0, 1, 1); // enable

	hexdump((void *)0x1e00000, 0x100);
	#endif

	#if 0
	reg32_write(PERIENC_base+PERIENC_CON, 0x80|1); //b0= enable, b1=?, b2=?, b7=reset key
	reg32_write(PERIENC_base+PERIENC_KEY, 0x077A);

	sflash_sel(1);
	sflash_bytexfer(0x03);
	sflash_bytexfer(0x00);
	sflash_bytexfer(0x10);
	sflash_bytexfer(0x00);
	sflash_dmaxfer((void *)0x20000, 0x20, 1);
	hexdump((void *)0x20000, 0x20);
	sflash_sel(0);
	#endif

	#if 0
	static uint8_t buff[0x1000];

	for (int boff = 0; boff < sizeof(buff); boff += 0x20) {
		int off = boff + 0x120 + 0x6a5a4 + 0x394 - 0x20;

		off = (off + 0) & ~0x1f;

		uint32_t addr = 0x1000 + off;

		reg32_write(PERIENC_base+PERIENC_CON, 0x80|1);
		reg32_write(PERIENC_base+PERIENC_KEY, 0x077A ^ (off >> 2));

		sflash_sel(1);
		sflash_bytexfer(0x03);
		sflash_bytexfer(addr>>16);
		sflash_bytexfer(addr>>8);
		sflash_bytexfer(addr>>0);
		sflash_dmaxfer(&buff[boff], 0x20, 1);
		sflash_sel(0);
	}

	hexdump(buff, sizeof buff);

	#if 0
	for (int off = 0; off < sizeof(buff); off += 0x20) {
		uint32_t addr = 0x0000 + off;

		reg32_write(PERIENC_base+PERIENC_CON, 0x80|1);
		reg32_write(PERIENC_base+PERIENC_KEY, 0xffff);

		sflash_sel(1);
		sflash_bytexfer(0x03);
		sflash_bytexfer(addr>>16);
		sflash_bytexfer(addr>>8);
		sflash_bytexfer(addr>>0);
		sflash_dmaxfer(&buff[off], 0x20, 1);
		sflash_sel(0);
	}

	hexdump(buff, sizeof buff);
	#endif
	#endif

	//-----------------------------

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
