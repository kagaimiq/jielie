#include <diskio.h>
#include <wallclk.h>
#include <xprintf.h>
#include <jl_regs.h>
#include <maskrom_stuff.h>

DSTATUS s_dstatus;
WORD s_rca;
BYTE s_cardtype;
BYTE s_ocr[4], s_cid[16], s_csd[16];

int sd_send_cmd(BYTE cmd, DWORD arg, int resptype, DWORD *resp) {
	//xprintf("\e[1;44;33m======== CMD%d, %08x, R%d, %x =========\e[0m\n", cmd,arg,resptype,resp);

	/* resptype:
	 *   0 = no response
	 *   1 = R1 response: 48 bits, valid opcode, valid crc     [normal response]
	 *   2 = R2 response: 136 bits, invalid opcode, valid crc  [CID/CSD register]
	 *   3 = R3 response: 48 bits, invalid opcode, invalid crc [OCR register]
	 *   4 = R4 response: 48 bits, opcode == CMD39, valid crc  [fast I/O]
	 *   5 = R5 response: 48 bits, opcode == CMD40, valid crc  [interrupt request]
	 *   6 = R6 response: 48 bits, opcode == CMD3, valid crc   [published RCA response]
	 *   7 = R7 response: 48 bits, opcode == CMD8, valid crc   [card interface condition]
	 *
	 *  R4/R5/R6/R7 is basically the same as R1...
	 *    Mediatek's MSDC wants us to treat R5/R6/R7 as R1, but the R4 is still a special case...
	 *    JieLi's SD doesn't care because it's just too simple for that.
	 */

	BYTE cbuff[1+4+1 + 1+16] = {
		0x40 | (cmd & 0x3f),
		arg >> 24,
		arg >> 16,
		arg >> 8,
		arg >> 0,
	};

	reg32_write(SD0_base+SDx_CPTR, (DWORD)cbuff);

	reg32_wsmask(SD0_base+SDx_CON1, 6, 1, 0);
	reg32_wsmask(SD0_base+SDx_CON0, 4, 1, 0);

	reg32_wsmask(SD0_base+SDx_CON0_firecmd, (resptype == 2)? 0x6 : 0x5);

	// timeout...
	while (!reg32_rsmask(SD0_base+SDx_CON0_pnd_cmd));
	reg32_wsmask(SD0_base+SDx_CON0_cpnd_cmd, 1);

	//xprintf("con ---> %08x\n", reg32_read(SD0_base+SDx_CON0));

	reg32_wsmask(SD0_base+SDx_CON0, 4, 1, 0);

	asm volatile ("csync"); // important!

	/*xputs("\e[1;45;33m[ ");
	for (int i = 0; i < sizeof(cbuff); i++)
		xprintf("%02x ", cbuff[i]);
	xputs("]\e[0m\n");*/

	if (resp && resptype != 0) {
		if (resptype == 2) {
			// 136-bit response (last 8 bits are not received, though. -- i.e. not written into the cmd buffer!)
			resp[0] = (cbuff[ 7] << 24) | (cbuff[ 8] << 16) | (cbuff[ 9] << 8) | cbuff[10];
			resp[1] = (cbuff[11] << 24) | (cbuff[12] << 16) | (cbuff[13] << 8) | cbuff[14];
			resp[2] = (cbuff[15] << 24) | (cbuff[16] << 16) | (cbuff[17] << 8) | cbuff[18];
			resp[3] = (cbuff[19] << 24) | (cbuff[20] << 16) | (cbuff[21] << 8) | cbuff[22];
		} else {
			// 48-bit response
			resp[0] = (cbuff[ 7] << 24) | (cbuff[ 8] << 16) | (cbuff[ 9] << 8) | cbuff[10];
		}
	}

	wdt_clr();

	return 0;
}

int sd_wait_ready(int timeout) {
	DWORD resp;

	for (DWORD target = millis() + timeout; millis() < target;) {
		if (!sd_send_cmd(13, s_rca << 16, 1, &resp) && ((resp >> 10 & 0x7) == 2))
			return 0;

		wdt_clr();
	}

	return -1;
}

