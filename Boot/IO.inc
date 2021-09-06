;
; Boot/IO.inc
;
; The 80386EX Advanced Peripheral I/O space by default is disabled.
; Since we want to use some of them, it needs to be enabled with a sequence
; of accesses.

                SEGMENT         Boot.Code

                ALIGN           4

Boot.IO.Init:
                IN              AL, x86.EX.RemapCFG+1   ; Reset to State A
                MOV             AX, x86.EX.RemapCFG.ESE ; Enable Expanded I/O
                OUT             x86.EX.RemapCFG+1, AL   ; Move to State B
                XCHG            AH, AL
                OUT             x86.EX.RemapCFG, AL     ; Move to State C
                OUT             x86.EX.RemapCFG, AX     ; State D. ESE set!

                Boot.Table.Next Boot.IO.Init
