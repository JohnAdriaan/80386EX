;
; Dev/SRAM.inc
;

SRAM.Size       EQU             32 * 1024       ; In bytes
SRAM.Speed      EQU             20              ; In nanoseconds
SRAM.Waits      EQU             0

; Definitions for Static RAM
SRAM.Start      EQU             (ROM.Start & ~SRAM.Mask) - SRAM.Size
SRAM.Mask       EQU             SRAM.Size - 1

;-------------------------------------------------------------------------------
                SEGMENT         SRAM  START=SRAM.Start  NOBITS
