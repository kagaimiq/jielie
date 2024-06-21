# Chip markings explained

It is well-known that JieLi's chips mostly have completely nonsense/misleading markings, which does not tell the chip's name right away, at least at the first glance.

Sometimes the actual name is presnt on the chip, however this is the case either on early chips (like 2011 era AC2092), or on some recent chips too. (JL700N, JL697N, etc.)

But most of the time the chip's name is hidden into the chip's serial number, in the part that goes after a dash.
However sometimes even this might be absent, for example on AC209N/AC309N chips or the AC690N master chip.

In this case, to determine the actual chip name you need to consider a bunch of factors, namely:
 - Application: bluetooth speaker, MP3 player, dash cam, microscope, etc.
 - Package: e.g. in AC69xx the 'AC69x5' chips come in a SSOP24 package, the 'AC69x6' chips come in QFN32, and the 'AC69x1' come in LQFP48.
 - Design date: usually a recent design won't use some ancient chip series in favour of the recent ones
 - Chip's internal details: e.g. AC690N and AC691N series are marked the same way, but they're still different: BR17 and BR20. AC540N and AC560N are both DV16 but they differ by the SDRAM type used: former uses DDR2 but the latter uses DDR1 instead.

## Marking explaination

Let's look at some chip markings and break them apart to understand the parts that make up the marking:

| Marking             | A  | B  | C  | D | E        | f  | g | h | Actual name      |
|---------------------|----|----|----|---|----------|----|---|---|------------------|
| AB1526CG3X1F.1-82E  | AB | 15 | 26 |   | CG3X1F.1 | 82 | E |   | AC1082E          |
| AB1819CK1Y11.1-87   | AB | 18 | 19 |   | CK1Y11.1 | 87 |   |   | AC1187           |
| AC1135D22731        | AC | 11 | 35 |   | D22731   |    |   |   | AC2092 (indeed!) |
| AB225H77028         | AB | 2  | 25 |   | H77028   |    |   |   | ACx09N           |
| AC1245H7A935        | AC | 12 | 45 |   | H7A935   |    |   |   | AC2092           |
| AC1536CG4A3C-E      | AC | 15 | 36 |   | CG4A3C   |    | E |   | AC2092E          |
| AC19DH4502-01       | AC | 19 |    |   | DH4502   | 01 |   |   | AC4601           |
| ADDEF438-01B        | AD |    |    |   | DEF438   | 01 | B |   | AC4601B          |
| AC1631D97294-04A    | AC | 16 | 31 |   | D97294   | 04 | A |   | AC5204A          |
| AC19AP22917-1A4     | AC | 19 |    | A | P22917   | 1  | A | 4 | AC5x01A          |
| AC21BP0A908         | AC | 21 |    | B | P0A908   |    |   |   | AC690N           |
| AC20AP2J262-1A8     | AC | 20 |    | A | P2J262   | 1  | A | 8 | AC6901A          |
| AS1707AP0Y11Q-5A8   | AS | 17 | 07 | A | P0Y11Q   | 5  | A | 8 | AC6905A          |
| AS18AP16368-8C4     | AS | 18 |    | A | P16368   | 8  | C | 4 | AC6908C          |
| AC1835E8P348-9A4    | AC | 18 | 35 |   | E8P348   | 9  | A | 4 | AC6909A          |
| AC19AP26102-25E4    | AC | 19 |    | A | P26102   | 25 | E | 4 | AC6925E          |
| BP09766-26A4        |    |    |    | B | P09766   | 26 | A | 4 | AC6926A          |
| EA9395-26LC         |    |    |    |   | EA9395   | 26 | L | C | AC6926L          |
| AC20BP05193-65A4    | AC | 20 |    | B | P05193   | 65 | A | 4 | AC6965A          |

The parts in uppercase (ABCDE) is the 'serial number', while the parts in lowercase (fgh) is the 'part number', which comes after a dash.

### Serial number

- **A**: Letters 'AB', 'AC', 'AD', 'AS', ..
  * The first letter is always 'A'
  * May be omitted
- **B**: Manufacturing year
  * Usually it represent the last two digits of the year, e.g. '18' is year 2018, but sometimes it's truncated even further: '2' means 2012 (probably)
  * May be omitted
- **C**: Manufacturing week
  * Usually omitted on newer chips, but sometimes it might present.
  * Never present without the year code
