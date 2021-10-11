;
; Ints/Timer.inc
;

; This module implements the Timer interrupt handler.
; It simply performs some housekeeping and then calls the generic Task
; Switching code.

Ints.Timer:
                PUSH            EAX             ; Need this register
PUSH DS
MOV AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
MOV DS, AX
INC BYTE [(Demo.IDT.Timer - Demo.IDT) / x86.Desc.Size * 2]
POP DS

                MOV             AL,Dev.PIC.Cmd.EOI ; Acknowledge interrupt in PIC
                OUT             Dev.PIC.A.Cmd,AL   ; (Note interrupts still off)

                CALL            Ints.Switch     ; Switch Task

                POP             EAX
                IRETD                           ; And return where we left off
