# BR17 firmware structure

**Incomplete yet!**

This describes the structure of a firmare format used for (at least) the BR17, BR20 and BR21 chip families. (AC690x, AC691x and AC692x series resp.)

Note that every "file" is aligned on a 512-byte boundary.

## Top-level structure

```
      .--------------------------.  <==== flash beginning
      | Top-level file list      |---. <- points to the uboot.boot, user.app
      :--------------------------:   |     and another file list
      |                          |   |
      |       "uboot.boot"       |<--| <- contains code to boot into the main application
      |                          |   |        contained in "user.app"
      :--------------------------:   |
  .---|      "_____.____2"       |<--| <- points to the rest
  |   :--------------------------:   |
  |-->|        "ver.bin"         |   |
  |   :--------------------------: <==== there the flash is mapped in the SFC map
  |   |                          |   |
  |   |                          |   |
  |   .                          .   | <- contains the main application code and its
  |-->.        "user.app"        .<--'     data like voice prompts, bluetooth config, etc.
  |   .                          .
  |   |                          |
  |   |                          |
  |   |                          |
  |   :--------------------------:
  |-->|        "sys.cfg"         |
  |   :--------------------------:
  |-->|        "spc.aer"         |
  |   :--------------------------:
  `-->|      "chip_key.bin"      |
      :--------------------------:
      |     BOOT_START_FIRST     |
      :--------------------------:  <==== here the flash image ends
      /                          /
      /                          /
      /                          /
      /                          /
      /                          /
      /                          /
      /                          /
      /                          /
             VMIF, BTIF, etc.

   * not really to scale
```

### Top-level file list

The flash begins with 128 bytes of some "garbage", which is, in fact, four 32-byte blocks encrypted with a simple LFSR-based stream cipher algorithm used by the [ENC](/ip/enc.md) block.
The key used is 0xFFFF, which is really used in all chunks encrypted with this method (except the main "user.app" block, more on that later.)

```
00000000  34 be 62 24 1f 8e 7a f8  0d 3e 5c 98 cd bd 5b 97  |4.b$..z..>\...[.|
00000010  0f 1e 3c 78 d1 83 27 4e  84 19 e3 24 46 99 30 60  |..<x..'N...$F.0`|
00000020  fe df 3e 47 1f 3c 7c f8  a0 06 a3 67 ce bd 5b 97  |..>G.<|....g..[.|
00000030  7a 7c 53 17 a5 ad 45 21  f3 6d 13 26 4c 98 30 60  |z|S...E!.m.&L.0`|
00000040  fc df 3e 60 1f ee 7c f8  f0 c3 a3 67 cf bd 5b 97  |..>`..|....g..[.|
00000050  50 41 63 27 8e ad 78 11  c3 46 21 26 4c 98 30 60  |PAc'..x..F!&L.0`|
00000060  fd df d1 1f 3f e9 7c f8  f0 17 a6 67 cc bd 5b 97  |....?.|....g..[.|
00000070  7a 6d 59 0a ff e2 57 3e  9c 19 13 26 4c 98 30 60  |zmY...W>...&L.0`|
00000080  70 64 63 3a 00 00 00 00  00 00 00 00 00 00 00 00  |pdc:............|
00000090  70 64 6e 3a 6a 6c 5f 36  39 30 78 00 00 00 00 00  |pdn:jl_690x.....|
000000a0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
000000b0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
000000c0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
000000d0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
000000e0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
000000f0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
```

- `uboot.boot` (type 0x01) - the second-stage bootloder
- `_____.____2` (type 0x03) - the additional file list
- `user.app` (type 0x02) - the main app area itself

You might've noticed two 16-byte lines after these 128 bytes, what those are?

The first one, which starts with `pdc:` is followed by a byte, whose value is set to the value of the `UPVR_CTL` parameter in the ISD config.
That parameter by itself has two possible values: 0 or 1, thus there it will also have a value of 0x00 or 0x01.

The second one, which starts with `pdn:` is followed with a string, which is the one specified in the `PDCTNAME` parameter from the same ISD config, although it's converted to lowercase first.
Usually nobody changes the default value, so this field has something like `jl_690x` or `jl_692x` in it.

### Additional file list

The `_____.____2` file contains additional file entries that were not listed in top-level file list.

```
0000d000  05 00 46 8d 00 d2 00 00  14 05 00 00 00 00 00 00  |..F.............|
0000d010  76 65 72 2e 62 69 6e 00  00 00 00 00 00 00 00 00  |ver.bin.........|
0000d020  02 00 4e 00 20 d7 00 00  00 d6 05 00 01 00 00 00  |..N. ...........|
0000d030  75 73 65 72 2e 61 70 70  00 00 00 00 00 00 00 00  |user.app........|
0000d040  06 00 0f 9c 20 ad 06 00  44 00 00 00 02 00 00 00  |.... ...D.......|
0000d050  73 79 73 2e 63 66 67 00  00 00 00 00 00 00 00 00  |sys.cfg.........|
0000d060  07 00 49 9e 80 ad 06 00  30 00 00 00 03 00 00 00  |..I.....0.......|
0000d070  73 70 63 2e 61 65 72 00  00 00 00 00 00 00 00 00  |spc.aer.........|
0000d080  08 00 c5 5d c0 ad 06 00  20 00 00 00 04 00 00 00  |...].... .......|
0000d090  63 68 69 70 5f 6b 65 79  2e 62 69 6e 00 00 00 00  |chip_key.bin....|
0000d0a0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0000d0b0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0000d0c0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0000d0d0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0000d0e0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0000d0f0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
```

The files listed there are:
 - `ver.bin` (type 0x05) - contains the version info of the libraries linked with the main app
 - `user.app` (type 0x02) - the main app area itself (once again)
 - `sys.cfg` (type 0x06) - system configuration
 - `spc.aer` (type 0x07) - special area definition
 - `chip_key.bin` (type 0x08) - the obfuscated copy of the chipkey used to encrypt the main app area (how lame!)

### uboot.boot

### ver.bin

### user.app

### sys.cfg

### spc.aer

```
0006ad80  50 52 43 54 00 00 00 00  00 b0 06 00 02 ff af c2  |PRCT............|
0006ad90  42 54 49 46 00 f0 06 00  00 10 00 00 00 ff 00 6a  |BTIF...........j|
0006ada0  56 4d 49 46 00 00 07 00  00 00 01 00 01 ff ba 1b  |VMIF............|
```

### chip_key.bin

This file contains the obfuscated copy of the chipkey used to encrypt the main app area.

```
0006adc0  3a cc b5 50 f0 6e c9 65  f7 be e3 38 60 1e 2e 51  |:..P.n.e...8`..Q|
0006add0  8b a3 48 1b 1f de 8b d2  69 64 62 47 e2 72 21 ac  |..H.....idbG.r!.|
0006ade0  c5 5d 13 92 65 36 73 42  01 00 00 08 00 00 00 00  |.]..e6sB........|
0006adf0  41 43 36 39 30 58 00 01  00 00 00 00 00 00 00 00  |AC690X..........|
```

Actually, despite it's being reported as being 32 bytes long, it's actually 64 bytes long.

### BOOT_START_FIRST
