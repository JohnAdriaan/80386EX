;
; Dev/SRAM.inc
;

%ifdef USE_SRAM

; Definitions for Static RAM
SRAM.Start      EQU             (ROM.Start & ~SRAM.Mask) - SRAM.Size ; Just below ROM

SRAM.Size       EQU             32 * x86.1K.Size ; In bytes
SRAM.Mask       EQU             SRAM.Size - 1
SRAM.Speed      EQU             20               ; In nanoseconds
SRAM.Waits      EQU             0

;-------------------------------------------------------------------------------
                SEGMENT         SRAM  START=SRAM.Start  NOBITS

%assign         SRAM.Top        SRAM.Size
       
%endif
