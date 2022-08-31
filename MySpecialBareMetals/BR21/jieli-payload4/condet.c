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

static int JL_audio_dac_trim(int sw, int ch) {
	/* config trim */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_TRIMSEL, ch);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_TRIMSW, sw);

	/* set some trim */
	reg32_write(AUDIO_BASE + (ch?AUDIO_DAC_TRMR:AUDIO_DAC_TRML), 0x7F);

	

	return 50;
}

static void JL_audio_dac_init(void) {
	/**** From [audio_drv.a] -> [dac_drv.o] ****/

	/*======= dac_analog_init =======*/
	/* Clock config ---> Maybe not now */

	/* Mute DAC */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_MUTE, 1);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON1_VCMRSEL, 0);  // config...

	// delay(100);
	for (volatile int i = 1000; i; i--);

	reg32_wsmask(AUDIO_BASE+AUDIO_ADA_CON0, 22, 1, 0); // config...

	reg32_wsmask(AUDIO_BASE+AUDIO_ADA_CON0, 0, 1, 0); // config...
	reg32_wsmask(AUDIO_BASE+AUDIO_ADA_CON0, 23, 7, 0); // config...
	reg32_wsmask(AUDIO_BASE+AUDIO_ADA_CON0, 31, 1, 0); // config...

	/* LDO enables */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LDO1EN, 1); // config...
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LDO2EN, 0); // config...

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON2_DACDTSEL, 0);

	/* en DAC channels */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_HPLEN, 1); // config...
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_HPREN, 1); // config...

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LPFISEL, 0); // config...

	/* enable VCMO */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON1_VCMOUTEN, 0); // config...

	/* en dac analog part */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_DACEN, 1);

	/* en vcm */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_VCMEN, 1);

	/*==== dac_drv_on ->Continue ====*/
	/* reset trim */
	reg32_write(AUDIO_BASE+AUDIO_DAC_TRML, 0);
	reg32_write(AUDIO_BASE+AUDIO_DAC_TRMR, 0);

	/* DMA Addr/Len setting --> Not related */
	/* Int disable --> Not related */

	/* Disable audio mux */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON1_AMUXEN, 0);

	/* DAC enable --> Probably not related but we'll see */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACEN, 1);

	/* en dac analog part */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_DACEN, 1);

	/* DAC smaple rate --> Not related */

	/* Trim enable */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_TRIMEN, 1);

	/* --- trim woowoo */

	int trim_l  = JL_audio_dac_trim(0, 0);
	    trim_l += JL_audio_dac_trim(1, 0);

	int trim_r  = JL_audio_dac_trim(0, 1);
	    trim_r += JL_audio_dac_trim(1, 1);

	xprintf("TROM_L=%d, TROM_R=%d\n", trim_l,trim_r);

	/* Trim disable */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_TRIMEN, 0);

	/* set trim */
	reg32_write(AUDIO_BASE+AUDIO_DAC_TRML, trim_l / 2);
	reg32_write(AUDIO_BASE+AUDIO_DAC_TRMR, trim_r / 2);

	/*======= dac_digital_init =======*/
	/* DMA Addr/Len setting --> Not now! */

	/* DSM config ... strangely it's set bit by bit! */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON1_DSMC, 5); 

	/* PDM disable */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON1_PDMOE, 0);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON1_PDMRV, 0);

	/* DCCS setting */
	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_DCCS, 14);

	/* clear pending int ==> Not now? */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_CPND, 1);

	/* DAC enable --> Not now */
	/* Int enable --> Not now */

	// delay(100);
	for (volatile int i = 1000; i; i--);
}

static void JL_audio_init(void) {
	JL_audio_dac_init();

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_MUTE, 0);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LGSEL, 0x18);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_RGSEL, 0x18);
}



#include <ff.h>
#include <diskio.h>

#define MINIMP3_IMPLEMENTATION
//#include "minimp3.h"


/* ================ bit-banged mmc interface ================ */
enum {
	SDMMC_LINE_CLK,
	SDMMC_LINE_CMD,
	SDMMC_LINE_DAT0,
	SDMMC_LINE_DAT1,
	SDMMC_LINE_DAT2,
	SDMMC_LINE_DAT3,
};

