# SDK config

## AC46xx SDK

- file: ac46btcf.bin

```
2: CRC16 of the rest

2: Size of the file (including this field and the CRC16 field before)
    => Should be 0x31 (49) bytes

32: Device name

4: PIN code

6: MAC address

1: Something1 (0x18)

1: Something2 (0x0A)
```

## AC690N SDK (BT configuration tool)

- file: bt_cfg.bin

```
2: CRC16 of the rest

2: Size of the file (including this field and the CRC16 field before)
    => Should be 0x2B0 (688) bytes

1: Count of the device names
    => Range: 1~20

32: Device name [1]
32: Device name [2]
32: Device name [3]
32: Device name [4]
32: Device name [5]
32: Device name [6]
32: Device name [7]
32: Device name [8]
32: Device name [9]
32: Device name [10]
32: Device name [11]
32: Device name [12]
32: Device name [13]
32: Device name [14]
32: Device name [15]
32: Device name [16]
32: Device name [17]
32: Device name [18]
32: Device name [19]
32: Device name [20]

4: PIN code

6: MAC address

1: RF power
   => Range: 0~9

1: AEC dac analog gain
   => Range: 0~99 (seemingly)

1: AEC mic analog gain
   => Range: 0~99 (seemingly)

16: BLE device name

6: BLE public address

1: BLE random address type
    0 = Static random
    1 = Resolvable random
    2 = Non-resolvable random

6: BLE random address

1: BLE identity address
    0 = Uses public address
    1 = Uses random address

```

## AC692N SDK (SDK configuration tool)

- file: bt_cfg.bin

Differs from the AC690N SDK's bt_cfg by the fact that it the device names have
the CRC16 prepended to them, and the BLE device name being now 32 bytes long.

```
2: CRC16 of the rest

2: Size of the file (including this field and the CRC16 field before)
    => Should be 0x2C0 (704) bytes

1: Count of the device names
    => Range: 1~20

32: Device name [1]
32: Device name [2]
32: Device name [3]
32: Device name [4]
32: Device name [5]
32: Device name [6]
32: Device name [7]
32: Device name [8]
32: Device name [9]
32: Device name [10]
32: Device name [11]
32: Device name [12]
32: Device name [13]
32: Device name [14]
32: Device name [15]
32: Device name [16]
32: Device name [17]
32: Device name [18]
32: Device name [19]
32: Device name [20]
    ** Each field has the CRC16 of the name that comes next
    e.g. 29 52 74 73 75 6B 61 73 61 00 00 ...
         |---| |------------------>
         CRC16  Name (remaining 30 bytes)

4: PIN code

6: MAC address

1: RF power
   => Range: 0~9

1: AEC dac analog gain
   => Range: 0~99 (seemingly)

1: AEC mic analog gain
   => Range: 0~99 (seemingly)

32: BLE device name
    ** Same as with the BT device name, it starts with the CRC16

6: BLE public address

1: BLE random address type
    0 = Static random
    1 = Resolvable random
    2 = Non-resolvable random

6: BLE random address

1: BLE identity address
    0 = Uses public address
    1 = Uses random address

```

