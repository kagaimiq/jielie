# Boomsbox mini (HF9234-25E-V2 board)

**I don't have this thing anymore because it wasn't mine at all.**

Some JBL-ish bluetooth speaker...

- SoC: [AC6925E](../../chips/br21/index.md#ac6925e)

![The speaker](speaker.jpg)

![Board top](20220606_215005.jpg)

![Board bottom](20220606_215017.jpg)

![Chip closeup](20220606_214912.jpg)

## Pin usage

|    Pin    |             Usage              |
|-----------|--------------------------------|
| PR1       | Power button                   |
| PR2       | Amplifier shutdown             |
| PA0       | Microphone                     |
| PA3       | AUX in                         |
| PA4       | Keys1                          |
| PB0       | Onboard LEDs (BLUE1 and BLUE2) |
| PB4       | Keys2                          |
| PB5       | Keys3                          |
| PC5       | SD card CLK                    |
| PC4       | SD card CMD                    |
| USBDM/PC3 | SD card DAT0, USB D-           |
| USBDP     | USB D+                         |

Keys are connected as follows:

![Keys schematic](keys.svg)