DSTATUS disk_initialize(BYTE drv) {
	DWORD resp[4];
	s_dstatus |= STA_NOINIT;

	/*================================================================*/
	// iocfg.. PB4=SD0_DAT0, PB6=SD0_CMD, PB7=SD0_CLK
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0ios, 'F'-'A');
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0cken, 1);
	reg32_wsmask(IOMAP_base+IOMAP_CON0_sd0dten, 1);
	// pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(4), 1); //PB4 pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(6), 1); //PB6 pullup
	reg32_wsmask(PORTB_base+PORTx_PUn(7), 0); //PB7 no pullup
	// pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(4), 0); //PB4 no pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(6), 0); //PB6 no pulldown
	reg32_wsmask(PORTB_base+PORTx_PDn(7), 1); //PB7 pulldown
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

	// hw bit enable
	reg32_wsmask(SD0_base+SDx_CON1_enable, 1);
	reg32_wsmask(SD0_base+SDx_CTU_CON_enable, 1);

	// disable encrypting
	reg32_wsmask(PERIENC_base+PERIENC_CON_en_sd0data, 0);

	/*================================================================*/

	reg32_wsmask(SD0_base+SDx_CON1_baud, (48000/400)-1); // 400 kHz clock

	//------- unknown
	sd_send_cmd(0, 0, 0, NULL); // CMD0: GO_IDLE_STATE

	//------- idle
	sd_send_cmd(8, 0x1aa, 1, resp); // CMD8: SEND_IF_COND

	for (DWORD stime = millis();;) {
		if (millis() - stime  > 500)
			goto failed;

		sd_send_cmd(55, 0, 1, resp); // CMD55: APP_CMD

		sd_send_cmd(41, 0x40ff8000, 1, resp); // CMD41: APP_SEND_OP_COND
		if (resp[0] & 0x80000000) break;
	}

	s_cardtype = CT_SDC2;

	if (resp[0] & 0x40000000)
		s_cardtype |= CT_BLOCK;

	for (int i = 0; i < 4; i++)
		s_ocr[i] = resp[0] >> (8 * (~i & 3));

	//------- ready
	sd_send_cmd(2, 0, 2, resp); // CMD2: ALL_SEND_CID

	for (int i = 0; i < 16; i++)
		s_cid[i] = resp[i >> 2] >> (8 * (~i & 3));

	//------- ident
	sd_send_cmd(3, 0, 1, resp); // CMD3: SEND_RELATIVE_ADDR
	s_rca = resp[0] >> 16;

	//------- stby
	sd_send_cmd(9, s_rca << 16, 2, resp); // CMD9: SEND_CSD

	for (int i = 0; i < 16; i++)
		s_csd[i] = resp[i >> 2] >> (8 * (~i & 3));

	sd_send_cmd(7, s_rca << 16, 1, resp); // CMD7: SELECT_CARD

	//------- tran

	reg32_wsmask(SD0_base+SDx_CON1_baud, (48000/24000)-1); // 24 MHz clock

	/*================================================================*/

	s_dstatus &= ~STA_NOINIT;
failed:
	return s_dstatus;
}

DSTATUS disk_status(BYTE drv) {
	return s_dstatus;
}

DRESULT disk_read(BYTE drv, BYTE *buff, LBA_t lba, UINT cnt) {
	DRESULT res = RES_ERROR;
	DWORD resp;

	if (s_dstatus & STA_NOINIT) return RES_NOTRDY;

	if (!(s_cardtype & CT_BLOCK)) lba *= 512;

	if (sd_wait_ready(500)) return RES_ERROR;

	//----------------------------------------------------

	reg32_wsmask(SD0_base+SDx_CON0, 12, 1, 0);

	reg32_write(SD0_base+SDx_DPTR, (DWORD)buff);
	reg32_wsmask(SD0_base+SDx_CON1, 7, 1, 0);

	reg32_wsmask(SD0_base+SDx_CTU_CON, 1, 0x3, 0x0);

	reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
	reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

	reg32_write(SD0_base+SDx_CON2, REG_MKVAL(SDx_CON2_blksize, 512-1)); //block size
	reg32_wsmask(SD0_base+SDx_CTU_CON_firedat, 0x6); // data rx
	reg32_write(SD0_base+SDx_CTU_CNT, cnt-1); // block count

	// CMD17: READ_SINGLE_BLOCK
	// CMD18: READ_MULTIPLE_BLOCKS
	if (!sd_send_cmd((cnt > 1)? 18 : 17, lba, 1, &resp) && !(resp & 0xc0580000)) {
		for (DWORD stime = millis();;) {
			if (millis() - stime >= 500)
				break; // timed out

			wdt_clr();

			if (reg32_rsmask(SD0_base+SDx_CON0_pnd_dat)) {
				res = RES_OK;
				break;
			}
		}
	}

	reg32_wsmask(SD0_base+SDx_CON0_cpnd_dat, 1);

	reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
	reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

	//----------------------------------------------------

	if (res != RES_OK || cnt > 1)
		sd_send_cmd(12, 0, 1, &resp); // CMD12: STOP_TRANSMISSION

	return res;
}