char sdmmc_line_get(int line) {
	switch (line) {
	case SDMMC_LINE_CLK: /* PC5 */
		return reg32_rsmask(PORTC_BASE+PORTx_INn(5));
	case SDMMC_LINE_CMD: /* PC4 */
		return reg32_rsmask(PORTC_BASE+PORTx_INn(4));
	case SDMMC_LINE_DAT0: /* PC3 */
		return reg32_rsmask(PORTC_BASE+PORTx_INn(3));
	}
	
	return 0;
}

void sdmmc_line_set(int line, char lvl) {
	switch (line) {
	case SDMMC_LINE_CLK: /* PC5 */
		reg32_wsmask(PORTC_BASE+PORTx_DIRn(5), 0);
		reg32_wsmask(PORTC_BASE+PORTx_OUTn(5), !!lvl);
		break;
	case SDMMC_LINE_CMD: /* PC4 */
		if (lvl) {
			reg32_wsmask(PORTC_BASE+PORTx_DIRn(4), 1);
			reg32_wsmask(PORTC_BASE+PORTx_PUn(4), 1);
		} else {
			reg32_wsmask(PORTC_BASE+PORTx_OUTn(4), 0);
			reg32_wsmask(PORTC_BASE+PORTx_DIRn(4), 0);
		}
		break;
	case SDMMC_LINE_DAT0: /* PC3 */
		if (lvl) {
			reg32_wsmask(PORTC_BASE+PORTx_DIRn(3), 1);
			reg32_wsmask(PORTC_BASE+PORTx_PUn(3), 1);
		} else {
			reg32_wsmask(PORTC_BASE+PORTx_OUTn(3), 0);
			reg32_wsmask(PORTC_BASE+PORTx_DIRn(3), 0);
		}
		break;
	}
	
	//delay(1);

	for (volatile int i = 20; i; i--);
}

void sdmmc_send_nclocks(int cnt) {
	while (cnt-- > 0) {
		sdmmc_line_set(SDMMC_LINE_CLK, 1);
		sdmmc_line_set(SDMMC_LINE_CLK, 0);
	}
}

uint8_t sdmmc_calc_crc7(uint8_t *buff, int len) {
	uint8_t crc = 0;
	
	while (len--) {
		/* the resulting crc is shifted one bit right ! */
		for (int i = 7; i >= 0; i--)
			crc = (crc << 1) ^ (((crc >> 7) ^ (*buff >> i & 1)) ? 0x12 : 0);
		
		buff++;
	}
	
	return crc | 1;
}

uint16_t sdmmc_calc_crc16(uint8_t *buff, int len) {
	uint16_t crc = 0;
	
	while (len--) {
		crc ^= *buff++ << 8;
		
		for (int i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc >> 15) ? 0x1021 : 0);
	}
	
	return crc;
}

char sdmmc_datatyp;
uint8_t *sdmmc_databuff;
int sdmmc_blksize, sdmmc_blkcnt;

void sdmmc_data_transfer(char typ, uint8_t *buff, int blksize, int blkcnt) {
	if (!buff || !blksize || !blkcnt) typ = 0;
	
	sdmmc_datatyp = typ;
	sdmmc_databuff = buff;
	sdmmc_blksize = blksize;
	sdmmc_blkcnt = blkcnt;
}

