#include <stdint.h>
#include <xprintf.h>
#include <jl_regs.h>


void uputc(int c) {
	reg32_write(UART0_BASE+UARTx_BUF, c);
	while (!reg32_rsmask(UART0_BASE+UARTx_CON0_TPND));
	reg32_wsmask(UART0_BASE+UARTx_CON0_CLRTPND, 1);
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



struct usb_msc_cbw {
	uint32_t sign;		// 0x55534243 "USBC"
	uint32_t tag;
	uint32_t xfer_len;
	uint8_t flags;
	uint8_t lun;
	uint8_t cdb_len;
	uint8_t cdb[16];
};

struct JieLi_LoaderArgs {
	int (*msd_send)(void *ptr, int len);		// send request data
	int (*msd_recv)(void *ptr, int len);		// receive request data
	int (**msd_hook)(struct usb_msc_cbw *cbw);	// SCSI request hook
	uint32_t arg;		// Argument
	uint32_t wtw_10;	// set to zero?!
};

struct JieLi_LoaderArgs *largs;





void sflash_init(void) {
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(0), 0); // PD0 out  -> SCK
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(1), 0); // PD1 out  -> MOSI
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(2), 1); // PD2 in   -> MISO
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(3), 0); // PD3 out  -> CS
	reg32_wsmask(PORTD_BASE+PORTx_DIRn(4), 0); // PD4 out  -> ?? HOLD? Power?!

	reg32_wsmask(PORTD_BASE+PORTx_OUTn(3), 1); // PD3 high
	reg32_wsmask(PORTD_BASE+PORTx_OUTn(4), 1); // PD4 high

	reg32_wsmask(IOMAP_BASE+IOMAP_CON0, 2, 1, 0); // SPI0 on PD3/PD2/PD1/PD0

	reg32_write(SPI0_BASE+SPIx_CON, 0x20);
	reg32_write(SPI0_BASE+SPIx_BAUD, 32); // some clock speed
	reg32_wsmask(SPI0_BASE+SPIx_CON_BIDIR, 1); // full duplex
	reg32_wsmask(SPI0_BASE+SPIx_CON_SPIE, 1);
}

void sflash_sel(char sel) {
	reg32_wsmask(PORTD_BASE+PORTx_OUTn(3), !sel); // CS
}

uint8_t sflash_bytexfer(uint8_t val) {
	reg32_write(SPI0_BASE+SPIx_BUF, val);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
	return reg32_read(SPI0_BASE+SPIx_BUF);
}

void sflash_dmaxfer(void *ptr, int len, int dir) {
	reg32_wsmask(SPI0_BASE+SPIx_CON_DIR, !!dir); //1=recv, 0=send
	reg32_write(SPI0_BASE+SPIx_ADR, (uint32_t)ptr);
	reg32_write(SPI0_BASE+SPIx_CNT, len);
	while (!reg32_rsmask(SPI0_BASE+SPIx_CON_PND));
	reg32_wsmask(SPI0_BASE+SPIx_CON_PCLR, 1);
}



int KonaHook(struct usb_msc_cbw *cbw) {
	xprintf(
		"\e[1;45;33m---- SCSI Request ----\e[0m\n"
		"Tag: %08x, Flags: %02x, LUN: %d\n"
		"Xfer length: %u\n"
		"CDB: [%d] { ",
		cbw->tag, cbw->flags, cbw->lun, cbw->xfer_len, cbw->cdb_len
	);

	for (int i = 0; i < cbw->cdb_len; i++)
		xprintf("%02x ", cbw->cdb[i]);

	xputs("}\n\n");

	//============================================

	uint8_t *cmd = (uint8_t *)&cbw->cdb;
	static uint8_t buffer[512];

	switch (cmd[0]) {
	case 0xa5:
		{
			int len = (cbw->xfer_len > sizeof(buffer)) ? sizeof(buffer) : cbw->xfer_len;

			sflash_sel(1);
			sflash_bytexfer(0x03);
			sflash_bytexfer(cmd[1]);
			sflash_bytexfer(cmd[2]);
			sflash_bytexfer(cmd[3]);
			//sflash_bytexfer(0x00);
			sflash_dmaxfer(buffer, len, 1);
			sflash_sel(0);

			largs->msd_send(buffer, len);
		}
		return 1;
	}

	return 0;
}

void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	#if 0 // Remember that voodoo magic! ...basically like everything else??!?! ( i mean... )
	reg32_write(UART2_BASE+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART2_BASE+UARTx_BAUD, 48000000/4/115200);
	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 14, 3, 3); // UART2 to PC4/PC5
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 10, 1, 0); // UART2 ... IO SEL -> IOMUX ?
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 11, 1, 1); // UART2 I/O enable
	reg32_wsmask(PORTC_BASE+PORTx_DIRn(4), 0); // PC4 out
	reg32_wsmask(PORTC_BASE+PORTx_DIRn(5), 1); // PC5 in
	#endif

	// init UART0 on PB5
	reg32_write(UART0_BASE+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART0_BASE+UARTx_BAUD, (48000000 / 4 / 921600) - 1);
	reg32_wsmask(IOMAP_BASE+IOMAP_CON0, 3, 3, 2); // UART0 to PB5
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 2, 1, 0); // UART0 ... IO SEL -> IOMUX ?
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 3, 1, 1); // UART0 I/O enable
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(5), 0); // PB5 out

	xdev_out(uputc);
	xputs("\n\e[1;37;41;5m==== JieLi AC6965A! "__DATE__" "__TIME__" ====\e[0m\n");
	xprintf("r0: <%08x>  r1: <%08x>  r2: <%08x>  r3: <%08x>\n", r0,r1,r2,r3);

	largs = (void *)r0;
	xprintf(">>msd_send = %08x\n", largs->msd_send);
	xprintf(">>msd_recv = %08x\n", largs->msd_recv);
	xprintf(">>msd_hook = %08x\n", largs->msd_hook);
	xprintf(">>arg      = %08x\n", largs->arg);
	xprintf(">>wtw_10   = %08x\n", largs->wtw_10);

	/*==================================================================*/

	*largs->msd_hook = KonaHook;

	sflash_init();

	sflash_sel(1);
	sflash_bytexfer(0x03);
	sflash_bytexfer(0x00);
	sflash_bytexfer(0x00);
	sflash_bytexfer(0x00);
	sflash_dmaxfer((void *)0x20000, 0x100, 1);
	sflash_sel(0);

	hexdump((void *)0x20000, 0x100);
}
