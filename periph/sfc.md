# SFC

## Overview

SFC (Serial/SPI Flash Controller) is a dedicated SPI flash controller,
which supports SPI/DSPI/QSPI modes, and essentially allows to map an arbitrary flash location into memory.

```
mem
||                                                            _____........._
||                                 _____                     |     SPI flash |
||      ________       _____      |     | ---> CLK ========> | CLK           |
||     |        |     |     |     |     | <--> DO (DAT0) ==> | DI    - IO0   |
|| <== | icache | <== | ENC | <== | SFC | <--> DI (DAT1) ==> | DO    - IO1   |
||     |________|     |_____|     |     | <--> DAT2 =======> | /WP   - IO2   |
||        |      \                |     | <--> DAT3 =======> | /HOLD - IO3   |
||      __|__   __\___            |_____| ---> CS =========> | /CS           |
||     |_tag_| | sram |                                      |_____........._|
||             |_16k__|
```

### Memory map

The SFC is mapped into memory through the icache, which ultimately speeds up the flash access time (except when a cache miss happens).

The icache is usually a 16 KiB 4-way set-associative cache, with a 32-byte line size.

### Decryption

The contents it reads also can be decrypted with the ENC block
(a separate peripheral or an embedded block depending on the SFC variant).

Since the icache line size is 32 bytes, the encrypted block is also 32 bytes long.

Moreover, the key that's used for decryption is XORed with the current offset shifted right by 2 (i.e. `keydec = key ^ (off >> 2)`).
This also means that the key wraps each 256 KiB, as the key is 16 bits long and shifting offset by 2 allows for 4 times more,
thus it's 262144 bytes instead of just 65536.

## Registers

- Variant 1:

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| BAUD     | 0x04   | Clock divider      |
| CODE     | 0x08   |                    |
| BASE_ADR | 0x0C   | Flash base address |

- Variant 2:

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| BAUD     | 0x04   | Clock divider      |
| CODE     | 0x08   |                    |
| BASE_ADR | 0x0C   | Flash base address |
| QUCNT    | 0x10   |                    |

### CON

| Bits  | R/W | Default | Description                       |
|-------|-----|---------|-----------------------------------|
| 31:26 | /   | /       | /                                 |
| 25    | R/W |         | Read the JEDEC ID via opcode 0x9F |
| 24    | /   | /       | /                                 |
| 23:20 |     |         | ? set to 2, on init set to 0xf    |
| 19:16 | R/W |         | Dummy bit count                   |
| 15:12 | /   | /       | /                                 |
| 11:8  |     |         | SPI mode                          |
| 7     |     |         | ? set to 1                        |
| 6:4   | /   | /       | /                                 |
| 3     | R/W |         | Swap DO/DI on the DO input path (i.e. 0 = receive from DO, 1 = receive from DI) |
| 2:1   | /   | /       | /                                 |
| 0     | R/W | 0       | Enable SFC                        |

**Note:** on init, this register is set to 0xf00000, and then reset to 0

- SPI mode:

| Mode | Opcode | Command | Address | Data | Note             |
|------|--------|---------|---------|------|------------------|
| 0    | 0x03   | SPI     | SPI     | SPI  | Read             |
| 1    | 0x0B   | SPI     | SPI     | SPI  | Fast read        |
| 2    | 0x3B   | SPI     | SPI     | DSPI | Dual output read |
| 3    | 0x6B   | SPI     | SPI     | QSPI | Quad output read |
| 4    | 0xBB   | SPI     | DSPI    | DSPI | Dual I/O read    |
| 5    | 0xEB   | SPI     | QSPI    | QSPI | Quad I/O read    |
| 6    | 0xBB?  | DSPI?   | DSPI    | DSPI | Probably for the full DSPI cmd/addr/data cycle |
| 7    | 0xEB?  | QSPI?   | QSPI    | QSPI | Probably for the full QSPI cmd/addr/data cycle |

### BAUD

| Bits  | R/W | Default | Description                        |
|-------|-----|---------|------------------------------------|
| 31:8  | /   | /       | /                                  |
| 7:0   | W   |         | Clock divider: Fspi = Fsfc / (n+1) |

### BASE_ADR

| Bits  | R/W | Default | Description        |
|-------|-----|---------|--------------------|
| 31:x  | /   | /       | /                  |
| x:0   | W   |         | Flash base address |

## Example-ish

```c
/*
 * PD0 = SCK
 * PD1 = DI / IO0 (mosi)
 * PD2 = DO / IO1 (miso)
 * PD3 = CS#
 */

/* Init I/O */
JL_PORTD->DIR &= ~((1<<0)|(1<<1)|(1<<3));
JL_PORTD->DIR |= (1<<2);
JL_PORTD->PU |= (1<<1)|(1<<2);
JL_PORTD->OUT |= (1<<3);

//reg_wsmask(JL_IOMAP->CON0, 2, 0x1, 'A'-'A');	/* spi0 map A */
//reg_wsmask(JL_IOMAP->CON1, 5, 0x1, 'A'-'A');	/* sfc map A */

/* SFC init */
JL_SFC->CON = 0xf00000;
JL_SFC->CON = 0;

JL_SFC->BAUD = 128-1;  /* div 128 */

JL_SFC->BASE_ADR = 0x4000;  /* flash offset 0x4000 */

JL_SFC->CON =
    (0<<25) |	/* read JEDEC ID (command 0x9F) */
    (2<<20) |	/* ? */
    (8<<16) |	/* Dummy bit count */
    (2<<8) |	/* SPI mode */
    (1<<7) |	/* ? */
    (0<<3)		/* DO/DI combine */
;

JL_ENC->CON &= ~(1<<3);

/* Enable SFC */
JL_SPI0->CON &= ~(1<<0);	/* disable SPI0 */
JL_SFC->CON |= (1<<0);		/* enable SFC */

/* Enable SFC map */
JL_DSP->CON &= ~(1<<8);		/* disable SFC map */
memset((void *)0x1a000, 0x55, 0x4000);	/* clear icache data */
memset((void *)0x48000, 0x00, 0x1800);	/* clear icache tag */
JL_DSP->CON |= (1<<8);		/* enable SFC map */

hexdump((void *)0x1000000, 0x100);
```
