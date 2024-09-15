# BR17 firmware structure

**Almost completed!**

This describes the structure of a firmware format used for (at least) the BR17, BR20 and BR21 chip families. (AC690x, AC691x and AC692x series respectively)

## General layout

```
     .-----------------------. <=== Starts at 0x00000
     |  Top-level file list  |
     :-----------------------:
     |                       |
     |      "uboot.boot"     | <-- second stage bootloader
     |                       |
     :-----------------------:
     |     "_____.____2"     | <-- additional file list
     :-----------------------:
     |      "ver.bin"        |
     :-----------------------| <=== mapped to the memory map at 0x1000000
     |                       |    .---------------------.
     |                       |    |                     |
     |                       |    |                     |
     |                       |    |                     |
     |                       |    |                     |
     |                       |    |     "sdram.app"     |<--.
     |                       |    |                     |   |
     |                       |    |                     |   |
     |                       |    |                     |   |
     |                       |    |                     |   |
     |                       |    :---------------------:   |
     |                       |    |    "bt_cfg.bin"     |<--|
     |       "user.app"      |    :---------------------:   |
     |                       |    |   "fast_run.bin"    |<--|
     |                       |    :---------------------:   |
     |                       |    |      "bt.mp3"       |<--|
     |                       |    :---------------------:   |
     |                       |    |   "bt_conn.mp3"     |<--|
     |                       |    :---------------------:   |
     |                       |    |   "bt_dconn.mp3     |<--|
     |                       |    :---------------------:   |
     |                       |    .                     . <-|
     |                       |    .                     . <-|
     |                       |    :---------------------:   |
     |                       |    |  App data file list |---'
     |                       |    '---------------------'
     :-----------------------:
     |      "sys.cfg"        | <-- system configuration data
     :-----------------------: <=== here the encrypted SFC data ends
     |      "spc.aer"        | <-- special area definition
     :-----------------------:
     |    "chip_key.bin"     | <-- key used to encrypt the SFC data
     :-----------------------:
     |   BOOT_START_FIRST    | <-- first boot tag
     :-----------------------: <=== The flash image ends here
     .                       .
     .                       .
     .                       .
     .                       .
     .                       .
     :-----------------------:
     |        "VMIF"         |
     :-----------------------:
     |        "BTIF"         |
     :-----------------------:
               ....

```

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

Note: most sections are aligned to a 512-byte boundary.

### Top-level file list

The flash dump starts with 128 bytes of some "garbage", which are actually four 32-byte blocks that are scrambled with the method used by the [ENC](../periph/enc.md) block.
The key used there is always 0xFFFF, and does not depend on the chip key.

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

When the header is decrypted, the following content is revealed:

```
00000000  cb 61 fd 3b 00 b0 06 00  fd ff ff ff 03 00 00 00  |.a.;............|
00000010  00 00 00 00 00 00 00 00  18 00 f0 02 0a 01 00 00  |................|
00000020  01 00 a1 58 00 02 00 00  50 c7 00 00 00 00 00 00  |...X....P.......|
00000030  75 62 6f 6f 74 2e 62 6f  6f 74 00 00 00 00 00 00  |uboot.boot......|
00000040  03 00 a1 7f 00 d0 00 00  00 02 00 00 01 00 00 00  |................|
00000050  5f 5f 5f 5f 5f 2e 5f 5f  5f 5f 32 00 00 00 00 00  |_____.____2.....|
00000060  02 00 4e 00 20 d7 00 00  00 d6 05 00 02 00 00 00  |..N. ...........|
00000070  75 73 65 72 2e 61 70 70  00 00 00 00 00 00 00 00  |user.app........|
00000080  70 64 63 3a 00 00 00 00  00 00 00 00 00 00 00 00  |pdc:............|
00000090  70 64 6e 3a 6a 6c 5f 36  39 30 78 00 00 00 00 00  |pdn:jl_690x.....|
```

