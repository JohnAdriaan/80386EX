;
; Boot.inc
;

; This routine copies ROM structures to RAM before using them.

                SEGMENT         Demo.Boot

                USE32

Demo.Boot:

; Copy and fill IDT to RAM
                XOR             EAX, EAX        ; Zeroes
                XOR             ECX, ECX        ; Can now load just CX (smaller)

                MOV             CX,  Demo.IDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.IDT.start
                MOV             EDI, Demo.IDT.Base
             CS REP             MOVSD

                MOV             CX,  (x86.IDT.Num.Max - Demo.IDT.Num) * x86.Desc.Size / x86.DWORD.Size
                LEA             ESI, [EDI - x86.Desc.Size] ; Copy final entry
                REP             MOVSD                      ; Repeatedly

                PUSH   DWORD    Demo.IDT.Base        ; Put on stack as Pseudo-descriptor
                PUSH    WORD    x86.IDT.Size.Max - 1 ; Only this many entries in IDT
            O32 LIDT            [ESP]
; We're about to abandon the stack, so don't bother fixing it up!

; Copy and fill GDT to RAM
                MOV             CL,  Demo.GDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.GDT.start
                MOV             EDI, Demo.GDT.Base
             CS REP             MOVSD

                ; Zero out the rest of the GDT
                MOV             CX,  (x86.GDT.Num.Max - Demo.GDT.Num) * x86.Desc.Size / x86.DWORD.Size
                REP             STOSD

            O32 LGDT            [Demo.GDT.Base + Demo.GDT.Alloc.Pseudo]

; Copy and fill Exec.LDT to RAM
                MOV             CL,  Demo.Exec.LDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.Exec.LDT.start
                MOV             EDI, Demo.Exec.LDT.Base
             CS REP             MOVSD

;               MOV             CL,  (Demo.Exec.LDT.Num.Max - Demo.Exec.LDT.Num) * x86.Desc.Size / x86.DWORD.Size
;               REP             STOSD           ; Gonna be overwritten immediately anyway...

%ifdef USE_SRAM
; Copy code to SRAM
                MOV             CX,  Copy.Size / x86.DWORD.Size
                MOV             ESI, Copy.Source
                MOV             EDI, Copy.Dest
             CS REP             MOVSD
%endif

; Jump to Executive Entry
                MOV             AX, x86.Selector(Demo.GDT.Exec.LDT, .GDT, .RPL0)
                LLDT            AX
                JMP             x86.Selector(Demo.Exec.LDT.Code, .LDT, .RPL0) : DWORD Demo.Exec.Entry

%if 0
.Forever:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

                MOV             AL, 42
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                JMP             .Forever
%endif
