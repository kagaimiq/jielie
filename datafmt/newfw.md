# New Firmware Format

## General layout

Example of a layout for bluetooth audio chips e.g. BR23/BR25/BR28/etc.:

```
     .-----------------------. <-- may start at offsets 0x0000 or 0x1000
     |     Flash header      |
     :-----------------------:
 .---|  Top-level file list  | <-- Files used by the ROM bootloader and uboot.boot
 |   :-----------------------:
 |   |                       |
 |   |                       |
 |-->|     "uboot.boot"      | <-- The second-stage bootloader
 |   |                       |
 |   |                       |
 |   :-----------------------:
 |-->|   "isd_config.ini"    | <-- configuration data specified in the
 |   '-----------------------'     [SYS_CFG_PARAM] section of actual isd_config.ini
 |   .                       .
 |   .-----------------------. <=== mapped to the memory map at 0x1E00000
 |   |                       |       ** Application data area **
 |-->|                       |     .------------------------.
 |   |                       |     |    "app_area_head"     |  <-- offset field contains
 |   |                       |     '----.-------------------'-.        the entry point address
 |   |                       |          |  file list..        |---.
 |   |                       |          :---------------------:   |
 |   |                       |  .-------| Special area list   |   |
 |   |                       |  |       :---------------------:   |
 |   |                       |  |       |                     |   |
 |   |                       |  |       |                     |<--|
 |   |                       |  |       |                     |   |
 |   |                       |  |       |      "app.bin"      |   |
 |   |                       |  |       |                     |   |
 |   |                       |  |       |                     |   |
 |   |                       |  |       |                     |   |
 |   |                       |  |       :---------------------:   |
 |   |                       |  |       |   "cfg_tool.bin"    |<--|
 |   |                       |  |       :---------------------:   |
 |   |     "app_dir_head"    |  |                .....          <-'
 |   |                       |  |  .------------------------.
 |   |                       |  |  |     "EXT_RESERVED"     |
 |   |                       |  |  '----.-------------------'-.
 |   |                       |  |       | Additional reserved |
 |   |                       |  |-------|   area list         |
 |   |                       |  |       '---------------------'
 |   |                       |  |    ** Resource data area **
 |   |                       |  |  .------------------------.
 |   |                       |  |  |        "tone"          |
 |   |                       |  |  '----.-------------------'-.
 |   |                       |  |       |  file list..        |---.
 |   |                       |  |       :---------------------:   |
 |   |                       |  |       |     "tone.idx"      |<--|
 |   |                       |  |       :---------------------:   |
 |   |                       |  |       |                     |   |
 |   |                       |  |       |   "bt_conn.wtg"     | <-|
 |   |                       |  |       |   "bt_dconn.wtg"    | <-|
 |   |                       |  |       |   "low_power.mp3"   | <-|
 |   |                       |  |       |   "power_off.mp3"   | <-|
 |   |                       |  |       |        ....         | <-'
 |   |                       |  |       |                     |
 |   |                       |  |       |                     |
 |   |                       |  |       '---------------------'
 |   |                       |  |   ....
 |   '-----------------------'  |
 |   .                       .  |
 |   .                       .  |
 |   .                       .  |
 |   .                       .  |
 |   .-----------------------.  |
 |   |        "VM"           |<-|
 |   |                       |  |
 |   :-----------------------:  |
 |   |       "BTIF"          |<-|
 |   :-----------------------:  |
 |            .....           <-'
 |   .-----------------------.
 '-->|      "key_mac"        |
     '-----------------------'

```

## Details

The firmware header usually starts at offset 0x0000, but sometimes it starts at offset 0x1000 (seems to be influenced by the `NEED_RESERVED_4K` option of isd_config.ini).

It starts with a [flash header](jlfs.md#flash-header), which is then followed by the top-level file list entries describing the `uboot.boot`, `isd_config.ini`, `app_dir_head` and possibly something else, like `key_mac`.

### uboot.boot

This is a second stage bootloader that is in charge of setting up hardware according to `isd_config.ini`, and then finally entering the main code contained inside `app_dir_head`.

It is stored in a usual [BANKCB](bankcb.md) format, however if the 6th bit (0x40) is set in the flags field of the file header, the contents are [compressed with LZ4](bankcb.md#lz4-compression).

### isd_config.ini

This file contains the configuration options that were specified in the `[SYS_CFG_PARAM]` section of the actual isd_config.ini.

Each entry starts with a byte that specifies the size of parameter data this entry carries, then it's followed by the null-terminated string containing the key, finally followed by the parameter data itself.

In case a pure numeric value has been specified as a parameter, it is going to be exported there in a form of a 32-bit integer in little-endian byte ordering.

Note that the key and parameter strings are converted to uppercase by isd_download.

### tone.idx

This seems to be used for the actual indexing of the tone files (instead of referring to them by their file names), this file contains indexes of tone files in the `tone` directory along with its actual name. (but that is just a guess right now.)

```
54 49 44 58   <= Signature "TIDX"

D4 5B    <= CRC16 of the following 10 bytes:
  FF FF FF FF FF FF  <= Filler bytes
  08 00 00 00        <= Number of entries below:

--------------------------------------------------

F6 20   07   01   62 74 00                       "bt"
4A 01   0C   02   62 74 5F 63 6F 6E 6E 00        "bt_conn"
D6 F0   0D   03   62 74 5F 64 63 6F 6E 6E 00     "bt_dconn"
E2 AE   0E   04   6C 6F 77 5F 70 6F 77 65 72 00  "low_power"
AD 20   0E   05   70 6F 77 65 72 5F 6F 66 66 00  "power_off"
C7 6C   0B   06   6C 69 6E 65 69 6E 00           "linein"
98 25   0A   07   6D 75 73 69 63 00              "music"
66 64   07   08   70 63 00                       "pc"
\___/   \/   \/   \____________________________/
 (1)    (2)  (3)               (4)

1.  CRC16 of the whole entry excluding this field
2.  Size of the whole entry
3.  File index in the tone directory (0 is usually the tone.idx file itself)
4.  Tone name (null terminated)

```
