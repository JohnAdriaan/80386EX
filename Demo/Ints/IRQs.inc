;
; Ints/IRQs.inc
;

; This file holds the entry points for all of the Interrupt ReQuests (IRQs).
; They all jump to the same handler, but not before saving away the number
; of the interrupt - oh, and a fault code since these should not happen!

Ints.IRQ0:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 0  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ1:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 1  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ2:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 2  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ3:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 3  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ4:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 4  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ5:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 5  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ6:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 6  ; Interrupt number
                JMP             Ints.PIC.A
Ints.IRQ7:
                PUSH            EAX     ; Check for spurious interrupt
                MOV             AL, Dev.PIC.Cmd.ISR
                OUT             Dev.PIC.A.Cmd, AL
                IN              AL, Dev.PIC.A.Cmd
                TEST            AL, Dev.PIC.Spurious
                JNZ             .NotSpurious
                PUSH            DS
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             DS, AX
                INC   BYTE      [WORD (Boot.PIC.A.Base + 7) * 2] ; Dingle(tm)
                POP             DS
                POP             EAX
                IRETD
.NotSpurious:
                POP             EAX
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.A.Base + 7  ; Interrupt number
;               JMP             Ints.PIC.A
; Acknowledge Master PIC
Ints.PIC.A:
                PUSH            EAX
                Dev.PIC.A.EOI
                POP             EAX
; All IRQs jump to the default Fault handler
                JMP             Ints.Fault

Ints.IRQ8:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 0  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ9:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 1  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ10:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 2  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ11:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 3  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ12:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 4  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ13:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 5  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ14:
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 6  ; Interrupt number
                JMP             Ints.PIC.B
Ints.IRQ15:
                PUSH            EAX     ; Check for spurious interrupt
                MOV             AL, Dev.PIC.Cmd.ISR
                OUT             Dev.PIC.B.Cmd, AL
                IN              AL, Dev.PIC.B.Cmd
                TEST            AL, Dev.PIC.Spurious
                JNZ             .NotSpurious
                MOV             AL, Dev.PIC.Cmd.EOI  ; Still need to Ack Master
                OUT             Dev.PIC.A.Cmd, AL
                PUSH            DS
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             DS, AX
                INC   BYTE      [WORD (Boot.PIC.B.Base + 7) * 2] ; Dingle(tm)
                POP             DS
                POP             EAX
                IRETD
.NotSpurious:
                POP             EAX
                PUSH   DWORD    0                    ; Pseudo-fault code
                PUSH   DWORD    Boot.PIC.B.Base + 7  ; Interrupt number
;               JMP             Ints.PIC.B
; Acknowledge Slave PIC first
Ints.PIC.B:
                PUSH            EAX
                Dev.PIC.B.EOI
                POP             EAX
; All IRQs jump to the default Fault handler
                JMP             Ints.Fault
