#include <stdint.h>
#include <string.h>
#include <jl_regs.h>
#include <maskrom_stuff.h>

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
	reg32_wsmask(PORTD_base+PORTx_DIRn(0), 0); // PD0 out  -> SCK
	reg32_wsmask(PORTD_base+PORTx_DIRn(1), 0); // PD1 out  -> MOSI
	reg32_wsmask(PORTD_base+PORTx_DIRn(2), 1); // PD2 in   -> MISO
	reg32_wsmask(PORTD_base+PORTx_DIRn(3), 0); // PD3 out  -> CS
	reg32_wsmask(PORTD_base+PORTx_DIRn(4), 0); // PD4 out  -> ?? HOLD? Power?!

	reg32_wsmask(PORTD_base+PORTx_OUTn(3), 1); // PD3 high
	reg32_wsmask(PORTD_base+PORTx_OUTn(4), 1); // PD4 high

	reg32_wsmask(IOMAP_base+IOMAP_CON0_spi0ios, 0x0); // SPI0 on PD3/PD2/PD1/PD0

	reg32_write(SPI0_base+SPIx_CON, 0x20);
	reg32_write(SPI0_base+SPIx_BAUD, 32); // some clock speed
	reg32_wsmask(SPI0_base+SPIx_CON_bidir, 1); // full duplex
	reg32_wsmask(SPI0_base+SPIx_CON_spie, 1);

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


void sflash_wait_busy(void) {
	sflash_sel(1);
	sflash_bytexfer(0x05);
	while (sflash_bytexfer(0) & 0x01); // TODO timeout?
	sflash_sel(0);
}


