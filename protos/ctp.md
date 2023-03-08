# JieLi CTP

Some camera protocol used by the WiFi mode on the JieLi cameras..
At least for the AC520N (DV12) SDK.

Main source of information was the "iSDV Cam" android app (which is rather a hacked up version of JieLi's camera app),
link for which was in [this](/boards/ls-dv04-b-v1.1/index.md) camera.
(both on a box and in the camera fw itself, as two QR codes for Android and iOS)

Back in 2019-2020..

## Network stuff

- IP: 192.168.1.1 (AP mode)
- Ports:
  - TCP 21: FTP port (for transferring the files)
  - TCP 8080: HTTP port (for getting the app translations JSONs, info, etc.)
  - TCP 2222: Device port (the CTP command port)
  - UDP 2223: Video port
  - UDP 2224: RT stream port
  - UDP 2225: Thumbnail port
  - UDP 2226: Rear RT stream port
  - UDP 2227: Rear thumbnail port

## CTP protocol

The data is transmitted via TCP socket.

Each command is encapsulated into a CTP packet, which has the following structure:

- `CTP:IIII CCCC LLLL [D...]`
  - IIII = CTP ID
  - CCCC = Command
  - LLLL = Data length
  - D... = Data

The IIII/CCCC/LLLL fields are written out in decimal, the length field indicates the length in bytes (characters)!
e.g. `CTP:0001 4777 0006 kagami` is CTP ID 0001, Command 4777, data length 6: 'kagami'.

If there is more than one packet is transmitted in a row, then it just follows the previous packet like so:
`CTP:0001 4777 0006 kagamiCTP:0001 8168 0009 JIELITECH`: cmd 0001/4777/kagami, cmd 0001/8168/JIELITECH.

The parameters or the response is usually a set of numbers separated with spaces, e.g. `CTP:0001 2606 0011 4777 32 641`: 0001/2606 4777,32,641

### CTP IDs

- 0001 = Default (all commands are transferred using this ID)
- 9999 = Alive (for ping?)

### Commands

- -404 - NULL
- 0001 - DEVICE MODE
- 0004 - RESET DEVICE
- 0005 - AP SSID
- 0006 - AP PASSWORD
- 0007 - SP SSID
- 0008 - SP PASSWORD
- 0009 - PHOTO STATE
- 0010 - FORMAT SDCARD
- 0011 - SDCARD STATE
- 0012 - BATTERY STATE
- 0013 - TAKE PHOTO
- 0014 - START RECORD
- 0015 - STOP RECORD
- 0018 - DELETE FILE
- 0019 - DELETE ALL
- 0024 - VIDEO PICTURE QUALITY
- 0025 - METERING
- 0026 - DEVICE UUID
- 0027 - GET RECORDING STATUS
- 0028 - TIMER PICTURE STATUS
- 0029 - APP REQUEST CONNECTION
- 0030 - DEVICE WIFI DISABLED
- 0031 - ENTER BROWSING MODE
- 0032 - EXIT BROWSING MODE
- 0033 - FIRMWARE UPGRADE
- 0034 - DISABLE DEVICE WIFI
- 0035 - RESTART DEVICE
- 0036 - SHUTDOWN DEVICE
- 0037 - DEVICE LANGUAGE
- 0039 - DEVICE SSID PREFIX
- 0040 - DEVICE DATE
- 0041 - ALL VIDEO DESC NAME
- 0042 - GET VIDEO THUMBNAIL
- 0043 - VIDEO START PLAYBACK
- 0046 - VIDEO STOP
- 0050 - RT STREAM OPEN
- 0051 - RT STREAM CLOSE
- 0052 - SNAPSHOT
- 0054 - CONTROL RTS VOICE
- 0056 - DIGITAL ZOOM
- 0057 - ENV LIGHT LEVEL
- 0058 - PLAYBACK SPEED
- 0059 - VIDEO REMAINING TIME
- 0060 - PHOTO REMAINING NUMBER
- 0061 - REAR RTS OPEN
- 0062 - REAR RTS CLOSE
- 0063 - REAR CAMERA PLUG STATE
- 0064 - REAR ALL VIDEOS INFO
- 0065 - REAR GET VIDEO THUMBNAIL
- 0066 - REAR VIDEO PLAYBACK START
- 0069 - REAR VIDEO PLAYBACK STOP
- 0072 - REAR VIDEO PLAYBACK SPEED
- 0073 - DEVICE NAME
- 0074 - REVERSING STATE
- 1000 - PHOTO SIZE
- 1003 - WHITE BALANCE
- 1004 - CONTINUOUS SHOOTING
- 1005 - TIMER PICTURE
- 2000 - VIDEO SIZE

## RT stream

The data is tramsitted via UDP socket.

1: audio, 2/4/5/6/7: video, 3: photo

TODO..
