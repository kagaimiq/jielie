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

/*===================================================================*/

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

/*===================================================================*/

uint8_t disp_data[52];

void disp_txbit(int val) {
	reg32_wsmask(PORTB_base+PORTx_OUTn(7), !!val); // SI=x
	reg32_wsmask(PORTB_base+PORTx_OUTn(6), 1); // SCK=1
	for (volatile int i = 50; i; i--);
	reg32_wsmask(PORTB_base+PORTx_OUTn(6), 0); // SCK=0
	for (volatile int i = 50; i; i--);
}

void disp_show13(void) {
	reg32_wsmask(PORTB_base+PORTx_DIRn(4), 0); // PB4 out (CE)
	reg32_wsmask(PORTB_base+PORTx_DIRn(6), 0); // PB6 out (SCK)
	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 0); // PB7 out (SI)

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 0); // CE=0

	// addr (0x41 == 1/3 drive mode)
	for (uint8_t mask = 0x01; mask; mask <<= 1)
		disp_txbit(0x41 & mask);

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 1); // CE=1

	// data
	for (int i = 0; i < 156; i++)
		disp_txbit(disp_data[i / 3] & (1 << (i % 3)));

	// control
	disp_txbit(0); // DR [0: 1/2 bias, 1: 1/3 bias]
	disp_txbit(0); // SC [0: display on, 1: display off]
	disp_txbit(0); // BU [0: normal, 1: power saving]
	disp_txbit(0); // CU [0: normal, 1: low current drive]

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 0); // CE=0
}

void disp_show14(void) {
	reg32_wsmask(PORTB_base+PORTx_DIRn(4), 0); // PB4 out (CE)
	reg32_wsmask(PORTB_base+PORTx_DIRn(6), 0); // PB6 out (SCK)
	reg32_wsmask(PORTB_base+PORTx_DIRn(7), 0); // PB7 out (SI)

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 0); // CE=0

	// addr (0x80 == 1/4 drive mode)
	for (uint8_t mask = 0x01; mask; mask <<= 1)
		disp_txbit(0x80 & mask);

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 1); // CE=1

	// data
	for (int i = 0; i < 204; i++)
		disp_txbit(disp_data[i / 4] & (1 << (i % 4)));

	// control
	disp_txbit(0); // PC0
	disp_txbit(0); // PC1
	disp_txbit(0); // PC2
	disp_txbit(0); // PC3
	disp_txbit(0); // DR [0: 1/2 bias, 1: 1/3 bias]
	disp_txbit(0); // SC [0: display on, 1: display off]
	disp_txbit(0); // BU [0: normal, 1: power saving]
	disp_txbit(0); // CU [0: normal, 1: low current drive]

	reg32_wsmask(PORTB_base+PORTx_OUTn(4), 0); // CE=0
}




