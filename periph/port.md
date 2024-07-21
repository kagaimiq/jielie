# GPIO port

## Registers

- Variant 1:

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x00   | OUT      | Output levels           |
| 0x04   | IN       | Input levels            |
| 0x08   | DIR      | Direction (0: output, 1: input) |
| 0x0C   | DIE      | Digital input enable    |
| 0x10   | PU       | Pull-up enable          |
| 0x14   | PD       | Pull-down enable        |
| 0x18   | HD       | High drive current enable |

When both PU and PD are set for a specific pin, this will enable a special mux setting, that is selected with the DIE and OUT bits.

- Variant 2:

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x1C   | HD1      | High drive current enable #2 |

- Variant 3:

| Offset | Name     | Description             |
|--------|----------|-------------------------|
| 0x20   | DIEH     | ??                      |
