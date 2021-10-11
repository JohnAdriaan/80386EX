;
; Exec/Ints/Debug.inc
;

; This module installs a Debug handler
Exec.Ints.Debug:
                MOV             EAX, Ints.Debug
                MOV             BX,  Demo.IDT.Debug
                MOV             CX,  x86.Selector(Demo.GDT.Ints, .GDT, .RPL0) ; Note needs to RPL0
                MOV             DL,  x86.Type.Sys(.Trap, .DPL3, .386) & ~Demo.System.Present ; Allow User-mode Programs
                CALL            Exec.Alloc.IDT
                RET
