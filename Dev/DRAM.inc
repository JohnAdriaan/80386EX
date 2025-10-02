;
; Dev/DRAM.inc
;

; DRAM definitions.
; Elsewhere, the definition for `DRAM.Chip` will use one of these values.

; 8Mx32b, so single-sided=32 MB (0200_0000h)
DRAM.MT16D832.Speed      EQU             60              ; In nanoseconds
DRAM.MT16D832.Refresh    EQU             32              ; In milliseconds
DRAM.MT16D832.Rows       EQU             2048            ; In... rows
DRAM.MT16D832.Waits      EQU             2

; 4Mx4b, so single-sided=16 MB (0100_0000h), double-sided=32 MB (0200_0000h)
DRAM.HY5116404B.Speed    EQU             60              ; In nanoseconds
DRAM.HY5116404B.Refresh  EQU             64              ; In milliseconds
DRAM.HY5116404B.Rows     EQU             4096            ; In... rows
DRAM.HY5116404B.Waits    EQU             2

;DRAM.Size      EQU             8 * x86.1M.Size ; Detected at runtime
DRAM.Speed      EQU             DRAM.%[DRAM.Chip].Speed
DRAM.Refresh    EQU             DRAM.%[DRAM.Chip].Refresh
DRAM.Rows       EQU             DRAM.%[DRAM.Chip].Rows
DRAM.Waits      EQU             DRAM.%[DRAM.Chip].Waits

DRAM.Start      EQU             0000_0000h

;-------------------------------------------------------------------------------
                SEGMENT         DRAM   START=DRAM.Start  NOBITS

