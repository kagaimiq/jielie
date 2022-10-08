#include <stdint.h>
#include <jl_regs.h>
#include <xprintf.h>

void uputc(int c) {
	reg32_write(UART0_base+UARTx_BUF, c);
	while (!reg32_rsmask(UART0_base+UARTx_CON0_tpnd));
	reg32_wsmask(UART0_base+UARTx_CON0_clrtpnd, 1);
}

void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	xdev_out(uputc);
	xputs("!!!!! hhi Jieli at the SFC !!!!!\n");
	xprintf("r0:<%08x> r1:<%08x> r2:<%08x> r3:<%08x>\n", r0,r1,r2,r3);
}
