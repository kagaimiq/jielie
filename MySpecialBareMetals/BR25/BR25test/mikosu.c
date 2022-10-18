#include <stdint.h>
#include <xprintf.h>
#include <jl_regs.h>
#include <jl_irq.h>
#include <wallclk.h>
#include <maskrom_stuff.h>

void uputc(int c) {
	reg32_write(UART0_base+UARTx_BUF, c);
	while (!reg32_rsmask(UART0_base+UARTx_CON0_tpnd));
	reg32_wsmask(UART0_base+UARTx_CON0_clrtpnd, 1);
}


/*
 * http://martin.hinner.info/vga/pal.html
 *
 * noninterlaced:
 *  6-5-5 304 == 8 + 304 = 312!
 *
 * sync:
 *            XXXXXXXXXXXXXXXXXXX
 *            XXXXXXXXXXXXXXXXXXX
 * _     _____XXXXXXXXXXXXXXXXXXX___
 *  \___/     |                 |  |
 *  |<->|<--->|<--------------->|<>|
 *  |4.7  5.8 |       52        1.5|
 *  |<------->|                    |
 *  |   12                         |
 *  |<---------------------------->|
 *                  64
 *
 * vsync:
 *
 * |      short      |     long      |
 * _    _____________             ____
 * |\__/             \___________/   |
 * |<->|<----------->|<--------->|<->|
 * |2.3      29.7    |    27.1   |4.9|
 * |<--------------->|<------------->|
 *          32              32
 */


volatile int currline = 0, displine = 0;
//uint8_t framebuffer[288][312/8];

#include "XXX/pic.h"

void IRQ_HANDLER Timer5_IRQHandler(void) {
	reg32_wsmask(TIMER5_base+TIMERx_CON_pclr, 1); // clr pending

	if ((currline >= 16) && (currline < 304)) {
		// prepare to send the line
		reg32_wsmask(TIMER4_base+TIMERx_CON_mode, 0x1);
		reg32_write(SPI1_base+SPIx_ADR, (uint32_t)&framebuffer[displine]);

		displine++;
	}

	currline++;

	if ((currline == 304) || (currline == 304+6+5)) {
		reg32_write(TIMER5_base+TIMERx_PRD, 1535); // 32us period
		reg32_write(TIMER5_base+TIMERx_PWM, 110);  // 2.3us sync pulse
	} else if (currline == 304+6) {
		reg32_write(TIMER5_base+TIMERx_PRD, 1535); // 32us period
		reg32_write(TIMER5_base+TIMERx_PWM, 1300); // 27.1us sync pulse
	} else if (currline >= 304+6+5+5) {
		reg32_write(TIMER5_base+TIMERx_PRD, 3071); // 64us period
		reg32_write(TIMER5_base+TIMERx_PWM, 225);  // 4.7us sync pulse

		currline = 0;
		displine = 0;
	}
}

void IRQ_HANDLER Timer4_IRQHandler(void) {
	reg32_wsmask(SPI1_base+SPIx_CON_spie, 1); // enable
	reg32_write(SPI1_base+SPIx_CNT, 312/8);

	reg32_wsmask(TIMER4_base+TIMERx_CON_pclr, 1); // clr pending
	reg32_wsmask(TIMER4_base+TIMERx_CON_mode, 0x0); // stop!
}

void IRQ_HANDLER SPI1_IRQHandler(void) {
	reg32_wsmask(SPI1_base+SPIx_CON_pclr, 1); // clear pending int
	reg32_wsmask(SPI1_base+SPIx_CON_spie, 0); // disable
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

	//----------- sync generation timer -----------//
	reg32_write(TIMER5_base+TIMERx_CON, 0);
	reg32_write(TIMER5_base+TIMERx_PRD, 3071); // 64us period
	reg32_write(TIMER5_base+TIMERx_CNT, 3071); // overflow right now
	reg32_write(TIMER5_base+TIMERx_PWM, 225); // 4.7us sync pulse
	reg32_wsmask(TIMER5_base+TIMERx_CON_pwmen, 1);
	reg32_wsmask(TIMER5_base+TIMERx_CON_pwminv, 1);
	reg32_wsmask(TIMER5_base+TIMERx_CON_pclr, 1); // clear pending int

	irq_attach(55, Timer5_IRQHandler);

	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 0); // PB7 out -> PWM5

	//---------- horizontal delay timer ----------//
	reg32_write(TIMER4_base+TIMERx_CON, 0);
	reg32_write(TIMER4_base+TIMERx_PRD, 575); // 12us delay
	reg32_write(TIMER4_base+TIMERx_CNT, 0);
	reg32_wsmask(TIMER4_base+TIMERx_CON_pclr, 1); // clear pending int

	irq_attach(54, Timer4_IRQHandler);

	//----------- video data generator -----------//
	reg32_write(SPI1_base+SPIx_CON, 0);
	reg32_write(SPI1_base+SPIx_ADR, 0x12000);
	reg32_write(SPI1_base+SPIx_BAUD, 7-1); // ... 312 pixels per line
	reg32_wsmask(SPI1_base+SPIx_CON_pclr, 1); // clear pending int
	reg32_wsmask(SPI1_base+SPIx_CON_ie, 1); // enable ints

	irq_attach(15, SPI1_IRQHandler);

	reg32_wsmask(PORTC_base+PORTx_DIRn(5), 0); // PC5 out -> SPI1_DO
	reg32_wsmask(IOMAP_base+IOMAP_CON1_spi1ios, 0x1); // SPI1 = di/clk/do -> PC3/PC4/PC5

	//------------------ START! ------------------//
	reg32_wsmask(TIMER5_base+TIMERx_CON_mode, 0x1); // start
}
