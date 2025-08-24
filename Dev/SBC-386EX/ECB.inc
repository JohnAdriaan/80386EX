;
; Dev/SBC-386EX/ECB.inc
;

; The Euro Card Bus holds peripherals - but has its own Address Range and IO Range

ECB.Mem.Start   EQU             x86.EX.Addr.Size - (1024 * 1024)
ECB.Mem.Mask    EQU             ECB.Mem.Size - 1
%define         ECB.Mem.Bus     BS8

ECB.IO.Start    EQU             00E0h
ECB.IO.Mask     EQU             ECB.IO.Size - 1
%define         ECB.IO.Bus      BS8

;-------------------------------------------------------------------------------
                SEGMENT         ECB   START=ECB.Mem.Start  NOBITS

