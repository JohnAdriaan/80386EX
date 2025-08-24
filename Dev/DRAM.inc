;
; Dev/DRAM.inc
;

; DRAM definitions.
; Elsewhere, the definition for `DRAM.Chip` will use one of these values.

DRAM.MT16D832.Speed      EQU             60              ; In nanoseconds
DRAM.MT16D832.Refresh    EQU             32              ; In milliseconds
DRAM.MT16D832.Rows       EQU             2048            ; In... rows
DRAM.MT16D832.Waits      EQU             2

DRAM.HY5116494B.Speed    EQU             60              ; In nanoseconds
DRAM.HY5116494B.Refresh  EQU             64              ; In milliseconds
DRAM.HY5116494B.Rows     EQU             4096            ; In... rows
DRAM.HY5116494B.Waits    EQU             2

;DRAM.Size      EQU             8 * 1024 * 1024 ; Calculated at runtime
DRAM.Speed      EQU             DRAM.%[DRAM.Chip].Speed
DRAM.Refresh    EQU             DRAM.%[DRAM.Chip].Refresh
DRAM.Rows       EQU             DRAM.%[DRAM.Chip].Rows
DRAM.Waits      EQU             DRAM.%[DRAM.Chip].Waits

DRAM.Start      EQU             0000_0000h

;-------------------------------------------------------------------------------
                SEGMENT         RAM   START=DRAM.Start  NOBITS

