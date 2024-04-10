# SDFILE / SYDFS

This is a simple "filesystem" that can contain a number of named files, in a flat structure.

## Format

### Flash header

```c
struct sydfs_hdr {
  uint16_t  hdr_crc;    /* Header CRC */
  uint16_t  list_crc;   /* File list CRC */
  uint32_t  info1;
  uint32_t  info2;
  uint32_t  count;      /* File count */
  uint32_t  version1;
  uint32_t  version2;
  uint8_t   chiptype[8];
};
```

- u16: CRC16 of the header
  * Excluding this field
- u16: CRC16 of the file list
  * If the file entries are encrypted, then this means the CRC16 of them **encrypted**, i.e. as they're stored in flash.
- u32: Info 1
  * Usually this is set to the filesystem size
- u32: Info 2
  * 0xFFFFFFFD
- u32: File count
- u32: Version 1
- u32: Version 2
- u8[8]: Chip type

### File header

```c
struct sydfs_ent {
  uint8_t   type;       /* File type */
  uint8_t   resvd;      /* (reserved) */
  uint16_t  data_crc;   /* Data CRC */
  uint32_t  offset;     /* Data offset */
  uint32_t  size;       /* File size */
  uint32_t  index;      /* Index */
  char      name[16];   /* File name */
};
```

- u8: File type
  * _(as per AC69xx or AC5xxx:)_
  * 0 = Undefined
  * 1 = `uboot.boot` ~ Bootloader
  * 2 = `user.app` ~ Application
  * 3 = `cmd_zone`, `__zone2.zon`, `_____.____2` ~ Zones
  * 4 = `sdram.apu` ~ Compressed app
  * 5 = `ver.bin` ~ Version file
  * 6 = `sys.cfg` ~ System config
  * 7 = `spc.aer` ~ Special area
  * 8 = `chip_key.bin` ~ Chip key
- u8: (reserved)
- u16: CRC16 of data
  * Sometimes this is not just the raw CRC16 (e.g. for encrypted firmware regions)
- u32: Data offset
- u32: Data length
- u32: Index
- u8[16]: File name
  * Null-terminated, unless the name is exactly 16 bytes long.
