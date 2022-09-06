# HF9234-25E-V2

**I don't have this board (and device) anymore. Because it wasn't mine at all**

A board from some blue JBL-ish speaker... that has two speakers, implying that it's stereo...
but the chip they used has only one output channel.... yikes!

- MCU: AC6925E

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
| PB0       | Onboard LEDs (half of them)    |
| PB4       | Keys2                          |
| PB5       | Keys3                          |
| PC5       | SD card CLK                    |
| PC4       | SD card CMD                    |
| USBDM/PC3 | SD card DAT0, USB D-           |
| USBDP     | USB D+                         |

Keys are connected as follows:

![Keys schematic](keys.svg)