int sdmmc_send_cmd(char cmd, uint32_t arg, uint32_t *resp, char resptyp) {
	if (!resp) resptyp = 0;
	
	uint8_t ctmp[6], rtmp[17] = {};
	uint16_t dcrc = 0;
	
	/* ===== Send CMD ===== */
	ctmp[0] = 0x40 | (cmd & 0x3f);
	ctmp[1] = arg >> 24;
	ctmp[2] = arg >> 16;
	ctmp[3] = arg >> 8;
	ctmp[4] = arg >> 0;
	ctmp[5] = sdmmc_calc_crc7(ctmp, 5);

	for (int i = 0; i < 6; i++) {
		for (int j = 7; j >= 0; j--) {
			sdmmc_line_set(SDMMC_LINE_CMD, ctmp[i] >> j & 1);
			sdmmc_line_set(SDMMC_LINE_CLK, 1);
			sdmmc_line_set(SDMMC_LINE_CLK, 0);
		}
	}
	
	/* ===== Recv RESP ===== */
	for (int ds=0,rs=0,dc=0,rc=0; resptyp || sdmmc_datatyp ; ) {
		sdmmc_line_set(SDMMC_LINE_CLK, 1);
		char vc = sdmmc_line_get(SDMMC_LINE_CMD);
		char vd = sdmmc_line_get(SDMMC_LINE_DAT0);
		sdmmc_line_set(SDMMC_LINE_CLK, 0);
		
		/* TODO: timeout! */
		
		if (!vc && !rs && resptyp) {
			/* received response! */
			rs = (resptyp == 2) ? 136 : 48;
		}
		/* we need to keep the start bit! */
		if (rs) {
			if (rc < rs) {
				/* receive the bit! */
				rtmp[rc/8] <<= 1;
				rtmp[rc/8] |= vc;
				rc++;
			} else {
				/* process! */
				
				if (resptyp != 2 && resptyp != 3) {
					/* these have valid crc7 */
					if (rtmp[5] != sdmmc_calc_crc7(rtmp, 5))
						return -2;
				}
				
				if (resptyp == 1) {
					/* these have cmd number valid (++ also checks for transmission bit) */
					if (rtmp[0] != cmd)
						return -3;
				}
				
				if (resptyp == 2) {
					/* 136-bit response */
					resp[0] = (rtmp[ 1] << 24) | (rtmp[ 2] << 16) | (rtmp[ 3] << 8) | rtmp[ 4];
					resp[1] = (rtmp[ 5] << 24) | (rtmp[ 6] << 16) | (rtmp[ 7] << 8) | rtmp[ 8];
					resp[2] = (rtmp[ 9] << 24) | (rtmp[10] << 16) | (rtmp[11] << 8) | rtmp[12];
					resp[3] = (rtmp[13] << 24) | (rtmp[14] << 16) | (rtmp[15] << 8) | rtmp[16];
				} else {
					/* 32-bit response */
					resp[0] = (rtmp[1] << 24) | (rtmp[2] << 16) | (rtmp[3] << 8) | rtmp[4];
				}
				
				resptyp = 0;
			}
		}
		
		if (!vd && !ds && sdmmc_datatyp) {
			/* received data! */
			ds = (sdmmc_blksize * 8) + 16;
			memset(sdmmc_databuff, 0, sdmmc_blksize);
		} else if (ds) {
			if (dc < ds) {
				if (dc < (ds - 16)) {
					/* data */
					sdmmc_databuff[dc/8] <<= 1;
					sdmmc_databuff[dc/8] |= vd;
				} else {
					/* crc */
					dcrc <<= 1;
					dcrc |= vd ? 0x0001 : 0;
				}
				
				dc++;
			} else {
				/* block is fully received */
				if (dcrc != sdmmc_calc_crc16(sdmmc_databuff, sdmmc_blksize))
					return -2;
				
				if (--sdmmc_blkcnt > 0) {
					/* receive next block */
					dc = ds = 0;
					sdmmc_databuff += sdmmc_blksize;
				} else {
					/* terminate */
					sdmmc_datatyp = 0;
				}
			}
		}
	}
	
	sdmmc_send_nclocks(100);
	
	return 0;
}

int sdspi_typ = 0;

DSTATUS disk_initialize(BYTE drv) {
	//reg32_wsmask(RCC_BASE+RCC_APB2ENR, 2, 1, 1); /* IOPA en */
	
	/* set lines */
	sdmmc_line_set(SDMMC_LINE_CLK, 0);
	sdmmc_line_set(SDMMC_LINE_CMD, 1);
	sdmmc_line_set(SDMMC_LINE_DAT0, 1);
	sdmmc_line_set(SDMMC_LINE_DAT1, 1);
	sdmmc_line_set(SDMMC_LINE_DAT2, 1);
	sdmmc_line_set(SDMMC_LINE_DAT3, 1);
	
	/* init clocks */
	sdmmc_send_nclocks(100);
	
	uint32_t resp[4];
	uint16_t rca = 0;
	
	/* send cmds */
	xprintf("0>%d\n", sdmmc_send_cmd(0, 0, NULL, 0)); /* CMD0 GO_IDLE_STATE */
	
	xprintf("8>%d\n", sdmmc_send_cmd(8, 0x1aa, resp, 1)); /* CMD8 SEND_IF_COND */
	xprintf("=== %08x\n", resp[0]);
	
	for (;;) {
		xprintf("55>%d\n", sdmmc_send_cmd(55, rca<<16, resp, 1)); /* CMD55 APP_CMD */
		xprintf("=== %08x\n", resp[0]);
		
		xprintf("a41>%d\n", sdmmc_send_cmd(41, 0x40ff8000, resp, 3)); /* ACMD41 APP_SEND_OP_COND */
		xprintf("=== %08x\n", resp[0]);
		
		if (resp[0] & 0x80000000) break;
	}
	
	xprintf("2>%d\n", sdmmc_send_cmd(2, 0, resp, 2)); /* CMD2 ALL_SEND_CID */
	xprintf("=== %08x %08x %08x %08x\n", resp[0],resp[1],resp[2],resp[3]);
	
	xprintf("3>%d\n", sdmmc_send_cmd(3, rca<<16, resp, 1)); /* CMD3 SEND_RELATIVE_ADDR */
	xprintf("=== %08x\n", resp[0]);
	rca = resp[0] >> 16;
	
	xprintf("9>%d\n", sdmmc_send_cmd(9, rca<<16, resp, 2)); /* CMD9 SEND_CSD */
	xprintf("=== %08x %08x %08x %08x\n", resp[0],resp[1],resp[2],resp[3]);
	
	xprintf("7>%d\n", sdmmc_send_cmd(7, rca<<16, resp, 1)); /* CMD7 SELECT_CARD */
	xprintf("=== %08x\n", resp[0]);
	
	int typ = 3;
	
	xputs("sd card init comes to the end\n");
	xprintf("card type :%d\n", typ);
	
	sdspi_typ = typ;
	return sdspi_typ == 0 ? STA_NOINIT : 0;
}

