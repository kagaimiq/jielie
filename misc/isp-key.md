# ISP_KEY

The ISP_KEY uses [ISP](isp.md) for entering the USB bootloader on the chips which can't accept a normal [USB_KEY](usb-key.md),
for example on the AC608N series that are basically using dies of the AC695N/AC696N chips that doesn't have a working Bluetooth radio and thus lack the pins related to that, including the inputs for a Bluetooth oscillator (the BT_OSC) that is usually used as a clock source for the entire chip as well, and is expected by the ROM's bootloader.
