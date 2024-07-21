# BANKCB

BANKCB (probably: BANKed Code Block(s)) is used to store banked code, for example in the early chip series like [AC410N](../chips/cd03/index.md#ac410n) or in 8051-based chips like [SH50](../chips/sh50/index.md), etc.

This format is also used in chip series that inherently have access to a relatively huge memory storage such as a memory mapped SPI flash or some kind of SDRAM.
In these cases it is used to store the second stange bootloader (`uboot.boot`) which is used to initialize such memories and finally handle over execution to code contained there.

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

- u16: Bank number, or bank count for a master bank.
- u16: Bank size
- u32: Bank load address
- u32: Bank data offset
- u16: Data CRC
- u16: Header CRC (of the previous 14 bytes)

### Layout

All bank headers are stored at the beginning of an image, then the individual bank's data follow.

If the image is scrambled, then each header and data portion is scrambled individually.

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

The "master bank" contains common code, usually with the code that loads subsequent banks in process.
Its header's "index" field contains count of all banks in the image.
It is usually inclusive (i.e. the master bank is included in the count), but sometimes it's exclusive (i.e. only the additional banks are counted).
The latter can be observed within SH50 series.

## LZ4 compression

Recent chips usually have the `uboot.boot`'s contents compressed with LZ4 in order to keep its size on flash small.

One of the annoying features it has is that you can specify an additional dictionary, which is in most cases is the BootROM of the chip itself, meaning that in order to decompress such image, you have to obtain the dump of the BootROM.

### LZ4 header

The compressed image starts with a header, which is then followed by the raw LZ4 stream.

```c
struct lz4hdr {
	uint32_t	dict_size;	/* Dictionary data size */
	void		*dict_data;	/* Dictionary data pointer */
	void		*temp_data;	/* Temporary load address */
	uint32_t	dec_size;	/* Decompressed data size */
}
```

- u32: Dictionary size
- u32: Dictionary data pointer
- u32: Temporary data buffer (where the compressed image is loaded into for decompression)
- u32: Size of the decompressed data
