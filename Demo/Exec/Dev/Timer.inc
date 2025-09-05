;
; Exec/Dev/Timer.inc
;

; This module installs a Timer interrupt handler, then sets the Programmable
; Interval Timer (PIT) to interrupt often. The Interrupt handler will cycle
; through the active Tasks, emulating simultaneity.

Exec.Dev.Timer:
; First, install a Timer interrupt handler
                MOV             EAX, Ints.Timer      ; Offset
                MOV             BX,  Demo.IDT.Timer  ; Interrupt
                MOV             CX,  x86.Selector(Demo.GDT.Ints, .GDT, .RPL0)
                MOV             DL,  x86.Type.Sys(.Int, .DPL0, .386)
                CALL            Exec.Alloc.IDT

; Then, reprogram the Programmable Interrupt Timer to the desired frequency
                MOV             AX, Demo.Timer.Div

                OUT             Dev.Timer.Port, AL ; Low byte
                MOV             AL, AH             ; High byte
                OUT             Dev.Timer.Port, AL

; Finally, enable the Timer interrupt in the PIC
                Dev.PIC.A.Enable  .Timer           ; Unmask Timer IRQ

                RET
