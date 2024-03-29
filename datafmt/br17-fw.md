# BR17 firmware structure

**Almost competed!**

This describes the structure of a firmware format used for (at least) the BR17, BR20 and BR21 chip families. (AC690x, AC691x and AC692x series resp.)

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

So, when decrypted the contents reveal this:

```
AC690N    18 00 F0 02 0A 01 00 00
AC691N    18 00 F0 02 0A 01 00 00
AC692N    18 00 F0 0A 0A 01 00 00
```


- `uboot.boot` (type 0x01) - the second-stage bootloder
- `_____.____2` (type 0x03) - the additional file list
- `user.app` (type 0x02) - the main app area itself

#### pdc/pdn

You might've noticed two 16-byte lines after these 128 bytes, what they are?

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
 - `ver.bin` (type 0x05) - contains version info of libraries linked with the main app
 - `user.app` (type 0x02) - the main app area itself (once again)
 - `sys.cfg` (type 0x06) - system configuration
 - `spc.aer` (type 0x07) - special area definition
 - `chip_key.bin` (type 0x08) - obfuscated copy of a chipkey used to encrypt the main app area (how lame!)

### uboot.boot

This file contains the second-stage bootloader, which is stored in an encrypted [BANKCB](bankcb.md) format.

Actually, there are *two* BANKCB blobs, which are located next to each other.
The first one is loaded by the Boot ROM, which then chainloads the second one and runs it.

Even if the second blob's load address claims to be 0x01000000 or something like that,
actually it is loaded next to the first blob.
So if the first blob's load address is 0x2000 and size is 0x260, then the second blob is loaded at address 0x2260.

### ver.bin

This contains version info of libraries linked with the main app.

```
0000d200  2f 00 00 00 76 65 72 73  69 6f 6e 5f 73 74 61 72  |/...version_star|
0000d210  74 00 15 00 00 00 73 6f  75 6e 64 62 6f 78 5f 73  |t.....soundbox_s|
0000d220  64 6b 5f 76 32 2d 30 2d  39 00 0a 11 00 00 00 1e  |dk_v2-0-9.......|
0000d230  db d3 02 72 74 6f 73 5f  76 32 2d 30 2d 32 00 0a  |...rtos_v2-0-2..|
0000d240  10 00 00 00 1d db d3 02  6d 65 6d 5f 76 32 2d 30  |........mem_v2-0|
0000d250  2d 32 00 0a 0f 00 00 00  1e db d3 02 62 74 5f 76  |-2..........bt_v|
0000d260  32 2d 30 2d 38 00 0a 10  00 00 00 1e db d3 02 64  |2-0-8..........d|
0000d270  61 63 5f 76 32 2d 30 2d  34 00 0a 10 00 00 00 1d  |ac_v2-0-4.......|
0000d280  db d3 02 61 65 63 5f 76  32 2d 30 2d 34 00 0a 10  |...aec_v2-0-4...|
0000d290  00 00 00 1d db d3 02 64  65 63 5f 76 32 2d 30 2d  |.......dec_v2-0-|
0000d2a0  34 00 0a 10 00 00 00 1e  db d3 02 64 6d 67 5f 76  |4..........dmg_v|
0000d2b0  32 2d 30 2d 34 00 0a 10  00 00 00 1d db d3 02 66  |2-0-4..........f|
0000d2c0  61 74 5f 76 32 2d 30 2d  34 00 0a 11 00 00 00 1d  |at_v2-0-4.......|
0000d2d0  db d3 02 73 79 64 66 5f  76 32 2d 30 2d 32 00 0a  |...sydf_v2-0-2..|
0000d2e0  0f 00 00 00 1e db d3 02  76 6d 5f 76 32 2d 30 2d  |........vm_v2-0-|
0000d2f0  32 00 0a 10 00 00 00 1d  db d3 02 75 73 62 5f 76  |2..........usb_v|
          ...
```

### user.app

This is where the main app lives in, along with its resources.

This area is exposed into the CPU's memory map via [SFC](../ip/sfc.md), and it is encrypted.
The encryption key depends on the chipkey that's burned into the chip, although in this case it's  actually derived from the `chip_key.bin` file, chipkey readout from the chip is done in order to check if they match or not..

If this area is decrypted, then the following structure can be observed:

```
   .------------------------.   <==== mapped at address 0x01000000
   |                        |
   |                        |
   |                        |
   |                        |
   |                        |
   .       "sdram.app"      . 
   .        "sdk.app"       .
   .                        .
   |                        |
   |                        |
   |                        |
   |                        |
   |                        |
   :------------------------:
   .                        .
   .                        .
   .                        .
   .                        .
   :------------------------:   <==== pointed there by sys.cfg
   |     File list          |
   `------------------------'

