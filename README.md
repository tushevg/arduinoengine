## Communication layout

```
!SRCCDnCS[NL]
```
* **!** start byte (1 ASCII) [exclamation mark = 0x21]
* **S** address receiver (1 ASCII) [0..9 permitted]
* **R** address sender (1 ASCII) [0..9 permitted]
* **CC** command (2 ASCII) [00..FF permitted]
* **Dn** data (2 ASCII, one byte, max 16 data bytes [00..FF permitted]
* **CS** checksum (2 ASCII) two-part compelemnt of the sum of SR, CC and nxDD
* **NL** stop byte (1 ASCII) [new line = 0x0A]
* Message maximum buffer size **40** ASCII 

## Input

**SR = 01** (input addres)

**CC = inputEventId**

	00. Handshake (D1-4 32bit value to flip)
	01. Power (D1 line, D2 state)
	02. Start (no data)
	03. Stop (no data)
	04. Resume (no data)
	05. Pause (no data)
	06. Trial (D1 8bit trigger mask)
	07. SetTimer (D1-4 32bit period value)
	08. SetDelay (D1 index, D2-5 32bit value ms)
	09. SetUptime (D1 index, D2-5 32bit value ms)
	10. SetDowntime (D1 index, D2-5 32bit value ms)
	11. SetCycles (D1 index, D2-5 32bit value ms)        

## Output
**SR = 11** (output address)

**CC = outputEventId**

	00. Handshake (D1-4 32bit eventCounter, D5-8 32bit eventTimestamp, D9-12 flipped value)
	01. SYNC_Basler (D1-4 32bit eventCounter, D5-8 32bit eventTimestamp)
	02. SYNC_nVista (D1-4 32bit eventCounter, D5-8 32bit eventTimestamp)
	03. SYNC_trigger (D1-4 32bit eventCounter, D5-8 32bit eventTimestamp, D9 8bit trigger mask)

**BYTE ORDER** 

from left to right

## Error
**SR = EE** (error address)

**CC = outputErrorId**
	




