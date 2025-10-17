;
; Boot/Defn.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data   NOBITS

Boot.Stack.Top  EQU             Demo.GDT.Base

Boot.Text.Colour EQU            Dev.VGA.BlackBack | Dev.VGA.Grey
