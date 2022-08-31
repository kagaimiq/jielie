#include <stdint.h>
#include <string.h>
#include "xprintf.h"
#include "jl_regs.h"
#include "jl_irtc.h"

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



uint8_t glitch(const char *prog, uint64_t t) {
	uint32_t stack[256] = {}; // 1024 bytes
	uint32_t num = 0, a, b;
	uint8_t sp = 0, wasnum = 0;

	/* skip the title */
	while (*prog) {
		prog++;
		if (prog[-1] == '!') break;
	}

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
				stack[++sp] = num;
				wasnum = num = 0;
			}
			break;
		}

		/* gather an opcode */
		switch (tk) {
		case 'a': /* t */
			stack[++sp] = t;
			break;

		case 'b': /* put */
			a = (stack[sp++] + 1) & 0xff;
			b = stack[sp--];
			stack[((sp--) - a) & 0xff] = b;
			break;

		case 'c': /* drop */
			sp--;
			break;

		case 'd': /* mul */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b * a;
			break;

		case 'e': /* div */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = a ? (b / a) : 0;
			break;

		case 'f': /* add */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b + a;
			break;

		case 'g': /* sub */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b - a;
			break;

		case 'h': /* mod */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = a ? (b % a) : 0;
			break;

		case 'j': /* lshift */
			a = stack[sp--];
			b = stack[sp--];
			//stack[++sp] = b << (a&0x1f);
			stack[++sp] = a > 31 ? 0 : (b << a);
			break;

		case 'k': /* rshift */
			a = stack[sp--];
			b = stack[sp--];
			//stack[++sp] = b >> (a&0x1f);
			stack[++sp] = a > 31 ? 0 : (b >> a);
			break;

		case 'l': /* and */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b & a;
			break;

		case 'm': /* or */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b | a;
			break;

		case 'n': /* xor */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b ^ a;
			break;

		case 'o': /* not */
			a = stack[sp--];
			stack[++sp] = ~a;
			break;

		case 'p': /* dup */
			a = stack[sp--];
			stack[++sp] = a;
			stack[++sp] = a;
			break;

		case 'q': /* pick */
			a = (stack[sp] + 1) & 0xff;
			a = stack[(sp - a) & 0xff];
			stack[sp] = a;
			break;

		case 'r': /* swap */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = a;
			stack[++sp] = b;
			break;

		case 's': /* lt */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b < a ? ~0 : 0;
			break;

		case 't': /* gt */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b > a ? ~0 : 0;
			break;

		case 'u': /* eq */
			a = stack[sp--];
			b = stack[sp--];
			stack[++sp] = b == a ? ~0 : 0;
			break;

		}
	} while (*prog++);

	return stack[sp--];
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