At the very beginning, a [flash header](sdfile.md#flash-header) can be observed, which contains the following info:
- `info1` → Size of the whole flash image
- `info2` → unknown, 0xFFFFFFFD (-3)
- `version1`, `version2` → always zero?
- `chiptype` → the following:
  * AC690N: `18 00 F0 02 0A 01 00 00`
  * AC691N: *same as AC690N*
  * AC692N: `18 00 F0 0A 0A 01 00 00`

Then, at offsets 0x20, 0x40 and 0x60 the [file headers](sdfile.md#flash-header) can be seen, which describes three files:

- `uboot.boot` (type 0x01) → the second-stage bootloader
- `_____.____2` (type 0x03) → the additional file list
- `user.app` (type 0x02) → the main app area itself

#### pdc/pdn

You might've noticed that there are two 16-byte blocks coming right after the file list, what are they?

The one that starts with `pdc:` is followed by a byte whose value is set to the value of the `UPVR_CTL` parameter from an ISD config file.
It is either 0 or 1, and as far as I understand, it specifies whether the version 'downgrade' is disallowed, but not sure what it actually means in practice.

The one that starts with `pdn:` is followed by a string which is taken from the `PDCTNAME` parameter from the ISD config file, which is then converted to lowercase. Usually nobody bothers to change this, so it will say something like `jl_690x` or `jl_692x`.

### Additional file list

The `_____.____2` file contains additional file entries that were not listed in top-level file list.

The file headers are stored in raw form, so we can immediatly see the following contents:

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
 - `ver.bin` (type 0x05) → Version info of the SDK, libraries, etc.
 - `user.app` (type 0x02) → The main app area
 - `sys.cfg` (type 0x06) → System configuration
 - `spc.aer` (type 0x07) → Special area definitions (for VM, BTIF, etc.)
 - `chip_key.bin` (type 0x08) → An obfuscated copy of a chipkey used for this image

### uboot.boot

The file contains the second-stage bootloader that is in charge of doing SPI flash memory map setup, as well as doing firmware upgrades via Bluetooth, the USB UBOOT2.00 bootloader or from BFU files on a USB drive / SD card.

It is stored in a scrambled [BANKCB](bankcb.md) format, which also uses the same constant 0xFFFF key.

And there are actually *two* BANKCB blobs coming next to another: the first one is loaded by the ROM, which is used to chainload the second bankcb image that contains the actual bootloader code.

The second blob is also loaded next to the first one in memory, meaning that the 'load address' field is meaningless in this case (they set it to 0x01000000, which of course couldn't be in a SPI flash map in any way possible).
For example if the first blob's load address is 0x2000 and size is 0x260, then the second blob is going to be loaded at address 0x2260.

### ver.bin

This file contains the version info of the SDK, libraries, etc.

This is generated by the `link-version` utility in the toolchain, consolidating data from all `.version` sections.

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

This file contains the data exposed into CPU's memory space via the [SFC](../periph/sfc.md) peripheral.
This is where the main code alongside all of its resources are living in.

Since it is accessed by the SFC peripheral with the cache, it is scrambled in 32-byte blocks, with the key being XORed by the absolute address shifted two times right (i.e. `key ^ (addr >> 2)`).

The actual scrambling key is supposed to be the one stored in chip's "chipkey" fuses, but the stock `uboot.boot` actually takes it from the firmware's `chip_key.bin` file instead.
However, it does read out the key fuses on the chip in order to check if the firmware key matches with the chip key, however this is done in a rather quirky way:
both keys are ORed together and then the result is compared to the firmware key, meaning that:
- A chip with the 0xFFFF key could only run firmware that has a 0xFFFF key
- A chip with the 0x0000 key can run firmware with any key
- A firmware with the 0xFFFF key can work on any chip, even when they have a chip key different from 0xFFFF
- Some combinations of the firmware and chip keys can also work, for example 2606/36EF.

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
   .     Other files...     .
   .                        .
   .                        .
   :------------------------:   <==== pointed there by sys.cfg
   |     File list          |
   `------------------------'

```

The code file (`sdram.app`, `sdk.app`, or something else, perhaps) is always the first file and comes immediately at the beginning, because the execution always starts from the start of the SFC map.
And because of that, the file list itself is located at the very end in this area, so in order to know where it is located, you need to look into `sys.cfg` first.

```
0000d720  40 c6 0f c6 15 c6 1e c6  cb ea 34 00 4b ea e8 33  |@.........4.K..3|
0000d730  c7 ea 34 00 47 ea e8 33  1c e1 60 1d 00 98 2f 11  |..4.G..3..`.../.|
0000d740  80 ea 34 00 00 ea e8 2f  01 80 82 ea 00 00 02 ea  |..4..../........|
0000d750  b4 17 b2 20 02 99 29 03  03 80 90 ee 22 20 13 c6  |... ..)....." ..|
0000d760  02 80 0b 01 48 e8 01 40  5a 27 80 ea 34 00 00 ea  |....H..@Z'..4...|
0000d770  80 00 81 ea 05 01 01 ea  06 24 82 ea 00 00 02 ea  |.........$......|

....

0006ab20  b3 0b 9a 53 00 d4 05 00  fd ff ff ff 08 00 00 00  |...S............|
0006ab30  00 00 00 00 00 00 00 00  18 00 f0 02 0a 01 00 00  |................|
0006ab40  00 00 bc 96 00 00 00 00  6e 53 05 00 00 00 00 00  |........nS......|
0006ab50  73 64 72 61 6d 2e 61 70  70 00 ff ff ff ff ff ff  |sdram.app.......|
0006ab60  00 00 da ce 00 54 05 00  b0 02 00 00 01 00 00 00  |.....T..........|
0006ab70  62 74 5f 63 66 67 2e 62  69 6e 00 ff ff ff ff ff  |bt_cfg.bin......|
0006ab80  00 00 7c c3 00 58 05 00  40 0b 00 00 02 00 00 00  |..|..X..@.......|
0006ab90  66 61 73 74 5f 72 75 6e  2e 62 69 6e 00 ff ff ff  |fast_run.bin....|
0006aba0  00 00 9b 09 00 64 05 00  dc 16 00 00 03 00 00 00  |.....d..........|
0006abb0  62 74 2e 6d 70 33 00 ff  ff ff ff ff ff ff ff ff  |bt.mp3..........|
0006abc0  00 00 42 85 00 7c 05 00  3c 0e 00 00 04 00 00 00  |..B..|..<.......|
0006abd0  6d 75 73 69 63 2e 6d 70  33 00 ff ff ff ff ff ff  |music.mp3.......|
0006abe0  00 00 42 e8 00 8c 05 00  fc 0e 00 00 05 00 00 00  |..B.............|
0006abf0  63 6f 6e 6e 65 63 74 2e  6d 70 33 00 ff ff ff ff  |connect.mp3.....|
0006ac00  00 00 20 dd 00 9c 05 00  3c 0b 00 00 06 00 00 00  |.. .....<.......|
0006ac10  64 69 73 63 6f 6e 6e 65  63 74 2e 6d 70 33 00 ff  |disconnect.mp3..|
0006ac20  00 00 ea 4d 00 a8 05 00  12 2b 00 00 07 00 00 00  |...M.....+......|
0006ac30  6c 6f 77 5f 70 6f 77 65  72 2e 6d 70 33 00 ff ff  |low_power.mp3...|
```

The file list is once again an sydfs, although its header and file entries are not encrypted since it is already located in an encrypted area.
Another thing that should've probably noted too is that the addressing is done relatively to the start of the area.

Typical files found here:
 - `sdram.app`, `sdk.app`, etc. → the main code - should be the first one
 - `bt_cfg.bin`, `ac691x_cfg.bin`, etc. → the [bluetooth/SDK config](sdkcfg.md) file, contains stuff like bluetooth device names, power level and few other things
 - `bt_conn.mp3`, `power_on.mp3`, `music.mp3`, etc. → the voice/sound/audio/whatever prompts.
 - `fast_run.bin` → a piece code loaded into RAM1 in order to do the bare minimum to run the main code when returning from deep sleep (present only on AC690N, as far as I can tell)
 - `f_ascii_s.pix`, `f_gb2312_s.pix`, `f_gb2312.tab`, etc. → the UI font files
 - `menu.res`, `ui_sty.sty` → the UI resource/style files

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

Decrypting the example above reveals the following:

```
0006ad20  00 00 00 00 00 00 08 00  00 b0 06 00 00 d4 05 00  |................|
0006ad30  0a a1 00 00 01 00 00 00  20 d7 00 00 00 00 00 00  |........ .......|
0006ad40  60 d6 05 00 30 00 00 00  00 00 00 00 00 36 6e 01  |`...0........6n.|
0006ad50  00 00 00 00 01 00 00 00  01 00 00 00 00 f0 06 00  |................|
0006ad60  00 10 01 00
```

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

I believe the "option flag" is used in the firmware update process (e.g. via a USB stick or SD card) in order to decide what to do with this area, e.g. in order to erase the VM, or something like that.

Common regions are:
 - `PRCT` → Protect region, usually covers the entire flash image, and has a "protect area" option on it.
 - `BTIF` → Something Bluetooth related
 - `VMIF` → [VM region](vm.md)
 - `WTIF` → Something else related

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
That's right, they kept the key in the firmware blob! It's just obfuscated in such a manner that it won't make sense.

```
0006adc0  3a cc b5 50 f0 6e c9 65  f7 be e3 38 60 1e 2e 51  |:..P.n.e...8`..Q|
0006add0  8b a3 48 1b 1f de 8b d2  69 64 62 47 e2 72 21 ac  |..H.....idbG.r!.|
0006ade0  c5 5d 13 92 65 36 73 42  01 00 00 08 00 00 00 00  |.]..e6sB........|
0006adf0  41 43 36 39 30 58 00 01  00 00 00 00 00 00 00 00  |AC690X..........|
```

Actually, despite it's being reported as being 32 bytes long, it's actually 64 bytes long - you can clearly see that in the example above.
More on that later.

#### chipkey encoding

The first 32 bytes encode the chipkey itself, and their usage is as follows:

- The first 16 bytes is filled with random bytes, in order to generate some random entropy.
- Next 16 bytes is the 16 bits of the chipkey itself, which are also XORed with the random bytes above *in reverse*

The chipkey is decoded as follows:

First the sum of the first 16 bytes is obtained, with the example provided above it would be: 0x864.
Since the checksum is calculated into a 8-bit variable, the sum thus becomes 0x64.

If the sum is below 0x10, it is set to 0x55. If it is above or equal to 0xE0, it is set 0xAA.

Then XOR the bytes 0-15 with bytes 16-31, where the latter is indexed backwards, i.e. `data[0] ^ data[31]`, `data[1] ^ data[30]`, etc.

In our case it will result in this byte string:
`96 ed c7 b2 b7 0c ad 0c 25 35 3d 27 7b 56 8d da`

Then it's a matter of subtracting the extracted byte with the sum that we calculated before:
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
Well, at offset +48 you can see the chip series name, which in this case may contain `AC690X`, `AC691X` and `AC692X` respectively.

### BOOT_START_FIRST

Just 32 bytes before the end of a flash image, there is a space for a `BOOT_START_FIRST` tag.

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
This tag is present only once, as it is erased to all 0x00's in order to not trigger the "first boot" each time the device turns on.

Whether this tag is put into image or not is specified in the `BOOT_FIRST` parameter of the ISD config.
