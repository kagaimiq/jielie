# 4k wifi sports dv cam (LS-DV04-B-V1.1 board)

**I don't have this thing anymore... RIP 08.02.2019 - 05.03.2019 - 23.03.2019**

Super Action Dash DV Camera 4K GC0307 sensor camera based on the **JieLi AC5204A**!
I was *really* shocked when i saw that there was an **JIE LI** chip inside!!

- SoC: [AC5204A](../../chips/dv12/index.md#ac5204a)
- Flash: 32 Mbit (4 MiB) SPI flash (in my case, Pm25LQ032)
- Sensor: GC0307 (640x480) - the right choice for the 4K camera!!
- Display: ILI9341(?) TFT display (~220x176, 208x176 used)
- Wi-Fi: RTL8189ES
- External display: **Fake** micro-HDMI connector
- USB: Charging & USB device (MSD + UVC + UAC)

![Kinda in action](20190222_200456.jpg)

![AC5204A chip](AC5204A-board.jpeg)

![Board front side](20190221_180608.jpg)

![Board back side](20190221_180616.jpg)

## The Sensor

The image sensor that was used in it is the GalaxyCore's GC0307.
It has an resolution of **640x480**. Yeah.... That's the 4K quality we want!

Pinout: (labels as per GC0307 datasheet, on order that appears when looking at its back side)

| 24 | 23  | 22 | 21   | 20   | 19 | 18   | 17  | 16     | 15  | 14 | 13 | 12 | 11 | 10 | 9  | 8  | 7  | 6  | 5  | 4     | 3     | 2   | 1    |
|----|-----|----|------|------|----|------|-----|--------|-----|----|----|----|----|----|----|----|----|----|----|-------|-------|-----|------|
|    | VDD |    | SBDA | SBCL |    | PWDN | GND | IN_CLK | GND |    |    | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 | VSYNC | HSYNC | GND | PCLK |

--------------------------------------------------------------------------------------------

[MOAR!!!](moarpics.md)