DSTATUS disk_status(BYTE drv) {
	return sdspi_typ == 0 ? STA_NOINIT : 0;
}

DRESULT disk_read(BYTE drv, BYTE *buff, LBA_t lba, UINT cnt) {
	if (!buff || !cnt) return RES_PARERR;
	if (disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
	if (!(sdspi_typ & 4)) lba *= 512;
	
	char cmd = (cnt > 1) ? 18 : 17;
	uint32_t resp;
	
	sdmmc_data_transfer(1, buff, 512, cnt);
	
	if (!sdmmc_send_cmd(cmd, lba, &resp, 1) && !(resp & 0xc0580000))
		cnt = 0;
	
	sdmmc_data_transfer(0, NULL, 0, 0);
	if (cnt || cmd == 18)
		sdmmc_send_cmd(12, 0, &resp, 1);
	
	return cnt == 0 ? RES_OK : RES_ERROR;
}


uint32_t get_keys(void) {
	uint32_t keys = 0;

	/* Get key 0 */
	reg32_wsmask(PORTA_BASE+PORTx_PUn(4), 0);
	reg32_wsmask(PORTA_BASE+PORTx_PDn(4), 1);
	for (volatile int i = 100; i; i--);
	if (reg32_rsmask(PORTA_BASE+PORTx_INn(4))) keys |= (1<<0);

	/* Get key 1 */
	reg32_wsmask(PORTA_BASE+PORTx_PDn(4), 0);
	reg32_wsmask(PORTA_BASE+PORTx_PUn(4), 1);
	for (volatile int i = 100; i; i--);
	if (!reg32_rsmask(PORTA_BASE+PORTx_INn(4))) keys |= (1<<1);

	/* Get key 2 */
	if (!irtc_rsmask(0x1, 1, 1)) keys |= (1<<2);

	/* Get key 3 */
	reg32_wsmask(PORTB_BASE+PORTx_PDn(5), 0);
	reg32_wsmask(PORTB_BASE+PORTx_PUn(5), 1);
	for (volatile int i = 100; i; i--);
	if (!reg32_rsmask(PORTB_BASE+PORTx_INn(5))) keys |= (1<<3);

	/* Get key 4 */
	reg32_wsmask(PORTB_BASE+PORTx_PUn(4), 0);
	reg32_wsmask(PORTB_BASE+PORTx_PDn(4), 1);
	for (volatile int i = 100; i; i--);
	if (reg32_rsmask(PORTB_BASE+PORTx_INn(4))) keys |= (1<<4);

	/* Get key 5 */
	reg32_wsmask(PORTB_BASE+PORTx_PDn(4), 0);
	reg32_wsmask(PORTB_BASE+PORTx_PUn(4), 1);
	for (volatile int i = 100; i; i--);
	if (!reg32_rsmask(PORTB_BASE+PORTx_INn(4))) keys |= (1<<5);

	return keys;
}



void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	/* disable WDT */
	//reg32_write(CRC_BASE+CRC_REG, 0x6EA5); // CRC_REG = 0x6EA5 to unlock WDT reg
	//reg32_write(SYSCFG_BASE+SYSCFG_WDTCON, 0x00);   // disable WDT altogether
	//reg32_write(CRC_BASE+CRC_REG, 0x0000); // lock WDT reg back

	JL_clk_config();
	JL_uart_init();
	irtc_init();

	// disconnect usb
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPPU, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMPU, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPPD, 1);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMPD, 0);

	/* gpio */
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(0), 0); //PB0: out

	reg32_wsmask(PORTA_BASE+PORTx_DIRn(4), 1); // PA4=input
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(4), 1); // PB4=input
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(5), 1); // PB5=input

	reg32_wsmask(PORTA_BASE+PORTx_DIEn(4), 1); // PA4=digital in en
	reg32_wsmask(PORTB_BASE+PORTx_DIEn(4), 1); // PB4=digital in en
	reg32_wsmask(PORTB_BASE+PORTx_DIEn(5), 1); // PB5=digital in en

	/* ============================================================== */

	xprintf("r0=%08x, r1=%08x, r2=%08x, r3=%08x\n", r0,r1,r2,r3);

	static FATFS ftfs;
	xprintf("f_mount->%d\n", f_mount(&ftfs, "0:", 1));

	/* RTC stuff */
	irtc_wsmask(0x2, 5, 1, 1); // PR1 in
	irtc_wsmask(0x3, 1, 1, 1); // PR1 pu
	irtc_wsmask(0x8, 1, 1, 1); // PR1 dig in enable
	irtc_wsmask(0x8, 4, 3, 1); // rst on PR1
	irtc_wsmask(0x8, 6, 1, 1); // en rst

	irtc_wsmask(0x2, 6, 1, 0); // PR2 out
	irtc_wsmask(0x2, 2, 1, 0); // PR2 low

	JL_audio_init();

	/* init audio */
	reg32_write(AUDIO_BASE+AUDIO_DAC_CON, 0);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACSR, 0xA); // 0=44100, 1=48000, 8=11025, A=8000 hz
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DCCS, 14);

	static uint16_t dac_buff[2][1024][2];

	reg32_write(AUDIO_BASE+AUDIO_DAC_ADR, (uint32_t)dac_buff);
	reg32_write(AUDIO_BASE+AUDIO_DAC_LEN, sizeof(dac_buff)/8); // 2 buffs + 2 channels + 2 bytes/channel

	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACEN, 1); // en

	static FIL fil;
	xprintf("f_open->%d\n", f_open(&fil, "0:BREATHE.U8", FA_READ));

	char led = 0;
	uint32_t okeys = 0;

	uint8_t vol = 0x18;

	for (;;) {
		reg32_wsmask(SYSCFG_BASE+SYSCFG_WDTCON, 6, 1, 1); // feed watchdog

		uint32_t keys = get_keys();
		if (keys ^ okeys) {
			xprintf("%08x\n", keys);

			if (keys & (1<<2)) break; // stop

			if (keys & (1<<1)) {
				if (vol < 0x1f) vol++;
				reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LGSEL, vol);
				reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_RGSEL, vol);
			}

			if (keys & (1<<4)) {
				if (vol > 0) vol--;
				reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LGSEL, vol);
				reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_RGSEL, vol);
			}

			okeys = keys;
		}

		/*if (!reg32_rsmask(PORTB_BASE+PORTx_INn(5))) {
			break;
		}*/

		if (reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_PND)) {
			reg32_wsmask(PORTB_BASE+PORTx_OUTn(0), led);
			led = !led;

			int saddr = reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_BUFF);
			saddr = (saddr + 1) % 2;

			uint8_t rdb[1024];
			UINT rdn;
			f_read(&fil, rdb, sizeof(rdb), &rdn);

			for (int i = 0; i < sizeof(dac_buff)/8; i++) {
				uint16_t v16 = rdb[i] << 8 ^ 0x8000;
				dac_buff[saddr][i][0] = dac_buff[saddr][i][1] = v16;
			}

			reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_CPND, 1);
		}
	}

	/* reset */
	reg32_write(CRC_BASE+CRC_REG, 0x6EA5); // CRC_REG = 0x6EA5 to unlock WDT reg
	reg32_write(SYSCFG_BASE+SYSCFG_WDTCON, 0x10);   // ~1ms timeout
	reg32_write(CRC_BASE+CRC_REG, 0x0000); // lock WDT reg back
}