static void JL_audio_init(void) {
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LDO1EN, 1); // en ldo1
	for (volatile int i = 1000; i; i--);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_VCMEN, 1); // en vcm
	for (volatile int i = 1000; i; i--);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_DACEN, 1); // en dac
	for (volatile int i = 1000; i; i--);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_HPLEN, 1); // en dacl
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_HPREN, 1); // en dacr

	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_LGSEL, 0x18);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAA_CON0_RGSEL, 0x18);
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
	reg32_wsmask(USB_BASE+USB_IO_CON0_DPPD, 0);
	reg32_wsmask(USB_BASE+USB_IO_CON0_DMPD, 0);

	/* gpio */
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(0), 0); //PB0: out

	reg32_wsmask(PORTA_BASE+PORTx_DIRn(4), 1); // PA4=input
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(4), 1); // PB4=input
	reg32_wsmask(PORTB_BASE+PORTx_DIRn(5), 1); // PB5=input

	reg32_wsmask(PORTA_BASE+PORTx_DIEn(4), 1); // PA4=digital in en
	reg32_wsmask(PORTB_BASE+PORTx_DIEn(4), 1); // PB4=digital in en
	reg32_wsmask(PORTB_BASE+PORTx_DIEn(5), 1); // PB5=digital in en

	reg32_wsmask(PORTA_BASE+PORTx_PUn(4), 1); // PA4=pullup en
	reg32_wsmask(PORTB_BASE+PORTx_PUn(4), 1); // PB4=pullup en
	reg32_wsmask(PORTB_BASE+PORTx_PUn(5), 1); // PB5=pullup en

	/* ============================================================== */

	xprintf("r0=%08x, r1=%08x, r2=%08x, r3=%08x\n", r0,r1,r2,r3);

	/* RTC stuff */
	irtc_wsmask(0x8, 4, 3, 1); // reset on PR1
	irtc_wsmask(0x2, 6, 1, 0); // PR2 out
	irtc_wsmask(0x2, 2, 1, 0); // PR2 low

	JL_audio_init();

	/* init audio */
	reg32_write(AUDIO_BASE+AUDIO_DAC_CON, 0);
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACSR, 0xA); // 0=44100, 1=48000, 8=11025, A=8000 hz
	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DCCS, 14);

	const int dac_addr = 0x8000;
	const int dac_len = 0x4000;
	memset((void *)dac_addr, 0, dac_len * 2);

	reg32_write(AUDIO_BASE+AUDIO_DAC_ADR, dac_addr);
	reg32_write(AUDIO_BASE+AUDIO_DAC_LEN, dac_len / 2 / 2);

	reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_DACEN, 1); // en

	const char *glitches[] = {
		"sierpinski666!aAkal",
		"sierpinski_42!aaAkalk!2Al!ad",
		"!9.8.6.4.6.3.6.3!aDk7lqad!Ce80l!aCkaCk2gn!Bhad4eaDkm!7Fl!f",
		"!aAk1n5l3f!aEk3l5f!dad!a8k3lk",

		/* https://github.com/erlehmann/libglitch/tree/master/tracks */
		"42_forever!a13880fa400he!a5kma6kn40g!aCk28!a12k1ld!2fladm!43n",
		"4659840!a12epda12hpdf!a24e..a24h..f..m!a12epda12hpdf!a24e..a24h..g..m!f4e",
		"alive!12.17.12.F!12.17.12.E!aA00e8hq!ad6e60l",
		"barbarian!a8k3h1f!aDk5l9rg!ad7ed!p5fn!a6km",
		"barbarian2!a8k3h1f!aDk5l9gdad9e!p5fn.a6km",
		"beatwrap!a315ham!aa12k3lAfk5h!1fd!a3km!aDk100hn!40g",
		"chalk_1!10.C.F.A!10.C.F.A!10.9.F.9!8.C.F.A!aoFk10hq!ad!3ep!aBk4h2fd!p1km!raoBk2hk!p1kaoAk2hdm!l",
		"du_dup!a2ja6kn2d!a3ja7knf",
		"eerie_arpeggio!aCkAl1f!9f!a8Ce4l1fd!ad9e!p9fm!a6km20g",
		"factorii!499602D2!a10kFld!aAk1Flk3l1f!a11k3l1fdad3d!a2da5kmm!a5kf80f!a35da7Bhm9!a13k1lF6dfl!a3km!aCk1l!a10k1lmd!aEk1ld!n",
		"glitch_machine!a10k4h1f!aAk5h2ff!aCk3hg!ad3e!p!9fm!a4kl13f!aCk7Fhn",
		"guitar!a3kal!a2000h400sl!80qD0h3d!ff4eFFl!p",
		"guitar2!a6kal!a400hFFsl!60qD0h3d!ff4eFFl!p",
		"inpwm!a3da7klm!an!a4dFFhl",
		"kitt_malfunction!aAk5h!aEk6h1fd!aCk3hd!adaFkd!FFh",
		"glitch://lowpass_filter!a80l!FefFd10ep",
		"malady!ca20hea2kr!aAkalm!FFl8g!a20kq!48b!a100ere",
		"malordy!ca40hea2kr",
		"martians!a64d!a80e64h1fe!a6km",
		"mitch!a80h30ga9kl!a40h20ga6kl!a20h10ga4kl!nn",
		"octo!a2k14had!a2000he!a8!a11k3h1fde!m!aEk7Fhn!20g",
		"onion!aE1ha70hh!a71ha38hh!a39ha1Chh!a1Dha.Ehh!a.Fha.7hh!ffff",
		"pewpew!caa2000hhea2kr",
		"pipe_symphony!aEk5h5f!a11k2h!a9k3hdf!aDk4hg!ad4e!p5fm!a11k2h1rg!a5kdm",
		"pulsating!cAjan4kagp!Cjan6kagq!80h2d!a4000h480tl",
		"quatsi!a6e7kad!a6e8kl!a6eBkn",
		"query!aCk1l6d3f!a10k3hfad!p3dn!1g!a4km",
		"quiddit!3BFA6766!aAk10h1feAhad!a10k3h1fd!p!9qm!a5ka7komf!a2km",
		"roboducky!a5k2ad35hd!aBk9l1fd!a4km!aBk13l1fadl!a11k5l1fd!a8kn",
		"roboducky_redux!aBk13l1fad!a11k5l1fd!1869FaFFFlen!p5en!3d43n",		// awesome when t is & 0x7fff
		"rolling!a9da4kl!a5da7kl!a3da400el!mm1g",
		"sadglitch!4.4.9.8.9.6.4.2!aoCk8hq!ad2d!aFk3h1fe!p5d3em!a63hm!a7kFFlp80slf",
		"scale!a1000e!a11k7hq!ad",
		"sidekick!a6da9kl!a3da6klm!a4km",
		"sidewalk!a5da9kl!a2da5kl!m!a11k5lad!a4kmm",
		"simple!a8kal",					// no way i have the same solution
		"sine!aFl0agFld!a10l3k1gd!80d41e80f",		// clever!
		"starlost!aFFha1FFhn3d",
		"the_42_melody!aAk2Alad",			// no way i have the same solution
		"tripster!a800eoad!ada5kla4kg!a18jf!a4kb",
		"upwards!ADkaDkm10h10fad1!FFlpp100slropoFF!tlma6km",
		"waldo!a2e5d5gC0dl!da4eFDb!FDq8k3h1f!FDqDk5l9gdad9e!p5fn!FDq6km",
		"wistful!aa!aEk4h5f!a13k1l1fd!Adhe!a5kl!a11k2lg",
	};
	int glitchno = 3;

	char led = 0, showtrack=1;

	for (uint32_t t = 0;;) {
		reg32_wsmask(SYSCFG_BASE+SYSCFG_WDTCON, 6, 1, 1); // feed watchdog

		if (!reg32_rsmask(PORTA_BASE+PORTx_INn(4)) && (t > 4000)) {
			if (glitchno > 0) glitchno--;
			t = 0;
			showtrack = 1;
		}

		if (!reg32_rsmask(PORTB_BASE+PORTx_INn(4)) && (t > 4000)) {
			if (glitchno < (sizeof(glitches)/sizeof(glitches[0])) - 1)
				glitchno++;
			t = 0;
			showtrack = 1;
		}

		if (showtrack) {
			xprintf("%3d: %s\n", glitchno, glitches[glitchno]);
			showtrack = 0;
		}

		if (reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_PND)) {
			reg32_wsmask(PORTB_BASE+PORTx_OUTn(0), led);
			led = !led;

			int saddr = reg32_rsmask(AUDIO_BASE+AUDIO_DAC_CON_BUFF);
			saddr = (saddr + 1) % 2;
			saddr *= dac_len;
			saddr += dac_addr;
			//xprintf("Slice @ %x\n", saddr);

			for (int i = 0; i < dac_len; i += 4) {
				uint8_t v = glitch(glitches[glitchno], t);
				uint16_t v16 = (v << 7) ^ 0x8000;

				*(uint16_t *)(saddr + i + 0) = v16;
				*(uint16_t *)(saddr + i + 2) = v16;

				t++;
			}

			reg32_wsmask(AUDIO_BASE+AUDIO_DAC_CON_CPND, 1);
		}
	}
}
