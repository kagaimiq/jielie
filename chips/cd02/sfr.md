# CD02 SFR list

## SFR

8051 SFR space

| Address | Name         | Description                        |
|---------|--------------|------------------------------------|
| 0x80    | P0           | Port 0                             |
| 0x81    | SP           | Stack pointer                      |
| 0x82    | DP0L         | Data pointer 0 (low)               |
| 0x83    | DP0H         | Data pointer 0 (high)              |
| 0x84    | DP1L         | Data pointer 1 (low)               |
| 0x85    | DP1H         | Data pointer 1 (high)              |
| 0x86    | DPCON        | Data pointer control               |
| 0x87    | SPH          | Stack pointer high(?)              |
| 0x88    | P0HD         | Port 0 high-drive                  |
| 0x89    | SINT         |                                    |
| 0x8A    | IP0L         | Interrupt priority 0 (low)         |
| 0x8B    | IP0H         | Interrupt priority 0 (high)        |
| 0x8C    | IP1L         | Interrupt priority 1 (low)         |
| 0x8D    | IP1H         | Interrupt priority 1 (high)        |
| 0x8E    | WKUPPND      | Wakeup pending                     |
| 0x8F    | WKUPCON      | Wakeup control                     |
| 0x90    | P1           | Port 1                             |
| 0x91    | PWR_CON      | Power control register             |
| 0x92    | WDT_CON      | Watchdog control register          |
| 0x93    | BANK_SEL     | Bank select                        |
| 0x94    | PBANK        | Program bank?                      |
| 0x95    | IE1          | Interrupt enable register 1        |
| 0x96    | IO_MC0       | I/O map control register 0         |
| 0x97    | IO_MC1       | I/O map control register 1         |
| 0x98    | P1HD         | Port 1 high-drive                  |
| 0x99    | SPI_BUF      | SPI data buffer                    |
| 0x9A    | P2PD         | Port 2 pulldown                    |
| 0x9B    | P3PD         | Port 3 pulldown                    |
| 0x9C    | P2PU         | Port 2 pullup                      |
| 0x9D    | P3PU         | Port 3 pullup                      |
| 0x9E    | SD_CON0      | SD host control register 0         |
| 0x9F    | SD_CON1      | SD host control register 1         |
| 0xA0    | P2           | Port 2                             |
| 0xA1    | IRFLT_CON    | IR filter control register         |
| 0xA2    | P0DIR        | Port 0 direction                   |
| 0xA3    | P1DIR        | Port 1 direction                   |
| 0xA4    | P2DIR        | Port 2 direction                   |
| 0xA5    | P3DIR        | Port 3 direction                   |
| 0xA6    | LCD_CON0     | LCD control register 0             |
| 0xA7    | LCD_CON1     | LCD control register 1             |
| 0xA8    | IE0          | Interrupt enable register 0        |
| 0xA9    | SD_CON2      | SD host control register 2         |
| 0xAA    | DAC_CON0     | DAC control register 0             |
| 0xAB    | DAC_CON1     | DAC control register 1             |
| 0xAC    | DAC_VLML     | (W) DAC volume left..?             |
| 0xAC    | DAC_RDLL     | (R) DAC read left (low) ..?        |
| 0xAD    | DAC_VLMR     | (W) DAC volume right..?            |
| 0xAD    | DAC_RDLH     | (R) DAC read left (high) ..?       |
| 0xAE    | SD_CPTR      | (W) SD host command buffer pointer |
| 0xAE    | DAC_RDRL     | (R) DAC read right (low) ..?       |
| 0xAF    | SD_DPTR      | (W) SD host data buffer pointer    |
| 0xAF    | DAC_RDRH     | (R) DAC read right (high) ..?      |
| 0xB0    | P3           | Port 3                             |
| 0xB1    | P4           | Port 4                             |
| 0xB2    | P4DIR        | Port 4 direction                   |
| 0xB3    | P4PU         | Port 4 pullup                      |
| 0xB4    | P4PD         | Port 4 pulldown                    |
| 0xB5    | P4HD         | Port 4 high-drive                  |
| 0xB6    | P2HD         | Port 2 high-drive                  |
| 0xB7    | P3HD         | Port 3 high-drive                  |
| 0xB8    | P0DIE        | Port 0 digital input enable        |
| 0xB9    | P2DIE        | Port 2 digital input enable        |
| 0xBA    | P3DIE        | Port 3 digital input enable        |
| 0xBB    | P4DIE        | Port 4 digital input enable        |
| 0xBC    | CLK_CON0     | Clock control register 0           |
| 0xBD    | CLK_CON1     | Clock control register 1           |
| 0xBE    | CLK_CON2     | Clock control register 2           |
| 0xBF    | CLK_CON3     | Clock control register 3           |
| 0xC0    | P0PU         | Port 0 pullup                      |
| 0xC1    | UART_CON     | UART control register              |
| 0xC2    | UART_STA     | UART status register               |
| 0xC3    | UART_BUF     | UART data buffer                   |
| 0xC4    | MRES0        | Multiply result 0                  |
| 0xC5    | MRES1        | Multiply result 1                  |
| 0xC6    | MRES2        | Multiply result 2                  |
| 0xC7    | MRES3        | Multiply result 3                  |
| 0xC8    | P0PD         | Port 0 pulldown                    |
| 0xC9    | RTC_BUF      | RTC data buffer                    |
| 0xCA    | RTC_CON0     | RTC control register 0             |
| 0xCB    | RTC_CON1     | (W) RTC control register 1         |
| 0xCB    | CHIP_VERSION | (R) Chip version                   |
| 0xCC    | ADC_CON0     | ADC control register 0             |
| 0xCD    | ADC_CON1     | (W) ADC control register 1         |
| 0xCE    | SPI_CON      | SPI control register               |
| 0xCF    | SPI_STA      | SPI status register                |
| 0xD0    | PSW          | Processor status word              |
| 0xD1    | USB_CON2     | USB control register 2             |
| 0xD2    | TMR0_CON0    | Timer 0 control register 0         |
| 0xD3    | TMR0_CON1    | Timer 0 control register 1         |
| 0xD4    | TMR0_CNT     | Timer 0 counter                    |
| 0xD5    | TMR0_PRD     | Timer 0 period                     |
| 0xD6    | TMR0_PWM0    | Timer 0 PWM duty 0                 |
| 0xD7    | TMR0_PWM1    | Timer 0 PWM dity 1                 |
| 0xD8    | P1DIE        | Port 1 digital input enable        |
| 0xD9    | CRC_FIFO     | CRC FIFO register                  |
| 0xDA    | TMR1_CON0    | Timer 1 control register 0         |
| 0xDB    | TMR1_CON1    | Timer 1 control register 1         |
| 0xDC    | TMR1_CNT     | Timer 1 counter                    |
| 0xDD    | TMR1_PRD     | Timer 1 period                     |
| 0xDE    | TMR1_PWM0    | Timer 1 PWM duty 0                 |
| 0xDF    | TMR1_PWM1    | Timer 1 PWM duty 1                 |
| 0xE0    | ACC          | Accumulator                        |
| 0xE1    | CLK_GAT      | Clock gating ..?                   |
| 0xE2    | TMR2_CON     | Timer 2 control register           |
| 0xE3    | TMR2_CNTL    | Timer 2 counter (low)              |
| 0xE4    | TMR2_CNTH    | Timer 2 counter (high)             |
| 0xE5    | TMR2_PRDL    | Timer 2 period (low)               |
| 0xE6    | TMR2_PRDH    | Timer 2 period (high)              |
| 0xE7    | USB_DAT      | USB register data                  |
| 0xE8    | P1PU         | Port 1 pullup                      |
| 0xE9    | USB_CON1     | USB control register 1             |
| 0xEA    | TMR3_CON     | Timer 3 control register           |
| 0xEB    | TMR3_CNTL    | Timer 3 counter (low)              |
| 0xEC    | TMR3_CNTH    | Timer 3 counter (high)             |
| 0xED    | TMR3_PRDL    | Timer 3 period (low)               |
| 0xEE    | TMR3_PRDH    | Timer 3 period (high)              |
| 0xEF    | DAA_CON1     | DAC analog control 1               |
| 0xF0    | BREG         | B register                         |
| 0xF1    | HBITS        | (W) huffman bits?                  |
| 0xF1    | ADC_DATL     | (R) ADC conversion (low)           |
| 0xF2    | MP_CON0      | (W)                                |
| 0xF2    | ADC_DATH     | (R) ADC conversion (high)          |
| 0xF3    | MP_CON1      |                                    |
| 0xF4    | MP_CON2      |                                    |
| 0xF5    | MP_CON3      |                                    |
| 0xF6    | WPTRL        |                                    |
| 0xF7    | WPTRH        |                                    |
| 0xF8    | P1PD         | Port 1 pulldown                    |
| 0xF9    | DAA_CON2     | DAC analog control 2               |
| 0xFA    | HUFF_CON0    | Huffman control register 0         |
| 0xFB    | HUFF_CON1    | Huffman control register 1         |
| 0xFC    | VLENL        |                                    |
| 0xFD    | VLENH        |                                    |
| 0xFE    | SFTOUTH      |                                    |
| 0xFF    | SFTOUTL      |                                    |