```

The code file (`sdram.app`, `sdk.app`, or something else, perhaps) is always the first file and comes immediatly at the beginning, as the execution starts from address 0x01000000, where the user.app is mapped to.
Thus, the file list is located at the very end of the area, so in order to know where it is located, you need to look into `sys.cfg` first.

The file list is once again an sydfs, although its header and file entries are not encrypted since it is already located in an encrypted area.

Typical files found here:
 - `sdram.app`, `sdk.app`, etc. - the main code - should be the first one
 - `bt_cfg.bin`, `ac691x_cfg.bin`, etc. - the [bluetooth/SDK config](sdkcfg.md) file, contains stuff like bluetooth device names, power level and few other things
 - `bt_conn.mp3`, `power_on.mp3`, `music.mp3`, etc. - the voice/sound/audio/whatever prompts
 - `fast_run.bin` - a piece code loaded into RAM1 in order to do the bare minimum to run the main code when returning from deep sleep (present only on AC690N, as far as I can tell)
 - `f_ascii_s.pix`, `f_gb2312_s.pix`, `f_gb2312.tab`, etc. - the UI font files
 - `menu.res`, `ui_sty.sty` - the UI resource/style files

### sys.cfg

This file contains some system configuration stuff like flash SPI config, clock config, etc.

```
0006ad20  74 e8 f1 c3 a7 4e b5 5b  97 9e 5a b8 70 15 87 25  |t....N.[..Z.p..%|
0006ad30  40 35 28 71 c2 86 2d 5a  b5 fd 54 a8 71 c3 a7 4e  |@5(q..-Z..T.q..N|
0006ad40  1c 2e d4 83 17 4e bd 5b  97 2e 5c b8 70 d6 ae a0  |.....N.[..\.p...|
0006ad50  42 a5 4a b5 4a b7 4f 9e  3d 59 b2 64 e9 03 c1 8e  |B.J.J.O.=Y.d....|
0006ad60  64 d8 b0 43 ff ff ff ff  ff ff ff ff ff ff ff ff  |d..C............|
0006ad70  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
```

An important thing to notice is that this file is also stored encrypted, and the "encryption state" actually follows the `user.app`, described above. Thus in order to decrypt sys.cfg you should know the chipkey and know how big user.app is..

### spc.aer

This file contains definition of some special areas like the protected code region (`PRCT`), `BTIF`, the VM area (`VMIF`), and sometimes something else, like `WTIF`.

Typically in a AC690X/AC691X firmware you can see something like this:

```
0006ad80  50 52 43 54 00 00 00 00  00 b0 06 00 02 ff af c2  |PRCT............|
0006ad90  42 54 49 46 00 f0 06 00  00 10 00 00 00 ff 00 6a  |BTIF...........j|
0006ada0  56 4d 49 46 00 00 07 00  00 00 01 00 01 ff ba 1b  |VMIF............|
```

In a AC692X fimware you might see something like this instead:

```
00070020  50 52 43 54 00 00 00 00  00 10 07 00 02 ff 7f 9e  |PRCT............|
00070030  42 54 49 46 00 40 07 00  00 10 00 00 01 ff 52 55  |BTIF.@........RU|
00070040  56 4d 49 46 00 50 07 00  00 a0 00 00 01 ff 4d 4b  |VMIF.P........MK|
00070050  57 54 49 46 46 45 4e 44  00 10 00 00 01 ff fb d0  |WTIFFEND........|
```

Each entry is 16 bytes long and contain information about the region name, its offset and size, the option flag and the CRC16 of the entry itself.

 - u8[4]: Entry name
 - u32: Offset
   * 0x444E4546 (`FEND`) implies the address near the flash end, perhaps (minus the size of the region)
 - u32: Size
 - u8: Option flag
   * 0 = Erase area
   * 1 = Keep as-is
   * 2 = Protect area
 - u8: (reserved)
 - u16: CRC16 of the previous 14 bytes

I believe the "option flag" is used in the firmware update process (via a USB stick or SD card, via BFU files) in order to decide what to do with this area, e.g. in order to erase the VM, or something like that.

Common regions are:
 - `PRCT` - Protect region, usually covers the entire flash image, and has a "protect area" option on it.
 - `BTIF` - Something Bluetooth related
 - `VMIF` - [VM region](vm.md)
 - `WTIF` - Something else related

These regions are configured in the `SPECIAL_AREA_[START|END]` block in the ISD config.
There are three parameters related to each area:

- `xxxx_ADR` sets the address for the area `xxxx`
  * `AUTO` will allocate the area from the end of flash.
  * `BEGIN_END` puts the `FEND` as the address, and also allocates from the end of flash. Maybe it has more priority?
- `xxxx_LEN` sets the size for the area `xxxx`
  * `CODE_LEN` puts the size of the flash image into the length field (used for `PRCT` area)
- `xxxx_OPT` sets the option flag for the area `xxxx`
  * The value is the same as present in the `spc.aer` itself.

### chip_key.bin

This file contains an obfuscated copy of a chipkey used to encrypt the main app area.
Right, they kept the key in the firmware blob! It's just obfuscated in such a manner that it won't make sense.

```
0006adc0  3a cc b5 50 f0 6e c9 65  f7 be e3 38 60 1e 2e 51  |:..P.n.e...8`..Q|
0006add0  8b a3 48 1b 1f de 8b d2  69 64 62 47 e2 72 21 ac  |..H.....idbG.r!.|
0006ade0  c5 5d 13 92 65 36 73 42  01 00 00 08 00 00 00 00  |.]..e6sB........|
0006adf0  41 43 36 39 30 58 00 01  00 00 00 00 00 00 00 00  |AC690X..........|
```

Actually, despite it's being reported as being 32 bytes long, it's actually 64 bytes long.

#### chipkey encoding

The first 32 bytes encode the chipkey itself, and their usage is as follows:

- The first 16 bytes is filled with random bytes, in order to generate some random entropy.
- Next 16 bytes is the 16 bits of the chipkey itself, which are also XORed with the random bytes above *in reverse*

The chipkey is decoded as follows:

First the sum of all 16 random bytes is obtained, with the example provided above it would be: 0x864.
Since the checksum is calculated into a 8-bit variable, the sum thus becomes 0x64.

If the sum is below 0x10, it is set to 0x55. If it is above or equal to 0xE0, it is set 0xAA.

Then XOR the bytes 0-15 with bytes 16-31, where the latter is indexed backwards, i.e. `data[0] ^ data[31]`, `data[1] ^ data[30]`, etc.

In our case it will result in this byte string:
`96 ed c7 b2 b7 0c ad 0c 25 35 3d 27 7b 56 8d da`

Then it's a matter of subtracting the extracted byte with the sum that was calculated before:
 - 0x96 - 0x64 = 50
 - 0xed - 0x64 = 137
 - 0xc7 - 0x64 = 99
 - 0xb2 - 0x64 = 78
 - 0xb7 - 0x64 = 83
 - 0x0c - 0x64 = -88
 - 0xad - 0x64 = 73
 - 0x0c - 0x64 = -88
 - 0x25 - 0x64 = -63
 - 0x35 - 0x64 = -47
 - 0x3d - 0x64 = -39
 - 0x27 - 0x64 = -61
 - 0x7b - 0x64 = 23
 - 0x56 - 0x64 = -14
 - 0x8d - 0x64 = 41
 - 0xda - 0x64 = 118

Each negative value corresponds to a '1' bit, and a positive value corresponds to a '0' bit.

So this chipkey finally decodes into a bit string '0000 0101 1111 0100' or 0x05F4 in hexadecimal.

#### The rest

Okay, we know the first 32 bytes is the chipkey itself, what are the rest?

```
0006ade0  c5 5d 13 92 65 36 73 42  01 00 00 08 00 00 00 00  |.]..e6sB........|
0006adf0  41 43 36 39 30 58 00 01  00 00 00 00 00 00 00 00  |AC690X..........|
```

The first 2 bytes is actually the CRC16 of the first 32 bytes, which is what's actually checked by uboot (not the data CRC field in the file entry!)

The rest is yet to be investigated.
Well, at offset +48 you can see the chip series name, which correspond to `AC690X`, `AC691X` and `AC692X` series respectively.

### BOOT_START_FIRST

Just 32 bytes before the end of a flash image, there is a space for a `BOOT_START_FIRST` string.

```
0006afc0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0006afd0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0006afe0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
0006aff0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
          -or-
0006afc0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0006afd0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
0006afe0  42 4f 4f 54 5f 53 54 41  52 54 5f 46 49 52 53 54  |BOOT_START_FIRST|
0006aff0  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
```

This is used in order for uboot to set a "first boot flag" when entering the code in the main app area.
This string is present only once, as it is erased to all 0x00's in order to not trigger the "first boot" each time the device turns on.

Whether this string is put into image or not is specified in the `BOOT_FIRST` parameter in the ISD config.
