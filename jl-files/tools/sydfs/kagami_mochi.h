#ifndef _JL_STUFF_H
#define _JL_STUFF_H

#include <stdint.h>

/* ====== data structures ====== */

/* flash configuration */
struct jl_cfg_flash {
	uint32_t flash_id;		// flash id
	uint32_t flash_size;		// size of flash
	uint32_t flash_file_size;	// ??
	uint32_t syd_head_addr;	// syd header address
	uint32_t spi_run_mode;		// spi mode
	uint32_t spi_div;		// spi clock divider
	uint32_t flash_base;		// base of the user.app
	uint32_t protect_arg;		// ?
	uint32_t cfg_zone_addr;	// address of flash zone config
	uint32_t cfg_zone_size;	// size of flash zone config
};

/* clock config */
struct jl_cfg_clock {
	uint32_t pll_sel;	//
	uint32_t osc_freq;	//
	uint32_t osc_src;	//
	uint32_t osc_hc_en;	//
	uint32_t osc_1pin_en;	//
};

/* sys.cfg file */
struct jl_cfg_file {
	struct jl_cfg_flash flash_cfg;
	struct jl_cfg_clock clock_cfg;
};

/* header of `apu` files (sdram.apu, ui.apu, etc) */
struct jl_apu_header {
	uint32_t unknown1;
	uint32_t unknown2;	// 0x02000000
	uint32_t unknown3;
	uint32_t crypt_blk_size;// 0 - no encryption?, other - size
	uint32_t unknown4;
};

/* originally called `BANKCB`, used in uboot images */
struct jl_bankcb_head {
	uint16_t bank_num;	// bank count <?>
	uint16_t size;		// bank data size
	uint32_t bank_addr;	// bank load adress <?>
	uint32_t data_addr;	// bank data offset in file
	uint16_t data_crc16;	// crc16 of data
	uint16_t head_crc16;	// crc16 of previous 14 bytes
};

/* sydfs header */
struct jl_syd_head {
	uint16_t crc16_head;	// crc16 of next 30 bytes
	uint16_t crc16_list;	// crc16 of file entry list
	uint32_t info1;		// syd end? / header offset? / syd size? | <class+0xa0>
	uint32_t info2;		// <class+0xc8> -- ??
	uint32_t file_count;	// count of files
	uint32_t version1;	// <class+0xc0> -- ??
	uint32_t version2;	// <class+0xbc> -- ??
	uint32_t chiptype1;	// <class+0xc4> -- ??
	uint32_t chiptype2;	// <class+0xb8> -- ??
};

/* sydfs file entry */
struct jl_syd_entry {
	uint8_t file_type;	// file type
	uint8_t resvd;		// reserved
	uint16_t crc16;	// crc16 of file data
	uint32_t addr;		// file address
	uint32_t size;		// file size
	uint32_t num;		// file number
	char name[16];		// zero-terminated file name
};

/* ===== functions ===== */

void jl_crypt(uint8_t *ptr, int len, uint16_t key);
void jl_crypt_dyn(uint8_t *ptr, int len, uint16_t key, int offs);
void jl_crypt_blk(uint8_t *ptr, int len, uint16_t key, int blksize);
uint16_t jl_crc16(uint8_t *data, int len, uint16_t sr);

#endif
