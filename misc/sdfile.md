# sdfile / sydfs

## Version 1

### Flash header

- u16: CRC16 of the header
  * Excluding this field
- u16: CRC16 of the file list
  * If the file entries are encrypted, then this means the CRC16 of them *unencrypted*
- u32: Info 1
  * Usually this is set to the filesystem size
- u32: Info 2
- u32: File count
- u32: Version 1
- u32: Version 2
- u32: Chip type 1
- u32: Chip type 2

### File header

- u8: File type
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
  * Sometimes this field means the CRC16 of the data being *unencrypted*
- u32: Data offset
- u32: Data length
- u32: Index
- u8[16]: File name
  * Null-terminated, unless the name is exactly 16 bytes long. Longer names are simply truncated.

## Version 2

### Flash header (v2)

- u16: CRC16 of the header
  * Excluding this field
- u16: Burner size
- u8[4]: Version ID (vid)
  * Stored unencrypted
- u32: Flash size
- u8: FS version
  * 0 = BR18
  * 1 = BR22
- u8: "Block align modulus"
- u8: (reserved)
  * Seemingly this is stored unencrypted too.
- u8: Special option flag
- u8[16]: Product ID (pid)
  * Stored unencrypted

### File header

- u16: CRC16 of the header
  * Excluding this field
- u16: CRC16 of data
  * On files that are undefined (variable) this is set to 0xFFFF
  * same deal, sometimes it is not simply a CRC16 of the raw data
- u32: Data offset
- u32: Data length
- u8: Attributes
- u8: (reserved)
- u16: Index
  * A nonzero means that this is the last file entry (or in some cases it probably should be zero instead)
- u8[16]: File name
  * same deal
