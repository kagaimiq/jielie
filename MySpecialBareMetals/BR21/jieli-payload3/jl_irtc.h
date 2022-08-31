#ifndef _JL_IRTC_H
#define _JL_IRTC_H

#include <stdint.h>

/* init */
void irtc_init(void);

/* basic communication */
void irtc_sel(int sel);
uint8_t irtc_xfer(uint8_t val);

/* register comms */
uint8_t irtc_read(int addr);
uint8_t irtc_rsmask(int addr, int shift, uint8_t mask);
void irtc_write(int addr, uint8_t val);
void irtc_wsmask(int addr, int shift, uint8_t mask, uint8_t val);

#endif