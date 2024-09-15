# SFC

SFC (Serial/SPI Flash Controller) is used to access the SPI flash from the system memory map.
This block consitutes the interface part of the process; on the other side there is a cache that interfaces with the system memory bus and asks SFC for data whenever there is a cache miss and cache needs to be refilled.

- SPI and DSPI/QSPI interface variants supported
- Configurable base address offset

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

## Memory map

The SFC is connected to the system memory bus through the icache, which is used to cache data from the SPI flash (which is naturally slow to access on its own, since it is attached to a serial bus and it's a command-oriented device.), which in turn also provides a reasonable burst of data to transfer from the flash chip whenever the cache needs to be refilled.

The cache is usually organized as a 16 KiB 4-way set-associative cache with a 32-byte line size.

Between the cache and SFC there is an [ENC](enc.md) block in the way, which provides ability to descramble the data read from flash (so that you can't easily see what's going on!).

Due to the cache line size, the data is scrambled in 32-byte blocks, additionally the key used for scrambling is the actual key set up in the ENC/SFCENC XORed with the absolute memory address shifted right by 2, i.e. `key = key ^ (addr >> 2)`.
Since the key is just 16 bits long, this means that it will wrap around each 262144 bytes (i.e. 65536 * 4).

A bit more info on icache can be found [there](icache.md)

## Registers

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| BAUD     | 0x04   | Clock divider      |
| CODE     | 0x08   |                    |
| BASE_ADR | 0x0C   | Flash base address |

- Variant 2:

| Name     | Offset | Description        |
|----------|--------|--------------------|
| QUCNT    | 0x10   |                    |

### CON

Control register.

| Bits  | R/W | Default | Description                       |
|-------|-----|---------|-----------------------------------|
| 31:26 | /   | /       | /                                 |
| 25    | R/W |         | If set, accessing SFC will cause the output from the RDID ($9F) command to be read out. |
| 24    | /   | /       | /                                 |
| 23:20 |     |         | Maybe operaiton mode (0: read_out, 1: read_i/o, 2: read_continue). On init it is set to 0xF. |
| 19:16 | R/W |         | Number of dummy bits between command/address and data readout |
| 15:12 | /   | /       | /                                 |
| 11:8  |     |         | SPI mode, see below               |
| 7     |     |         | ? set to 1                        |
| 6:4   | /   | /       | /                                 |
| 3     | R/W |         | D0 input source (0: D0, 1: D1). In other words, if it is cleared, the data is received from the MOSI pin, otherwise it's done from MISO. Multi-bit interface options are also affected by this afaik |
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

Clock divider.

| Bits  | R/W | Default | Description                        |
|-------|-----|---------|------------------------------------|
| 31:8  | /   | /       | /                                  |
| 7:0   | W   |         | Clock divider: Fspi = Fsfc / (n+1) |

The *Fsfc* clock source comes from *sfc_clk* or *hsb_clk* depending on the chip (chips after AC690N/BR17 use *sfc_clk*)

### BASE_ADR

Flash base address.

This register allows to set up the base address of the area in flash that's going to be visible from SFC.

| Bits  | R/W | Default | Description        |
|-------|-----|---------|--------------------|
| 31:16  | /   | /       | /                  |
| 15:0   | W   |         | Flash base address |

## Example-ish

The example below is for the AC690N chip series, however it is applicable to other chips provided the I/O port init and cache tag/data addresses are changed to ones applicable to your particular chip family.

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
