;
; Exec/Boot.inc
;

; This routine copies ROM structures to RAM before using them.

                SEGMENT         Demo.Exec

                USE32

Demo.Exec.Boot:

; Copy and fill IDT to RAM
                XOR             EAX, EAX        ; Zeroes

                MOV             ECX, Demo.IDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.IDT.start
                MOV             EDI, Demo.IDT.Base
             CS REP             MOVSD

                MOV             ECX, (x86.IDT.Num.Max - Demo.IDT.Num) * x86.Desc.Size / x86.DWORD.Size
                LEA             ESI, [EDI - x86.Desc.Size] ; Copy final entry
             ES REP             MOVSD                      ; Repeatedly

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
                MOV             ECX, (x86.GDT.Num.Max - Demo.GDT.Num) * x86.Desc.Size / x86.DWORD.Size
                REP             STOSD

            O32 LGDT            [Demo.GDT.Base + Demo.GDT.Alloc.Pseudo]

; Copy and fill Exec.LDT to RAM
                MOV             CL,  Demo.Exec.LDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.Exec.LDT.start
                MOV             EDI, Demo.Exec.LDT.Base
             CS REP             MOVSD

                MOV             CL,  (Demo.Exec.LDT.Num.Max - Demo.Exec.LDT.Num) * x86.Desc.Size / x86.DWORD.Size
                REP             STOSD

; Jump to Executive Entry
                MOV             AX, x86.Selector(Demo.GDT.Exec.LDT, .GDT, .RPL0)
                LLDT            AX
                JMP             x86.Selector(Demo.Exec.LDT.Code, .LDT, .RPL0) : DWORD Demo.Exec.Entry