DRESULT disk_write(BYTE drv, const BYTE *buff, LBA_t lba, UINT cnt) {
	DRESULT res = RES_ERROR;
	DWORD resp;

	if (s_dstatus & STA_NOINIT) return RES_NOTRDY;
	if (s_dstatus & STA_PROTECT) return RES_WRPRT;

	if (!(s_cardtype & CT_BLOCK)) lba *= 512;

	if (sd_wait_ready(500)) return RES_ERROR;

	//----------------------------------------------------

	if (cnt > 1) {
		sd_send_cmd(55, s_rca << 16, 1, &resp); // CMD55: APP_CMD
		sd_send_cmd(23, cnt, 1, &resp); // ACMD23: APP_SET_WR_BLK_ERASE_COUNT
	}

	// CMD24: WRITE_BLOCK
	// CMD25: WRITE_MULTIPLE_BLOCKS
	if (!sd_send_cmd((cnt > 1)? 25 : 24, lba, 1, &resp) && !(resp & 0xc0580000)) {
		reg32_wsmask(SD0_base+SDx_CON0, 12, 1, 0);

		reg32_write(SD0_base+SDx_DPTR, (DWORD)buff);
		reg32_wsmask(SD0_base+SDx_CON1, 7, 1, 0);

		reg32_wsmask(SD0_base+SDx_CTU_CON, 1, 0x3, 0x0);

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);

		reg32_write(SD0_base+SDx_CON2, REG_MKVAL(SDx_CON2_blksize, 512-1)); //block size
		reg32_wsmask(SD0_base+SDx_CTU_CON, 8, 0x7, 0x5); // data tx
		reg32_write(SD0_base+SDx_CTU_CNT, cnt-1); // block count

		for (DWORD stime = millis();;) {
			if (millis() - stime >= 500)
				break; // timed out

			wdt_clr();

			if (reg32_rsmask(SD0_base+SDx_CON0_pnd_dat)) {
				res = RES_OK;
				break;
			}
		}

		reg32_wsmask(SD0_base+SDx_CON0_cpnd_dat, 1); // clr data pend

		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_done, 1);
		reg32_wsmask(SD0_base+SDx_CTU_CON_clr_err, 1);
	}

	//----------------------------------------------------

	if (res != RES_OK || cnt > 1)
		sd_send_cmd(12, 0, 1, &resp); // CMD12: STOP_TRANSMISSION

	return res;
}

DRESULT disk_ioctl(BYTE drv, BYTE op, void *ptr) {
	if (s_dstatus & STA_NOINIT) return RES_NOTRDY;

	switch (op) {
	case CTRL_SYNC:
		return RES_OK;

	case GET_SECTOR_COUNT:
		if (s_cardtype & CT_SDC2) { // SDv2+
			*(LBA_t *)ptr = ((s_csd[9] | (s_csd[8] << 8) | ((s_csd[7] & 0x3f) << 16)) + 1) << 10;
			return RES_OK;
		}
		break;

	case GET_SECTOR_SIZE:
		*(WORD *)ptr = 512; // it's always 512!
		return RES_OK;

	//case GET_BLOCK_SIZE:
	//	*(DWORD *)ptr = 1; // in sectors
	//	break;

	//case CTRL_TRIM:
	//	//((LBA_t *)ptr)[0] ---start  ((LBA_t *)ptr)[1] ---end
	//	break;

	case MMC_GET_TYPE:
		*(BYTE *)ptr = s_cardtype;
		return RES_OK;

	case MMC_GET_CSD:
		memcpy(ptr, s_csd, sizeof(s_csd));
		return RES_OK;

	case MMC_GET_CID:
		memcpy(ptr, s_cid, sizeof(s_cid));
		return RES_OK;

	case MMC_GET_OCR:
		memcpy(ptr, s_ocr, sizeof(s_ocr));
		return RES_OK;

	//case MMC_GET_SDSTAT:
	//	break;

	//case MMC_GET_EXTCSD:
	//	break;

	default:
		return RES_PARERR;
	}

	return RES_ERROR;
}
