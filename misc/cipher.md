# JieLi cipher

The chips and related tools use a number of cipher/obfuscation techinques in order to hide something.

## "ENC" chiper

The cipher used by the [ENC](../periph/enc.md) periperal is of a simple stream chiper type, that basically uses the CRC16-CCITT shift register logic (with a polynomial x16+x12+x5+1 aka 0x1021) as the LFSR logic.

Each byte is XOR-ed with the low bits of the register (initialized with the "key" value, which is 16 bits long), and then the register is updated with the aforementioned LFSR logic.

Here's an example C snippet:
```c
uint16_t jl_enc_cipher(uint8_t *data, int len, uint16_t key) {
	while (len--) {
		*data++ ^= key;
		key = (key << 1) ^ (key >> 15 ? 0x1021 : 0);
	}
	return key;
}
```

## "CrcDecode" cipher

This cipher method was used first to scramble the chip key returned by the USB loader's "get chip key" command, but now it is also used to scramble the loader binaries for the aforementioned USB or UART bootloaders.

For its entropy it uses a CRC16 calculation against a magic byte array, with its initial CRC value derived from a CRC calculation of the upper 16 bits of the key (in little endian), which is in turn has been initialized to the lower 16 bits of the key.

The key itself seems to be always 0xFFFFFFFF (at least, I haven't see anything else being used, and the `CrcDecode` function from the ROM etc. is hardcoded to use this key anyway)

The magic array it uses has the following contents: `C3 CF C0 E8 CE D2 B0 AE C4 E3 A3 AC D3 F1 C1 D6`, which is in fact a string "孟黎我爱你，玉林" encoded with GB2312.

It is indexed by the current byte index modulo the size of the magic array (that is 16 bytes), and then the byte is XORed with the low byte of the current CRC.

Here's an example C snippet:
```c
/* replace this with a proper implementation */
static uint16_t crc16(uint8_t val, uint16_t crc) {
	crc ^= val << 8;
	for (int i = 0; i < 8; i++)
		crc = (crc << 1) ^ (crc >> 15 ? 0x1021 : 0);
	return crc;
}

void jl_crc_cipher(uint8_t *data, int len, uint32_t key) {
	static const uint8_t magic[16] = { 0xC3,0xCF,0xC0,0xE8,0xCE,0xD2,0xB0,0xAE,0xC4,0xE3,0xA3,0xAC,0xD3,0xF1,0xC1,0xD6 };

	/* initial CRC value */
	uint16_t crc = key;
	crc = crc16(key >> 16, crc);
	crc = crc16(key >> 24, crc);

	/* go scrambling */
	for (int i = 0; i < len; i++) {
		crc = crc16(magic[i % sizeof magic], crc);
		data[i] ^= crc;
	}
}
```

## "RxGp" cipher

This cipher method has been found to be used to scramble the USB loader of the DV15 chip family, with the UBOOT1.00 bootloader in the chip having a special command that can descramble the contents using this cipher.

Basically it uses a pseudorandom number generator as its entropy source, which is initialized to the value of 0x70477852 (that can be decoded as "RxGp", which is why I gave it that name), then for each byte it's updated and the byte is XORed with the low 8 bits of the register.

In terms of the C code, this is implemented like this:
```c
void jl_rxgp_cipher(uint8_t *data, int len) {
	uint32_t rng = 0x70477852;	/* "RxGp" */
	while (len--) {
		rng = (rng * 16807) + (rng / 127773) * -0x7fffffff;
		*data++ ^= rng;
	}
}
```

## AES cipher

Apart from all of these simple scrambling techniques described above, they've been also using the proper encryption algorithm, in particular the AES one.

It is used in the AC209/AC309N BSP files, and in the key files (containing the chipkey).

