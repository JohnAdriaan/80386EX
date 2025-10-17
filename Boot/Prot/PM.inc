;
; Boot/Prot/PM.inc
;

                SEGMENT         Boot.Prot

                USE32           ; We're in Protected Mode: 32-bit is king!

Boot.Prot.Entry:
                MOV             AX, x86.Selector(Boot.GDT.Data - Boot.GDT, .GDT, .RPL0)
                MOV             DS, AX            ; Set DS to whole address space
                MOV             ES, AX            ; Set ES to whole address space
                MOV             FS, AX            ; Set FS to whole address space
                MOV             GS, AX            ; Set GS to whole address space
                MOV             SS, AX            ; Set SS to whole address space
                MOV             ESP, Boot.Stack.Top
