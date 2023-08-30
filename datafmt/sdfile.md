# sdfile / sydfs

The "sydfs", "sdfile" (and maybe "jlfs" too) is a simple "filesystem" ...

## Version 1

First present in the "fw" files from the AC209N era, then used as the flash format until BR22 or so.

### Flash header

Originally this was intended as the actual flash header (i.e. the first 32 bytes in the flash), but as it also carries
the important metadata (that is, the file count) this is really can be considered as the fs header instead.

Although sometimes you don't have to do this but that's an exception rather than a rule.

- u16: CRC16 of the header
  * Excluding this field
- u16: CRC16 of the file list
  * If the file entries are encrypted, then this means the CRC16 of them **encrypted**
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
  * Sometimes this isn't quite simply a CRC16 of the contents
- u32: Data offset
- u32: Data length
- u32: Index
- u8[16]: File name
  * Null-terminated, unless the name is exactly 16 bytes long.

## Version 2

This version added support for directories, and changed the file enumeration method, meaning that carrying the flash header now wasn't needed.

### Flash header (v2)

- u16: CRC16 of the header
  * Excluding this field
- u16: Burner size
- u8[4]: Version ID (vid)
  * Appears as unencrypted
    If the header is encrypted, then this is stored encrypted in the raw form
    so that after the final encryption this will eventually decrypt and appear as if it wasn't encrypted,
    but moretheless, the header's CRC16 will be still correct, while doing that after encryption
    could render in a bad CRC16 instead.
- u32: Flash size
- u8: FS version
  * 0 = BR18
  * 1 = BR22
- u8: Block alignment ("block align modulus")
  * In 256-byte units
- u8: (reserved)
  * Usually appears as unencrypted, see above
    The procedure maybe is that first the buffer that holds this header is filled with 0xFF,
    then the vid/pid fields are filled out, then it gets encrypted,
    then other fields are filled in and finally it's "decrypted" back and written into the image.
- u8: Special option flag
- u8[16]: Product ID (pid)
  * Appears as unencrypted, see above

### File header

- u16: CRC16 of the header
  * Excluding this field, of course
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
