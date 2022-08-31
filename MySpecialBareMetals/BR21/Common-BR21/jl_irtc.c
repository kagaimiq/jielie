#include "jl_regs.h"
#include "jl_irtc.h"

void irtc_init(void) {
	reg32_wsmask(IRTC_BASE+IRTC_CON_BAUD, 3);
}


void irtc_sel(int sel) {
	reg32_wsmask(IRTC_BASE+IRTC_CON_RTCCS, !!sel);
}

uint8_t irtc_xfer(uint8_t val) {
	reg32_write(IRTC_BASE+IRTC_DAT, val);
	reg32_wsmask(IRTC_BASE+IRTC_CON_STRAN, 1);
	while (reg32_rsmask(IRTC_BASE+IRTC_CON_BUSY));
	return reg32_read(IRTC_BASE+IRTC_DAT);
}


uint8_t irtc_read(int addr) {
	uint8_t val;

	irtc_sel(1);
	irtc_xfer(0x80|0x20|(addr&0xf));
	val = irtc_xfer(0);
	irtc_sel(0);

	return val;
}

uint8_t irtc_rsmask(int addr, int shift, uint8_t mask) {
	return (irtc_read(addr) >> shift) & mask;
}

void irtc_write(int addr, uint8_t val) {
	irtc_sel(1);
	irtc_xfer(0x00|0x20|(addr&0xf));
	irtc_xfer(val);
	irtc_sel(0);
}

void irtc_wsmask(int addr, int shift, uint8_t mask, uint8_t val) {
	irtc_write(addr, (irtc_read(addr) & ~(mask << shift)) | ((val & mask) << shift));
}

