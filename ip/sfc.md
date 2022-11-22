# SFC

SFC (Serial/SPI/System Flash Controller) maps the SPI flash into memory so that the code from it
could be executed.

Together with [ENC/SFC_ENC](enc.md),
the encrypted data is decrypted in 32-byte blocks (which seems to be the icache's line size),
with the key being XORed with the current offset shifted 2 times right, i.e. `key ^ (addr >> 2)`.

## Registers

| Name     | Offset | Description        |
|----------|--------|--------------------|
| CON      | 0x00   | Control register   |
| BAUD     | 0x04   | Clock divider      |
| CODE     | 0x08   |                    |
| BASE_ADR | 0x0C   | Flash base address |
| QUCNT    | 0x10   |                    |

### CON

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:26 | /   | /       | /                                                    |
| 25    | R/W |         | If set, then the JEDEC ID is read out (via cmd 0x9F) |
| 24    | /   | /       | /                                                    |
| 23:20 |     |         |                                                      |
| 19:16 | R/W |         | Dummy bit count                                      |
| 15:12 | /   | /       | /                                                    |
| 11:8  |     |         |                                                      |
| 7     |     |         |                                                      |
| 6:4   | /   | /       | /                                                    |
| 3     | R/W |         | Combines DI and DO                                   |
| 2:1   | /   | /       | /                                                    |
| 0     | R/W | 0       | Enable SFC                                           |

### BAUD

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:8  | /   | /       | /                                                    |
| 7:0   | W   |         | Clock divider (n-1)                                  |

### BASE_ADR

| Bits  | R/W | Default | Description                                          |
|-------|-----|---------|------------------------------------------------------|
| 31:x  | /   | /       | /                                                    |
| x:0   | W   |         | Flash base address                                   |

## Example-ish

```c
reg32_wsmask(PORTD_base+PORTx_DIRn(0), 0); // PD0 out  -> SCK
reg32_wsmask(PORTD_base+PORTx_DIRn(1), 0); // PD1 out  -> MOSI
reg32_wsmask(PORTD_base+PORTx_DIRn(2), 1); // PD2 in   -> MISO
reg32_wsmask(PORTD_base+PORTx_DIRn(3), 0); // PD3 out  -> CS
reg32_wsmask(PORTD_base+PORTx_DIRn(4), 0); // PD4 out  -> ?? HOLD? Power?!

reg32_wsmask(PORTD_base+PORTx_PUn(1), 1); // PD1 pullup
reg32_wsmask(PORTD_base+PORTx_PUn(2), 1); // PD2 pullup

reg32_wsmask(PORTD_base+PORTx_OUTn(3), 1); // PD3 high
reg32_wsmask(PORTD_base+PORTx_OUTn(4), 1); // PD4 high

reg32_wsmask(IOMAP_base+IOMAP_CON0_spi0ios, 0x0); // SPI0 on PD3/PD2/PD1/PD0
reg32_wsmask(IOMAP_base+IOMAP_CON1_sfcios, 0x0); // SFC on PD3/PD2/PD1/PD0

reg32_write(SFC_base+SFC_CON, 0xf00000);
reg32_write(SFC_base+SFC_CON, 0);

reg32_write(SFC_base+SFC_BAUD, 0xff);

/*
 * mask -> 6ff0fbd : 0110'1111'1111'0000'1111'1011'1101
 *         0000034   0000'0000'0000'0000'0000'0011'0100
 *
 * write ->6ff0f89   0110'1111'1111'0000'1111'1000'1001
 *
 *          200088   0000'0010'0000'0000'0000'1000'1000
 *
 * b0 = enable
 * b3 = combine MOSI and MISO
 * b7 = 
 * b8~b11 = 
 * b16~b19 = dummy bits count
 * b20~b23 = 
 * b25 = if set, then the JEDEC ID is readed out (cmd 9F)
 *
 * 00000011 Aaaaaaaa:aaaaaaaa:aaaaaaaa          <Data>
 * 00001011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Data>
 * 00111011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Dual data>
 * 01101011 Aaaaaaaa:aaaaaaaa:aaaaaaaa XXXXXXXX <Quad data>
 * 10111011 AA.aa.aa.aa:aa.aa.aa.aa:... XX.XX.XX.XX <Dual data>
 * 11101011 AAAA.aaaa:aaaa.aaaa:.... XXXX.XXXX.XXXX.XXXX.XXXX.XXXX <Quad data>
 * xxxxyzzz
 * 
 *
 * SINGLE IO
 * 0x00200088 <== [r2 != 4] && [r1 != 8]  >>>> cmd 03 - read
 * 0x00280188 <== [r2 != 4] && [r1 == 8]  >>>> cmd 0B - read fast
 *
 * DUAL IO
 * 0x00200080 <== [r2 == 2] && [r1 != 8]  >>>> cmd 03 - read
 * 0x00280280 <== [r2 == 2] && [r1 == 4]  >>>> cmd 3B - read dual out
 * 0x00240480 <== [r2 == 2] && [r1 == 8]  >>>> cmd BB - read dual io
 * 0x00240680 <== [r2 == 2] && [r1 == 12] >>>> 
 *
 * QUAD IO
 * 0x00200080 <== [r2 == 4] && [r1 != 8]  >>>> cmd 03 - read
 * 0x00280380 <== [r2 == 4] && [r1 == 4]  >>>> cmd 6B - read quad out
 * 0x00260580 <== [r2 == 4] && [r1 == 8]  >>>> cmd EB - read quad io
 * 0x00260780 <== [r2 == 4] && [r1 == 12] >>>> 
 */

reg32_wsmask(SFC_base+SFC_CON, 0, 0x6ff0f88, 0x0280280);

reg32_write(SFC_base+SFC_BASE_ADR, 0x1000);

reg32_write(SFCENC_base+SFCENC_CON, 0); //b0 = enable, b1=?
reg32_write(SFCENC_base+SFCENC_KEY, 0x077A);
reg32_write(SFCENC_base+SFCENC_UNENC_ADRH, 0x0000);
reg32_write(SFCENC_base+SFCENC_UNENC_ADRL, 0x0000);
reg32_write(SFCENC_base+SFCENC_LENC_ADRH,  0x0000);
reg32_write(SFCENC_base+SFCENC_LENC_ADRL,  0x0000);
reg32_wsmask(SFCENC_base+SFCENC_CON_enable, 0);

reg32_wsmask(DSP_base+DSP_CON, 8, 1, 0); // disable sfc map
memset((void *)0xfc000, 0x00, 0x1c00);   // clear sfc cache tags
reg32_wsmask(DSP_base+DSP_CON, 8, 1, 1); // enable sfc map

reg32_wsmask(SPI0_base+SPIx_CON_spie, 0); // disable spi
reg32_wsmask(SFC_base+SFC_CON_enable, 1); // enable sfc

hexdump((void *)0x1000000, 0x100);
```