## XFR

SFRs in the XDATA

| Address | Name          | Description                                 |
|---------|---------------|---------------------------------------------|
| 0xFF00  | OTP_CMD1      | (W) OTP command 1                           |
| 0xFF01  | OTP_CMD0      | OTP command 0                               |
| 0xFF03  | OSC_DET_CON   | OSC detect control register                 |
| 0xFF04  | UART_BAUD     | (W) UART baudrate                           |
| 0xFF05  | SD_CON3       | (W) SD host control register 3              |
| 0xFF06  | LVD_CON       | Low voltage detector control register       |
| 0xFF07  | STACK_LMT     | (W, FPGA only) Stack limit                  |
| 0xFF08  | ISD_CON       | ISD control reigster                        |
| 0xFF09  | ISD_BUF       | ISD data buffer                             |
| 0xFF0A  | ISD_ADR       | ISD DMA buffer address                      |
| 0xFF0B  | ISD_CNT       | ISD DMA burst length                        |
| 0xFF0C  | MODE_CON      | Mode control register                       |
| 0xFF0D  | PWM4_CON      | (W) PWM4 control register                   |
| 0xFF0E  | CRC_REGL      | CRC register (low)                          |
| 0xFF0F  | CRC_REGH      | CRC register (high)                         |
| 0xFF10  | USB_CON0      | USB control register 0                      |
| 0xFF14  | USB_EP0_ADR   | (W) USB endpoint 0 buffer address           |
| 0xFF15  | USB_EP0_CNT   | (W) USB endpoint 0 send count               |
| 0xFF16  | USB_EPX_CNT   | (W) USB endpoint X send count               |
| 0xFF17  | USB_EP1TX_ADR | (W) USB endpoint 1.TX buffer address        |
| 0xFF17  | EP1_RX_ADDRL  | (R) USB endpoint 1.RX address (low)         |
| 0xFF18  | USB_EP1RX_ADR | (W) USB endpoint 1.RX buffer address        |
| 0xFF18  | EP1_RX_ADDTH  | (R) USB endpoint 1.RX address (high)        |
| 0xFF19  | USB_EP2TX_ADR | (W) USB endpoint 2.TX buffer address        |
| 0xFF1A  | USB_EP2RX_ADR | (R) USB endpoint 2.RX buffer address        |
| 0xFF20  | LOFC_CON      | LOFC control                                |
| 0xFF21  | LOFC_PR       | LOFC --PR--                                 |
| 0xFF22  | LOFC_CNTH     | LOFC count (high)                           |
| 0xFF23  | LOFC_CNTM     | LOFC count (mid)                            |
| 0xFF24  | LOFC_CNTL     | LOFC count (low)                            |
| 0xFF26  | BP_ADRL       | Bitpack(?) address (low)                    |
| 0xFF27  | BP_ADRH       | Bitpack(?) address (high)                   |
| 0xFF28  | PLL_CON0      | PLL control register 0                      |
| 0xFF29  | PLL_CON1      | PLL control register 1                      |
| 0xFF2A  | PLL_CON2      | PLL control register 2                      |
| 0xFF2B  | SEG_EN0       | LCD segment enable 0                        |
| 0xFF2C  | SEG_EN1       | LCD segment enable 1                        |
| 0xFF30  | DAA_CON0      | DAC analog control 0                        |
| 0xFF33  | DAA_CON3      | DAC analog control 3                        |
| 0xFF34  | DAA_CON4      | DAC analog control 4                        |
| 0xFF36  | DAC_TRML      | (W) DAC left channel trim                   |
| 0xFF37  | DAC_TRMR      | (W) DAC right channel trim                  |
| 0xFF40  | OBUF_NUM      | (W) OBUF number                             |
| 0xFF41  | OBUF_CON      | OBUF control register                       |
| 0xFF42  | OBUF_DATL     | (W, 16-bit only) OBUF left channel data(?)  |
| 0xFF44  | OBUF_DATR     | (W, 16-bit only) OBUF right channel data(?) |
| 0xFF46  | KV_DAT        | (W, 16-bit only) Key Voice data             |
| 0xFF48  | KV_START      | (W) Key Voice start address                 |
| 0xFF49  | KV_END        | (W) Key Voice end address                   |
| 0xFF4A  | KV_CNT        | (W) Key Voice repeat count                  |
| 0xFF4B  | KV_VLM        | (W) Key Voice volume                        |
| 0xFF4C  | IIC_CON       | IIC control register                        |
| 0xFF4D  | IIC_STA       | IIC status register                         |
| 0xFF4E  | IIC_BAUD      | (W) IIC clock divider                       |
| 0xFF4F  | IIC_BUF       | IIC data buffer                             |
| 0xFF52  | SPI_BAUD      | (W) SPI clock divider                       |
| 0xFF53  | SPI_CNT       | (W) SPI DMA burst length                    |
| 0xFF54  | SPI_ADR       | (W) SPI DMA buffer address                  |
| 0xFF55  | LDO_CON       | LDO control register                        |
| 0xFF56  | HTC_CON       | HTC control register                        |