void JieLi(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3) {
	largs = (void *)r0;

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

	#define D14S__A			0x0080
	#define D14S__B			0x8000
	#define D14S__C			0x2000
	#define D14S__D			0x0010
	#define D14S__E			0x0002
	#define D14S__F			0x0008
	#define D14S__G1		0x0004
	#define D14S__G2		0x4000
	#define D14S__H			0x0040
	#define D14S__I			0x0400
	#define D14S__J			0x0800
	#define D14S__K			0x0020
	#define D14S__L			0x0200
	#define D14S__M			0x0100

	const char digstart[] = {0,4,8,13,17,21,26,30,34,39};

	/*
	 *   AAAAAAAAAAA
	 *  F H   I   J B
	 *  F  H  I  J  B
	 *  F   H I J   B
	 *   G1G1G G2G2G
	 *  E   K L M   C
	 *  E  K  L  M  C
	 *  E K   L   M C
	 *   DDDDDDDDDDD
	 * україньска мова
	 * 15  14  13  12 | 11  10  9   8 | 7   6   5   4 | 3   2   1   0
	 * B   G2  C   -- | J   I   L   M | A   H   K   D | F   G1  E   --
	 */

	/*
	 * |       | COM1    | COM2    | COM3    | COM4    |
	 * |-------|---------|---------|---------|---------|
	 * | SEG1  | EQ      | 1.E     | 1.G1    | 1.F     |
	 * | SEG2  | 1.D     | 1.K     | 1.H     | 1.A     |
	 * | SEG3  | 1.M     | 1.L     | 1.I     | 1.J     |
	 * | SEG4  | XDSS+   | 1.C     | 1.G2    | 1.B     |
	 * | SEG5  | WMA     | 2.E     | 2.G1    | 2.F     |
	 * | SEG6  | 2.D     | 2.K     | 2.H     | 2.A     |
	 * | SEG7  | 2.M     | 2.L     | 2.I     | 2.J     |
	 * | SEG8  | WMA/MP3 | 2.C     | 2.G2    | 2.B     |
	 *           frame
	 * | SEG9  | MP3     | 3.E     | 3.G1    | 3.F     |
	 * | SEG10 | 3.D     | 3.K     | 3.H     | 3.A     |
	 * | SEG11 | 3.M     | 3.L     | 3.I     | 3.J     |
	 * | SEG12 | USB     | 3.C     | 3.G2    | 3.B     |
	 * | SEG13 |         |         |         |         |
	 * | SEG14 | iPod    | 4.E     | 4.G1    | 4.F     |
	 * | SEG15 | 4.D     | 4.K     | 4.H     | 4.A     |
	 * | SEG16 | 4.M     | 4.L     | 4.I     | 4.J     |
	 * | SEG17 | Folder  | 4.C     | 4.G2    | 4.B     |
	 * | SEG18 | 1 (rpt) | 5.E     | 5.G1    | 5.F     |
	 * | SEG19 | 5.D     | 5.K     | 5.H     | 5.A     |
	 * | SEG20 | 5.M     | 5.L     | 5.I     | 5.J     |
	 * | SEG21 | RPT     | 5.C     | 5.G2    | 5.B     |
	 * | SEG22 | INT     | 6.E     | 6.G1    | 6.F     |
	 * | SEG23 | 6.D     | 6.K     | 6.H     | 6.A     |
	 * | SEG24 | 6.M     | 6.L     | 6.I     | 6.J     |
	 * | SEG25 | 6.comma | 6.C     | 6.G2    | 6.B     |
	 * | SEG26 | <<SUB>> | PTY     | TP      | TA      |
	 * | SEG27 | SHF     | 7.E     | 7.G1    | 7.F     |
	 * | SEG28 | 7.D     | 7.K     | 7.H     | 7.A     |
	 * | SEG29 | 7.M     | 7.L     | 7.I     | 7.J     |
	 * | SEG30 |bluetooth| 7.C     | 7.G2    | 7.B     |
	 * | SEG31 | ?phone  | 8.E     | 8.G1    | 8.F     |
	 * | SEG32 | 8.D     | 8.K     | 8.H     | 8.A     |
	 * | SEG33 | 8.M     | 8.L     | 8.I     | 8.J     |
	 * | SEG34 | 8.comma | 8.C     | 8.G2    | 8.B     |
	 * | SEG35 | 8.dp    | 9.E     | 9.G1    | 9.F     |
	 * | SEG36 | 9.D     | 9.K     | 9.H     | 9.A     |
	 * | SEG37 | 9.M     | 9.L     | 9.I     | 9.J     |
	 * | SEG38 | <       | 9.C     | 9.G2    | 9.B     |
	 * | SEG39 | DISC    | ST      | ((o))   | AF      |
	 * | SEG40 | >       | 10.E    | 10.G1   | 10.F    |
	 * | SEG41 | 10.D    | 10.K    | 10.H    | 10.A    |
	 * | SEG42 | 10.M    | 10.L    | 10.I    | 10.J    |
	 * | SEG43 | separat | 10.C    | 10.G2   | 10.B    |
	 * | SEG44 | 
	 * | SEG45 | 
	 * | SEG46 | 
	 * | SEG47 | 
	 * | SEG48 | 
	 * | SEG49 | 
	 * | SEG50 | 
	 * | SEG51 | 
	 */

	const uint16_t chars[] = {
	/*-------------- 20-2f --------------*/
		/* null/space */
		0,
		/* ! */
		D14S__I|D14S__L|D14S__M, // qq
		/* " */
		D14S__H|D14S__J,
		/* # */
		D14S__I|D14S__L|D14S__G1|D14S__G2|D14S__B|D14S__C|D14S__D,
		/* $ */
		D14S__A|D14S__F|D14S__G1|D14S__G2|D14S__C|D14S__D|D14S__I|D14S__L,
		/* % */
		D14S__F|D14S__J|D14S__K|D14S__C,
		/* & */
		D14S__A|D14S__H|D14S__J|D14S__M|D14S__D|D14S__E|D14S__G1,
		/* ' */
		D14S__I,
		/* ( */
		D14S__J|D14S__M,
		/* ) */
		D14S__H|D14S__K,
		/* * */
		D14S__H|D14S__J|D14S__K|D14S__M|D14S__G1|D14S__G2,
		/* + */
		D14S__G1|D14S__G2|D14S__I|D14S__L,
		/* , */
		D14S__K,
		/* - */
		D14S__G1|D14S__G2,
		/* . */
		D14S__M,
		/* / */
		D14S__K|D14S__J, // KJ!
	/*-------------- 30-3f --------------*/
		/* 0 */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__E|D14S__F|D14S__J|D14S__K,
		/* 1 */
		D14S__J|D14S__B|D14S__C,
		/* 2 */
		D14S__A|D14S__B|D14S__G2|D14S__K|D14S__D,
		/* 3 */
		D14S__A|D14S__J|D14S__G2|D14S__C|D14S__D,
		/* 4 */
		D14S__F|D14S__G1|D14S__G2|D14S__I|D14S__L,
		/* 5 */
		D14S__A|D14S__F|D14S__G1|D14S__M|D14S__D,
		/* 6 */
		D14S__A|D14S__F|D14S__E|D14S__D|D14S__M|D14S__G1,
		/* 7 */
		D14S__A|D14S__J|D14S__L,
		/* 8 */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__E|D14S__F|D14S__G1|D14S__G2,
		/* 9 */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__G2|D14S__H,
		/* : */
		D14S__I|D14S__L, // ==|
		/* ; */
		D14S__I|D14S__K,
		/* < */
		D14S__J|D14S__B|D14S__M|D14S__C,
		/* = */
		D14S__G1|D14S__G2|D14S__D,
		/* > */
		D14S__F|D14S__H|D14S__E|D14S__K,
		/* ? */
		D14S__F|D14S__A|D14S__J|D14S__L,
	/*-------------- 40-5f --------------*/
		/* @ */
		D14S__A|D14S__F|D14S__E|D14S__D|D14S__C|D14S__G2|D14S__L,
		/* A */
		D14S__K|D14S__J|D14S__G2|D14S__B|D14S__C,
		/* B */
		D14S__A|D14S__I|D14S__L|D14S__D|D14S__J|D14S__M,
		/* C */
		D14S__A|D14S__F|D14S__E|D14S__D,
		/* D */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__L|D14S__I,
		/* E */
		D14S__A|D14S__F|D14S__E|D14S__D|D14S__G1,
		/* F */
		D14S__A|D14S__F|D14S__E|D14S__G1,
		/* G */
		D14S__A|D14S__F|D14S__E|D14S__D|D14S__C|D14S__G2,
		/* H */
		D14S__F|D14S__E|D14S__G1|D14S__G2|D14S__B|D14S__C,
		/* I */
		D14S__A|D14S__I|D14S__L|D14S__D,
		/* J */
		D14S__B|D14S__C|D14S__D|D14S__E,
		/* K */
		D14S__F|D14S__E|D14S__G1|D14S__J|D14S__G2|D14S__C,
		/* L */
		D14S__F|D14S__E|D14S__D,
		/* M */
		D14S__F|D14S__E|D14S__H|D14S__J|D14S__B|D14S__C,
		/* N */
		D14S__F|D14S__E|D14S__H|D14S__M|D14S__B|D14S__C,
		/* O */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__E|D14S__F,
		/* P */
		D14S__A|D14S__B|D14S__G2|D14S__G1|D14S__F|D14S__E,
		/* Q */
		D14S__A|D14S__B|D14S__C|D14S__D|D14S__E|D14S__F|D14S__M,
		/* R */
		D14S__A|D14S__B|D14S__G2|D14S__G1|D14S__M|D14S__F|D14S__E,
		/* S */
		D14S__A|D14S__H|D14S__M|D14S__D,
		/* T */
		D14S__A|D14S__I|D14S__L,
		/* U */
		D14S__F|D14S__E|D14S__D|D14S__C|D14S__B,
		/* V */
		D14S__F|D14S__E|D14S__K|D14S__J,
		/* W */
		D14S__F|D14S__E|D14S__K|D14S__M|D14S__C|D14S__B,
		/* X */
		D14S__H|D14S__J|D14S__K|D14S__M,
		/* Y */
		D14S__H|D14S__G2|D14S__B|D14S__C|D14S__D,
		/* Z */
		D14S__A|D14S__J|D14S__K|D14S__D,
		/* [ */
		D14S__A|D14S__F|D14S__E|D14S__D,
		/* \ */
		D14S__H|D14S__M,
		/* ] */
		D14S__A|D14S__B|D14S__C|D14S__D,
		/* ^ */
		D14S__K|D14S__M,
		/* _ */
		D14S__D,
	/*-------------- 60-7f --------------*/
		/* ` */
		D14S__H,
		/* a */
		D14S__C|D14S__D|D14S__K|D14S__G2,
		/* b */
		D14S__F|D14S__E|D14S__D|D14S__M|D14S__G1,
		/* c */
		D14S__G1|D14S__E|D14S__D,
		/* d */
		D14S__K|D14S__G2|D14S__B|D14S__C|D14S__D,
		/* e */
		D14S__D|D14S__E|D14S__G1|D14S__K,
		/* f */
		D14S__L|D14S__J|D14S__G2,
		/* g */
		D14S__C|D14S__D|D14S__G2|D14S__M,
		/* h */
		D14S__F|D14S__E|D14S__G1|D14S__M,
		/* i */
		D14S__D|D14S__L|D14S__G1,
		/* j */
		D14S__D|D14S__C|D14S__M,
		/* k */
		D14S__I|D14S__L|D14S__M|D14S__J,
		/* l */
		D14S__F|D14S__E|D14S__K,
		/* m */
		D14S__E|D14S__G1|D14S__G2|D14S__L|D14S__C,
		/* n */
		D14S__E|D14S__G1|D14S__G2|D14S__C,
		/* o */
		D14S__E|D14S__G1|D14S__G2|D14S__C|D14S__D,
		/* p */
		D14S__E|D14S__G1|D14S__K,
		/* q */
		D14S__M|D14S__G2|D14S__C,
		/* r */
		D14S__E|D14S__G1|D14S__G2,
		/* s */
		D14S__G2|D14S__M|D14S__D,
		/* t */
		D14S__G1|D14S__G2|D14S__I|D14S__M,
		/* u */
		D14S__E|D14S__D|D14S__C,
		/* v */
		D14S__E|D14S__K,
		/* w */
		D14S__E|D14S__K|D14S__M|D14S__C,
		/* x */
		D14S__H|D14S__J|D14S__K|D14S__M,
		/* y */
		D14S__M|D14S__C|D14S__D,
		/* z */
		D14S__G1|D14S__K|D14S__D,
		/* { */
		D14S__J|D14S__M|D14S__G1,
		/* | */
		D14S__I|D14S__L,
		/* } */
		D14S__H|D14S__K|D14S__G2,
		/* del */
		D14S__D|D14S__K|D14S__M,
	};

	const char text[] = "NOW PLAYING: KaSa / Satan @ 0:/ZoranLtd/kona/(11) KaSa - Satan.mp3 || JL JIELI TECH!";
	/*
	"Kagami Hiiragi (?? ??????, Hiiragi Kagami)\n"
"    Voiced by: Ami Koshimizu (old drama CD, NDS video game),\n"
"               Emiri Katou (anime, radio, PS2 and PSP video game, new drama CD, Miyakawa-ke no K??fuku anime and drama CD),\n"
"               Kari Wahlgren (English)\n"
"\n"
"Kagami is the older fraternal twin sister of Tsukasa Hiiragi.\n"
"In school, her grades are excellent, as she studies very hard,[11]"
"and she was elected class president in her first year.\n"
"She is in a different class than Konata Izumi and Tsukasa, but she frequently comes to their class during lunch time to eat with Tsukasa.\n"
"Additionally, Kagami chose the humanities stream in her second year, so that she could be with her friends,[12] but she was the only one separated into a different classroom; the same occurred in her third year.\n"
"Kagami, occasionally referred to as \"Kagamin\" (oh shit) by Konata, is very boyish, a bit egotistical, and not as good a cook as Tsukasa.[12]\n"
"Konata loves to irritate her, and their arguments act as one of the main factors of comic relief throughout the series.\n"
"Kagami is usually annoyed by Konata's constant references to her otaku interests, but usually has an idea on what she is saying.\n"
"\n"  
"Kagami's physique is average, but she is flat chested like her twin and Konata.\n"
"Though Kagami is a tough tomboy, she has a very girly side.\n"
"She is usually concerned about her weight, counting every kilogram she gains or loses.\n"
"Kagami likes to eat sweet food and she is often seen eating sweet food at night, such as chocolate Pocky sticks.\n"
"Despite her concern about her weight, she has no willpower controlling her eating habit, being the tomboy she is, resulting in an \"eat now, fret later\" attitude.[6]\n"
"She has long, purple hair with a ribbon tied into bunches,[13] and unlike Tsukasa, has sharp tsurime eyes.\n"
"Kagami is the quintessential \"tsundere\";[13] she on one side can be the straight and intolerant type however, \e[35;1mshe is prone to become shy and lonely at times.\n"
"Kagami is constantly attempting to hide the fact that she has a deep sense of attachment to her friends, especially Konata.[13]\n"
"She also seems to take a twisted delight in mocking Konata's smaller-than-average physique, her lack of motivation and her tendency to be a troublemaker, which usually results in Konata becoming very defensive.\n"
"In spite of all this, she \e[31;1mreally does care about Konata, and is almost always willing to go places or do favors for her.\n"
"\n"
"Similarly to Konata, Kagami is a tomboy who likes video games, but plays a different genre than Konata: scrolling shooters.[7]\n"
"She loves to read light novels, but is lonely, as no one around her has the same interests as her (though she is implied to have a knack for anime, since a \e[31mstuffed Bonta-kun doll from Full Metal Panic! can be seen in her room).\n"
"Both Kagami and Tsukasa are left-handed.\n"
"Kagami shares the name of her creator, Kagami Yoshimizu, and according to the creator, Kagami was his pen name in his school days, and had her personality thought out long ago.\n"
"Kagami became the 2008 Anime Saimoe Tournament's champion with her sister Tsukasa being runner-up.\n"
"\n"
"[6] from LS4\n"
"[7] from LS9\n"
"[11] https://web.archive.org/web/20080725115818/http://lucky-star.bandai-ent.com/characters/kagami.php (archvied)\n"
"[12] from LS7\n"
"[13] from LS8\n"
"\n";
	*/

	for (int off = 0;;off++) {
		wdt_clr();

		// clear disp data
		for (int i = 0; i < (sizeof disp_data / sizeof disp_data[0]); i++)
			disp_data[i] = 0;

		// 14-segment digits
		for (int i = 0; i < 10; i++) {
			int n = (i + off) % sizeof text; //(sizeof chars / sizeof chars[0]);

			n = text[n];

			if (n < 0x20 || n > 0x7f) continue;
			n -= 0x20;

			disp_data[digstart[i]+0] |= (chars[n] >> 0) & 0xf;
			disp_data[digstart[i]+1] |= (chars[n] >> 4) & 0xf;
			disp_data[digstart[i]+2] |= (chars[n] >> 8) & 0xf;
			disp_data[digstart[i]+3] |= (chars[n] >> 12) & 0xf;
		}

		// etc
		disp_data[42] |= 1;

		if (off & 1) disp_data[37] |= 1;
		else         disp_data[39] |= 1;

		if (!(off & 3)) disp_data[29] |= 1;

		int xxx = off % (9 * 4);

		     if (xxx < 4 ) disp_data[12] |= 1 << (xxx - 0);
		else if (xxx < 8 ) disp_data[43] |= 1 << (xxx - 4);
		else if (xxx < 12) disp_data[44] |= 1 << (xxx - 8);
		else if (xxx < 16) disp_data[45] |= 1 << (xxx - 12);
		else if (xxx < 20) disp_data[46] |= 1 << (xxx - 16);
		else if (xxx < 24) disp_data[47] |= 1 << (xxx - 20);
		else if (xxx < 28) disp_data[48] |= 1 << (xxx - 24);
		else if (xxx < 32) disp_data[49] |= 1 << (xxx - 28);
		else if (xxx < 36) disp_data[50] |= 1 << (xxx - 32);

		// show!
		disp_show14();

		for (volatile int i = 500000; i; i--);
	}

}
