# Chip markings explained

_I might've misused terminology for "part number" and "serial number" in this context.._

It is well-known that JieLi's chips have completely nonsense/misleading markings, which does not tell the chip's part number right away, at least at the first glance.

Sometimes the part number does actually present on the chip, however this is the case either on very early chips (e.g. 2011 era AC2092) or seemingly on very recent chips too.
Most of the time the (part of a) part number is hidden into the chip's serial number after the dash (e.g. -04A, -5A8, -65A4), or might be completely absent in some cases (e.g. AC209N/AC309N chips, AC690N "master" chip).

Here you consider a bunch of other factors to determine the rest of the part number correctly, I mean: application (e.g. bluetooth speaker, MP3 player, dash cam), package (e.g. in AC69xx the '5' chips come in SSOP24 package: AC6905, AC6925, AC6965; and the '6' come in QFN32: AC6926, AC6966, AC6976), design date (e.g. a recent design won't use some ancient chip series in favor of the recent one), etc.

## Explaining the marking

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

The parts written in uppercase letters (ABCDE) is the serial number, which comes before the dash, while the parts wrtten in lowercase (fgh) is the part number itself.

### Serial number:

- Part 'A': Letters 'AB', 'AC', 'AD', 'AS', etc.
- Part 'B': Manufacturing year
  * usually truncates the first two digits of the year, so '12' means year 2012
  * but sometimes it can truncate even further into the third digit, so '2' means year 2012 too.
  * Can be omitted, together with the week code.
- Part 'C': Manufacturing week/something like that
  * Can be omitted (e.g. mostly in recent chips), never present without the year code.
- Part 'D': Letters 'A', 'B', etc.
  * Probably a part of the factory batch code, but idk
- Part 'E': Factory batch code
  * Sometimes (e.g. for AC109N chips the '.1' suffix is intact, so this can be used to distinguish from e.g. AC608N chips)
  * Never omitted

So, to save space on some tiny packages (e.g. QFN32), several parts of the serial number might be omitted from the marking.

### Part number:

- Part 'f': Chip's part number (or a part of it)
  * e.g. '5', '9', '25', '65', 'JL6976'
- Part 'g': Chip variant
  * e.g. 'A', 'B', 'C', ...
- Part 'h': Misc info
  * e.g. size of the chip's flash in Mbits
  * can also define the series (e.g. the '-9A0' means the OTP AC6919A, not AC6909A)

----------------------------------------------------------------------------

# Some chip lists

Just a list of some chips...

| Chip marking            | Actual name  | Some details                   | Source |
|-------------------------|--------------|--------------------------------|--------|
| AB225H77028             | AC309N??     |                                |        |
| AC1520CFA813.1-82E      | AC1082       | year 2015                      |        |
| **AB1526CG3X1F.1-82E**  | AC1082       | year 2015                      | myself |
| AC1626CG9278.1-82E      | AC1082       | year 2016                      |        |
| AB1828CH2G0Q.1-82E      | AC1082       | year 2018                      |        |
| AD1431CF5243.1-83EM     | AC1083       | year 2014                      |        |
| **AB1819CK1Y11.1-87**   | AC1187       | year 2018                      | myself |
| AC1135D22731            | AC2092       | year 2011, it has the part number!!| [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| AC1245H7A935            | AC2092       | year 2012                      | [radioskot](https://cxemi.ru/forum/11-14227-396258-16-1539715165) |
| AC1536CG4A3C-E          | AC2092E      | year 2015                      | [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| ADDEF438-01B            | AC4601B      |                                |        |
| AC19DH4502-01           | AC4601       | year 2019                      | [esp8266](https://esp8266.ru/forum/threads/jl-soc.5500/post-88589) |
| **AC1631D97294-04A**    | AC5204A      | year 2016                      | myself |
| AC19AP22917-1A4         | AC5401A?     | year 2019, 4 == 4 Mbit flash?? |        |
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
| BP15698TKE JL6976M4     | JL6976M      | 4 Mbit flash, it has the part number! | [Julian Ilett](https://youtu.be/Ww3OU6scz1A?t=148) |
