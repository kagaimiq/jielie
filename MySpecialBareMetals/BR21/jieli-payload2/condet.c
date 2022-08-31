#include <stdint.h>
#include <string.h>
#include "xprintf.h"
#include "jl_regs.h"

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



#if 1
const uint32_t fft_tab[] = {
	0x20000, 0x1FD89, 0x1F629, 0x1E9F4,
	0x1D907, 0x1C38B, 0x1A9B6, 0x18BC8,
	0x16A0A, 0x144CF, 0x11C74, 0x0F15B,
	0x0C3EF, 0x094A0, 0x063E3, 0x0322F,
	0x00000
};

void fft_run(int *in, int *out, int forward, int nshift) {
	while (!reg32_rsmask(FFT_BASE+FFT_CON, 7, 1)); // wait for idle

	reg32_write(FFT_BASE+FFT_CON, 0); // clr con

	reg32_write(FFT_BASE+FFT_ADRW, (uint32_t)fft_tab); // put table addr

	reg32_wsmask(FFT_BASE+FFT_CON, 0, 0x0601, 0x0601); // ?

	reg32_wsmask(FFT_BASE+FFT_CON, 1, 1, in == out); // whether the in and out on the same address

	reg32_wsmask(FFT_BASE+FFT_CON, 12, 0xf, 7 - nshift); // nshift ...

	reg32_wsmask(FFT_BASE+FFT_CON, 2, 1, !!forward); // xxx/forward fft

	reg32_write(FFT_BASE+FFT_ADRI, (uint32_t)in); // input addr
	reg32_write(FFT_BASE+FFT_ADRO, (uint32_t)out); // output addr

	reg32_wsmask(FFT_BASE+FFT_CON_start, 1); // start
	while (!reg32_rsmask(FFT_BASE+FFT_CON_busy)); // wait
}
#endif



void irtc_sel(int sel) {
	reg32_wsmask(IRTC_BASE+IRTC_CON_RTCCS, !!sel);
}

uint8_t irtc_xfer(uint8_t val) {
	reg32_write(IRTC_BASE+IRTC_DAT, val);
	reg32_wsmask(IRTC_BASE+IRTC_CON_STRAN, 1);
	while (reg32_rsmask(IRTC_BASE+IRTC_CON_BUSY));
	return reg32_read(IRTC_BASE+IRTC_DAT);
}

void irtc_write(int addr, uint8_t val) {
	irtc_sel(1);
	irtc_xfer(0x00|0x20|(addr&0xf));
	irtc_xfer(val);
	irtc_sel(0);
}

uint8_t irtc_read(int addr) {
	uint8_t val;

	irtc_sel(1);
	irtc_xfer(0x80|0x20|(addr&0xf));
	val = irtc_xfer(0);
	irtc_sel(0);

	return val;
}

void irtc_wsmask(int addr, int shift, uint8_t mask, uint8_t val) {
	irtc_write(addr, (irtc_read(addr) & (mask << shift)) | ((val & mask) << shift));
}

uint8_t irtc_rsmask(int addr, int shift, uint8_t mask) {
	return (irtc_read(addr) >> shift) & mask;
}


