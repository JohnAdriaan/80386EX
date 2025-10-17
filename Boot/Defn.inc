;
; Boot/Defn.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data   NOBITS

Boot.Data.Base  EQU             Demo.IDT.Base + x86.IDT.Size.Max
Boot.Stack.Top  EQU             Demo.GDT.Base

Boot.Text.Colour EQU            Dev.VGA.BlackBack | Dev.VGA.Grey
