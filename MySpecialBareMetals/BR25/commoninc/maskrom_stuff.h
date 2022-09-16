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

void CrcDecode(void *ptr, int len);

void wdt_clr(void);

void nvram_set_boot_state(int state);

void chip_reset(void);

void doe(uint16_t key, void *ptr, int len, uint32_t addr);

//--------------------------------

void JL_LZ_StateSetup(void *state, void *dict_ptr, int dict_len);
int JL_LZ_Decompress(void *state, const void *in, void *out, int in_len);
uint32_t JL_LZ_Export174(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3);
uint32_t JL_LZ_Export175(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3);

//--------------------------------

#endif