uint8_t glitch(const char *prog, uint64_t t) {
	static uint32_t stack[256]; // 1024 bytes
	uint32_t num = 0, a, b;
	uint8_t sp = 0, wasnum = 0;

	/* skip the title */
	while (*prog) {
		prog++;
		if (prog[-1] == '!') break;
	}

#define xputs(s)

	/* interpret */
	do {
		char tk = *prog;
		if (tk == '!') continue; /* skip line separator */

		/* gather a number */
		switch (tk) {
		/* numbers */
		case '0' ... '9': num = (num << 4) | (tk - '0'      ); wasnum = 1; break;
		case 'A' ... 'F': num = (num << 4) | (tk - 'A' + 0xA); wasnum = 1; break;

		/* any other op - push */
		default:
			if (wasnum) {
				stack[sp++] = num;
				wasnum = num = 0;
			}
			break;
		}

		/* gather an opcode */
		switch (tk) {
		case 'a': /* t */
			xputs("T\n");
			stack[sp++] = t;
			break;

		case 'b': /* put */
			xputs("PUT\n");
			/*a = stack[--sp];
			b = stack[--sp]; sp++;
			stack[(sp - a) & 0xff] = b;*/
			break;

		case 'c': /* drop */
			xputs("DROP\n");
			sp--;
			break;

		case 'd': /* mul */
			xputs("MUL\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b * a;
			break;

		case 'e': /* div */
			xputs("DIV\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = a ? (b / a) : 0;
			break;

		case 'f': /* add */
			xputs("ADD\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b + a;
			break;

		case 'g': /* sub */
			xputs("SUB\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b - a;
			break;

		case 'h': /* mod */
			xputs("MOD\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = a ? (b % a) : 0;
			break;

		case 'j': /* lshift */
			xputs("LSHIFT\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b << a;
			break;

		case 'k': /* rshift */
			xputs("RSHIFT\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b >> a;
			break;

		case 'l': /* and */
			xputs("AND\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b & a;
			break;

		case 'm': /* or */
			xputs("OR\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b | a;
			break;

		case 'n': /* xor */
			xputs("XOR\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b ^ a;
			break;

		case 'o': /* not */
			xputs("NOT\n");
			a = stack[--sp];
			stack[sp++] = ~a;
			break;

		case 'p': /* dup */
			xputs("DUP\n");
			a = stack[--sp]; sp++;
			stack[sp++] = a;
			break;

		case 'q': /* pick */
			xputs("PICK\n");
			/*a = stack[--sp];
			a = stack[(sp - a) & 0xff];
			stack[++sp] = a;*/
			break;

		case 'r': /* swap */
			xputs("SWAP\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = a;
			stack[sp++] = b;
			break;

		case 's': /* lt */
			xputs("LT\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b < a ? ~0 : 0;
			break;

		case 't': /* gt */
			xputs("GT\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b > a ? ~0 : 0;
			break;

		case 'u': /* eq */
			xputs("EQ\n");
			a = stack[--sp];
			b = stack[--sp];
			stack[sp++] = b == a ? ~0 : 0;
			break;

		}
	} while (*prog++);

	xputs("end\n");

	return stack[--sp];
}







void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	/* disable WDT */
	//reg32_write(CRC_BASE+CRC_REG, 0x6EA5); // CRC_REG = 0x6EA5 to unlock WDT reg
	//reg32_write(SYSCFG_BASE+SYSCFG_WDTCON, 0x00);   // disable WDT altogether
	//reg32_write(CRC_BASE+CRC_REG, 0x0000); // lock WDT reg back

	reg32_wsmask(PORTB_BASE+PORTx_DIRn(0), 0); //PB0: out
	reg32_wsmask(PORTA_BASE+PORTx_DIRn(3), 0); //PA3: out

	// pll_sys_clk == PLL 192 MHz / 3 / 2  -> 32 MHz
	//reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON2, 0, 0x3f, 0x14);

	// config uart clock
	reg32_wsmask(CLOCK_BASE+CLOCK_CLKCON1, 10, 3, 1); // UART clk is PLL 48 MHz

	// config uart
	reg32_write(UART2_BASE+UARTx_CON0, 1); // 8n1, en
	reg32_write(UART2_BASE+UARTx_BAUD, 48000000/4/115200);

	// config uart iomux
	reg32_wsmask(IOMAP_BASE+IOMAP_CON1, 14, 3, 0); // UART2 to PA3/PA4
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3,  8, 7, 0); // UART2 I/O sel -> IOMUX
	reg32_wsmask(IOMAP_BASE+IOMAP_CON3, 11, 1, 1); // UART2 I/O enable

	/* ============================================================== */
	
	xdev_out(uputc);
	for (int i = 0; i < 10; i++) xputc('\n');
	xputs("\n\e[1;40;33;7m <<  Tsukasa, Konata and Miyuki  >> \e[0m\n");

	xprintf("r0=%08x, r1=%08x, r2=%08x, r3=%08x\n", r0,r1,r2,r3);
	xprintf("Argument>>>>%04x\n", ((uint32_t*)r0)[3]);

	/* RTC stuff */
	reg32_wsmask(IRTC_BASE+IRTC_CON_BAUD, 3);
	irtc_wsmask(0x8, 4, 3, 1); // reset on PR1
	irtc_wsmask(0x2, 6, 1, 0); // PR2 out
	irtc_wsmask(0x2, 2, 1, 0); // PR2 low

	/* init audio */
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LDO1EN, 1); // en ldo1
	for (volatile int i = 1000; i; i--);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_VCMEN, 1); // en vcm
	for (volatile int i = 1000; i; i--);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_DACEN, 1); // en dac
	for (volatile int i = 1000; i; i--);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_HPLEN, 1); // en dacl

	memset((void *)0x8000, 0, 0x8000);

#if 1
	reg32_write(AUDIO_BASE+AUDIO_DAC_CON, 0);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACSR, 0xa); // 0=44100, 8=11025, A=8000 hz
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DCCS, 14);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LGSEL, 0x18);

	const int dac_addr = 0x8000;
	const int dac_len = 0x4000;

	reg32_write(AUDIO_BASE+AUDIO_DAC_ADR, dac_addr);
	reg32_write(AUDIO_BASE+AUDIO_DAC_LEN, dac_len / 2 / 2);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACEN, 1); // en

#ifdef GLITCH_MACHINE
	const char *glitches[] = {
		"sadglitch!4.4.9.8.9.6.4.2|aoCk8hq!ad2d!aFk3h1fe!p5d3em!a63hm!a7kFFlp80slf",
		"pipe_symphony!aEk5h5f!a11k2h!a9k3hdf!aDk4hg!ad4e!p5fm!a11k2h1rg!a5kdm",
	};
#endif

	for (uint64_t t = 0;;) {
		reg32_wsmask(SYSCFG_BASE+SYSCFG_WDTCON, 6, 1, 1); // feed watchdog

		int saddr = reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_BUFF);
		saddr = (saddr + 1) % 2;
		saddr *= dac_len;
		saddr += dac_addr;
		xprintf("Slice @ %x\n", saddr);

		for (int i = 0; i < dac_len; i += 4) {
#ifdef GLITCH_MACHINE
			uint8_t v = glitch(glitches[0], t);
#else
			uint8_t v = (t*((3+(1^(t>>10&5)))*(5+(3&t>>14))))>>(t>>8&3);
#endif

			uint16_t v16 = (v << 8) ^ 0x8000;

			*(uint16_t *)(saddr + i + 0) = v16;
			*(uint16_t *)(saddr + i + 2) = v16;

			t++;
		}

		while (!reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_PND));
		reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_CPND, 1);
	}
#endif

#if 0
	reg32_write(AUDIO_BASE+AUDIO_ADC_CON, 0);
	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_ADCSR, 0xA); // 8000 hz
	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_CHE0, 1);
	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_DCCS, 14);

	reg32_write(AUDIO_BASE+AUDIO_ADC_ADR, 0x8000);
	reg32_write(AUDIO_BASE+AUDIO_ADC_LEN, 0x1000);

	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_ADCEN, 1); // en

	while (!reg32_rsmask(AUDIO_BASE+AUDIO_ADC_CON_PND));
	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_CPND, 1);

	reg32_wsmask(AUDIO_BASE+AUDIO_ADC_CON_ADCEN, 0); // dis

	xputs("REC done\n");

	for (int i = 0; i < 2*3; i++) {
		hexdump((void *)(0x8000 + i * 0x1000), 0x40);
	}
#endif
}
