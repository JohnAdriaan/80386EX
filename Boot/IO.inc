;
; Boot/IO.inc
;
; The 80386EX Advanced Peripheral I/O space by default is disabled.
; Since we want to use some of them, it needs to be enabled with a sequence
; of accesses.

                SEGMENT         Boot.Code

                ALIGN           4

Boot.IO.Init:
                MOV             AX, x86.EX.RemapCFG.ESE ; Enable Expanded I/O
                OUT             x86.EX.RemapCFG+1, AL   ; Don't ask - see doc
                XCHG            AH, AL
                OUT             x86.EX.RemapCFG, AL     ; Stright from doc
                OUT             x86.EX.RemapCFG, AX     ; Supposedly done!

                Boot.Table.Next Boot.IO.Init
