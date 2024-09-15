# Instruction cache

The instruction cache (icache) is a glue between the system memory bus and the SPI flash controller known as [SFC](sfc.md).

| Family | Cache memory | Tag memory | Organization                          | Notes |
|--------|--------------|------------|---------------------------------------|-------|
| BR17   | 0x1A000      | 0x48000    | 128 sets x 4 ways x 32 bytes (16 KiB) |       |
| BR21   | 0x1C000      | 0x48000    | 128 sets x 4 ways x 32 bytes (16 KiB) | Cache memory occupies the top 16K of the RAM1. |
| BR23+  | 0xF8000      | 0xFC000    | 128 sets x 4 ways x 32 bytes (16 KiB) |       |

## Cache memory

The cache memory stores the cached data themselve.

### BR17

It is organized in four blocks by 4 KiB each, where the blocks themselve represent a cache way, which are numbered in backwards (i.e. 0x1A000-0x1AFFF corresponds to way 4, 0x1B000-0x1BFFF to way 3, 0x1C000-0x1CFFF to way 2 and 0x1D000-0x1DFFF corresponds to way 1.)

### BR25

Same thing as in BR17 but now it is in order, i.e. 0xF8000-0xF8FFF is the way 1, 0xF9000-0xF9FFF is the way 2, and so on.

## Tag memory

The tag memory stores information about which address the corresponding set/way/line's data belong to,
as well as seemingly data related to selection of ways.

### BR17

```
00048000: FF 1F 00 00 01 10 00 00 FF 1F 00 00 00 10 00 00  |................|
00048010: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048020: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048030: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048040: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048050: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048060: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048070: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
00048080: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 FF 1F 00 00  |................|
          .....
000487b0: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 FF 1F 00 00  |................|
000487c0: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
000487d0: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
000487e0: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 FF 1F 00 00  |................|
000487f0: FF 1F 00 00 FF 1F 00 00 FF 1F 00 00 00 10 00 00  |................|
~ 128 entries

00049000: 01 00 00 00 02 00 00 00 02 00 00 00 02 00 00 00  |................|
00049010: 02 00 00 00 02 00 00 00 02 00 00 00 02 00 00 00  |................|
00049020: 07 00 00 00 07 00 00 00 07 00 00 00 07 00 00 00  |................|
          .....
000491e0: 07 00 00 00 07 00 00 00 07 00 00 00 07 00 00 00  |................|
000491f0: 02 00 00 00 02 00 00 00 07 00 00 00 02 00 00 00  |................|
~ 128 entries
```


```
1000 ==> 1000.000
1001 ==> 1001.000


1a000 ---> 4
1b000 ---> 3
1c000 ---> 2
1d000 ---> 1

48000
```

selection of ways:


```
waysel: 0314 0365 0365 0365 0365 0365 0365 0365
way:    1234 1324 1324 1324 1324 1324 1324 1324

011
010
110
100
011
101
011
101
011
101
011
101
...


000 0xxx
  ^ 011     + 011
011 o1xx
  ^ 010     + 110
001 oo2x
  ^ 110     + 011
100 ooo3
  ^ 100     + 100
000 4ooo
  ^ 011     + 011
011 oo5o
  ^ 101     + 011
110 o6oo
  ^ 011     + 111
101 ooo7
  ^ 101     + 011
000 
  ^ 011     + 011
011
  ^ 101     + 011
110
  ^ 011     + 111
101
  ^ 101
000
011
110
101
```

### BR25 

```
000fc000: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc010: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc020: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc030: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc040: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc050: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc060: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc070: FF 3F 00 00 00 3E 00 00 FF 3F 00 00 00 30 00 00  |.?...>...?...0..|
000fc080: FF 3F 00 00 FF 3F 00 00 FF 3F 00 00 FF 3F 00 00  |.?...?...?...?..|
          .....
000fc7f0: FF 3F 00 00 FF 3F 00 00 FF 3F 00 00 FF 3F 00 00  |.?...?...?...?..|
~ 128 entries

000fd000: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF  |................|
          .....
000fd7f0: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF  |................|

000fd800: 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  |................|
000fd810: 01 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  |................|
000fd820: 07 00 00 00 07 00 00 00 07 00 00 00 07 00 00 00  |................|
          .....
000fd9f0: 07 00 00 00 07 00 00 00 07 00 00 00 07 00 00 00  |................|
~ 128 entries
```

```
f8000 ---> 1
f9000 ---> 2
fa000 ---> 3
fb000 ---> 4

fc000


3000 = 1000'000
3e00 = 1e00'000
```

