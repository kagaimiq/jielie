# HW-770 V0.2

Just an bluetooth audio board like the XY-BT-MINI, etc.

- SoC: [AC6965A](../../chips/br25/index.md#ac6965a)

![hw-770 and hw-221](20220707_172552.jpg)

![front](20220707_172919.jpg)
![back](20220707_172913.jpg)

## Pin usage

| Pin       | Usage         | Note                                        |
|-----------|---------------|---------------------------------------------|
| PB5       | Onboard LED   |                                             |
| PC5       | ?             | Exposed on a pad on front side              |
| USBDM/PC3 | USB D-        | Exposed on a pad on back side (next to VCC) |
| USBDP     | USB D+        | Exposed on a pad on back side (next to GND) |

### Extra

Some extra function pins...

| Pin       | Usage         | Note                                        |
|-----------|---------------|---------------------------------------------|
| PA0/PA2   | Mic bias      |                                             |
| PA1 (MIC) | Microphone    |                                             |
| PA3       | Line in L     |                                             |
| PA4       | Line in R     |                                             |
| PB4       | ?             |                                             |
| PB6       | Line in sense | Active low                                  |
| PB7       | ?             |                                             |
| PC4       | ADKEY         |                                             |

#### ADKEY

The pullup resistor resistance is ~10k (uses the chip's internal pullup)

| Resistance     | Key        | < long press |
|----------------|------------|--------------|
| 0R .. 1k2      | Prev       | Vol-         |
| 2k2 .. 4k3     | Play/Pause | Mode         |
| 4k7 .. 6k8     | Next       | Vol+         |
| 30k .. 33k     | EQ         |              |
| 47k .. 68k     | Vol+       | <-           |
| 100k .. 120k   | Vol-       | <-           |

