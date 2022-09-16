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




int sd_send_cmd(uint8_t cmd, uint32_t addr, int rtype, uint32_t *resp) {
	uint8_t cbuff[32] = {
		0x40 | (cmd & 0x3f),
		addr >> 24,
		addr >> 16,
		addr >> 8,
		addr >> 0,
	};

	reg32_write(SD0_base+SDx_CPTR, (uint32_t)cbuff);

	reg32_wsmask(SD0_base+SDx_CON1, 6, 1, 0);
	reg32_wsmask(SD0_base+SDx_CON0, 4, 1, 1);

	reg32_wsmask(SD0_base+SDx_CON0_firecmd, rtype == 2 ? 0x6 : 0x5);

	// timeout...
	while (!reg32_rsmask(SD0_base+SDx_CON0_pnd_cmd));
	reg32_wsmask(SD0_base+SDx_CON0_cpnd_cmd, 1);

	reg32_wsmask(SD0_base+SDx_CON0, 4, 1, 0);

	asm volatile ("csync");

	if (rtype == 1) {
		resp[0] = (cbuff[ 7] << 24) | (cbuff[ 8] << 16) | (cbuff[ 9] << 8) | cbuff[10];
		xprintf("RESP->%08x\n", resp[0]);
	} else if (rtype == 2) {
		resp[0] = (cbuff[ 6] << 24) | (cbuff[ 7] << 16) | (cbuff[ 8] << 8) | cbuff[ 9];
		resp[1] = (cbuff[12] << 24) | (cbuff[13] << 16) | (cbuff[14] << 8) | cbuff[15];
		resp[2] = (cbuff[16] << 24) | (cbuff[17] << 16) | (cbuff[18] << 8) | cbuff[19];
		resp[3] = (cbuff[20] << 24) | (cbuff[21] << 16) | (cbuff[22] << 8) | cbuff[23];
		xprintf("RESP->%08x %08x %08x %08x\n", resp[0],resp[1],resp[2],resp[3]);
	}

	return 0;
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

	//wallclk_init();
	//irq_attach(1, ExceptionHandler_entry);

	// iocfg
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0ios, 'f'-'a');
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0cken, 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0dten, 1);
	// pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(4), 1); //PB4 pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(6), 1); //PB6 pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(7), 1); //PB7 pullup
	// pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(4), 0); //PB4 no pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(6), 0); //PB6 no pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(7), 0); //PB7 no pulldown
	// output
	reg32_wsmask(PORTB_base+PORTx_DIRn(4), 0); // PB4 output
	reg32_wsmask(PORTB_base+PORTx_DIRn(6), 0); // PB6 output
	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 0); // PB7 output
	// digital in
	reg32_wsmask(PORTB_base+PORTx_DIEn(4), 1); // PB4 digital in
	reg32_wsmask(PORTB_base+PORTx_DIEn(6), 1); // PB6 digital in
	reg32_wsmask(PORTB_base+PORTx_DIEn(7), 1); // PB7 digital in

	// hw CLOSE
	reg32_write(SD0_base+SDx_CON0, REG_SMASK(SDx_CON0_cpnd_cmd)|REG_SMASK(SDx_CON0_cpnd_dat));
	reg32_write(SD0_base+SDx_CON1, 0);
	reg32_write(SD0_base+SDx_CON2, REG_MKVAL(SDx_CON2_blksize, 512-1));
	reg32_write(SD0_base+SDx_CTU_CON, REG_SMASK(SDx_CTU_CON_done)); //waa
	reg32_write(SD0_base+SDx_CTU_CNT, 0);

	// set BUAD
	reg32_wsmask(SD0_base+SDx_CON1_baud, (48000 / 400) - 1);

	// hw bit enable
	reg32_wsmask(SD0_base+SDx_CON1_enable, 1);
	reg32_wsmask(SD0_base+SDx_CTU_CON_enable, 1);

	// idle clock enable
	reg32_wsmask(SD0_base+SDx_CON1_idleclken, 1);

	// wait for some time (at least 74 clock ticks should be sent to the card)
	for (volatile int i = 1000; i; i--) {};

	//-------------------------------------------------------//

	uint32_t resp[4];
	uint16_t rca;

	sd_send_cmd(0, 0, 0, NULL);		// CMD0 (GO_IDLE_STATE)

	//----------------------idle state-----------------------//

	sd_send_cmd(8, 0x1aa, 1, resp);		// CMD8 (SEND_IF_COND)

	for (int i = 0; i < 100; i++) {
		sd_send_cmd(55, 0, 1, resp);		// CMD55 (APP_CMD)

		sd_send_cmd(41, 0x40ff8000, 1, resp);	// ACMD41 (APP_SEND_OP_COND)

		if (resp[0] & 0x80000000) break;
	}

	//---------------------ready state-----------------------//

	sd_send_cmd(2, 0, 2, resp);		// CMD2 (APP_SEND_CID)
	xprintf("CID => %08x %08x %08x %08x\n", resp[0],resp[1],resp[2],resp[3]);

	//---------------------ident state-----------------------//

	sd_send_cmd(3, 0, 1, resp);		// CMD3 (SEND_RELATIVE_ADDR)
	rca = resp[0] >> 16;
	xprintf("Card address => %04x\n", rca);

	//----------------------stby state-----------------------//

	sd_send_cmd(9, rca << 16, 2, resp);	// CMD9 (SEND_CSD)
	xprintf("CSD => %08x %08x %08x %08x\n", resp[0],resp[1],resp[2],resp[3]);

	xprintf("...%u\n", (((resp[1] & 0xff) << 16) | (resp[2] >> 16)) << 10);

	sd_send_cmd(7, rca << 16, 1, resp);	// CMD7 (SELECT_CARD)

	//----------------------tran state-----------------------//

	reg32_wsmask(SD0_base+SDx_CON1_baud, (48000 / 12000) - 1);

	static uint8_t databuff[512];

	/* send CMD24 (WRITE_BLOCK) */ {
		for (int i = 0; i < sizeof databuff; i++)
			databuff[i] = reg32_read(RAND_base+RAND_R64L);

		sd_send_cmd(24, 2, 1, resp);

		reg32_wsmask(SD0_base+SDx_CON0, 12, 1, 0);

		reg32_write(SD0_base+SDx_DPTR, (uint32_t)databuff);
		reg32_wsmask(SD0_base+SDx_CON1, 7, 1, 0);

		reg32_wsmask(SD0_base+SDx_CTU_CON, 1, 0x3, 0x0);

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

		reg32_write(SD0_base+SDx_CON2, REG_MKVAL(SDx_CON2_blksize, 512-1)); //block size
		reg32_wsmask(SD0_base+SDx_CTU_CON, 8, 0x7, 0x5); // data tx
		reg32_write(SD0_base+SDx_CTU_CNT, 0); // block count

		while (!reg32_rsmask(SD0_base+SDx_CON0_pnd_dat));
		reg32_wsmask(SD0_base+SDx_CON0_cpnd_dat, 1); // clr data pend

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);
	}

	memset(databuff, 'k', sizeof(databuff));

	/* send CMD17 (READ_SINGLE_BLOCK) */ {
		reg32_wsmask(SD0_base+SDx_CON0, 12, 1, 0);

		reg32_write(SD0_base+SDx_DPTR, (uint32_t)databuff);
		reg32_wsmask(SD0_base+SDx_CON1, 7, 1, 0);

		reg32_wsmask(SD0_base+SDx_CTU_CON, 1, 0x3, 0x0);

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

		reg32_write(SD0_base+SDx_CON2, REG_MKVAL(SDx_CON2_blksize, 512-1)); //block size
		reg32_wsmask(SD0_base+SDx_CTU_CON_firedat, 0x6); // data rx
		reg32_write(SD0_base+SDx_CTU_CNT, 1-1); // block count

		sd_send_cmd(17, 2, 1, resp);

		while (!reg32_rsmask(SD0_base+SDx_CON0_pnd_dat));
		reg32_wsmask(SD0_base+SDx_CON0_cpnd_dat, 1); // clr data pend

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

		hexdump(databuff, sizeof databuff);
	}
}
