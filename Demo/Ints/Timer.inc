;
; Ints/Timer.inc
;

; This module implements the Timer interrupt handler.
; It performs some housekeeping and then calls the generic Task Switching code -
; unless it interrupted CPL0 Code in the GDT: i.e. not User or Executive code.
; A perfect example: the double-buffer video copy code in the Vertical Refresh

%push           Ints.Timer      ; Don't leave these %defines lying around

Ints.Timer:

;                               Current + saved EAX  +  saved EIP
%define         .CS             ESP + x86.DWORD.Size + x86.DWORD.Size

                PUSH            EAX             ; Need this register
                PUSH            DS              ; And this one
MOV AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
MOV DS, AX
INC BYTE [WORD (Boot.PIC.A.Base + 0) * x86.WORD.Size]
                MOV             AX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             DS, AX
                ADD             [WORD Data.Ticks], DWORD Demo.Timer.Delta
                ADC             [WORD Data.Secs],  DWORD 0
                POP             DS              ; Not anymore

                Dev.PIC.A.EOI   ; Acknowledge interrupt in PIC (Note interrupts still off)

                TEST     WORD   [.CS], x86.Seg.LDT | x86.Seg.CPL
                JZ              .Exit           ; Don't switch from GDT CPL0 code!
                CALL            Ints.Switch     ; Switch Task
.Exit:
                POP             EAX
                IRETD                           ; And return where we left off

%pop
