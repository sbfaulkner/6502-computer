# be6502

This repo contains the supporting code to build a 6502-based computer as described by [Ben Eater][beneater].

## Memory Map

| Address   | Description |
| :-------: |-----------|
| 0000-3FFF | 16K RAM |
| 0100-01FF | Processor stack |
| 4000-7FFF | Unmapped memory (except as noted) |
| 6000-600F | VIA (Versatile Interface Adapter) |
| 6000      | ORB/IRB (Output/Input Register "B") |
|           | %10000000 = LCD DB7: bi-directional data pin |
|           | %01000000 = LCD DB6: bi-directional data pin |
|           | %00100000 = LCD DB5: bi-directional data pin |
|           | %00010000 = LCD DB4: bi-directional data pin |
|           | %00001000 = LCD E  : Starts data read/write |
|           | %00000100 = LCD RW : Selects read or write (0: Write; 1: Read) |
|           | %00000010 = LCD RS : Register select (0: IR; 1: DR) |
|           | %00000001 = NC : ie. Unused |
| 6001      | ORA/IRA (Output/Input Register "A") |
| 6002      | DDRB (Data Direction Register "B") |
| 6003      | DDRA (Data Direction Register "A") |
| 6004      | T1C-L (T1 Low-Order Latches/Counter) |
| 6005      | T1C-H (T1 High-Order Counter) |
| 6006      | T1L-L (T1 Low-Order Latches) |
| 6007      | T1L-H (T1 High-Order Latches) |
| 6008      | T2C-L (T2 Low-Order Latches/Counter) |
| 6009      | T2C-H (T2 High-Order Counter) |
| 600A      | SR (Shift Register) |
| 600B      | ACR (Auxiliary Control Register) |
| 600C      | PCR (Peripheral Control Register) |
| 600D      | IFR (Interrupt Flag Register) |
| 600E      | IER (Interrupt Enable Register) |
| 600F      | ORA/IRA (Same as Reg 1 except no "Handshake") |
| 8000-FFFF | 32K ROM |
| FFFC-FFFD | Reset vector |

### RAM

The 62256 provides supports 32KB of addressable memory, but to keep address mapping simple we only map 16KB from $0000 to $3FFF.

### I/O

The 16-byte range of addresses from $6000 to $600F, within the unmapped 16KB address space from $4000 to $7FFF, is used to control the W65C22 for I/O (eg. for the LCD).

Note: The entire address space from $6000 to $7FFF is mapped to the VIA to simplify address decoding (ignoring all bits masked by $1FF0 -- eg. $7FFF ^ $1FF0 = $600F)

#### LCD Module

PORTB of the W65C22 VIA is used to control a LCD module based on the HD44780U (LCD-II) Dot Matrix Liquid Crystal Display Controller/Driver operating in 4-bit mode (ie. DB0 to DB3 unused).

### Reset Vector

Execution begins at the address pointed to by the reset vector (WORD) at $FFFC.

[beneater]: https://eater.net/6502
