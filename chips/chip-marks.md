# Chip markings explained

It is well-known that JieLi chips have some completely nonsense markings that
doesn't point out the real chip name (at least, at the first glance).

Althrough they are not the only ones that do that...

- Bluetrum (the 'AB' chips) does that too..
- Buildwin/Appotech is no exception. However they have so many similarities to JieLi that i doubt that's just a coincidence...

## What's going on.

The chips do actually have some meaning in their markings, althrough this depends on the chip series in question.
But even then, it only tells a part of the information needed to know what exact chip you've got.

So let's see some chip markings and break them apart:

| Marking             | A  | B  | C  | D        | a  | b | c | Actual name      |
|---------------------|----|----|----|----------|----|---|---|------------------|
| AB1526CG3X1F.1-82E  | AB | 15 | 26 | CG3X1F.1 | 82 | E |   | AC1082E          |
| AB1819CK1Y11.1-87   | AB | 18 | 19 | CK1Y11.1 | 87 |   |   | AC1187           |
| AC19DH4502-01       | AC | 19 |    | DH4502   | 01 |   |   | AC4601           |
| ADDEF438-01B        | AD |    |    | DEF438   | 01 | B |   | AC4x01B          |
| AC1631D97294-04A    | AC | 16 | 31 | D97294   | 04 | A |   | AC5204A          |
| AC19AP22917-1A4     | AC | 19 | A  | P22917   | 1  | A | 4 | AC5x01A          |
| AC21BP0A908         | AC | 21 | B  | P0A908   |    |   |   | AC690N           |
| AC20AP2J262-1A8     | AC | 20 | A  | P2J262   | 1  | A | 8 | AC6901A          |
| AS18AP16368-8C4     | AS | 18 | A  | P16368   | 8  | C | 4 | AC6908C          |
| AC1835E8P348-9A4    | AC | 18 | 35 | E8P348   | 9  | A | 4 | AC6909A          |
| AC19AP26102-25E4    | AC | 19 | A  | P26102   | 25 | E | 4 | AC6925E          |
| BP09766-26A4        |    |    | B  | P09766   | 26 | A | 4 | AC6926A          |
| EA9395-26LC         |    |    |    | EA9395   | 26 | L | C | AC6926L          |
| AC20BP05193-65A4    | AC | 20 | B  | P05193   | 65 | A | 4 | AC6965A          |
| AC1135D22731        | AC | 11 | 35 | D22731   |    |   |   | AC2092 (indeed!) |
| AC1245H7A935        | AC | 12 | 45 | H7A935   |    |   |   | AC2092           |
| AC1536CG4A3C-E      | AC | 15 | 36 | CG4A3C   |    | E |   | AC2092E          |
| AB225H77028         | AB | 2  | 25 | H77028   |    |   |   | ACx09N           |

Here we can see the marking that's on the chip, and its parts on columns A,B,C,D (before dash) and a,b,c (after dash).

... TODO

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
| AC1135D22731            | AC2092       | year 2011, it has the marking!!| [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| AC1245H7A935            | AC2092       | year 2012                      | [radioskot](https://cxemi.ru/forum/11-14227-396258-16-1539715165) |
| AC1536CG4A3C-E          | AC2092E      | year 2015                      | [radioskot](https://cxemi.ru/forum/11-14227-412259-16-1553886662) |
| ADDEF438-01B            | AC4?01B      |                                |        |
| AC19DH4502-01           | AC4601       | year 2019                      | [esp8266](https://esp8266.ru/forum/threads/jl-soc.5500/post-88589) |
| **AC1631D97294-04A**    | AC5204A      | year 2016                      | myself |
| AC19AP22917-1A4         | AC5401A?     | year 2019, 4 == 4 Mbit flash?? |        |
| AC21BP0A908             | AC690        | year 2021                      |        |
| AC20AP2J262-1A8         | AC6901A      | year 2020, 8 Mbit flash        |        |
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
