# JLFS

## Format

### Flash header

Unlike its predecessor, the [SDFILE](sdfile.md), the flash header now is only present in the beginning of a flash image, rather than being a header for each filesystem image as in the former case.

```c
struct jlfs2_flash_header {
  uint16_t  hdr_crc;      /* Header CRC */
  uint16_t  burner_size;  /* Burner size */
  char      vid[4];       /* Version ID */
  uint32_t  flash_size;   /* Flash size */
  uint8_t   fs_ver;       /* FS version */
  uint8_t   block_align;  /* Block alignment */
  uint8_t   resvd;        /* (reserved) */
  uint8_t   special_opt;  /* Special option flag */
  char      pid[16];      /* Product ID */
};
```

- u16: CRC16 of the header
  * Excluding this field
- u16: Burner size
- u8[4]: Version ID (vid)
  * Appears as unencrypted, see below
- u32: Flash size
- u8: FS version
  * 0x00 = BR18
  * 0x01 = BR22
  * 0x02 = BR23?
  * 0x03 = BR25?
- u8: Block alignment ("block align modulus")
  * In 256-byte units
- u8: (reserved)
- u8: Special option flag
- u8[16]: Product ID (pid)
  * Appears as unencrypted, see below

When this header is put into the flash image, it is usually stored in encrypted form, however, some fields actually appear as unencrypted in the final image, while the header CRC still being correct.

Presumeably, this is done as follows:
 - First, the buffer which contains the flash header is filled with 0xFF (the contents of erased flash bits)
 - Fields such as vid or pid are filled in immediately
 - Then, the whole header gets "encrypted" and the rest of the fields are populated, including the header CRC
 - Finally, the header is "decrypted" back and now there are encrypted header contents next to the fields that appear unencrypted.

### File header

```c
struct jlfs2_file_entry {
  uint16_t  hdr_crc;  /* Header CRC */
  uint16_t  data_crc; /* Data CRC */
  uint32_t  offset;   /* Data offset */
  uint32_t  size;     /* Size */
  uint8_t   attr;     /* Attributes */
  uint8_t   resvd;    /* (reserved) -- or not quite */
  uint16_t  index;    /* Index */
  char      name[16]; /* File name */
};
```

- u16: CRC16 of the header
  * Excluding this field, of course
- u16: CRC16 of data
  * On files that are undefined (variable) this is set to 0xFFFF
- u32: Data offset
- u32: Data length
  * In some cases (e.g. in the `app_dir_head` entry) the size is set to 0xFFFFFFFF, which means undefined..
- u8: Attributes
  * presumeably:
  * bit0-3 = type: 0 = `uboot.boot`, 1 = `app_dir_head`, 2 = file, 3 = directory ...
  * bit4 = absolute address? special area entry? (used in the latter, also in `key_mac`, as well for the `EXT_RESERVED` directory containing additional special area definitions)
  * bit5 = ?
  * bit6 = `uboot.boot` is compressed
  * bit7 = ? set within/for `app_dir_head`
- u8: (reserved) - or not?
- u16: Index
  * A nonzero means that this is the last file entry
  * Presumeably at some point this field contained remaining file entry count, thus a zero meant that this was the last entry.
  * Well sometimes this is done the other way - this is the 'index' field until the last entry which has a '0' index.. weird
- u8[16]: File name
  * Null terminated

Unlike SDFILE, the file entries contain the 'index' field which can indicate whether it is the last file in the list or not, as well as having the header's CRC field, thus completely eliminating need for a global header as a such. (in SDFILE, the header contains file count and a CRC of all file entries)

## Layout

A typical layout has a block of file headers followed by the data for each file, like so:

```
    .------------------------.
    |  File A header         |  <=== index is zero
    :------------------------:
    |  File B header         |
    :------------------------:
    |  File C header         |
    :------------------------:
    .                        .
    .                        .
    :------------------------:
    |  File X header         |  <=== index is nonzero
    :------------------------:
    |                        |
    |  File A data           |
    |                        |
    :------------------------:
    |                        |
    |  File B data           |
    |                        |
    :------------------------:
    .                        .
    .                        .
    :------------------------:
    |                        |
    |  File X data           |
    |                        |
    '------------------------'
```

However, in some cases, like in the SFC map area, file headers and their data are interleaved like so:

```
    .------------------------.
    |  File A header         |  <=== index is zero
    :------------------------:
    |                        |
    |  File A data           |
    |                        |
    :------------------------:
    |  File B header         |
    :------------------------:
    |                        |
    |  File B data           |
    |                        |
    :------------------------:
    |  File C header         |
    :------------------------:
    .                        .
    .                        .
    :------------------------:
    |  File X header         |  <=== index is nonzero
    :------------------------:
    |                        |
    |  File X data           |
    |                        |
    '------------------------'
```

Moreover, the data are addressed relative to the location of the file header, rather than the beginning of a whole image, and the size field contains size of both the file header and its data, effectively indicating the size of the whole 'image'.
If this is a directory entry, then the files within such an entry (laid in a usual way now) are addressed relative to the directory's entry header as well.

This approach allows to easily construct an image simply by concatenating several images together, without any need to reconstruct the whole image.
