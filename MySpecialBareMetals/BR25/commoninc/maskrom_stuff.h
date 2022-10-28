#ifndef _MASKROM_STUFF_H
#define _MASKROM_STUFF_H

#include <stdint.h>

//--------------------------------

void local_irq_enable(void);
void local_irq_disable(void);

//--------------------------------

void p33_buf(uint8_t val);
void p33_xor_1byte(uint16_t addr, uint8_t val);
void p33_and_1byte(uint16_t addr, uint8_t val);
void p33_or_1byte(uint16_t addr, uint8_t val);
void p33_tx_1byte(uint16_t addr, uint8_t val);
uint8_t p33_rx_1byte(uint16_t addr);
void P33_CON_SET(uint16_t addr, int shift, int bits, uint8_t val);

//--------------------------------

void sfc_suspend(int en_spi);
void sfc_resume(int dis_spi);
void sfc_drop_cache(uint32_t addr, int len);

//--------------------------------

uint16_t chip_crc16(void *ptr, int len);

/* essentially:
 * ----------------------------------------------------------------------
 * 	void CrcDecode(uint8_t *buff, int len) {
 * 		uint16_t crc = 0xffff;
 * 
 * 		// meng li i love you, julin
 * 		static const uint8_t magic[16] = {
 * 			0xc3,0xcf,0xc0,0xe8,
 * 			0xce,0xd2,0xb0,0xae,
 * 			0xc4,0xe3,0xa3,0xac,
 * 			0xd3,0xf1,0xc1,0xd6
 *		};
 * 
 * 		for (int i = 0; len > 0; len--, i++) {
 * 			// calculate crc16 of the array's byte
 *			crc ^= magic[i % sizeof(magic)] << 8;
 * 			for (int j = 0; j < 8; j++)
 * 				crc = (crc << 1) ^ (crc >> 15 ? 0x1021 : 0);
 * 
 * 			*buff++ ^= crc;
 * 		}
 * 	}
 */
void CrcDecode(uint8_t *buff, int len);

void wdt_clr(void);

void nvram_set_boot_state(int state);

void chip_reset(void);

/* essentially:
 * ----------------------------------------------------------------------
 * 	void doe(uint16_t key, uint8_t *buff, int len, uint32_t addr) {
 * 		while (len--) {
 * 			*buff++ ^= key ^ (addr >> 2);
 * 			key = (key << 1) ^ (key >> 15 ? 0x1021 : 0);
 * 		}
 * 	}
 */
void doe(uint16_t key, uint8_t *buff, int len, uint32_t addr);

//--------------------------------

// see https://github.com/lz4/lz4/blob/dev/lib/lz4.h

int LZ4_setStreamDecode(void *stream,
			const char *dictionary, int dictSize);

int LZ4_decompress_safe_continue(void *stream,
				 const char *src, char *dst,
				 int srcSize, int dstCapacity);

//int LZ4_decompress_generic(...);

int LZ4_decompress_safe_usingDict(const char *src, char *dst,
				  int srcSize, int dstCapacity,
				  const char *dictStart, int dictSize);

//--------------------------------

#endif