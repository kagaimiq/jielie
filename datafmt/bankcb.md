# BANKCB

BANKCB (probably: BANKed Code Block(s)) is used to store banked code, for example in the early chip series like [AC410N](../chips/cd03/index.md#ac410n) or in 8051-based chips like [SH50](../chips/sh50/index.md), etc.

Even with chips that have access to relatively huge memory storage (e.g. a memory-mapped SPI flash or an SDRAM of some kind), this thing still lives to this day to store the second stage bootloader (the `uboot.boot`) that is in charge of initializing such memories and eventually starting execution from them.

## Format

### Header

```c
struct bankcb {
	uint16_t	count;		/* Bank number/count */
	uint16_t	size;		/* Bank data size */
	uint32_t	load;		/* Bank load address */
	uint32_t	offset;		/* Bank data offset */
	uint16_t	data_crc;	/* Data CRC */
	uint16_t	hdr_crc;	/* Header CRC */
};
```

- u16: Bank number (or count, for a 'master' bank)
- u16: Bank size
- u32: Bank load address
- u32: Bank data offset
- u16: Data CRC
- u16: Header CRC (of the previous 14 bytes)

### Layout

All banks, including the master bank, is stored at the beginning of a BANKCB image.
Then the bank data themselve follows.

If the image is scrambled, each header and data portion are scrambled individually.

```
     .------------------------.
     |   Master bank header   |  <-- contains the number of all banks
     :------------------------:
     |     Bank #0 header     |
     :------------------------:
     |     Bank #1 header     |
     :------------------------:
     |     Bank #2 header     |
     :------------------------:
          . . . . . . . . .
     :------------------------:
     |     Bank #n header     |
     :------------------------:
     |                        |
     |    Master bank data    |
     |                        |
     :------------------------:
     |                        |
     |      Bank #0 data      |
     |                        |
     :------------------------:
     |                        |
     |      Bank #1 data      |
     |                        |
     :------------------------:
     |                        |
     |      Bank #2 data      |
     |                        |
     :------------------------:
          . . . . . . . . .
     :------------------------:
     |                        |
     |      Bank #n data      |
     |                        |
     `------------------------'
```

The "master bank" is a bank that contains some common code, and is in charge of loading subsequent banks in process.
Its header also contains a number of all banks in the image; it is either inclusive (accounts a master bank too) or a non-inclusive (only accounts additional banks).

## LZ4 compression

Recent chips have an ability to load an LZ4-compressed bank in order to keep the SPL size small.

One of the annoying features it has is that you can specify an additional dictonary, which is in most cases is the BootROM of the chip itself, meaning that in order to decompress such image, you have to obtain the dump of the BootROM.
It, however, allows to have better compression ratio by referencing common patterns from the dictonary (e.g. the BootROM) instead of storing them in the compressed image itself.

### LZ4 header

The compressed image starts with a header, which is then followed by the raw LZ4 stream.

```c
struct lz4hdr {
	uint32_t	dict_size;	/* Dictonary data size */
	void		*dict_data;	/* Dictonary data pointer */
	void		*temp_data;	/* Temporary load address */
	uint32_t	dec_size;	/* Decompressed data size */
}
```

- u32: Dictonary size
- u32: Dictonary data pointer
- u32: Temporary data buffer (where the compressed image is loaded into for decompression)
- u32: Size of decompressed data