- **D**: Letters 'A', 'B', ..
  * probably that's a part of the lot number
- **E**: Lot number
  * Sometimes it can be used to distinguish between e.g. AC109N and AC608N: the former has the '.1' suffix, the latter lacks it.

In some cases, some parts of the serial number may be omitted to fit into tiny packages like QFN32 (in that case only the lot number is present).

### Part number

- **f**: Chip series variant (i.e. AC690**1**, AC690**2**, AC69**65**)
- **g**: Chip variant letter (A, B, C, D, etc.)
- **h**: Additional information (e.g. flash size, sdram size, psram size..)
  * Flash size is expressed in megabits (e.g. 8 means 8 Mb = 1 MB)
  * Chips without any flash put '0' here (e.g. AC691N without flash) or what's more relevant to them (e.g. SDRAM size)

*This also applies to the full chip marking too, with the first part now being the actual chip name (JL6976, JL700N, etc.)*

----------------------------------------------------------------------------

# Some chip lists

| Chip marking            | Actual name  | Some details                   | Source |
|-------------------------|--------------|--------------------------------|--------|
| AB225H77028             | AC309N??     | year 2012                      |        |
| AC1520CFA813.1-82E      | AC1082       | year 2015                      |        |
| **AB1526CG3X1F.1-82E**  | AC1082       | year 2015                      | myself |
| AC1626CG9278.1-82E      | AC1082       | year 2016                      |        |
| AB1828CH2G0Q.1-82E      | AC1082       | year 2018                      |        |
| AD1431CF5243.1-83EM     | AC1083       | year 2014                      |        |
| **AB1819CK1Y11.1-87**   | AC1187       | year 2018                      | myself |
| AC2092 AC1135D22731     | AC2092       | year 2011                      | [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| AC1245H7A935            | AC2092       | year 2012                      | [radioskot](https://cxemi.ru/forum/11-14227-396258-16-1539715165) |
| AC1536CG4A3C-E          | AC2092E      | year 2015                      | [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| ADDEF438-01B            | AC4601B      | - I guess                      |        |
| AC19DH4502-01           | AC4601       | year 2019                      | [esp8266](https://esp8266.ru/forum/threads/jl-soc.5500/post-88589) |
| **AC1631D97294-04A**    | AC5204A      | year 2016                      | myself |
| AC19AP22917-1A4         | AC5x01A      | year 2019, 4 = ??              |        |
| AC24BP1Y297-51C8        | AC635N       | year 2024, 8 Mbit flash        | deadman96385 |
| AC21BP0A908             | AC690        | year 2021                      |        |
| AC20AP2J262-1A8         | AC6901A      | year 2020, 8 Mbit flash        |        |
| AS1707AP0Y11Q-5A8       | AC6905A      | year 2017, 8 Mbit flash        |        |
| AS21BP0A909-5A8         | AC6905A      | year 2021, 8 Mbit flash        |        |
| **AS18AP16368-8C4**     | AC6908C      | year 2018, 4 Mbit flash        | myself |
| AC1835E8P348-9A4        | AC6909A      | year 2018                      | [EEVblog #1330](https://youtu.be/gj70jpdVMPY?t=702) |
| AC19AP1S079-25A4        | AC6925A      | year 2019, 4 Mbit flash        |        |
| AC20BP09548-25A4        | AC6925A      | year 2020, 4 Mbit flash        |        |
| AS20BP03306-25C4        | AC6925C      | year 2020, 4 Mbit flash        |        |
| AC21BP0A221-25C4        | AC6925C      | year 2021, 4 Mbit flash        |        |
| **AC19AP26102-25E4**    | AC6925E      | year 2019, 4 Mbit flash        | myself |
| BP09766-26A4            | AC6926A      | 4 Mbit flash                   |        |
| EA9395-26LC             | AC6926L      | ...                            |        |
| AS19AP29069-25F4        | AC6925F      | year 2019, 4 Mbit flash        |        |
| AS21BP03721-55F4        | AC6955F      | year 2021, 4 Mbit flash        |        |
| **AC20BP05193-65A4**    | AC6965A      | year 2020, 4 Mbit flash        | myself |
| AS21BP0B847-65A4        | AC6965A      | year 2021, 4 Mbit flash        |        |
| BP15698TKE JL6976M4     | JL6976M      |                                | [Julian Ilett](https://youtu.be/Ww3OU6scz1A?t=148) |
