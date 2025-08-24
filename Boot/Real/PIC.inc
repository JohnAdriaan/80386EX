;
; Boot/Real/PIC.inc
;

; The original IBM PC had one Priority Interrupt Controller (PIC) to allow up to
; eight individually controlled interrupts. The 80286 IBM AT added a cascaded
; PIC to IRQ 2 for eight more (less IRQ 2, so actually 7). They wired the old
; IRQ 2 to IRQ 9. All future PCs only had two PICs - until they invented the
; Advanced Priority Interrupt Controller (APIC), that could handle 256 interrupts.
; The original PIC was configured to avoid the 8086's 5 base interrupts, so
; the original BIOS starts IRQ 0 at Int 8. Intel has now reserved the first 32
; vectors for its own use, so we need to program  them appropriately.
; To program a PIC, you first give it the Init Cmd, then you program the Mask
; register a few times in a prescribed order. The details change depending on
; whether the PIC is a Master or a Slave.

; The PICs need to be based to keep them away from the Intel-reserved interrupts
Boot.PIC.A.Base EQU             20h
Boot.PIC.B.Base EQU             28h

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.PIC:
; But first, need to configure the ICU Configuration register
                MOV             DX, x86.EX.INT.CFG
                MOV             AL, x86.EX.INT.CFG.IR1   ; Enable video interrupt
                OUT             DX, AL

                MOV             AL, Dev.PIC.Cmd.Init     ; Initialise PICs
                OUT             Dev.PIC.A.Cmd, AL
                OUT             Dev.PIC.B.Cmd, AL

                MOV             AL, Boot.PIC.A.Base      ; Set PIC.A's Base
                OUT             Dev.PIC.A.Mask, AL
                MOV             AL, Boot.PIC.B.Base      ; Set PIC.B's Base
                OUT             Dev.PIC.B.Mask, AL

                MOV             AL, Dev.PIC.A.Cascade    ; Tell PIC.A where Slave is
                OUT             Dev.PIC.A.Mask, AL

                MOV             AL, Dev.PIC.B.Cascade    ; Tell PIC.B where it is Slave
                OUT             Dev.PIC.B.Mask, AL

                MOV             AL, Dev.PIC.Init.8086    ; 80x86 mode
                OUT             Dev.PIC.A.Mask, AL
                OUT             Dev.PIC.B.Mask, AL

                MOV             AL, ~Dev.PIC.A.Cascade   ; Allow Cascade interrupts through
                OUT             Dev.PIC.A.Mask, AL
                MOV             AL, 0FFh                 ; Mask all interrupts
                OUT             Dev.PIC.B.Mask, AL
