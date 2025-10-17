;
; Dev/SBC-386EX/ECB.inc
;

; The Euro Card Bus holds peripherals - but has its own Address Range and IO Range
ECB.Mem.Start   EQU            (x86.EX.Addr.Size - ROM.Size - ECB.Mem.Size) & ~ECB.Mem.Mask
ECB.Mem.Size    EQU             x86.1M.Size     ; Only A0-A19 are connected to ECB
ECB.Mem.Mask    EQU             ECB.Mem.Size - 1
ECB.Mem.Speed   EQU             20
ECB.Mem.Waits   EQU             0
%define         ECB.Mem.Bus     BS8

ECB.IO.Start    EQU             00E0h
ECB.IO.Size     EQU             0020h
ECB.IO.Mask     EQU             ECB.IO.Size - 1
ECB.IO.Speed    EQU             40
ECB.IO.Waits    EQU             2
%define         ECB.IO.Bus      BS8

;-------------------------------------------------------------------------------
                SEGMENT         ECB   START=ECB.Mem.Start  NOBITS

