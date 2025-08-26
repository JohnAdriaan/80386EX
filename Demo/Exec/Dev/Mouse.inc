;
; Exec/Mouse.inc
;

; This module installs a Mouse interrupt handler. There's not much to do:
; the defaults as set by the Boot ROM are good enough.
; Of course, to be a true Device Driver, something needs to convert the movements
; sensed by the mouse into the X/Y coordinates and button presses for more
; general consumption by other programs. This has been left as an exercise for
; the reader - until I get impatient and do it myself...

Exec.Mouse:
; First, install a Mouse interrupt handler
                MOV             EAX, Ints.Mouse      ; Handler
                MOV             BX,  Demo.IDT.Mouse  ; Interrupt
                MOV             CX,  x86.Selector(Demo.GDT.Ints, .GDT, .RPL0)
                MOV             DL,  x86.Type.Sys(.Int, .DPL0, .386)
                CALL            Exec.Alloc.IDT

; Finally, enable the Mouse interrupt in the PIC
                Dev.PIC.B.Enable .Mouse            ; Unmask Mouse IRQ

                RET