int KonaHook(struct usb_msc_cbw *cbw) {
	uint8_t *cmd = (uint8_t *)&cbw->cdb;
	static uint8_t buffer[16384];

	int len = cbw->xfer_len;
	if (len > sizeof(buffer)) len = sizeof(buffer);

	// blink a led
	static char thing;
	reg32_wsmask(PORTB_base+PORTx_OUTn(5), !thing);
	thing = !thing;

	// process
	switch (cmd[0]) {
	case 0xE1 ... 0xEF: // raw spi transfer (Custom command!)
		sflash_sel(1);

		for (int i = 1; i <= (cmd[0] & 0xf); i++)
			sflash_bytexfer(cmd[i]);

		if (len > 0) {
			if (cbw->flags & 0x80) {
				sflash_dmaxfer(buffer, len, 1);
				largs->msd_send(buffer, len);
			} else {
				largs->msd_recv(buffer, len);
				sflash_dmaxfer(buffer, len, 0);
			}
		}

		sflash_sel(0);
		return 1;

	case 0xF5: // dunno (BR25 isd tool calls this...)
		memset(buffer, 0x55, len);
		largs->msd_send(buffer, len);
		return 1;

	case 0xFB: // "Flash write"
		switch (cmd[1]) {
		case 0x00: // Erase flash block
		case 0x01: // Erase flash sector
		case 0x02: // Erase flash chip
			if (len < 16) break;

			// enable write
			sflash_sel(1);
			sflash_bytexfer(0x06);
			sflash_sel(0);

			// erase
			sflash_sel(1);
			if (cmd[1] == 0x00 || cmd[1] == 0x01) {
				// ersae block or sector
				sflash_bytexfer((cmd[1] == 0x00) ? 0xD8 : 0x20);
				// address
				sflash_bytexfer(cmd[3]);
				sflash_bytexfer(cmd[4]);
				sflash_bytexfer(cmd[5]);
			} else {
				// erase whole chip
				sflash_bytexfer(0x60);
			}
			sflash_sel(0);

			sflash_wait_busy();

			// response
			memset(buffer, 0, sizeof(buffer));
			buffer[0] = cmd[0];
			buffer[1] = cmd[1];
			largs->msd_send(buffer, 16);
			return 1;

		case 0x04: // Program flash
			{
				uint32_t addr = (cmd[2] << 24) | (cmd[3] << 16) | (cmd[4] << 8) | cmd[5];
				int qlen = (cmd[6] << 8) | cmd[7];
				uint8_t *buff = buffer;

				if (qlen > len) qlen = len;
				qlen = largs->msd_recv(buffer, qlen);

				while (qlen > 0) {
					int plen = 0x100 - (addr & 0xff); // page boundary
					if (plen > qlen) plen = qlen;

					// enable write
					sflash_sel(1);
					sflash_bytexfer(0x06);
					sflash_sel(0);

					// program
					sflash_sel(1);
					sflash_bytexfer(0x02);
					sflash_bytexfer(addr >> 16);
					sflash_bytexfer(addr >> 8);
					sflash_bytexfer(addr >> 0);
					sflash_dmaxfer(buff, plen, 0);
					sflash_sel(0);

					sflash_wait_busy();

					qlen -= plen;
					addr += plen;
					buff += plen;
				}
			}
			return 1;
		}
		break;

	case 0xFC: // "Other"
		switch (cmd[1]) {
		case 0x09: // Get chip key
			if (len < 16) break;

			memset(buffer, 0, sizeof(buffer));
			buffer[0] = cmd[0];
			buffer[1] = cmd[1];

			// chip key
			{
				uint16_t chipkey;

				// read efuse : bank1, byte0 & byte1
				p33_tx_1byte(0xb0, (1<<6));
				p33_tx_1byte(0xb1, (0<<2) | (1<<7)|(1<<1)); chipkey |= p33_rx_1byte(0xb2) << 0;
				p33_tx_1byte(0xb1, (1<<2) | (1<<7)|(1<<1)); chipkey |= p33_rx_1byte(0xb2) << 8;
				p33_tx_1byte(0xb1, 0);

				CrcDecode(&chipkey, 2);

				buffer[6] = chipkey >> 8;
				buffer[7] = chipkey >> 0;
			}

			largs->msd_send(buffer, 16);
			return 1;

		case 0x0A: // Get online device
			if (len < 16) break;

			memset(buffer, 0, sizeof(buffer));
			buffer[0] = cmd[0];
			buffer[1] = cmd[1];

			// device type
			buffer[2] = 3; // SPI0 NOR flash

			// device id
			sflash_sel(1);
			sflash_bytexfer(0x9F); // get JEDEC id
			buffer[6] = sflash_bytexfer(0);
			buffer[5] = sflash_bytexfer(0);
			buffer[4] = sflash_bytexfer(0);
			sflash_sel(0);

			largs->msd_send(buffer, 16);
			return 1;

		case 0x13: // Flash CRC16
			if (len < 16) break;

			memset(buffer, 0, sizeof(buffer));
			buffer[0] = cmd[0];
			buffer[1] = cmd[1];

			{
				uint32_t addr = (cmd[2] << 24) | (cmd[3] << 16) | (cmd[4] << 8) | cmd[5];
				int qlen = (cmd[6] << 8) | cmd[7];

				// TODO!!!
			}

			largs->msd_send(buffer, 16);
			return 1;

		case 0x14: // Flash max page size
			if (len < 16) break;

			memset(buffer, 0, sizeof(buffer));
			buffer[0] = cmd[0];
			buffer[1] = cmd[1];

			{
				uint32_t tmp = sizeof(buffer);
				buffer[2] = tmp >> 24;
				buffer[3] = tmp >> 16;
				buffer[4] = tmp >> 8;
				buffer[5] = tmp >> 0;
			}

			largs->msd_send(buffer, 16);
			return 1;
		}
		break;

	case 0xFD: // "Flash read"
		switch (cmd[1]) {
		case 0x05: // Read flash
			{
				uint32_t addr = (cmd[2] << 24) | (cmd[3] << 16) | (cmd[4] << 8) | cmd[5];
				int qlen = (cmd[6] << 8) | cmd[7];

				if (qlen > len) qlen = len;

				sflash_sel(1);
				sflash_bytexfer(0x0B);
				sflash_bytexfer(addr >> 16);
				sflash_bytexfer(addr >> 8);
				sflash_bytexfer(addr >> 0);
				sflash_bytexfer(0);
				sflash_dmaxfer(buffer, qlen, 1);
				sflash_sel(0);

				largs->msd_send(buffer, qlen);
			}
			return 1;
		}
		break;
	}

	return 0;
}



void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	largs = (void *)r0;

	*largs->msd_hook = KonaHook;

	sflash_init();

	// power on
	sflash_sel(1);
	sflash_bytexfer(0xab);
	sflash_sel(1);

	// reset
	sflash_sel(1);
	sflash_bytexfer(0x66);
	sflash_sel(1);

	sflash_sel(1);
	sflash_bytexfer(0x99);
	sflash_sel(1);

	sflash_wait_busy();

	// disable protection
	sflash_sel(1);
	sflash_bytexfer(0x06);
	sflash_sel(0);

	sflash_sel(1);
	sflash_bytexfer(0x01);
	sflash_bytexfer(0x00);
	sflash_sel(0);

	sflash_wait_busy();

	reg32_wsmask(IOMAP_base+IOMAP_CON3_ut0ioen, 0); // disable UART0
	reg32_wsmask(PORTB_base+PORTx_DIRn(5), 0);
}
